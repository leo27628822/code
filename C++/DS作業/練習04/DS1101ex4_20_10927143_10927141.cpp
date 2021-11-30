// DS1101ex4_20_10927143_10927141
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

struct data {
    int OID, Arrival, Duration, Timeout ;
    int Departure, cpu ;
};

struct simulation {
    int OID, Time, Delay ;
};

struct simulation2 {
    int OID, Departure, Abort, CID, Delay, Arrival ;
    bool status ;  // 0 : Arrival  1 : Departure
};

struct event {
    bool status ; // 0 : Arrival  1 : Departure
    int OID, Time, Duration, Timeout ;
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
//*
class Queue {

    public :
        Queue() ;
        ~Queue() ;
        bool isEmpty() ;
        void enqueue( data process ) ;
        void dequeue() ;
        data getFront() ;
        void cleanQueue() ;
        int size() {
            return queue_size ;
        } // end size() ;
        void print() {
            QueueNode * temp = backPtr -> next ;
            for ( int j = 3 ; j > 0 ; j-- ) {
                cout << temp -> process.OID << "\t CHECK q\n" ;
                temp = temp -> next ;
            }
        }

    private :
        int queue_size ;
        struct QueueNode {
            data process ;
            QueueNode * next  ;
        };
        QueueNode * backPtr ;
};

Queue::Queue() {
    backPtr = NULL ;
    queue_size = 0 ;
} // end Queue

bool Queue::isEmpty() {
    return backPtr == NULL ;
} // qnd isEmpty

void Queue::enqueue( data process ) {
    queue_size++ ;
    QueueNode * newPtr = new QueueNode ;
    newPtr -> process =  process ;
    if ( isEmpty() )
        newPtr -> next = newPtr ;
    else {
        newPtr -> next = backPtr -> next ;
        backPtr -> next = newPtr ;
    } // end else
    backPtr = newPtr ;
} // end enqueue

void Queue::dequeue() {
    if ( isEmpty() )
        cout << "\n### Error! There is no data in queue. ###\n" ;
    else {
        queue_size-- ;
        QueueNode * tempPtr = backPtr -> next ;
        if ( backPtr -> next == backPtr )
            backPtr = NULL ;
        else
            backPtr -> next = tempPtr -> next ;
        tempPtr -> next = NULL ;
        delete tempPtr ;
    } // end else
} // end dequeue

data Queue::getFront() {
    return backPtr -> next -> process ;
} // end getFront

void Queue::cleanQueue() {
    while ( !isEmpty() )
        dequeue() ;
} // end cleanQueue

Queue::~Queue() {
    Queue::cleanQueue() ;
} // end ~Queue
//*/

int main() {

    int command = 0 ;
    cout << "*** Simulate FIFO Queues by SQF *****\n" ;
    cout << "* 0. Quit                            *\n" ;
    cout << "* 1. Sort a file                     *\n" ;
    cout << "* 2. Simulate one FIFO queue         *\n" ;
    cout << "* 3. Simulate two FIFO queue         *\n" ;
    cout << "**************************************\n" ;
    cout << "Input a command(0, 1, 2, 3): " ;

    string filename, number, temp ;
    vector <data> process ;
    double start, end ;

    while ( cin >> command && command ) {

        if ( command != 1 && command != 2 && command != 3 ) {
            cout << "\nCommand does not exist!\n" ;
            cout << "\n" ;
            cout << "**** Simulate FIFO Queues by SQF *****\n" ;
            cout << "* 0. Quit                            *\n" ;
            cout << "* 1. Sort a file                     *\n" ;
            cout << "* 2. Simulate one FIFO queue         *\n" ;
            cout << "* 3. Simulate two FIFO queue         *\n" ;
            cout << "**************************************\n" ;
            cout << "Input a command(0, 1, 2, 3): " ;
            continue ;
        } // end if

        double start, end, r, s, w;

        cout << "Input a file number : ( e.g., 401, 402, ...... ) : " ;
        cin.ignore() ;
        getline( cin, number ) ;
        if ( command == 1 )
            filename = "input" + number + ".txt" ;
        else if ( command == 2 || command == 3 )
            filename = "sorted" + number + ".txt" ;
        ifstream file ;
        start = clock() ;
        file.open( filename ) ;
        if ( !file.is_open() )
            cout << "\n### " << filename << " does not exists! ###\n";
        else {

            getline( file, temp ) ;

            while ( !file.eof() ) {
                data data ;
                file >> data.OID >> data.Arrival >> data.Duration >> data.Timeout ;
                if ( file.fail() ) break;
                process.push_back( data ) ;
            } // end while
            file.close() ;
            end = clock() ;
            r = end - start ;

            if ( command == 1 ) {
                cout << "\n\t" << temp << "\n" ;
                for ( int i = 0 ; i < process.size() ; ++i )
                    cout << "(" << i+1 << ")\t" << process[i].OID << "\t" << process[i].Arrival << "\t" << process[i].Duration << "\t" << process[i].Timeout << "\n" ;
                cout << "\n" ;

                start = clock() ;
                shellSort( process, process.size() ) ;
                end = clock() ;
                s = end - start ;

                ofstream newFile ;
                filename = "sorted" + number + ".txt" ;
                start = clock() ;
                newFile.open( filename ) ;
                newFile << temp << "\n" ;
                for ( int i = 0 ; i < process.size() ; i++ ) {
                    newFile << process[i].OID << "\t" << process[i].Arrival << "\t" << process[i].Duration << "\t" << process[i].Timeout ;
                    if ( i != process.size() - 1 ) newFile << "\n" ;
                } // end for
                newFile.close() ;
                end = clock() ;
                w = end - start ;

                cout << "Reading data: " << fixed << setprecision(2) << r << " ms. \n" ;
                cout << "Sorting data: " << s << " ms . \n" ;
                cout << "Writing data: " << w << " ms . \n" ;
            } // end if
            else if ( command == 2 ) {
                int cputime = 0, total = process.size() ;
                bool work = 0 ;
                Queue myqueue ;
                simulation sim ;
                data nextjob ;
                vector<simulation> Done, Abort ;
                sim.OID = process[0].OID ;
                cputime = process[0].Arrival + process[0].Duration ;
                if ( cputime <= process[0].Timeout ) {
                    sim.Time = cputime  ;
                    sim.Delay = 0 ;
                    Done.push_back( sim ) ;
                } // end if
                else {
                    sim.Time = process[0].Timeout ;
                    sim.Delay = process[0].Timeout - process[0].Arrival ;
                    Abort.push_back( sim ) ;
                } // end else

                process.erase( process.begin() ) ;
                bool done = false ;
                while ( !done ) {
                    int i = 0 ;
                    for ( ; i < process.size() && process[i].Arrival < cputime ; i++ ) {
                        if ( myqueue.size() < 3 )
                                myqueue.enqueue( process[i] ) ;
                        else {
                            sim.OID = process[i].OID ;
                            sim.Time = process[i].Arrival ;
                            sim.Delay = 0 ;
                            Abort.push_back( sim ) ;
                        } // end else
                    } // end for

                    process.erase( process.begin(), process.begin() + i ) ;

                    while ( !myqueue.isEmpty() ) {
                        sim.OID = myqueue.getFront().OID ;
                        if ( myqueue.getFront().Timeout < cputime ) {
                            sim.Time = cputime ;
                            sim.Delay = cputime - myqueue.getFront().Arrival ;
                            Abort.push_back( sim ) ;
                        } // end if
                        else if ( cputime + myqueue.getFront().Duration <= myqueue.getFront().Timeout ) {
                            sim.Time = cputime + myqueue.getFront().Duration ;
                            sim.Delay = cputime - myqueue.getFront().Arrival ;
                            Done.push_back( sim ) ;
                            cputime += myqueue.getFront().Duration ;
                        } // end else if
                        else {
                            cputime = myqueue.getFront().Timeout ;
                            sim.Time = myqueue.getFront().Timeout ;
                            sim.Delay = cputime - myqueue.getFront().Arrival ;
                            Abort.push_back( sim ) ;
                        } // end else
                        myqueue.dequeue() ;
                    } // end while

                    if ( process.empty() ) done = true ;
                    else {
                        if ( cputime < process[0].Arrival ) cputime = process[0].Arrival ;
                        sim.OID = process[0].OID ;
                        if ( cputime + process[0].Duration <= process[0].Timeout ) {
                            sim.Time = cputime + process[0].Duration ;
                            sim.Delay = cputime - process[0].Arrival;
                            Done.push_back( sim ) ;
                            cputime += process[0].Duration ;
                        } // end if
                        else {
                            sim.Time = cputime ;
                            sim.Delay = cputime - process[0].Arrival ;
                            Abort.push_back( sim ) ;
                        } // end else

                        process.erase( process.begin() ) ;
                    } // end else
                } // end while

                ofstream newFile ;
                filename = "output" + number + ".txt" ;
                newFile.open( filename ) ;
                newFile << "\t[Abort Jobs]\n" ;
                newFile << "\tOID\tAbort\tDelay\n" ;
                float delay = 0 ;
                for ( int i = 0 ; i < Abort.size() ; i++ ) {
                    newFile << "[" << i+1 << "]\t" << Abort[i].OID << "\t" << Abort[i].Time << "\t" << Abort[i].Delay << "\n" ;
                    delay += Abort[i].Delay ;
                } // end for
                newFile << "\t[Jobs Done]\n" ;
                newFile << "\tOID\tDeparture\tDelay\n" ;
                for ( int i = 0 ; i < Done.size() ; i++ ) {
                    newFile << "[" << i+1 << "]\t" << Done[i].OID << "\t" << Done[i].Time << "\t" << Done[i].Delay << "\n" ;
                    delay += Done[i].Delay ;
                } // end for
                newFile << "[Average Delay]\t" << fixed << setprecision(2) << delay / total << " ms\n" ;
                newFile << "[Success Rate]\t" << ((float)Done.size() / total) * 100 << " %" ;
                newFile.close() ;
                Done.clear() ;
                Abort.clear() ;

            } // end else if
            else if ( command == 3 ) {

                cout << "\n### 想不出來~~~ ###\n" ;

                /*
                int cputime1 = 0, cputime2 = 0, total = process.size() ;
                bool done = 0 ;
                Queue queue1, queue2 ;
                simulation2 sim ;
                data nextjob ;
                vector<simulation2> Done, Abort ;

                int ct = 1 ;
                bool cpu1 = 0, cpu2 = 0;
                int i = 0 ;
                while ( !done ) {


                    if ( !queue1.isEmpty() ) {

                        if ( ct == queue1.getFront().Departure ) {

                            int tmp = ct ;
                            while ( !queue1.isEmpty() ) {

                                sim.OID = queue1.getFront().OID ;
                                sim.CID = 1 ;

                                if ( tmp + queue1.getFront().Duration <= queue1.getFront().Timeout ) {
                                    sim.Departure = tmp + queue1.getFront().Duration ;
                                    sim.Delay = tmp - queue1.getFront().Arrival ;
                                    Done.push_back( sim ) ;
                                    tmp += queue1.getFront().Departure ;
                                } // end if
                                else {
                                    sim.Abort = queue1.getFront().Timeout ;
                                    sim.Delay = tmp - queue1.getFront().Arrival ;
                                    Abort.push_back( sim ) ;
                                    tmp = queue1.getFront().Timeout ;
                                } // end else

                                queue1.dequeue() ;

                            } // end while

                            cpu1 = false ;
                        } // end if

                    } // end if

                    if ( !queue2.isEmpty() ) {

                        if ( ct == queue2.getFront().Departure ) {

                            int tmp = ct ;
                            while ( !queue2.isEmpty() ) {

                                sim.OID = queue2.getFront().OID ;
                                sim.CID = 1 ;

                                if ( tmp + queue2.getFront().Duration <= queue2.getFront().Timeout ) {
                                    sim.Departure = tmp + queue2.getFront().Duration ;
                                    sim.Delay = tmp - queue2.getFront().Arrival ;
                                    Done.push_back( sim ) ;
                                    tmp += queue2.getFront().Departure ;
                                } // end if
                                else {
                                    sim.Abort = queue2.getFront().Timeout ;
                                    sim.Delay = tmp - queue2.getFront().Arrival ;
                                    Abort.push_back( sim ) ;
                                    tmp = queue2.getFront().Timeout ;
                                } // end else

                                queue2.dequeue() ;

                            } // end while

                            cpu2 = false ;
                        } // end if

                    } // end if

                    while ( i < process.size() && process[i].Arrival == ct ) {

                        if ( cpu1 == false ) {
                            process[i].Departure = process[i].Arrival + process[i].Duration ;
                            process[i].Arrival = ct ;
                            process[i].cpu = 1 ;
                            queue1.enqueue( process[i] ) ;
                            cpu1 = true ;
                        } // end if
                        else if ( cpu2 == false ) {
                            process[i].Departure = process[i].Arrival + process[i].Duration ;
                            process[i].Arrival = ct ;
                            process[i].cpu = 2 ;
                            queue2.enqueue( process[i] ) ;
                            cpu2 = true ;
                        } // end else if
                        else {  // Queue

                            if ( queue1.size() <= queue2.size() && queue1.size() < 4 ) {
                                process[i].Departure = process[i].Arrival + process[i].Duration ;
                                process[i].Arrival = ct ;
                                process[i].cpu = 1 ;
                                queue1.enqueue( process[i] ) ;
                            } // end if
                            else if ( queue2.size() < 4 ) {
                                process[i].Departure = process[i].Arrival + process[i].Duration ;
                                process[i].Arrival = ct ;
                                process[i].cpu = 2 ;
                                queue1.enqueue( process[i] ) ;
                            } // end else
                            else {
                                // ABORT
                                sim.OID = process[i].OID ;
                                sim.CID = 0 ;
                                sim.Delay = 0 ;
                                sim.Abort = process[i].Arrival ;
                                Abort.push_back( sim ) ;
                            } // end else

                        } // end else

                        i++ ;

                    } // end while

                    if ( i == process.size() && queue1.isEmpty() && queue2.isEmpty() ) done = true ;
                    ct++ ;

                } // end while

                ofstream newFile ;
                filename = "double" + number + ".txt" ;
                newFile.open( filename ) ;
                newFile << "\t[Abort Jobs]\n" ;
                newFile << "\tOID\tCID\tAbort\tDelay\n" ;
                float delay = 0 ;
                for ( i = 0 ; i < Abort.size() ; i++ ) {
                    newFile << "[" << i+1 << "]\t" << Abort[i].OID << "\t" << Abort[i].CID << "\t" << Abort[i].Abort << "\t" << Abort[i].Delay << "\n" ;
                    delay += Abort[i].Delay ;
                } // end for
                newFile << "\t[Jobs Done]\n" ;
                newFile << "\tOID\tCID\tDeparture\tDelay\n" ;
                for ( int i = 0 ; i < Done.size() ; i++ ) {
                    newFile << "[" << i+1 << "]\t" << Done[i].OID << "\t" << Done[i].CID << "\t" << Done[i].Departure << "\t" << Done[i].Delay << "\n" ;
                    delay += Done[i].Delay ;
                } // end for
                newFile << "[Average Delay]\t" << fixed << setprecision(2) << delay / total << " ms\n" ;
                newFile << "[Success Rate]\t" << ((float)Done.size() / total) * 100 << " %" ;
                newFile.close() ;
                Done.clear() ;
                Abort.clear() ;

                //*/

            } // end else if

        } // end else

        process.clear() ;

        cout << "\n" ;
        cout << "**** Simulate FIFO Queues by SQF *****\n" ;
        cout << "* 0. Quit                            *\n" ;
        cout << "* 1. Sort a file                     *\n" ;
        cout << "* 2. Simulate one FIFO queue         *\n" ;
        cout << "* 3. Simulate two FIFO queue         *\n" ;
        cout << "**************************************\n" ;
        cout << "Input a command(0, 1, 2, 3): " ;

    } // end while

    system("pause") ;
} // main()
