#pragma once

#include "LSASGlobal.h"
#include <memory>
#include <map>

namespace LSAS
{
	class Work
	{
	public:
		Work(const uint32 id, const uint8 orderInDay);
		Work(const uint32 id, const uint8 orderInDay, const uint8 needPeopleNum);

		const uint32 id(void) const;
		const uint8 orderInDay(void) const;
		const bool activated(void) const;

		const uint8 needPeopleNum(void) const;
		const uint8 stillNeedPeopleNum(void) const;

		const std::set<std::reference_wrapper<Worker>> &getWantedWorkers(void) const;
		void setWantedWorkders(const std::set<std::reference_wrapper<Worker>> &wantedWorkers);
		
		const std::set<std::reference_wrapper<Worker>> &getSelectedWorkers(void) const;
		bool hasSelected(const std::reference_wrapper<Worker> &worker);
		void addSelectedWorkers(const std::set<std::reference_wrapper<Worker>> &workers);

		std::set<std::reference_wrapper<Worker>> getWantedBunNotSelectedWorkers(void) const;
		void clearSelectedWorkers(void);

	private:
		uint32 m_id;
		uint8 m_orderInDay;		// 在一天中的序号
		bool m_activated;
		uint8 m_needPeopleNum;

		std::set<std::reference_wrapper<Worker>> m_wantedWorkers;
		std::set<std::reference_wrapper<Worker>> m_selectedWorker;
	};

	class WorkTable
	{
	public:
		WorkTable() : m_types(), m_tables() {};
		~WorkTable() {};

		std::string toTemplateBuf(void) const;
		static std::shared_ptr<WorkTable> fromTemplateBuf(const std::string &buf);

		std::map<std::string, PeriodWorkTable> &tables(void);
		const std::map<std::string, PeriodWorkTable> &tables(void) const;

		const std::set<std::string> &types(void) const;

		std::map<std::string, PeriodWorkTable>::iterator findType(const std::string &type);
		std::map<std::string, PeriodWorkTable>::const_iterator findType(const std::string &type) const;
		bool existType(const std::string &type) const;
		bool addType(const std::string &type);
		bool removeType(const std::string &type);

		PeriodWorkTable &tableOfType(const std::string type);
		const PeriodWorkTable &tableOfType(const std::string type) const;

		void generateWorkTable(void);
		void clearWorkTable(void);

	private:
		static void generatePeriodWorkTableProcess(PeriodWorkTable *periodWork);

	private:
		std::set<std::string> m_types;
		std::map<std::string, PeriodWorkTable> m_tables;
	};
};
