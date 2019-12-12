#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <bitset>

#include <tbb/parallel_for.h>

using namespace std;
using namespace tbb;

class Field {
public:
    Field();
    Field(int number);
    Field(Field* field);
    Field(Field& field);
    int nextFree();
    int nextFree(int n);
    int getSize();
    int freeFields();
    bool isFree(int index);
    void set(int index, int count);
    void printField();

private:
    vector<bool> field;
    int number;

    void setNumber(int n);
};

