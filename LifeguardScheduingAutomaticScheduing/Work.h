#pragma once

#include "LSASGlobal.h"

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
		WorkTable() : m_table() {};
		~WorkTable() {};

		std::string toTemplate(void) const;
		static WorkTable fromTemplate(const std::string &buf);

		std::vector<PeriodWorkTable> &table(void);
		const std::vector<PeriodWorkTable> &table(void) const;

		PeriodWorkTable &tableOfType(const uint32 type);
		const PeriodWorkTable &tableOfType(const uint32 type) const;

		void generateWorkTable(void);
		void clearWorkTable(void);

	private:
		static void generatePeriodWorkTable(PeriodWorkTable &periodWork);

	private:
		std::vector<PeriodWorkTable> m_table;
	};
};
