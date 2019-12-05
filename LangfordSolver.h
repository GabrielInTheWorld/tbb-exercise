#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <thread>
#include <tbb/task.h>

#include "langford-vector.h"

using namespace tbb;

class LangfordSolver : public task {
public:
    LangfordSolver(LangfordVector* langford, unsigned long* sub);
    virtual ~LangfordSolver();

    task* execute();

private:
    LangfordVector* langford;
    unsigned long* subtasks;
    
};