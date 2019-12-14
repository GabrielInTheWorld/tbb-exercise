// tbb-exercise.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "langford.h"
#include "langford-vector.h"
#include "langford-solver-runner.h"
#include "langford-task.h"
#include "LangfordSolver.h"
#include "langford-sequence.h"
#include "field.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#include <bitset>

#include <tbb/tbb.h>
#include <tbb/task.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <thread>
#include <mutex>

using namespace tbb;
using namespace std;

void printVector(std::vector<int>& vector) {
    for ( int i = 0; i < vector.size(); ++i ) {
        std::cout << "Vector: " << vector[i] << std::endl;
    }
}


void printDuration(double duration) {
    std::cout << "duration: " << duration << " - per sec: " << (duration / (double)CLOCKS_PER_SEC) << std::endl;
    std::cout << "clocks per sec: " << CLOCKS_PER_SEC << std::endl;
}

void testAddToVector() {
    std::vector<int> vector;
    std::vector<int> readVector;
    std::mutex mutex;

    using lock_type = std::lock_guard<std::mutex>;
    //using lock_vector = std::lock_guard<std::vector<int>>;
    srand(time(0));

    auto initVector = [&mutex, &vector, &readVector](auto index) {
        lock_type lock(mutex);
        //lock_vector lock(vector);
        //lock_vector lock_two(readVector);
        vector.push_back(0);
        readVector.push_back(0);
    };

    auto insertVector = [&mutex, &vector](auto index) {
        //lock_type lock(mutex); 
        int number = rand() % 2001 - 1000;
        std::cout << "index: " << index << std::endl;
        std::cout << "Thread id:" << std::this_thread::get_id() << "- number: " << number << std::endl;
        vector[index] = number;
    };

    auto readOutVector = [&mutex, &vector, &readVector](auto index) {
        //lock_type lock(mutex);
        std::cout << "index: " << index << ", Vector: " << vector[index] << std::endl;
        if ( vector[index] == 0 ) {
            readVector[index];
        } else {
            readVector[index] = vector[index] > 0 ? 1 : -1;
        }
    };

    int rangeBegin = 0;
    int rangeEnd = 20;
    std::cout << "First" << std::endl;
    tbb::parallel_for(rangeBegin, rangeEnd, initVector);
    std::cout << "Second: " << readVector.size() << std::endl;
    tbb::parallel_for(rangeBegin, rangeEnd, insertVector);
    std::cout << "Third" << std::endl;
    tbb::parallel_for(rangeBegin, rangeEnd, readOutVector);

    for ( int i = rangeBegin; i < rangeEnd; ++i ) {
        std::cout << "Vector: " << vector[i] << ", bool: " << readVector[i] << std::endl;
    }
}

void tbbTest() {
    std::mutex mutex;
    using lock_type = std::lock_guard<std::mutex>;
    std::cout << "Hello World!\n";

    auto callback = [&mutex](auto index) {
        //lock_type lock(mutex);
        std::cout << "Thread id:" << std::this_thread::get_id() << " - index = " << index << std::endl;
    };

    tbb::parallel_for(1, 11, callback);

}

void runEratosthenes(std::vector<int> &vector) {
    int rangeBegin = 2;
    int rangeEnd = vector.size();
    int maxPrim = sqrt(rangeEnd) + 2;
    std::vector<int> tmp = vector;

    double duration;
    std::clock_t start = clock();

    for ( int i = rangeBegin + 2; i < rangeEnd; i += 2 ) {
        tmp[i] = -1;
    }

    for ( int i = rangeBegin + 1; i < maxPrim; i += 2 ) {
        if ( tmp[i] == -1 ) {
            continue;
        }
        for ( int j = 3*i; j < rangeEnd; j += 2*i ) {
            tmp[j] = -1;
        }
    }

    duration = clock() - start;

    printDuration(duration);
    //printVector(tmp);
}

void runErasthotenesParallel(std::vector<int>& vector) {
    int rangeBegin = 2;
    int rangeEnd = vector.size();
    double duration;

    int maxPrim = sqrt(rangeEnd) + 2;
    int counter = 0;

    std::vector<std::thread::id> vectorId;

    std::vector<int> tmp = vector;

    auto callback = [&](int index) {
        if ( tmp[index] == -1 ) return;
        tmp[index] = -1;
    };

    std::clock_t start = clock();
    for ( int i = rangeBegin + 2; i < rangeEnd; i += 2 ) {
        tmp[i] = -1;
    }

    for ( int i = rangeBegin + 1; i < maxPrim; i += 2 ) {
        if ( tmp[i] == -1 ) {
            continue;
        }
        counter = i;
        parallel_for(3*i, (int)vector.size(), 2*i, callback);
    }

    duration = clock() - start;
    cout << "Parallel" << endl;
    printDuration(duration);
}

