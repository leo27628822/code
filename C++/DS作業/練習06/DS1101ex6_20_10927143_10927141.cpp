// DS1101ex6_20_10927143_10927141
# include <iostream>
# include <string>
# include <algorithm>
# include <fstream>
# include <vector>
# include <sstream>
# include <math.h>

using namespace std;

void PrintTitle() ;

class BST {

private:
    typedef struct node {
        string name ;
        int hp ;
        node * left ;
        node * right ;
    } * nodePtr ;
    nodePtr root ;
    int height ;

public:
    void insert( string name, int hp, nodePtr tempPtr ) ;
    BST() { root = NULL ; height = 0 ; } // end BST
    nodePtr getRoot() { return root ; }
    int Height( nodePtr tempPtr ) ;
    int getHeight() { height = Height( root ) ; return height ; } // end getHeight
    void getMin( nodePtr tempPtr, string & name ) ;
    void getMax( nodePtr tempPtr, string & name ) ;
    void clearUp() ;
};

class MaxHeap {

private:
    int height ;
    typedef struct dT{
        string name, type1 ;
        int no, hp, atk, def ;
    }dataType ;
    vector<dataType> mh ;

public:
    MaxHeap() { height = 0 ; mh.clear() ; } // end MaxHeap
    void heapInsert( int no, int hp, int atk, int def, string name, string type1 ) ;
    void clearUp() { height = 0 ; mh.clear() ;} // end clearUp
    int getHeight() { Height() ; return height ; } // end getHeight
    void Height() ;
    void getLeftMost() ;
    void getMin() ;
    void showAll() ;
    void printLeftMost() ;
    void printBottom() ;
};

class pokemonList {

private:
    typedef struct pT{
        string name, type1 ;
        int no, hp, atk, def ;
    }pokemonType ;
    vector<pokemonType> pSet ;
    BST bst ;
    MaxHeap mh ;

public:
    bool isEmpty() ;
    bool readFile() ;
    void showAll() ;
    void buildBST() ;
    void buildMaxHeap() ;
    void buildMaxHeap2() ;
    void clearUp() ;
    int getHeight() { return bst.getHeight() ; } // end getHeight
    int getHeight_mh() { return mh.getHeight() ; } // end getHeight_mh
    ~pokemonList() { clearUp() ; }
    void printMin() ;
    void printMax() ;
    void printMhLeftMost() { mh.printLeftMost() ; } // end printMhLeftMost
    void printMhBottom() { mh.printBottom() ; } // end printMhBottom
    void reheapUp( int i ) ;
}; // class pokemonList

int main() {
    int command ;
    bool done = false ;
    pokemonList pL ;
    PrintTitle() ;
    while ( cin >> command ) {
        if ( command == 0 ) break ;
        else if ( command == 1 ) {
            pL.clearUp() ;
            if ( pL.readFile() ) {
                done = true ;
                pL.showAll() ;
                pL.buildBST() ;
                cout << "HP tree height = " << pL.getHeight() << "\n\n" ;
                pL.printMin() ;
                pL.printMax() ;
            } // end if
        } // end else if
        else if ( command == 2 ) {
            if ( !done ) cout << "\n----- Execute Mission 1 first! -----\n\n" ;
            else {
                int method ;
                cout << "\nWhich version do you want?\n(1: method One 2: method Two ) : " ;
                cin >> method ;
                if ( method == 2 ) pL.buildMaxHeap2() ;
                else if ( method == 1 ) {
                    pL.buildMaxHeap() ;
                    cout << "HP tree height = " << pL.getHeight_mh() << "\n" ;
                    pL.printMhLeftMost() ;
                    pL.printMhBottom() ;
                } // end else if
                else cout << "\nmethod" << method << " does not exist!\n\n" ;
            } // end else
        } // end else if
        else cout << "\nCommand does not exist!\n" ;
        PrintTitle() ;
    } // end while

    system("pause") ;
} // end main

void PrintTitle() {
    cout << "****** Pokemon Tree and Heap ******\n" ;
    cout << "* 0. QUIT                         *\n" ;
    cout << "* 1. Read a file to build BST     *\n" ;
    cout << "* 2. Transform it into Max Heap   *\n" ;
    cout << "***********************************\n" ;
    cout << "Input a choice(0, 1, 2): " ;
} // end PrintTitle

bool pokemonList::isEmpty() {
    return pSet.empty() ;
} // emd isEmpty

bool pokemonList::readFile() {
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

            pokemonType tempPT ;
            tempPT.no   =   stoi( words[0] ) ;
            tempPT.name =   words[1] ;
            tempPT.type1=   words[2] ;
            tempPT.hp   =   stoi( words[5] ) ;
            tempPT.atk  =   stoi( words[6] ) ;
            tempPT.def  =   stoi( words[7] ) ;
            pSet.push_back( tempPT ) ;
        } // end while

        file.close() ;
        return true ;
    } // end else
} // end readFile

