// tbb-exercise.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

#include <tbb/tbb.h>
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
    cout << maxPrim << endl;
    std::vector<int> tmp = vector;

    double duration;
    std::clock_t start = clock();

    for ( int i = rangeBegin; i < rangeEnd; i += 2 ) {
        tmp[i] = -1;
    }

    for ( int i = rangeBegin + 1; i < maxPrim; i += 2 ) {
        //cout << i << endl;
        if ( tmp[i] == -1 ) {
            continue;
        }
        for ( int j = i+tmp[i]; j < rangeEnd; j += tmp[i] ) {
            //cout << tmp[j] << endl;
            if ( tmp[j] == -1 ) {
                continue;
            }
            if ( tmp[j] % tmp[i] == 0 ) {
                tmp[j] = -1;
            }
        }
    }

    duration = clock() - start;

    printDuration(duration);
    //printVector(tmp);
    //std::cout << "duration: " << duration << " - per sec: " << (duration /(double)CLOCKS_PER_SEC) << std::endl;
    //std::cout << "clocks per sec: " << CLOCKS_PER_SEC << std::endl;

    /*for ( int i = rangeBegin; i < rangeEnd; ++i ) {
        std::cout << "Value: " << vector[i] << std::endl;
    }*/
}

void runErasthotenesParallel(std::vector<int>& vector) {
    int rangeBegin = 2;
    int rangeEnd = vector.size();
    double duration;

    int amountLoop = 0;
    int amountCallback = 0;

    int startCount = 0;
    int endCount = 0;

    int maxPrim = sqrt(rangeEnd) + 2;
    int counter = 0;

    std::vector<std::thread::id> vectorId;

    std::vector<int> tmp = vector;
    //std::clock_t start = clock();

    auto callback = [&](int index) {
        //vectorId.push_back(std::this_thread::get_id());
        //++amountCallback;
        //cout << "Run callback: " << index << endl;
        //startCount += rangeEnd / 8;
        //startCount = index;
        //endCount += (rangeEnd - index) / 8;
        //endCount = rangeEnd;

        //for ( int i = index+1; i < rangeEnd; ++i ) {
        //    //cout << tmp[i] << endl;
        //    if ( tmp[i] == -1 ) {
        //        continue;
        //    }
        //    if ( tmp[i] % tmp[index] == 0 ) {
        //        tmp[i] = -1;
        //    }
        //}

        //cout << "number: " << tmp[index] << "\t" << counter << "\t" << tmp[counter] << "\t" << tmp[index] % tmp[counter] << endl;
        if ( tmp[index] == -1 ) return;
        //if ( index % counter == 0 ) tmp[index] = -1;
        tmp[index] = -1;
    };

    amountCallback = 0;

    std::clock_t start = clock();
    for ( int i = rangeBegin + 2; i < rangeEnd; i += 2 ) {
        tmp[i] = -1;
    }

    for ( int i = rangeBegin + 1; i < maxPrim; i += 2 ) {
        //cout << "i: " << i << "\t" << tmp[i] << endl;
        if ( tmp[i] == -1 ) {
            continue;
        }
        counter = i;
        //cout << tmp[i] << endl;
        /*startCount = i;
        endCount = i;*/
        //int increase = (rangeEnd - i) / 8;
        //for ( int j = i + 1; j < rangeEnd; j += increase ) {
        //    //cout << "j: " << j << endl;
        //    if ( rangeEnd - j < increase )
        //        parallel_for(j, rangeEnd - j, callback);
        //    else
        //        parallel_for(j, (int)(j+increase - 1), callback);
        //}
        parallel_for(3*i, (int)vector.size(), 2*i, callback);
        //++amountLoop;
        //cout << "Parallel loop ready" << endl;
        /*parallel_for(rangeBegin, rangeEnd, [=](auto index) {
            cout << "any: " << tmp[i] << endl;
            });*/
    }

    duration = clock() - start;
    cout << "Parallel" << endl;
    printDuration(duration);
    //printVector(tmp);
    //for (int i = 0; i < vectorId.size(); ++i ) {
    //    //cout << "ID: " << vectorId[i] << endl;
    //}
    //printVector(tmp);
    //cout << "Amount loop: " << amountLoop << endl;
    //cout << "Amount callback: " << amountCallback << endl;
}

int main()
{
    //tbbTest();

    //testAddToVector();
    std::vector<int> vector(pow(10, 8), 0);

    auto callback = [&](int index) {
        vector[index] = index;
    };
    tbb::parallel_for(0, (int)vector.size(), callback);

    /*for ( int i = 2; i < pow(10, 8); ++i ) {
        vector.push_back(i);
    }*/
    //std::vector<int> vectorParallel = vector;
    //printVector(vector);
    cout << "ready" << endl;
    runEratosthenes(vector);
    runErasthotenesParallel(vector);
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
