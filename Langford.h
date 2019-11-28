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

using namespace tbb;

class Langford : public task {
public:
    Langford();
    virtual ~Langford();

    //task* execute();

private:
    unsigned long* subtasks;

};