#include "Langford.h"

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

//class Langford : public tbb::task {
//public: 
//    Langford() {
//
//    }
//};
Langford::Langford() {
    Langford::subtasks = 0;
}

Langford::~Langford() {

}

//Langford::execute() {
//    return 0;
//}
