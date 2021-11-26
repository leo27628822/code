// DS1101ex4_20_10927143_10927141
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include<time.h>

using namespace std;

struct data {
    int OID, Arrival, Duration, Timeout ;
};

void shellSort( vector<data> & process, int n ) {

    for ( int h = n / 2 ; h > 0 ; h /= 2 ) {
        for ( int unsorted = h ; unsorted < n ; ++unsorted ) {
            int loc = unsorted ;
            data next = process[unsorted] ;
            for ( ; ( loc >= h ) && ( ( process[loc-h].Arrival > next.Arrival ) || ( process[loc-h].Arrival == next.Arrival && process[loc-h].OID > next.OID ) ) ; loc -= h )
                process[loc] = process[loc-h] ;
            process[loc] = next ;
        } // end for
    } // end for

} // end shellSort
/*
class Queue {

    public :
        Queue() ;
        ~Queue() ;
        bool isEmpty() ;
        void enqueue() ;
        void dequeue() ;
        void getFront() ;
        void cleanQueue() ;
    private :
        struct QueueNode {
            data Data ;
            QueueNode * next  ;
        };
        QueueNode * backPtr ;
};

Queue::Queue() {
    backPtr = NULL ;
} // end Queue

bool Queue::isEmpty() {
    return backPtr == NULL ;
} // qnd isEmpty

void Queue::enqueue( struct data ) {
    QueueNode * newPtr = new QueueNode ;
    newPtr -> Data = ;
    if ( isEmpty() )
        newPtr -> next = newPtr ;
    else {
        newPtr -> next = backPtr -> next ;
        backPtr -> next = new Ptr ;
    } // end else
    backPtr = newPtr ;
} // end enqueue

void Queue::dequeue() {
    if ( isEmpty() )
    else {
        QueueNode * tempPtr = backPtr -> next ;
        if ( backPtr -> next == backPtr )
            backPtr = NULL ;
        else
            tempPtr -> next = NULL ;
        delete tempPtr ;
    } // end else
} // end dequeue

void Queue::getFornt() {
    = backPtr -> next -> ;
} // end getFront

void Queue::cleanQueue() {
    while ( !isEmpty() )
        deQueue() ;
} // end cleanQueue

Queue::~Queue() {
    cleanQueue() ;
} // end ~Queue
//*/
int main() {

    int command = 0 ;
    cout << "*** Simulate FIFO Queues by SQF *****\n" ;
    cout << "* 0. Quit                            *\n" ;
    cout << "* 1. Sort a file                     *\n" ;
    cout << "* 2. Simulate one FIFO queue         *\n" ;
    cout << "**************************************\n" ;
    cout << "Input a command(0, 1, 2): " ;

    string filename, number ;
    vector <data> process ;
    double start, end ;
    while ( cin >> command && command ) {
        double start, end, r, s, w;
        string temp ;
        if ( command == 1 ) {
            cout << "Input a file number : ( e.g., 401, 402, ...... ) : " ;
            cin.ignore() ;
            getline( cin, number ) ;
            filename = "input" + number + ".txt" ;
            //cout << "\nCheck filename : " << filename << "\n" ;
            ifstream file ;
            start = clock() ;
            file.open( filename ) ;
            if ( !file.is_open() )
                cout << "\n### " << filename << " does not exists! ###\n\n";
            else {
                getline( file, temp ) ;
                while ( !file.eof() ) {
                    data data ;
                    file >> data.OID >> data.Arrival >> data.Duration >> data.Timeout ;
                    process.push_back( data ) ;
                } // end while

                file.close() ;
                end = clock() ;
                r = end - start ;
                start = clock() ;
                shellSort( process, process.size() ) ;
                end = clock() ;
                s = end - start ;
                ofstream newFile ;
                filename = "sorted" + number + ".txt" ;
                start = clock() ;
                newFile.open( filename ) ;
                newFile << temp << "\n" ;
                for ( int i = 0 ; i < process.size() ; i++ )
                    newFile << process[i].OID << "\t" << process[i].Arrival << "\t" << process[i].Duration << "\t" << process[i].Timeout << "\n" ;

                newFile.close() ;
                end = clock() ;
                w = end - start ;
            } // else
        } // end if
        else if ( command == 2 ) {

        } // end else if
        else
            cout << "\nCommand does not exists!\n\n" ;

        process.clear() ;
        cout << "\n" ;
        cout << "**** Simulate FIFO Queues by SQF *****\n" ;
        cout << "* 0. Quit                            *\n" ;
        cout << "* 1. Sort a file                     *\n" ;
        cout << "* 2. Simulate one FIFO queue         *\n" ;
        cout << "**************************************\n" ;
        cout << "Input a command(0, 1, 2): " ;

    } // end while

    system("pause") ;
} // main()
