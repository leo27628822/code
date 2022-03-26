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

typedef struct dT{
    string school, subject, dn, lv ;
    int student ;
    int number ;
} dataType ;
vector<dataType> dt ;

bool readFile() ;

class TwoThreeTree {

private:


    typedef struct sT {
        vector<int> number ;
        string name ;
    } slotType ;

    typedef struct nT{
        vector<slotType> school ;
        nT * left ;
        nT * middle ;
        nT * right ;
        nT * parent ;
        nT * temp ;
    }nodeType ;

    nodeType * root ;

public:
    // bool readFile() ;
    TwoThreeTree() { root = NULL ; dt.clear() ; } // constructor
    ~TwoThreeTree() { destroy() ; } // destructor
    void build() ;
    void insert( nodeType * tempPtr ) ;
    void destroy() ;
    void split()
    void init() { dt.clear() ; destroy() ; } // end clearUp
    void printRoot() ;
};
/*
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
*/
int main() {

    printTitle() ;
    string command ;
    TwoThreeTree ttt ;

    while ( getline( cin, command ) ) {

        if ( command == "1" ) {
            while ( !readFile() )  ;
            ttt.build() ;
            ttt.printRoot() ;
        } // if
        else if ( command == "2" ) {
            if ( dt.empty() ) {
                cout << "\nPlease input '1' at the first time.\n\n" ;
                break ;
            } // end if

            dp.deapInsert() ;
            cout << "<Deap>\n" ;
            dp.printBottom() ;
            dp.printLeftMostBottom() ;
        } // else if
        else if ( command == "0" ) {
            break ;
        } // else if
        else {
            cout << "\nCommand does not exist!\n" ;
        } // else

        cout << "\n" ;
        ttt.init() ;
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

bool readFile() {
    // readFile and put data into vector

    string filename, tempStr ;
    ifstream file ;
    cout << "Input a file number : " ;
    cin >> filename ;
    cin.ignore() ;
    filename = "input" + filename + ".txt" ;
    file.open( filename ) ;
    if ( !file.is_open() ) {

        cout << "\n### " << filename << " does not exist! ###\n\n" ;
        return false ;
    } // end if
    else {

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
            dT.school = words[1] ;
            dT.subject = words[3] ;
            dT.dn = words[4] ;
            dT.lv = words[5] ;
            dT.student = stoi( words[6] ) ;
            dT.serialNumber = i ;
            i++ ;
            dt.push_back( dT ) ;
        } // end while

        file.close() ;

        return true ;
    } // end else

} // end readFile()

void TwoThreeTree::build() {

    for ( int i = 0 ; i < dt.size() ; ++i ) {
        slotType tempSlot ;
        tempSlot.name = dt[i].school ;
        tempSlot.number.push_back( dt[i].number ) ;
        if ( root != NULL ) {
            insert( root, tempSlot, NULL ) ;
        } // end if
        else {
            root = new nodeType ;
            root -> parent = root -> left = root -> right = root -> middle = NULL ;
            root -> school.push_back( tempSlot ) ;
        } // end else
    } // end for
} // end build()

int TwoThreeTree::findPath( int i, nodeType * tempPtr, slotType * tempSlot, bool & equal ) {
// find insert position and check school name < | = | >

    if ( i == tempPtr -> school.size() || slotType -> school.name < tempPtr -> school[i].name ) {
        return i ;
    } // end if

    if ( slotType -> school.name == tempPtr -> school[i].name ) {
        tempPtr -> school[i].number.push_back( tempSlot.number.get( tempSlot.begin() ) ) ;
        equal = true ;
        return i ;
    } // end else if
    i++ ;
    findPath( i, tempPtr, tempSlot, equal ) ;
} // findPath()

void TwoThreeTree::insert( nodeType * curPtr, slotType * tempSlot, nodeType * prePtr ) {

    if ( curPtr == NULL ) {
        prePtr -> school.push_back( tempSlot ) ;
        sort( prePtr ) ;
        if ( prePtr -> school.size() == 3 ) {
            split( prePtr ) ;
        } // end if
        return ;
    } // if

    int i = 0 ;
    bool equal = false ;
    i = findPath( i, curPtr, tempSlot, equal ) ;

    if ( !equal && curPtr -> school.size() == 1 ) {
        if ( i == 0 ) {
            insert( curPtr -> left, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 1 ) {
            insert( curPtr -> right, tempSlot, curPtr ) ;
        } // else if
    } // end if
    else if ( !equal && curPtr -> school.size() == 2 ) {
        if ( i == 0 ) {
            insert( curPtr -> left, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 1 ) {
            insert( curPtr -> middle, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 2 ) {
            insert( curPtr -> right, tempSlot, curPtr ) ;
        } // else if
    } // end else if

} // end insert()

void TwoThreeTree::split( nodeType * tempPtr ) {

    nodeType * n1, * n2, * p ;
    n1 = new nodeType ;
    n1 -> school.push_back( tempPtr -> school[0] ) ;
    n2 = tempPtr ;
    n2 -> school.erase( n2 -> school.begin() ) ;

    if ( tempPtr == root ) {
        p = new nodeType ;
    } // end if
    else {
        p = tempPtr -> parent ;
    } // end else

    n1 -> parent = p ;
    n2 -> parent = p ;
    n1
    p -> left = ;
    p -> right = ;
    p -> middle = ;

} // end split()

void TwoThreeTree::sort( nodeType * tempPtr ) {
    for ( int i = 0 ; i < tempPtr -> school.size() ; ++i ) {
        for ( int j = 0 ; j < tempPtr -> school.size() ; ++j ) {
            if ( tempPtr -> school[i].name > tempPtr -> school[j].name ) {
                auto x = tempPtr -> school[i] ;
                tempPtr -> school[i] = tempPtr -> school[j] ;
                tempPtr -> school[j] = x ;
            } // end if
        } // inner for
    } // outer for
} // end split()

void TwoThreeTree::destroy( nodeType * tempPtr ) {

    if ( tempPtr != NULL) {
        destroy( tempPtr -> left);
        destroy( tempPtr -> right);
        delete tempPtr ;
    } // end if
} // destroy()
