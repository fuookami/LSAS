#include "Work.h"
#include "Worker.h"
#include <algorithm>

namespace LSAS
{
	Work::Work(const std::string buf)
		: m_id((static_cast<uint32>(buf[0]) << 24)
			| (static_cast<uint32>(buf[1]) << 16)
			| (static_cast<uint32>(buf[2]) << 8)
			| (static_cast<uint32>(buf[3]))),
		m_orderInDay(static_cast<uint8>(buf[4])), 
		m_activated(static_cast<uint8>(buf[5]) == 1),
		m_needPeopleNum(static_cast<uint8>(buf[6]))
	{
	}

	Work::Work(const uint32 id, const uint8 orderInDay)
		: m_id(id), m_orderInDay(orderInDay), m_activated(false), m_needPeopleNum(0)
	{
	}

	Work::Work(const uint32 id, const uint8 orderInDay, const uint8 needPeopleNum)
		: m_id(id), m_orderInDay(orderInDay), m_activated(true), m_needPeopleNum(needPeopleNum)
	{
	}

	const uint32 Work::id(void) const
	{
		return m_id;
	}

	const uint8 Work::orderInDay(void) const
	{
		return m_needPeopleNum;
	}

	const bool Work::activated(void) const
	{
		return m_activated;
	}

	const uint8 Work::needPeopleNum(void) const
	{
		return m_needPeopleNum;
	}

	const uint8 Work::stillNeedPeopleNum(void) const
	{
		return m_needPeopleNum - m_selectedWorker.size();
	}

	const std::set<std::reference_wrapper<Worker>> &Work::getWantedWorkers(void) const
	{
		return m_wantedWorkers;
	}

	void Work::setWantedWorkders(const std::set<std::reference_wrapper<Worker>> &wantedWorkers)
	{
		m_wantedWorkers = std::move(wantedWorkers);
	}

	const std::set<std::reference_wrapper<Worker>>& Work::getSelectedWorkers(void) const
	{
		return m_selectedWorker;
	}

	bool Work::hasSelected(const std::reference_wrapper<Worker>& worker)
	{
		return m_selectedWorker.find(worker) != m_selectedWorker.cend();
	}

	void Work::addSelectedWorkers(const std::set<std::reference_wrapper<Worker>>& workers)
	{
		for (const std::reference_wrapper<Worker> &worker : workers)
		{
			worker.get().addAllocatedWork(*this);

			if (m_wantedWorkers.find(worker) == m_wantedWorkers.cend())
			{
				throw std::runtime_error("Unwanted worker has been selected.");
			}
			m_selectedWorker.insert(worker);
		}
	}

	std::set<std::reference_wrapper<Worker>> Work::getWantedBunNotSelectedWorkers(void) const
	{
		std::set<std::reference_wrapper<Worker>> ret;
		std::set_difference(m_wantedWorkers.cbegin(), m_wantedWorkers.cend(),
			m_selectedWorker.cbegin(), m_selectedWorker.cend(),
			std::back_inserter(ret));
		return ret;
	}

	void Work::clearSelectedWorkers(void)
	{
		m_selectedWorker.clear();
	}

	const std::string Work::toBuf(void) const
	{
		std::string ret;
		ret.resize(7);

		ret[0] = static_cast<uint8>((m_id >> 24) & 0x000000ff);
		ret[1] = static_cast<uint8>((m_id >> 16) & 0x000000ff);
		ret[2] = static_cast<uint8>((m_id >> 8) & 0x000000ff);
		ret[3] = static_cast<uint8>(m_id & 0x000000ff);
		ret[4] = m_orderInDay;
		ret[5] = m_activated ? 1 : 0;
		ret[6] = m_needPeopleNum;

		return ret;
	}
};
