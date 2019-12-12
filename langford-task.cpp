#include "langford-task.h"

LangfordTask::LangfordTask(int count, int startPosition, int *solutions): langford(count), count(count), position(startPosition), solutions(solutions) {
}

LangfordTask::LangfordTask(Field& field, int count, int position, int *solutions): langford(field), count(count), position(position), solutions(solutions) {
}

task* LangfordTask::execute() {
    int index = position;
    if ( index > -1 && langford.isFree(index + count + 1) ) {
        vector<int> childTasks(2*4, 0);
        int childs = 0;
        task_list list;

        langford.set(index, count);
        if ( count == 1 ) {
            *solutions += 1;
        } else {
            for ( int i = langford.nextFree(); i < langford.getSize() - count && i > -1; i = langford.nextFree(i+1) ) {
                Field child(langford);
                list.push_back(*new(allocate_child())LangfordTask(child, count - 1, i, solutions));
                ++childs;
            }
            if ( childs > 0 ) {
                set_ref_count(childs + 1);
                spawn_and_wait_for_all(list);
            }
        }
    }

    return NULL;
}

void LangfordTask::init(int count) { }

void LangfordTask::print(string message) {
    cout << message << endl;
}
