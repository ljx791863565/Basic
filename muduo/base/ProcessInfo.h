#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include "Stringpiece.h"
#include "Types.h"
#include "Timestamp.h"

#include <vector>
#include <sys/types.h>

namespace muduo {
namespace ProcessInfo {
	pid_t pid();
	string pidString();
	uid_t uid();
	string username();
	uid_t euid();
	Timesramp startTime();
	int clockTicksPerSecond();
	int pageSize();
	bool isDebugBuild();

	string hostname();
	string procname();
	StringPiece procname(const string &stat);

	string procStatus();
	string procStat();
	string threadStat();
	string exePath();
	
	int openedFiles();
	int maxOpenFiles();
	struct CpuTime
	{
		double userSeconds;
		double systemSeconds;
		CpuTime()
			:userSeconds(0.0), systemSeconds(0.0)
		{}

		double total() const
		{
			return userSeconds + systemSeconds;
		}
	};

	CpuTime cpuTime();
	int numThreads();
	std::vector<pid_t> thread();
} /* namespace ProcessInfo */
} /* namespace muduo */
#endif /* end of :PROCESS_INFO_H */
