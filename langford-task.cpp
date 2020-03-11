#include "langford-task.h"

LangfordTask::LangfordTask(int count, int startPosition, int* solutions) : langford(count), count(count), position(startPosition), solutions(solutions) {
    init(count);
}

LangfordTask::LangfordTask(Field& field, int count, int position, int* solutions) : langford(field), count(count), position(position), solutions(solutions) {
    init(count);
}

task* LangfordTask::execute() {
    //cout << "Run execute" << endl;
    //int index = position;
    if ( langford.isFree(position + count + 1) ) {

        langford.set(position, count);
        if ( count == 1 ) {
            *solutions += 1;
            return NULL;
        }
        int childs = 0;
        task_list list;

      /*  auto callback = [&](int index) {
            if ( langford.isFree(index) && langford.isFree(index + count) ) {
                Field child(langford);
                list.push_back(*new(allocate_child())LangfordTask(child, count - 1, index, solutions));
                ++childs;
            }
        };
        parallel_for(langford.nextFree(), langford.getSize() - count, callback);*/
        for ( int i = langford.nextFree(); i < langford.getSize() - count && i > -1; i = langford.nextFree(i+1)) {
            //if ( langford.isFree(i) && langford.isFree(i + count) ) {
                Field child(langford);
                list.push_back(*new(allocate_child())LangfordTask(child, count - 1, i, solutions));
                ++childs;
            //}
        }

        if ( childs > 0 ) {
            set_ref_count(childs + 1);
            spawn_and_wait_for_all(list);
        }

    }
    return NULL;
}

void LangfordTask::init(int count) {
    //langford.set(position, count);
}

void LangfordTask::print(string message) {
    cout << message << endl;
}