void pokemonList::showAll() {
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    for ( int i = 0 ; i < pSet.size() ; i++ ) {
        if ( i < 9 ) cout << "[ " << i+1 << "]\t" ;
        else cout << "[" << i+1 << "]\t" ;
        cout << pSet[i].no << "\t" << pSet[i].name ;
        if ( pSet[i].name.length() < 8 ) cout << "\t\t\t" ;
        else if ( pSet[i].name.length() < 16 ) cout << "\t\t" ;
        else cout << "\t" ;
        cout << pSet[i].type1 ;
        if ( pSet[i].type1.length() < 8 ) cout << "\t\t" ;
        else cout << "\t" ;
        cout << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << "\n" ;
    } // end for
    cout << "\n" ;
} // end showAll

void pokemonList::clearUp() {
    pSet.clear() ;
    bst.clearUp() ;
    mh.clearUp() ;
} // end clestUp

void BST::clearUp() {
    height = 0 ;
    root = NULL ;
} // end clearUp

void pokemonList::buildBST() {
    for ( int i = 0 ; i < pSet.size() ; i++ ) {
        bst.insert( pSet[i].name, pSet[i].hp, bst.getRoot() ) ;
    } // end for
} // end buildBST

void pokemonList::buildMaxHeap() {
    mh.clearUp() ;
    for ( int i = 0 ; i < pSet.size() ; i++ ) {
        mh.heapInsert( pSet[i].no, pSet[i].hp, pSet[i].atk, pSet[i].def, pSet[i].name, pSet[i].type1 ) ;
    } // end for
    mh.showAll() ;
} // end buildMaxHeap

