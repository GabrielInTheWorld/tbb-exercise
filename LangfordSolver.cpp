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
    //count = numberOfColors;
    //LangfordSolver::solutions = solutions;
}

LangfordSolver::LangfordSolver(Field* langford, int count, int position, int* sub): langford(langford), count(count), position(position), solutions(sub) {
    /*LangfordSolver::langford = langford;
    LangfordSolver::count = count;
    LangfordSolver::position = position;
    solutions = sub;*/
}

LangfordSolver::~LangfordSolver() {
    delete langford;
}

task* LangfordSolver::execute() {
    //*subtasks = 0;

    //cout << "Count: " << count << endl;
    int index = position;
    //if ( langford->isFree(index + count + 1) ) {
        //int size = langford->freeFields();
        //unsigned long childTasks[7] = { 0 };
        langford->set(index, count);
        if ( count == 1 ) {
            // Ready!
            //cout << "Ready!" << endl;
            *solutions += 1;
            return NULL;
        }
        int childs = 0;
        task_list list;

        //} else {

        /*for ( int i = langford->nextFree(); i < langford->getSize() - count && i > -1; i = langford->nextFree(i+1) ) {
            Field* child = new Field(*langford);
            list.push_back(*new(allocate_child())LangfordSolver(child, count - 1, i, solutions));
            ++childs;
        }*/

        auto callback = [&](int index) {
            if ( langford->isFree(index) && langford->isFree(index + count) ) {
                Field* child = new Field(*langford);
                list.push_back(*new(allocate_child())LangfordSolver(child, count - 1, index, solutions));
                ++childs;
            }
        };
        parallel_for(langford->nextFree(), langford->getSize() - count, callback);

        if ( childs > 0 ) {
            set_ref_count(childs + 1);
            spawn_and_wait_for_all(list);
            /*for ( int i = 0; i < 7; ++i ) {
                *subtasks += childTasks[i];
            }
            *subtasks += childs;*/
        }
        //}
    //}

    //for (int i = 0; i <  )
    //if ( langford->isFree()
    return NULL;
}
