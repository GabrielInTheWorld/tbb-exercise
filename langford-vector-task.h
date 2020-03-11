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

class LangfordVectorTask : public task {
public:
    LangfordVectorTask(int count, int* solutions);
    LangfordVectorTask(vector<bool>& field, int count, int* solutions);

    task* execute();

private:
    vector<bool> langford;
    int* solutions;
    int count;
    int position;
    int length;
    int pointFree = 0;
    int pointTmp = 0;

    int nextFree(int startAt);
    bool isFree(int index, int count);
    bool setNext(int index, int count);
    vector<bool> copyVector(vector<bool> v);
    void printVector(vector<bool>& v);
};

