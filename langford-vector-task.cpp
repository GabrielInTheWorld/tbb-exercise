#include "langford-vector-task.h"

LangfordVectorTask::LangfordVectorTask(int count, int* solutions) : count(count), solutions(solutions) {
    langford = vector<bool>(2 * count, 0);
    length = count % 2 == 0 ? count - 1 : ((double)count - 1) / 2;
}

LangfordVectorTask::LangfordVectorTask(vector<bool>& field, int count, int* solutions) : langford(field), count(count), solutions(solutions) {
    length = field.size() - count - 1;
    //nextFree();
}

task* LangfordVectorTask::execute() {
    task_list list;
    int childs = 0;
    //cout << "length: " << length << " byCount: " << count << endl;
    for ( int i = nextFree(0); i < length && i > -1; i = nextFree(i+1) ) {
        //cout << "count: " << count << " isFree: " << isFree(i, count) << endl;
        if ( isFree(i, count)) {
            vector<bool> child = langford;
            child[i] = 1;
            child[i + count + 1] = 1;

            if ( count == 1 ) {
                *solutions += 1;
                return NULL;
            }

            list.push_back(*new(allocate_child())LangfordVectorTask(child, count - 1, solutions));
            ++childs;
        }
    }

    if ( childs > 0 ) {
        set_ref_count(childs + 1);
        spawn_and_wait_for_all(list);
    }

    return NULL;
}

int LangfordVectorTask::nextFree(int startAt) {
    for ( int i = startAt; i < langford.size() - count - 1; ++i ) {
        if ( langford[i] == 0 ) {
            //pointFree = i;
            return i;
        }
    }
    return -1;
}

bool LangfordVectorTask::isFree(int index, int count) {
    return langford[index] == 0 && langford[index + count + 1] == 0;
}

bool LangfordVectorTask::setNext(int index, int count) {
    bool next = isFree(index, count);
    if ( next ) {
        langford[index] = 1;
        langford[index + count + 1] = 1;
    }
    return next;
}

vector<bool> LangfordVectorTask::copyVector(vector<bool> v) {
    vector<bool> child(v.size(), 0);
    for ( int i = 0; i < v.size(); ++i ) {
        child[i] = v[i];
    }
    return child;
}

void LangfordVectorTask::printVector(std::vector<bool>& vector) {
    cout << "Vector: ";
    for ( int i = 0; i < vector.size(); ++i ) {
        cout << vector[i];
    }
    cout << endl;
}
