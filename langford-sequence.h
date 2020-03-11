#pragma once

#include <tbb/parallel_for.h>
#include <tbb/task.h>

#include "field.h"

class LangfordSequence : public task {
public:
    LangfordSequence(int numberOfColors, int* solutions);
    LangfordSequence(Field &field, int count, int* solutions);
    task* execute();
private:
    int firstIndex = 0;
    int secondIndex = 0;
    int count = 0;
    int* solutions;
    Field langford;

    void initialize();
    bool check();
};

