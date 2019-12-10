#pragma once
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
#include <tbb/task_group.h>

#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <thread>
#include <tbb/task.h>

#include "field.h"
#include "LangfordSolver.h"

using namespace tbb;

class LangfordSolverRunner {
public:
    LangfordSolverRunner();
    LangfordSolverRunner(int n);
    ~LangfordSolverRunner();

    void run();

private:
    Field* f;
    int number;
    task_group list;

    void init(int n);
};

