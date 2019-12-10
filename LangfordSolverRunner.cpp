#include "langford-solver-runner.h"

LangfordSolverRunner::LangfordSolverRunner() {
    //LangfordSolverRunner(3);
    init(3);
}

LangfordSolverRunner::LangfordSolverRunner(int n) {
    /*f = new Field(n);
    number = n;*/
    //task_group list;
    init(n);
}

LangfordSolverRunner::~LangfordSolverRunner() {
    delete f;
}

void LangfordSolverRunner::run() {
    LangfordSolver* root = new(task::allocate_root())LangfordSolver(f, number, 0);
    //list.run_and_wait(*new(task::allocate_child())LangfordSolver(f, number, 0));
    task::spawn_root_and_wait(*root);
}

void LangfordSolverRunner::init(int n) {
    f = new Field(n);
    number = n;
}