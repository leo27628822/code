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
    ~TwoThreeTree() { destroy( root ) ; } // destructor
    void build() ;
    void insert( nodeType * tempPtr, slotType tempSlot, nodeType * prePtr ) ;
    void destroy( nodeType * tempPtr ) ;
    void split( nodeType * tempPtr, nodeType * childPtr ) ;
    void sort( nodeType * tempPtr ) ;
    void findPath( int & i, nodeType * tempPtr, slotType tempSlot, bool & equal ) ;
    //void init() { destroy( root ) ; } // end init
    void init() {
        root = NULL ;
    } // end init
    void Output(){
        // calculate Tree High
        int high = 0 ;
        for( auto temp = root ; temp != NULL ; temp = temp -> left, high++ ) ;
        cout << "Tree Hight : " << high << endl << endl ;

        // output the information
        int index = 1;

        for( int x = 0 ; x < root -> school.size() ; x++ ){
            for( int y = 0 ; y < root -> school[x].number.size() ; y++ ){
                cout << index << " : "  ;
                SearchFile( root -> school[x].number[y] ) ;
                index++ ;
            }
        }

        cout << endl << endl ;
    } // end Output

    void SearchFile(int index){
        int i = 0 ;
        for( ; i < dt.size() && dt[i].number != index ; i++ ) ;
        cout << "[ " << dt[i].number << " ]\t" << dt[i].school << "\t"
        << dt[i].subject << "\t"
        << dt[i].dn << "\t" << dt[i].lv
        << "\t" << dt[i].student << endl ;

    } // end SearchFile

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
            dt.clear() ;
            while ( !readFile() )  ;
            ttt.build() ;
            ttt.Output() ;
        } // if
        else if ( command == "2" ) {
            if ( dt.empty() ) {
                cout << "\nPlease input '1' at the first time.\n\n" ;
            } // end if
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
            dT.number = i ;
            i++ ;
            dt.push_back( dT ) ;
        } // end while

        file.close() ;

        return true ;
    } // end else

} // end readFile()

void TwoThreeTree::build() {

    for ( int i = 0 ; i < dt.size() ; ++i ) {
        cout << "--- input " << dt[i].school << " ---\n" ;
        slotType tempSlot ;
        tempSlot.name = dt[i].school ;
        tempSlot.number.push_back( dt[i].number ) ;
        if ( root != NULL ) {
            insert( root, tempSlot, NULL ) ;
        } // end if
        else {
            cout << "--- put data at root ---\n" ;
            root = new nodeType ;
            root -> parent = root -> left = root -> right = root -> middle = NULL ;
            root -> school.push_back( tempSlot ) ;
        } // end else

        system( "pause" );
    } // end for
} // end build()

void TwoThreeTree::findPath( int & i, nodeType * tempPtr, slotType tempSlot, bool & equal ) {
// find insert position and check school name < | = | >

    if ( i == tempPtr -> school.size() ) {
        cout << "--- check all data in school return i ---\n" ;
        return ;
    }

    if ( tempSlot.name < tempPtr -> school[i].name ) {
        cout << "--- " << tempSlot.name << " < " << tempPtr -> school[i].name << " return i ---\n" ;
        return ;
    } // end if

    if ( tempSlot.name == tempPtr -> school[i].name ) {
        cout << "--- same school add serial number ---\n" ;
        tempPtr -> school[i].number.push_back( tempSlot.number[0] ) ;
        equal = true ;
        return ;
    } // end else if

    i++;
    findPath( i, tempPtr, tempSlot, equal ) ;
} // findPath()