void runEratosthenesParallelBool(vector<bool>& vector) {
    cout << "Boolean" << endl;
    int rangeBegin = 2;
    int rangeEnd = vector.size();
    double duration;

    int maxPrim = sqrt(rangeEnd) + 2;
    std::vector<bool> tmp = vector;

    auto callback = [&](int index) {
        tmp[index] = false;
    };

    std::clock_t start = clock();
    for ( int i = rangeBegin + 2; i < rangeEnd; i += 2 ) {
        tmp[i] = false;
    }

    for ( int i = rangeBegin + 1; i < maxPrim; i += 2 ) {
        if ( tmp[i] == false ) {
            continue;
        }
        parallel_for(3 * i, rangeEnd, 2 * i, callback);
    }

    duration = clock() - start;
    printDuration(duration);
    //printVector(tmp);
    /*for ( int i = 0; i < rangeEnd; ++i ) {
        cout << i << ": " << tmp[i] << endl;
    }*/
}

int main() {
    cout << "Run main" << endl;
    //tbbTest();

    //testAddToVector();
    std::vector<int> vector(pow(10, 2), 0);
    std::vector<bool> vectorBool(pow(10, 2), true);

    auto callback = [&](int index) {
        vector[index] = index;
    };
    tbb::parallel_for(0, (int)vector.size(), callback);

    cout << "ready" << endl;
    //runEratosthenes(vector);
    //runErasthotenesParallel(vector);
    //runEratosthenesParallelBool(vectorBool);


    double numberOfColors = 11;
    //Langford lang = Langford();
    //LangfordVector v(numberOfColors);
    //LangfordSolverRunner* runner = new LangfordSolverRunner(4);
    //LangfordSolverRunner runner(4);
    //runner.run();
    //runner -> run();
    //LangfordSolver* lf = new(tbb::task::allocate_root())LangfordSolver(new Field(4), 4, &solutionsSolver);
    //Field field(4);
    int solutionsSequence = 0;
    int solutionsSolver = 0;
    int solutions = 0;
    int solutions2 = 0;
    int tries = ceil((numberOfColors - 1) / 2);
    cout << "Tries: " << tries << endl;
    clock_t sequenceStart = clock();
    //LangfordSequence* rootSequence = new(task::allocate_root()) LangfordSequence(numberOfColors, &solutions);
    //task::spawn_root_and_wait(*rootSequence);
    clock_t sequenceStop = clock();
    cout << "LangfordSequence: " << solutions << " in " << (sequenceStop - sequenceStart) / (double)CLOCKS_PER_SEC << endl;

    clock_t startBefore = clock();
    auto callbackSolverPointer = [&](int index) {
        LangfordSolver* root = new(tbb::task::allocate_root())LangfordSolver(numberOfColors, index, &solutionsSolver);
        task::spawn_root_and_wait(*root);
    };
    tbb::parallel_for(0, tries, callbackSolverPointer);
    clock_t startBeforeStop = clock();
    cout << "With pointers: " << solutionsSolver << " in " << (startBeforeStop - startBefore) / (double)CLOCKS_PER_SEC << endl;

    clock_t start = clock();
    for ( int i = 0; i < tries; ++i ) {
        LangfordTask* root = new(tbb::task::allocate_root()) LangfordTask(numberOfColors, i, &solutions);
        task::spawn_root_and_wait(*root);
    }
    clock_t end = clock();
    cout << "Normal task: " << solutions << " in " << (end - start) / (double)CLOCKS_PER_SEC << endl;

    clock_t endBefore = clock();
    auto callbackTask = [&](int index) {
        LangfordTask* root = new(tbb::task::allocate_root()) LangfordTask(numberOfColors, index, &solutions2);
        task::spawn_root_and_wait(*root);
    };
    tbb::parallel_for(0, tries, callbackTask);
    clock_t end2 = clock();

    cout << "Task with parallel: " << solutions2 << " in " << (end2 - endBefore) / (double)CLOCKS_PER_SEC << endl;
    
    //cout << "Found solutions with pointers: " << solutionsSolver << endl;
    //cout << "Found solutions summarized: " << solutions << endl;
    //cout << "Found solutions2: " << solutions2 << endl;
    //cout << "Solutions: " << solutions / 2 << endl;
    //cout << "Executed with pointers: " << (start - startBefore) / (double)CLOCKS_PER_SEC << endl;
    //cout << "Executed task in: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
    //cout << "2 executed in time: " << (end2 - endBefore) / (double)CLOCKS_PER_SEC << endl;

    //LangfordTask task(4);
    //tbb::task::spawn_root_and_wait(task);

    //tbb::task_group group;
    //group.run_and_wait(lf);
}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
