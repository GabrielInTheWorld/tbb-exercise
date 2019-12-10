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

LangfordSolver::LangfordSolver(Field* langford, int count, unsigned long* sub) {
    LangfordSolver::langford = langford;
    LangfordSolver::count = count;
    subtasks = sub;
}

LangfordSolver::~LangfordSolver() {

}

task* LangfordSolver::execute() {
    *subtasks = 0;

    int index = langford->nextFree();
    if ( index > -1 && langford->isFree(index + count + 1) ) {
        int size = langford->freeFields();
        unsigned long childTasks[7] = { 0 };
        int childs = 0;
        task_list list;

        langford->set(index, count);
        if ( count == 1 ) {
            // Ready!
            cout << "Ready!" << endl;
        } else {
            for ( int i = langford->nextFree(); i < langford->getSize(); ++i ) {
                Field* child = new Field(*langford);
                list.push_back(*new(allocate_child())LangfordSolver(child, count - 1, childTasks + childs));
                ++childs;
            }
            if ( childs > 0 ) {
                set_ref_count(childs + 1);
                spawn_and_wait_for_all(list);
                for ( int i = 0; i < 7; ++i ) {
                    *subtasks += childTasks[i];
                }
                *subtasks += childs;
            }
        }
    }

    //for (int i = 0; i <  )
    //if ( langford->isFree()
    return NULL;
}
