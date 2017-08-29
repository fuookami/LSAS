#include "Work.h"
#include <algorithm>

namespace LSAS
{
	namespace GeneratePeriodWorkTableProcesses
	{
		const GeneratePeriodWorkTableProcess getProcess(const Processes processId)
		{
			return std::find_if(ProcessMap.begin(), ProcessMap.end(),
				[processId](const std::pair<Processes, GeneratePeriodWorkTableProcess> &pair) -> bool
			{
				return pair.first == processId;
			}) -> second;
		}

		void processFullFirst(PeriodWorkTable & periodWork)
		{

		}
	};
};
