#include "Work.h"
#include <thread>
#include <sstream>
#include "Work.h"

namespace LSAS
{
	std::string WorkTable::toTemplateBuf(void) const
	{
		std::ostringstream sout;

		sout << m_types.size() << std::endl;
		for (const std::string &type : m_types)
		{
			sout << type << std::endl;

			const PeriodWorkTable &table(m_tables[type].table);
			sout << table.size() << std::endl;

			for (const DailyWorkTable &dailyWorkTable : table)
			{
				sout << dailyWorkTable.size() << std::endl;
				
				for (const Work &work : dailyWorkTable)
				{
					sout << work.id() << ' ' << work.orderInDay() << ' ' << (work.activated() ? 1 : 0) << ' ' << work.needPeopleNum() << std::endl;
				}
			}
		}

		std::string &ret(sout.str());
		return std::move(ret);
	}

	std::shared_ptr<WorkTable> WorkTable::fromTemplateBuf(const std::string & buf)
	{
		return std::shared_ptr<WorkTable>();
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

	bool WorkTable::addType(const std::string &type, GeneratePeriodWorkTableProcess process /* = GeneratePeriodWorkTableProcesses::DefaultGeneratePeriodWorkTableProcess */)
	{
		if (existType(type))
		{
			return false;
		}

		m_types.insert(type);
		m_tables.insert(std::make_pair(type, Table({PeriodWorkTable(), process})));
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
