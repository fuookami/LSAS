#include "Work.h"

namespace LSAS
{
	const std::set<std::string>& WorkTable::types(void) const
	{
		return m_types;
	}

	std::map<std::string, PeriodWorkTable>::iterator WorkTable::findType(const std::string & type)
	{
		return m_tables.find(type);
	}

	std::map<std::string, PeriodWorkTable>::const_iterator WorkTable::findType(const std::string & type) const
	{
		return m_tables.find(type);
	}

	bool WorkTable::existType(const std::string & type) const
	{
		return m_types.find(type) != m_types.cend();
	}

	bool WorkTable::addType(const std::string &type)
	{
		if (existType(type))
		{
			return false;
		}

		m_types.insert(type);
		m_tables.insert(std::make_pair(type, PeriodWorkTable()));
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
		return findType(type)->second;
	}

	const PeriodWorkTable & WorkTable::tableOfType(const std::string type) const
	{
		return findType(type)->second;
	}

	void WorkTable::generateWorkTable(void)
	{
		std::vector<std::thread> threads;

		for (auto &tablePair : m_tables)
		{
			
		}

		for (auto &thread : threads)
		{
			thread.join();
		}
	}
};
