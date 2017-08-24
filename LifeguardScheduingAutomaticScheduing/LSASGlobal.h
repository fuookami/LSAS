#pragma once

#include <vector>
#include <set>
#include <memory>
#include <functional>

namespace LSAS
{
	using int8 = char;
	using uint8 = unsigned char;
	using byte = unsigned char;
	using int16 = short;
	using uint16 = unsigned short;
	using int32 = int;
	using uint32 = unsigned int;
	using int64 = long;
	using uint64 = unsigned long;

	class Work;
	using DailyWorkTable = std::vector<Work>;
	using PeriodWorkTable = std::vector<DailyWorkTable>;
	class WorkTable;

	using GeneratePeriodWorkTableProcess = std::function<void (PeriodWorkTable &)>;

	class Worker;
	using WorkerSet = std::set<std::shared_ptr<Worker>>;
	using WorkerTypeMap = std::vector<std::string>;
};