void TwoThreeTree::insert( nodeType * curPtr, slotType tempSlot, nodeType * prePtr ) {

    if ( curPtr == NULL ) {
        cout << "--- NULL! put data in prePtr vector ---\n" ;
        prePtr -> school.push_back( tempSlot ) ;
        sort( prePtr ) ;
        if ( prePtr -> school.size() == 3 ) {
            cout << "--- spilt node ---\n" ;
            split( prePtr, NULL ) ;
        } // end if

        return ;
    } // if

    int i = 0 ;
    bool equal = false ;
    findPath( i, curPtr, tempSlot, equal ) ;
    cout << "--- i = " << i << " ---\n" ;

    if ( !equal && curPtr -> school.size() == 1 ) {
        if ( i == 0 ) {
            cout << "--- go left ---\n" ;
            insert( curPtr -> left, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 1 ) {
            cout << "--- go right ---\n" ;
            insert( curPtr -> right, tempSlot, curPtr ) ;
        } // else if
    } // end if
    else if ( !equal && curPtr -> school.size() == 2 ) {
        if ( i == 0 ) {
            cout << "--- go left ---\n" ;
            insert( curPtr -> left, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 1 ) {
            cout << "--- go middle ---\n" ;
            insert( curPtr -> middle, tempSlot, curPtr ) ;
        } // else if
        else if ( i == 2 ) {
            cout << "--- go right ---\n" ;
            insert( curPtr -> right, tempSlot, curPtr ) ;
        } // else if
    } // end else if

} // end insert()

void TwoThreeTree::split( nodeType * tempPtr, nodeType * childPtr ) {
    cout << "--- start split ---\n" ;

    nodeType * n1, * n2, * p ;
    n1 = tempPtr ;
    n2 = new nodeType ;
    n2 -> school.push_back( tempPtr -> school[2] ) ;
    tempPtr ->school.pop_back() ;

    if ( tempPtr == root ) {
        cout << "--- tempPtr is root ---\n" ;
        p = new nodeType ;
        p -> left = p -> right = p -> middle = p -> temp = NULL ;
    } // end if
    else {
        cout << "--- tempPtr is not root ---\n" ;
        p = tempPtr -> parent ;
    } // end else

    n1 -> parent = n2 -> parent = p ;

    n1 -> left = n1 -> right = n1 -> middle = n1 -> temp = NULL ;
    n2 -> left = n2 -> right = n2 -> middle = n2 -> temp = NULL ;

    p -> school.push_back( tempPtr -> school[1] ) ;
    tempPtr ->school.pop_back() ;
    sort(p) ;

    if( !( tempPtr -> left == NULL && tempPtr -> middle == NULL && tempPtr -> right == NULL) ){




        // tyhis




        cout << "--- tempPtr is no leaf node ---\n" ;
        if ( childPtr == p -> left ) {
            cout << "--- case I ---\n" ;
            n1 -> right =  tempPtr -> temp ;
            n2 -> left = tempPtr -> middle ;
            n2 -> right = tempPtr -> right ;
        } // end if
        else if ( childPtr == p -> middle ) {
            cout << "--- case II ---\n" ;
            n1 -> right =  tempPtr -> left ;
            n2 -> left = tempPtr -> temp ;
            n2 -> right = tempPtr -> right ;
        } // end if
        else if ( childPtr == p -> right ) {
            cout << "--- case III ---\n" ;
            n1 -> right =  tempPtr -> middle ;
            n2 -> left = tempPtr -> right ;
            n2 -> right = tempPtr -> temp ;
        } // end if

        n1 -> left -> parent = n1 -> right -> parent = n1 ;
        n2 -> left -> parent = n2 -> right -> parent = n2 ;
    } // end if

    // if ptr is head
    if( tempPtr == root ){
        cout << "--- tempPtr is root ---\n" ;
        p -> left = n1 ;
        p -> right = n2 ;
        root = p ;
    } // end if
    else if( p -> school.size() == 3 ){
        cout << "--- parent need split ---\n" ;
        p -> temp = n2 ;
        split( p, n1 ) ;
    } // end else if
    else {
        if( tempPtr == p -> left ){
            p -> middle = n2 ;
        } // end if
        else {  // ptr == p -> right
            p -> middle = n1 ;
            p -> right = n2 ;
        } // end else
    } // end else

} // end split()

void TwoThreeTree::sort( nodeType * tempPtr ) {
    cout << "--- start sort ---\n" ;
    for ( int i = 0 ; i < tempPtr -> school.size(); ++i ) {
        cout << tempPtr -> school[i].name ;
    }
    cout << endl ;
    for ( int i = 0 ; i < tempPtr -> school.size() ; ++i ) {
        for ( int j = 0 ; j < tempPtr -> school.size() ; ++j ) {
            if ( tempPtr -> school[i].name < tempPtr -> school[j].name ) {
                auto x = tempPtr -> school[i] ;
                tempPtr -> school[i] = tempPtr -> school[j] ;
                tempPtr -> school[j] = x ;
            } // end if
        } // inner for
    } // outer for

    for ( int i = 0 ; i < tempPtr -> school.size(); ++i ) {
        cout << tempPtr -> school[i].name ;
    }
    cout << endl ;
} // end split()

void TwoThreeTree::destroy( nodeType * tempPtr ) {

    if ( tempPtr != NULL) {
        destroy( tempPtr -> left);
        destroy( tempPtr -> middle);
        destroy( tempPtr -> right);
        delete tempPtr ;
    } // end if
} // destroy()
