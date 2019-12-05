#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

class LangfordVector {
public: 
    LangfordVector();
    LangfordVector(int n);

private:
    int solutions = 0;
    int numberOfColors = 3;
    vector<bool> field;

    void printField(vector<bool>& field);
    void setNumberOfColors(int n);
    bool isFree(int index, vector<bool>& field);
    bool set(int index, int count, vector<bool>& field);
    bool isFieldFull(vector<bool>& field);
    int findNextPosition(vector<bool>& field);
    int findNextPosition(int startPosition, vector<bool>& field);

    int solveHelper(int count, vector<bool>& field);
    int solveHelper(int index, int count, vector<bool>& field);
    void solve();
};

