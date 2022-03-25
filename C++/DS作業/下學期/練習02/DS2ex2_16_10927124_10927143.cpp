// DS2ex2_16_10927124_10927143
# include <iostream>
# include <string>
# include <algorithm>
# include <fstream>
# include <vector>
# include <sstream>
# include <math.h>
# include <cmath>
# include <string.h>
# include <iomanip>

using namespace std;

void printTitle() ;

class TwoThreeTree {

private:
    typedef struct dT{
        string school, subject, dn, lv, student ;
        int number ;
    }dataType ;
    vector<dataType> dt ;

    typedef struct nT{
        string name ;
        int serialNumber ;
        nT * left ;
        nT * right ;
    }nodeType ;



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

class AVLTree {

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

int main() {
    printTitle() ;
    int command ;
    MaxHeap mh ;
    Deap dp ;
    MinMaxHeap mm ;
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
        else if ( command == 3 ) {
            while ( !mm.readFile() )  ;
            mm.minmaxHeapInsert() ;
            mm.setHeight() ;
            cout << "<MinMax Heap>\n" ;
            mm.printRoot() ;
            mm.printBottom() ;
            mm.printLeftMostBottom() ;
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
        mm.clearUp() ;
        cout << "efficency:\t" << b / a << "\n\n" ;
        a = b = 0 ;
        printTitle() ;
    } // while

    system("pause") ;
} // end main

void printTitle() {
    cout << "*** Search Tree Utilities ***\n" ;
    cout << "* 0. QUIT                   *\n" ;
    cout << "* 1. Build 2-3 tree         *\n" ;
    cout << "* 2. Build AVL tree         *\n" ;
    cout << "*****************************\n" ;
    cout << "Input a choice(0, 1, 2): " ;
} // end PrintTitle

bool TwoThreeTree::readFile() {
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

        a = dt.size() ;
        return true ;

    } // end if
    else {
        cout << "\n### " << filename << " does not exist! ###\n\n" ;
        return false ;
    } // end else

} // end readFile()
