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
    //freePositions = field->freePositions;
    //printList();
}

Field::Field(Field& field) {
    Field::field = field.field;
    number = field.number;
    //freePositions = field.freePositions;
    //printList();
}

void Field::setNumber(int n) {
    number = n;
    field = vector<bool>(n * 2, 0);
    //initList(n);
    //printList();
}

void Field::initList(int n) {
    for ( int i = 0; i < n * 2; ++i ) {
        freePositions.insert(freePositions.end(), i);
    }
}

int Field::nextFree() {
    return nextFree(0);
}

int Field::nextFree(int startAt) {
    for ( int i = startAt; i < field.size(); ++i ) {
        if ( field[i] == 0 ) {
            return i;
        }
    }
    return -1;
    /*cout << "Before finding: " << startAt << endl;
    if ( freePositions.empty() ) {
        return -1;
    }
    list<int>::iterator it = std::next(freePositions.begin(), startAt);
    cout << "Find next index: " << *it << endl;
    return *it;*/
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
    field[index] = 1;
    field[index + count + 1] = 1;
    //deleteElementInList(index);
    //deleteElementInList(index + count + 1);
}

bool Field::setFree(int index, int count) {
    bool isFree = Field::isFree(index) && Field::isFree(index + count + 1);
    if ( isFree ) {
        field[index] = 1;
        field[index + count + 1] = 1;
    }
    return isFree;
}

void Field::deleteElementInList(int index) {
    cout << "Delete " << index << endl;
    cout << "Size of list: " << freePositions.size() << endl;
    printList();
    list<int>::iterator findIterator = findElementInList(freePositions.begin(), freePositions.end(), index);
    printList();
    freePositions.erase(findIterator);
    printList();
}

list<int>::iterator Field::findElementInList(list<int>::iterator begin, list<int>::iterator end, int value) {
    cout << "First element: " << *begin << ", second element: " << *end << endl;
    cout << "Size of freePositions: " << freePositions.size() << endl;
    list<int>::iterator it = begin;
    for ( ; it != end; ++it ) {
        cout << "Value for that: " << *it << endl;
        if ( *it == value ) {
            break;
        }
    }
    return it;
}

void Field::printField() {
    cout << "Field: ";
    for ( int i = 0; i < field.size(); ++i ) {
        cout << field[i];
    }
    cout << endl;
}

void Field::printList() {
    cout << "List: ";
    for ( list<int>::iterator it = freePositions.begin(); it != freePositions.end(); ++it ) {
        cout << *it << ", ";
    }
    cout << endl;
}