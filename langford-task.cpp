#include "langford-task.h"

LangfordTask::LangfordTask(int count, int startPosition, int *solutions): langford(count), count(count), position(startPosition), solutions(solutions) {
    //init(count);
    cout << "Hello world LangfordTask with default: " << endl;
}

LangfordTask::LangfordTask(Field& field, int count, int position, int *solutions): langford(field), count(count), position(position), solutions(solutions) {
    cout << "Hello world LangfordTask" << endl;
}

task* LangfordTask::execute() {
    //*subtasks = 0;
    cout << "Run execute with count: " << count << endl;
    langford.printField();

    //int index = langford.nextFree();
    int index = position;
    cout << "Index " << index << endl;
    //print("Next free index: " + index);
    if ( index > -1 && langford.isFree(index + count + 1) ) {
        int size = langford.freeFields();
        //unsigned long childTasks[7] = { 0 };
        cout << "Size of field: " << size << endl;

        vector<int> childTasks(2*4, 0);
        int childs = 0;
        task_list list;

        langford.set(index, count);
        langford.printField();
        if ( count == 1 ) {
            // Ready!
            cout << "Ready!" << endl;
            *solutions += 1;
        } else {
            for ( int i = langford.nextFree(); i < langford.getSize() - count && i > -1; i = langford.nextFree(i+1) ) {
                cout << "i: " << i << endl;
                Field child(langford);
                //int size = childTasks.size();
                list.push_back(*new(allocate_child())LangfordTask(child, count - 1, i, solutions));
                ++childs;
            }
            if ( childs > 0 ) {
                set_ref_count(childs + 1);
                spawn_and_wait_for_all(list);
                //for ( int i = 0; i < 7; ++i ) {
                //    subtasks += childTasks[i];
                //}
                //subtasks += childs;
            }
        }
    }

    return NULL;
}

void LangfordTask::init(int count) { }

void LangfordTask::print(string message) {
    cout << message << endl;
}
