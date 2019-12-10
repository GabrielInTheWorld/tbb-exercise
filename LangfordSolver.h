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

#include "langford-vector.h"
#include "field.h"

using namespace tbb;
using namespace std;

class LangfordSolver: public task {
public:
    LangfordSolver(Field* langford, int count, unsigned long* sub);
    virtual ~LangfordSolver();

    task* execute();

private:
    Field* langford;
    unsigned long* subtasks = 0;
    int count;
};