#include "langford-sequence.h"

LangfordSequence::LangfordSequence(int numberOfColors, int* solutions) : langford(numberOfColors), count(numberOfColors), solutions(solutions) {
    //initialize();
}

LangfordSequence::LangfordSequence(Field& field, int count, int* solutions) : langford(field), count(count), solutions(solutions) {
    //initialize();
}

task* LangfordSequence::execute() {
    task_list list;
    int childs = 0;
    auto callback = [&](int index) {
        cout << "Index: " << index << endl;
        cout << " with second: " << count << endl;
        //bool isFree = langford.isFree(index) && langford.isFree(index + count + 1);
        if ( langford.setFree(index, count) ) {
            //langford.set(index, count);
            langford.printField();
            if ( count == 1 ) {
                cout << "Ready" << endl;
                *solutions += 1;
            } else {
                Field child(langford);
                list.push_back(*new(allocate_child())LangfordSequence(child, count - 1, solutions));
                ++childs;
            }
        }
    };
    parallel_for(0, langford.getSize() - count - 1, callback);
    if ( childs > 0 ) {
        set_ref_count(childs + 1);
        spawn_and_wait_for_all(list);
    }
    //if ( check() ) {
    //    if ( count == 1 ) {
    //        *solutions += 1;
    //        return NULL;
    //    }
    //    task_list list;
    //    Field child(langford);
    //    list.push_back(*new(allocate_child())LangfordSequence(child, count - 1, solutions));
    //    set_ref_count(2);
    //    spawn_and_wait_for_all(list);
    //}
    return NULL;
}

bool LangfordSequence::check() {
    bool successful = false;
    for ( int i = 0; i < langford.getSize() - count && !successful; ++i ) {
        successful = langford.isFree(i) && langford.isFree(i + count + 1);
        firstIndex = i;
    }
    if ( successful ) {
        langford.set(firstIndex, count);
    }
    cout << "Check: " << successful << " by: " << count << endl;
    return successful;
}