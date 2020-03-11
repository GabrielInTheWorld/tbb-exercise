#include "LangfordSolver.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <cstdio>
//#include <ctime>
//#include <iostream>
//#include <vector>
//
//#include <tbb/tbb.h>
//#include <tbb/blocked_range.h>
//#include <tbb/parallel_for.h>
//#include <thread>
//#include <tbb/task.h>

LangfordSolver::LangfordSolver(int numberOfColors, int position, int* solutions): count(numberOfColors), position(position), solutions(solutions) {
    langford = new Field(numberOfColors);
}

LangfordSolver::LangfordSolver(Field* langford, int count, int position, int* sub): langford(langford), count(count), position(position), solutions(sub) {
}

LangfordSolver::~LangfordSolver() {
    delete langford;
}

task* LangfordSolver::execute() {
    int index = position;
    langford->set(index, count);
    if ( count == 1 ) {
        *solutions += 1;
        return NULL;
    }
    int childs = 0;
    task_list list;

    /*auto callback = [&](int index) {
        if ( langford->isFree(index) && langford->isFree(index + count) ) {
            Field* child = new Field(*langford);
            list.push_back(*new(allocate_child())LangfordSolver(child, count - 1, index, solutions));
            ++childs;
        }
    };
    parallel_for(langford->nextFree(), langford->getSize() - count, callback);*/
    for ( int i = langford->nextFree(); i < langford->getSize() - count; ++i ) {
        if ( langford->isFree(i) && langford->isFree(i + count) ) {
            Field* child = new Field(*langford);
            list.push_back(*new(allocate_child())LangfordSolver(child, count - 1, i, solutions));
            ++childs;
        }
    }

    if ( childs > 0 ) {
        set_ref_count(childs + 1);
        spawn_and_wait_for_all(list);
    }
    return NULL;
}