void pokemonList::buildMaxHeap2() {
    for ( int i = (pSet.size()-2)/2 ; i >= 0 ; i-- ) {
       reheapUp( i ) ;
    } // end for

    showAll() ;

    int mhHeight = 0 ;

    int n = pSet.size() ;

    while ( n > 0 ) {
        n /= 2 ;
        mhHeight++ ;
    } // end while

    cout << "HP tree height = " << mhHeight << "\n\n" ;

    cout << "Leftmost node:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    int i = pow(2,mhHeight) - pow(2,mhHeight-1) - 1 ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << pSet[i].no << "\t" << pSet[i].name ;
    if ( pSet[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( pSet[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].type1 ;
    if ( pSet[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << "\n\n" ;

    cout << "Bottom:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    i = pSet.size() - 1 ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << pSet[i].no << "\t" << pSet[i].name ;
    if ( pSet[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( pSet[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].type1 ;
    if ( pSet[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << "\n\n" ;
} // end buildMaxHeap2

void pokemonList::reheapUp( int i ) {
        int lchild = i*2+1, rchild = i*2+2 ;
        vector <pokemonType> temp ;
        if ( lchild < pSet.size() ) {
            if ( rchild < pSet.size() )  {
                if ( pSet[lchild].hp >= pSet[rchild].hp && pSet[i].hp < pSet[lchild].hp ) {
                    temp.push_back( pSet[i] ) ;
                    pSet[i] = pSet[lchild] ;
                    pSet[lchild] = temp[0] ;
                    temp.pop_back() ;
                    reheapUp(lchild) ;
                    // swap
                } // end if
                else if ( pSet[i].hp < pSet[rchild].hp ) {
                    temp.push_back( pSet[i] ) ;
                    pSet[i] = pSet[rchild] ;
                    pSet[rchild] = temp[0] ;
                    temp.pop_back() ;
                    reheapUp(rchild) ;
                    // swap
                } // end else if
            } // end if
            else if ( pSet[i].hp < pSet[lchild].hp ) {
                temp.push_back( pSet[i] ) ;
                pSet[i] = pSet[lchild] ;
                pSet[lchild] = temp[0] ;
                temp.pop_back() ;
                reheapUp(lchild) ;
                // swap
            } // end else
        } // end if

} // reheapUp

void BST::insert( string name,int hp, nodePtr tempPtr ) {

    nodePtr newNode = new node ;
    newNode -> name = name ;
    newNode -> hp = hp ;
    newNode -> left = newNode -> right = NULL ;
    if ( root == NULL ) {
        root = newNode ;
        return ;
    } // end if
    if ( hp >= tempPtr -> hp ) {
        if ( tempPtr -> right != NULL ) insert( name, hp, tempPtr -> right ) ;
        else tempPtr -> right = newNode ;
    } // end else
    else {
        if ( tempPtr -> left != NULL ) insert( name, hp, tempPtr -> left ) ;
        else tempPtr -> left = newNode ;
    } // end else
} // end insert

int BST::Height( nodePtr tempPtr ) {
    int lh, rh ;
    if ( tempPtr == NULL ) return 0 ;
    else {
        lh = Height( tempPtr -> left ) ;
        rh = Height( tempPtr -> right ) ;
        return ( lh > rh ? lh+1 : rh+1 ) ;
    } // end else
} // end getHeight

void pokemonList::printMin() {
    string name ;
    bst.getMin( bst.getRoot(), name ) ;
    int i ;
    for ( i = 0 ; i < pSet.size() && pSet[i].name != name ; i++ ) ;
    cout << "Leftmost node:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << pSet[i].no << "\t" << pSet[i].name ;
    if ( pSet[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( pSet[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].type1 ;
    if ( pSet[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << "\n\n" ;
} // end printMin

void pokemonList::printMax() {
    string name ;
    bst.getMax( bst.getRoot(), name ) ;
    int i ;
    for ( i = 0 ; i < pSet.size() && pSet[i].name != name ; i++ ) ;
    cout << "Rightmost node:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << pSet[i].no << "\t" << pSet[i].name ;
    if ( pSet[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( pSet[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].type1 ;
    if ( pSet[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << "\n\n" ;
} // end printMax

void BST::getMin( nodePtr tempPtr, string & name ) {
    if ( tempPtr -> left == NULL ) name = tempPtr -> name ;
    else getMin( tempPtr -> left, name ) ;
} // end getMax

void BST::getMax( nodePtr tempPtr, string & name ) {
    if ( tempPtr -> right == NULL ) name = tempPtr -> name ;
    else getMax( tempPtr -> right, name ) ;
} // end getMax

void MaxHeap::heapInsert( int no, int hp, int atk, int def, string name, string type1 ) {
    dataType data ;
    data.no = no ;
    data.hp = hp ;
    data.atk = atk ;
    data.def = def ;
    data.name = name ;
    data.type1 = type1 ;
    mh.push_back( data ) ;
    if ( mh.size() > 1) {
        int index = mh.size() - 1 ;
        for ( int parent = (index-1)/2 ; parent >= 0 ; parent = (index-1)/2 ) {
            if ( mh[index].hp > mh[parent].hp ) {
                dataType temp = mh[index] ;
                mh[index] = mh[parent] ;
                mh[parent] = temp ;
            } // end if
            else break ;

            index = parent ;
        } // end for
    } // end if
} // end heapInsert

void MaxHeap::Height() {
    int n = mh.size() ;
    height = 0 ;
    if ( n == 0 ) height = 0 ;
    else if ( n == 1 ) height = 1 ;
    else
        while ( n > 0 ) {
            n /= 2 ;
            height++ ;
        } // end while
} // end Height

void MaxHeap::showAll() {
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    for ( int i = 0 ; i < mh.size() ; i++ ) {
        if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
        else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
        else cout << "[" << i+1 << "]\t" ;
        cout << mh[i].no << "\t" << mh[i].name ;
        if ( mh[i].name.length() < 8 ) cout << "\t\t\t" ;
        else if ( mh[i].name.length() < 16 ) cout << "\t\t" ;
        else cout << "\t" ;
        cout << mh[i].type1 ;
        if ( mh[i].type1.length() < 8 ) cout << "\t\t" ;
        else cout << "\t" ;
        cout << mh[i].hp << "\t" << mh[i].atk << "\t" << mh[i].def << "\n" ;
    } // end for
    cout << "\n" ;
} // end showAll

void MaxHeap::printLeftMost() {
    cout << "Leftmost node:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    int i = pow(2,height) - pow(2,height-1) - 1 ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << mh[i].no << "\t" << mh[i].name ;
    if ( mh[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( mh[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << mh[i].type1 ;
    if ( mh[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << mh[i].hp << "\t" << mh[i].atk << "\t" << mh[i].def << "\n" ;
} // end printBottom

void MaxHeap::printBottom() {
    cout << "Bottom:\n" ;
    cout << "\t#\tName\t\t\tType 1\t\tHP\tAttack\tDefense\n" ;
    int i = mh.size() - 1 ;
    if ( i < 9 ) cout << "[  " << i+1 << "]\t" ;
    else if ( i < 99 ) cout << "[ " << i+1 << "]\t" ;
    else cout << "[" << i+1 << "]\t" ;
    cout << mh[i].no << "\t" << mh[i].name ;
    if ( mh[i].name.length() < 8 ) cout << "\t\t\t" ;
    else if ( mh[i].name.length() < 16 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << mh[i].type1 ;
    if ( mh[i].type1.length() < 8 ) cout << "\t\t" ;
    else cout << "\t" ;
    cout << mh[i].hp << "\t" << mh[i].atk << "\t" << mh[i].def << "\n" ;
} // end printBottom

