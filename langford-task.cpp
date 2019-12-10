#include "langford-task.h"

LangfordTask::LangfordTask(int count, int startPosition): langford(count), count(count), position(startPosition), subtasks(0) {
    //init(count);
    cout << "Hello world LangfordTask with default" << endl;
}

LangfordTask::LangfordTask(Field& field, int count, int position, unsigned long sub): langford(field), count(count), position(position), subtasks(sub) {
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
        } else {
            for ( int i = langford.nextFree(); i < langford.getSize() - count && i > -1; i = langford.nextFree(i+1) ) {
                cout << "i: " << i << endl;
                Field child(langford);
                //int size = childTasks.size();
                list.push_back(*new(allocate_child())LangfordTask(child, count - 1, i, (childTasks.size() + childs)));
                ++childs;
            }
            if ( childs > 0 ) {
                set_ref_count(childs + 1);
                spawn_and_wait_for_all(list);
                for ( int i = 0; i < 7; ++i ) {
                    subtasks += childTasks[i];
                }
                subtasks += childs;
            }
        }
    } else {
        cout << "No free field -> next" << endl;
    }

    return NULL;
}

void LangfordTask::init(int count) { }

void LangfordTask::print(string message) {
    cout << message << endl;
}
