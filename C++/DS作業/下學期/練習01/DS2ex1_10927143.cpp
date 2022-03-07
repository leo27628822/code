// DS2ex1_10927143
# include <iostream>
# include <string>
# include <algorithm>
# include <fstream>
# include <vector>
# include <sstream>
# include <math.h>
# include <string.h>

using namespace std;

void printTitle() ;

class MaxHeap {

private:
    int height ;
    typedef struct data{
        int numOfStudent;
        int serialNumber ;
    }dataType ;
    vector<dataType> dt ;
    vector<dataType> mh ;

public:
    bool readFile() ;
    MaxHeap() { height = 0 ; mh.clear() ; dt.clear() ; } // end MaxHeap
    void heapInsert() ;
    void clearUp() { height = 0 ; mh.clear() ; dt.clear() ; } // end clearUp
    void setHeight() ;
    void showAll() ;
    void printRoot() ;
    void printLeftMostBottom() ;
    void printBottom() ;
};

class Deap {

private:
    int height ;
    typedef struct data{
        int numOfStudent;
        int serialNumber ;
    }dataType ;
    vector<dataType> dt ;
    vector<dataType> dp ;

public:
    bool readFile() ;
    Deap() { height = 0 ; dp.clear() ; dt.clear() ; } // end Deap
    void deapInsert() ;
    void clearUp() { height = 0 ; dp.clear() ; dt.clear() ; } // end clearUp
    void setHeight() ;
    void showAll() ;
    void printLeftMostBottom() ;
    void printBottom() ;
    void swapData( int index1, int index2 ) ;
    void verifyMax( int index ) ;
    void verifyMin( int index ) ;
};
/*
class MinMaxHeap {


};
*/
int main() {
    printTitle() ;
    int command ;
    MaxHeap mh ;
    Deap dp ;
    while ( cin >> command ) {
        if ( command == 1 ) {
            while ( !mh.readFile() )  ;
            mh.heapInsert() ;
            mh.setHeight() ;
            cout << "<Max Heap>\n" ;
            mh.printRoot() ;
            mh.printBottom() ;
            mh.printLeftMostBottom() ;
        } // if
        else if ( command == 2 ) {
            while ( !dp.readFile() )  ;
            dp.deapInsert() ;
            cout << "<Deap>\n" ;
            dp.printBottom() ;
            dp.printLeftMostBottom() ;
        } // else if
        else if ( command == 0 ) {
            break ;
        } // else if
        else {
            cout << "\nCommand does not exist!\n" ;
        } // else

        cout << "\n" ;
        mh.clearUp() ;
        dp.clearUp() ;
        printTitle() ;
    } // while

    system("pause") ;
} // end main

void printTitle() {
    cout << "**** Heap Construction  *****\n" ;
    cout << "* 0. QUIT                   *\n" ;
    cout << "* 1. Build a Max Heap       *\n" ;
    cout << "* 2. Build a DEAP           *\n" ;
    cout << "*****************************\n" ;
    cout << "Input a choice(0, 1, 2): " ;
} // end PrintTitle

bool MaxHeap::readFile() {
    // readFile and put data into vector

    string filename, tempStr ;
    ifstream file ;
    cout << "Input a file number : " ;
    cin >> filename ;
    cin.ignore() ;
    filename = "input" + filename + ".txt" ;
    file.open( filename ) ;
    if ( file.is_open() ) {
        getline( file, tempStr ) ;
        getline( file, tempStr ) ;
        getline( file, tempStr ) ;
        int i = 1 ;
        while ( !file.eof() ) {
            getline( file, tempStr ) ;
            if ( file.fail() ) break ;
            string delimiter = "\t";
            vector<string> words ;
            size_t pos ;
            while ( ( pos = tempStr.find(delimiter) ) != string::npos ) {
                words.push_back( tempStr.substr(0, pos) ) ;
                tempStr.erase( 0, pos + delimiter.length() ) ;
            } // end while

            if ( words[6].size() > 3 ) {
                char chars[] = ",\"" ;
                for ( int i = 0; i < strlen(chars) ; ++i ) {
                    words[6].erase ( std::remove( words[6].begin(), words[6].end(), chars[i] ), words[6].end() );
                } // for
            } // if

            dataType dT ;
            dT.numOfStudent = stoi( words[6] ) ;
            dT.serialNumber = i ;
            i++ ;
            dt.push_back( dT ) ;
        } // end while

        file.close() ;
        return true ;

    } // end if
    else {
        cout << "\n### " << filename << " does not exist! ###\n\n" ;
        return false ;
    } // end else

} // end readFile()

bool Deap::readFile() {
    // readFile and put data into vector

    string filename, tempStr ;
    ifstream file ;
    cout << "Input a file number : " ;
    cin >> filename ;
    cin.ignore() ;
    filename = "input" + filename + ".txt" ;
    file.open( filename ) ;
    if ( file.is_open() ) {
        getline( file, tempStr ) ;
        getline( file, tempStr ) ;
        getline( file, tempStr ) ;
        int i = 1 ;
        while ( !file.eof() ) {
            getline( file, tempStr ) ;
            if ( file.fail() ) break ;
            string delimiter = "\t";
            vector<string> words ;
            size_t pos ;
            while ( ( pos = tempStr.find(delimiter) ) != string::npos ) {
                words.push_back( tempStr.substr(0, pos) ) ;
                tempStr.erase( 0, pos + delimiter.length() ) ;
            } // end while

            if ( words[6].size() > 3 ) {
                char chars[] = ",\"" ;
                for ( int i = 0; i < strlen(chars) ; ++i ) {
                    words[6].erase ( std::remove( words[6].begin(), words[6].end(), chars[i] ), words[6].end() );
                } // for
            } // if

            dataType dT ;
            dT.numOfStudent = stoi( words[6] ) ;
            dT.serialNumber = i ;
            i++ ;
            dt.push_back( dT ) ;
        } // end while

        file.close() ;
        return true ;

    } // end if
    else {
        cout << "\n### " << filename << " does not exist! ###\n\n" ;
        return false ;
    } // end else

} // end readFile()

