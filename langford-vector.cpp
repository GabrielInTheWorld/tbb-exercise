#include "langford-vector.h"

LangfordVector::LangfordVector() {
    cout << "Langford with vector<bool>" << endl;
    setNumberOfColors(3);
}

LangfordVector::LangfordVector(int n) {
    setNumberOfColors(n);
}

void LangfordVector::printField(vector<bool>& field) {
    string out = "";
    for ( int i = 0; i < field.size(); ++i ) {
        out += field.at(i) ? 1 : 0;
    }
    cout << "Field: " << out << endl;
}

void LangfordVector::setNumberOfColors(int n) {
    numberOfColors = n;
    field = vector<bool>(n*2, 0);
    solve();
}

int LangfordVector::findNextPosition(vector<bool>& field) {
    /*int index = -1;
    for ( int i = 0; i < field.size(); ++i ) {
        if ( field[i] == false ) {
            index = i;
            return i;
        }
    }
    return index;*/
    return findNextPosition(0, field);
}

int LangfordVector::findNextPosition(int startPosition, vector<bool>& field) {
    int index = -1;
    for ( int i = startPosition; i < field.size(); ++i ) {
        if ( field[i] == false ) {
            index = i;
            return i;
        }
    }
    return index;
}

bool LangfordVector::isFieldFull(vector<bool>& field) {
    for ( int i = 0; i < field.size(); ++i ) {
        if ( field[i] == 0 ) {
            return false;
        }
    }
    return true;
}

bool LangfordVector::isFree(int index, vector<bool>& field) {
    //cout << "isFree? " << index << endl;
    return index < field.size() && field[index] == 0;
}

bool LangfordVector::set(int index, int count, vector<bool>& field) {
    if ( index >= field.size() ) return false;
    field[index] = 1;
    field[index + count + 1] = 1;
    return true;
}

int LangfordVector::solveHelper(int count, vector<bool>& field) {
    //printField(field);
    int index = findNextPosition(field);
    //cout << "Index: " << index << " Count: " << count << endl;
    if ( index > -1 && isFree(index + count + 1, field) ) {
        set(index, count, field);
        if ( count == 1 ) {
            //cout << "Ready" << endl;
            if ( isFieldFull(field) ) {
                ++solutions;
            }
        } else {
            solveHelper(count - 1, field);
        }
    //} else {

    }
    return 0;
}

int LangfordVector::solveHelper(int index, int count, vector<bool>& field) {
    //cout << "Run helper: " << index << ": " << count << endl;
    //printField(field);
    //cout << "count: " << count << endl;
    /*if ( count == 0 ) {
        std::cout << "Ready" << std::endl;
        return isFieldFull(field) ? 1 : 0;
    }*/
    if ( isFree(index, field) && isFree(index + count + 1, field) ) {
        //cout << "Next " << field << endl;
        set(index, count, field);
        //cout << "Field: " << field << endl;
        //cout << "Count after set: " << count << endl;
        if ( count == 1 ) {
            //std::cout << "Ready" << std::endl;
            if ( isFieldFull(field) ) {
                ++solutions;
            }
            return isFieldFull(field) ? 1 : 0;
        }
        for ( int i = findNextPosition(field); i < field.size() - count; ++i ) {
            auto tmp = field;
            solveHelper(i, count - 1, tmp);
        }
    } else {
        return 0;
    }

}

void LangfordVector::solve() {
    int range = field.size() / numberOfColors;
    //cout << "Run solve: " << field.size() << " + numberOfColors: " << numberOfColors << " + Range: " << range << endl;
    for ( int i = 0; i < field.size() - numberOfColors; ++i ) {
        auto tmp = field;
        solveHelper(i, numberOfColors, tmp);
        //solveHelper(numberOfColors, tmp);

        /*if ( solveHelper(i, i + numberOfColors) == true ) {
            ++solutions;
        }*/
    }
    cout << "Solutions all: " << solutions << endl;
    solutions /= 2;
    cout << "Solutions: " << solutions << endl;
}
