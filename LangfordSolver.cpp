#include "LangfordSolver.h"

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

LangfordSolver::LangfordSolver(LangfordVector* langford, unsigned long* sub) {
    LangfordSolver::langford = langford;
    subtasks = sub;
}

LangfordSolver::~LangfordSolver() {

}

task* LangfordSolver::execute() {
    *subtasks = 0;

    //for (int i = 0; i <  )
    //if ( langford->isFree()
    return NULL;
}
