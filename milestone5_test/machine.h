#progma once

#include <queue>

#include "t.h"
#include "job.h"

class Machine : public Task {
	int inComing;
	std::queue< Job > inputQ;
	
	bool bInstaller;
	bool bRemover;
	
public:
	Machine()
		: inComing(0)
	{
		
	}
	
}