#include "langford.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Langford::Langford() {
    cout << "Run langford" << endl;
    setNumberOfColors(3);
    solve();
}

Langford::Langford(int n) {
    setNumberOfColors(3);
}

void Langford::setNumberOfColors(int n) {
    numberOfColors = n;
}

bool Langford::isFieldFull(bitset<6>& field) {
    for ( int i = 0; i < field.size(); ++i ) {
        if ( field[i] == 0 ) {
            return false;
        }
    }
    return true;
}

bool Langford::isFree(int index, bitset<6> &field) {
    cout << "isFree? " << index << endl;
    return index < field.size() && field[index] == 0;
}

bool Langford::set(int index, int count, bitset<6> &field) {
    if ( index >= field.size() ) return false;
    field[index] = 1;
    field[index + count + 1] = 1;
    return true;
}

int Langford::solveHelper(int index, int count, std::bitset<6> &field) {
    cout << "Run helper: " << field << endl;
    cout << "count: " << count << endl;
    /*if ( count == 0 ) {
        std::cout << "Ready" << std::endl;
        return isFieldFull(field) ? 1 : 0;
    }*/
    if ( isFree(index, field) && isFree(index + count + 1, field) ) {
            cout << "Next " << field << endl;
        set(index, count, field);
        cout << "Field: " << field << endl;
        cout << "Count after set: " << count << endl;
        if ( count == 1 ) {
            std::cout << "Ready" << std::endl;
            if ( isFieldFull(field) ) {
                ++solutions;
            }
            return isFieldFull(field) ? 1 : 0;
        }
        for ( int i = 0; i < field.size() - count; ++i ) {
            solveHelper(i, count - 1, field);
        }
    } else {
        return 0;
    }

}

void Langford::solve() {
    int range = field.size() / numberOfColors;
    cout << "Run solve: " << field.size() << " + numberOfColors: " << numberOfColors << " + Range: " << range << endl;
    for ( int i = 0; i < field.size() / numberOfColors; ++i ) {
        auto tmp = field;
        solveHelper(i, numberOfColors, tmp);
        /*if ( solveHelper(i, i + numberOfColors) == true ) {
            ++solutions;
        }*/
    }
    solutions /= 2;
    cout << "Solutions: " << solutions << endl;
}