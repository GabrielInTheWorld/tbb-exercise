#include "field.h"

Field::Field() {
    setNumber(3);
}

Field::Field(int n) {
    setNumber(n);
}

Field::Field(Field* field) {
    Field::field = field->field;
    number = field->number;
}

Field::Field(Field& field) {
    Field::field = field.field;
    number = field.number;
}

void Field::setNumber(int n) {
    number = n;
    field = vector<bool>(n*2, 0);
}

int Field::nextFree() {
    /*for ( int i = 0; i < field.size(); ++i ) {
        if ( field[i] == false ) {
            return i;
        }
    }
    return -1;*/
    return nextFree(0);
}

int Field::nextFree(int startAt) {
    for ( int i = startAt; i < field.size(); ++i ) {
        if ( field[i] == false ) {
            return i;
        }
    }
    return -1;
}

int Field::getSize() {
    return field.size();
}

int Field::freeFields() {
    int size = 0;
    for ( int i = 0; i < field.size(); ++i ) {
        size += field[i] == 0 ? 1 : 0;
    }
    return size;
}

bool Field::isFree(int index) {
    return field[index] == 0;
}

void Field::set(int index, int count) {
    cout << "Set: " << index << " with count: " << count << endl;
    field[index] = 1;
    field[index + count + 1] = 1;
}

void Field::printField() {
    cout << "Field: ";
    for ( int i = 0; i < field.size(); ++i ) {
        cout << field[i];
    }
    cout << endl;
}