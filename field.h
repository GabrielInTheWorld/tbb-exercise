#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
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
    bool setFree(int index, int count);
    void printField();
    void printList();

private:
    vector<bool> field;
    list<int> freePositions;
    int number;

    void setNumber(int n);
    void initList(int n);
    void deleteElementInList(int index);
    list<int>::iterator findElementInList(list<int>::iterator begin, list<int>::iterator end, int value);
};