void MaxHeap::heapInsert() {
    // put data one by one to build MaxHeap

    mh.push_back( dt[0] ) ;
    for ( int i = 1 ; i < dt.size() ; i++ ) {
        mh.push_back( dt[i] ) ;
        int index = mh.size() - 1 ;
        for ( int parent = (index-1)/2 ; parent >= 0 ; parent = (index-1)/2 ) {
            if ( mh[index].numOfStudent > mh[parent].numOfStudent ) {
                dataType temp = mh[index] ;
                mh[index] = mh[parent] ;
                mh[parent] = temp ;
            } // end if
            else {
                break ;
            } // end else

            index = parent ;
        } // end for
    } // for
} // end heapInsert()

void Deap::deapInsert() {
    // put data one by one to build Deap

    dataType temp ;
    temp.numOfStudent = -1 ;
    temp.serialNumber = -1 ;
    dp.push_back( temp ) ;
    dp.push_back( dt[0] ) ;
    dp.push_back( dt[1] ) ;
    if ( dp[1].numOfStudent > dp[2].numOfStudent ) swapData( 1, 2 ) ;
    for ( int i = 2 ; i < dt.size() ; i++ ) {
        dp.push_back( dt[i] ) ;
        setHeight() ;
        int index = dp.size() - 1 ;
        int check = pow( 2, height ) - 2 - pow( 2, height-2 ) ;
        int gap = pow( 2, height - 2 ) ;
        if ( index <= check ) {
            // input node at min-heap ( left tree )
            int parents = index + gap ;
            parents = ( parents - 1 ) / 2 ;
            if ( dp[index].numOfStudent > dp[parents].numOfStudent ) {
                swapData( index, parents ) ;
                index = parents ;
                verifyMax( index ) ;
            } // if
            else {
                verifyMin( index ) ;
            } // else
        } // if
        else {
            // input node at max-heap ( right tree )
            int corresponding = index - gap ;
            if ( dp[index].numOfStudent < dp[corresponding].numOfStudent ) {
                swapData( index, corresponding ) ;
                index = corresponding ;
                verifyMin( index ) ;
            } // if
            else {
                verifyMax( index ) ;
            } // else
        } // else
    } // for
} // end deapInsert()

void MaxHeap::setHeight() {

    height = 0 ;
    int n = mh.size() ;
    if ( n == 0 || n == 1 ) {
        height = n ;
    } // if
    else {
        while ( n > 0 ) {
            n /= 2 ;
            height++ ;
        } // end while
    } // else

} // end setHeight()

void Deap::setHeight() {

    height = 0 ;
    int n = dp.size() ;
    if ( n == 0 || n == 1 ) {
        height = n ;
    } // if
    else {
        while ( n > 0 ) {
            n /= 2 ;
            height++ ;
        } // end while
    } // else

} // end setHeight()

void Deap::swapData( int index1, int index2 ) {
    dataType temp = dp[index1] ;
    dp[index1] = dp[index2] ;
    dp[index2] = temp ;
} // swapData()

void Deap::verifyMin( int index ) {
    // maintain min-heap structure

    for ( int parent = (index-1)/2 ; parent > 0 ; parent = (index-1)/2 ) {
        if ( dp[index].numOfStudent < dp[parent].numOfStudent ) {
            // swapData( index, parent ) ;
            dataType temp = dp[index] ;
            dp[index] = dp[parent] ;
            dp[parent] = temp ;
        } // end if
        else {
            break ;
        } // end else

        index = parent ;
    } // end for
} // verifyMin()

void Deap::verifyMax( int index ) {
    // maintain max-heap structure

    for ( int parent = (index-1)/2 ; parent > 0 ; parent = (index-1)/2 ) {
        if ( dp[index].numOfStudent > dp[parent].numOfStudent ) {
            // swapData( index, parent ) ;
            dataType temp = dp[index] ;
            dp[index] = dp[parent] ;
            dp[parent] = temp ;
        } // end if
        else {
            break ;
        } // end else

        index = parent ;
    } // end for
} // verifyMax()

void MaxHeap::printRoot() {

    cout << "root:\t[" << mh[0].serialNumber << "]\t" << mh[0].numOfStudent << "\n" ;

} // end printRoot()

void MaxHeap::printLeftMostBottom() {

    int i = pow(2,height) - pow(2,height-1) - 1 ;
    cout << "leftmost bottom:\t[" << mh[i].serialNumber << "]\t" << mh[i].numOfStudent << "\n" ;

} // end printLeftMostBottom()

void Deap::printLeftMostBottom() {

    int i = pow(2,height) - pow(2,height-1) - 1 ;
    cout << "leftmost bottom:\t[" << dp[i].serialNumber << "]\t" << dp[i].numOfStudent << "\n" ;

} // end printLeftMostBottom()

void MaxHeap::printBottom() {

    int i = mh.size() - 1 ;
    cout << "bottom:\t[" << mh[i].serialNumber << "]\t" << mh[i].numOfStudent << "\n" ;

} // end printBottom()

void Deap::printBottom() {

    int i = dp.size() - 1 ;
    cout << "bottom:\t[" << dp[i].serialNumber << "]\t" << dp[i].numOfStudent << "\n" ;

} // end printBottom()




