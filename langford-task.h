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

class LangfordTask : public task {
public:
    LangfordTask(int count, int startPosition, int *solutions);
    LangfordTask(Field& langford, int count, int position, int *solutions);

    task* execute();
private:
    Field langford;
    int *solutions = 0;
    int count;
    int position;

    void init(int count);
    void print(string message);
};

