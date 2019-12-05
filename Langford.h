#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>

using namespace std;

//const int N = 3;

class Langford {

public:
    Langford();
    Langford(int n);
    //virtual ~Langford();

private:
    int solutions = 0;
    int numberOfColors = 3;
    std::bitset<6> field;

    void setNumberOfColors(int n);
    bool isFree(int index, std::bitset<6> &field);
    bool set(int index, int count, std::bitset<6> &field);
    bool isFieldFull(bitset<6>& field);
    int solveHelper(int index, int count, std::bitset<6> &field);
    void solve();
};

