#pragma once

#include "LSASGlobal.h"

namespace LSAS
{
	class Worker
	{
	public:
		Worker(const std::string &name, const std::string &code, const uint32 type);
		~Worker();

		const uint32 id(void) const;
		const std::string &name(void) const;
		const std::string &code(void) const;
		const uint32 &type(void) const;

		const std::vector<std::reference_wrapper<Work>> &wantedWork(void) const;
		void setWantedWork(const std::vector<std::reference_wrapper<Work>> &newWantedWork);
		const uint32 wantedWorkNum(void) const;

		const std::vector<std::reference_wrapper<Work>> &allocatedWork(void) const;
		void addAllocatedWork(const std::reference_wrapper<Work> &newAllcatedWork);
		const uint32 allocatedWorkNum(void) const;

	private:
		static uint32 generateId(void);

	private:
		uint32 m_id;
		std::string m_name;
		std::string m_code;
		uint32 m_type;

		std::set<std::reference_wrapper<Work>> m_wantedWork;
		std::set<std::reference_wrapper<Work>> m_allocatedWork;
	};
};
