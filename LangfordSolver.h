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
    LangfordSolver(int numberOfColors, int position, int* solutions);
    LangfordSolver(Field* langford, int count, int position, int* solutions);
    virtual ~LangfordSolver();

    task* execute();

private:
    Field* langford;
    int* solutions;
    int count;
    int position;
};