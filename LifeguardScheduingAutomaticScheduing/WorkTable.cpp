#include "Work.h"
#include <thread>
#include <sstream>
#include "Work.h"

namespace LSAS
{
	WorkTable::Table::Table(const GeneratePeriodWorkTableProcesses::Processes _processId)
		: table(), processId(_processId), process(GeneratePeriodWorkTableProcesses::getProcess(_processId)), score(0xffffffff)
	{
	}

	WorkTable::Table::Table(const PeriodWorkTable && _table, const GeneratePeriodWorkTableProcesses::Processes _processId)
		: table(std::move(_table)), processId(_processId), process(GeneratePeriodWorkTableProcesses::getProcess(_processId)), score(0xffffffff)
	{
	}

	std::string WorkTable::toTemplateBuf(void) const
	{
		std::ostringstream sout;

		sout << m_types.size() << std::endl;
		for (const std::string &type : m_types)
		{
			sout << type << std::endl;

			const Table &table(m_tables.find(type)->second);
			const PeriodWorkTable &periodWorkTable(table.table);
			sout << periodWorkTable.size() << ' ' << table.processId << std::endl;

			for (const DailyWorkTable &dailyWorkTable : periodWorkTable)
			{
				sout << dailyWorkTable.size() << std::endl;
				
				for (const Work &work : dailyWorkTable)
				{
					sout << work.toBuf() << std::endl;;
				}
			}
		}

		std::string &ret(sout.str());
		return std::move(ret);
	}

	std::shared_ptr<WorkTable> WorkTable::fromTemplateBuf(const std::string & buf)
	{
		std::shared_ptr<WorkTable> ret(new WorkTable());
		std::istringstream sin(buf);

		uint32 typeSize(0);
		sin >> typeSize;
		for (uint32 i(0); i != typeSize; ++i)
		{
			std::string type;
			getline(sin, type);
			
			uint32 periodWorkTableSize(0), processId(0);
			sin >> periodWorkTableSize >> processId;

			ret->addType(type, GeneratePeriodWorkTableProcesses::Processes(processId));
			PeriodWorkTable &table(ret->tableOfType(type));
			table.resize(periodWorkTableSize);

			for (uint32 j(0); j != periodWorkTableSize; ++j)
			{
				uint32 dailyWorkTableSize(0);
				sin >> dailyWorkTableSize;

				DailyWorkTable dailyWorkTable;
				dailyWorkTable.resize(dailyWorkTableSize);

				for (uint32 k(0); k != dailyWorkTableSize; ++k)
				{
					std::string buf;
					getline(sin, buf);

					dailyWorkTable.push_back(Work(buf));
				}

				table.push_back(std::move(dailyWorkTable));
			}
		}

		return ret;
	}

	const std::set<std::string>& WorkTable::types(void) const
	{
		return m_types;
	}

	std::map<std::string, WorkTable::Table>::iterator WorkTable::findType(const std::string & type)
	{
		return m_tables.find(type);
	}

	std::map<std::string, WorkTable::Table>::const_iterator WorkTable::findType(const std::string & type) const
	{
		return m_tables.find(type);
	}

	bool WorkTable::existType(const std::string & type) const
	{
		return m_types.find(type) != m_types.cend();
	}

	bool WorkTable::addType(const std::string & type, GeneratePeriodWorkTableProcesses::Processes processId)
	{
		if (existType(type))
		{
			return false;
		}

		m_types.insert(type);
		m_tables.insert(std::make_pair(type, Table()));
		return true;
	}

	bool WorkTable::removeType(const std::string & type)
	{
		auto it(findType(type));
		if (it != m_tables.end())
		{
			return false;
		}

		m_types.insert(type);
		m_tables.erase(it);
		return true;
	}

	PeriodWorkTable & WorkTable::tableOfType(const std::string type)
	{
		return findType(type)->second.table;
	}

	const PeriodWorkTable & WorkTable::tableOfType(const std::string type) const
	{
		return findType(type)->second.table;
	}

	void WorkTable::generateWorkTable(void)
	{
		static auto process(
			[](Table *table) 
		{
			for (auto &dailyWorkTable : table->table)
			{
				for (auto &work : dailyWorkTable)
				{
					work.clearSelectedWorkers();
				}
			}

			table->process(table->table);
			table->score = calScore(table->table);
		});

		std::vector<std::thread> threads;

		for (auto &tablePair : m_tables)
		{
			threads.push_back(std::thread(process, &tablePair));
		}

		for (auto &thread : threads)
		{
			thread.join();
		}
	}

	void WorkTable::clearWorkTable(void)
	{
		for (auto &tablePair : m_tables)
		{
			for (auto &dailyWorkTable : tablePair.second.table)
			{
				for (auto &work : dailyWorkTable)
				{
					work.clearSelectedWorkers();
				}
			}
		}
	}
	uint32 WorkTable::calScore(const PeriodWorkTable & table)
	{
		uint32 ret(0);
		for (const DailyWorkTable &dailyWorkTable : table)
		{
			for (const Work &work : dailyWorkTable)
			{
				ret += work.stillNeedPeopleNum();
			}
		}
		return ret;
	}
};
