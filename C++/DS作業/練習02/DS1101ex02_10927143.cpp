// 10927143 王胤迦
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Maze {

public:
    int x,y ;
    vector< vector<char> > v1 ;
    vector< char > v2 ;
    void init() ;
    void print() {  // 運用迭代器遍歷
        vector< vector<char> >::iterator it2 = v1.begin() ;
        while ( it2 != v1.end() ) {
            vector< char >::iterator it = (*it2 ).begin() ;
            while ( it != (*it2).end() ) {
                cout << *it ;
                it++ ;
            } // while

            cout << "\n" ;
            it2++ ;
        } // while
    } // print()

    void Search( int i, int j, bool & find ) ;
    void SearchR( int i, int j, bool & find ) ;
    void Search_For_N( int N, int i, int j, bool & find) ;

};


void Maze::init() {
    cout << "Input a file number : ( e.g., 201, 202, ...... ) : " ;
    int num ;
    stringstream ss ;
    string filename = "input" ;
    cin >> num ;
    ss << filename << num ;        // 將字串和數字一起丟進去字串流
    ss >> filename ;               // 將流內的字串丟回 filename
    filename += ".txt" ;           // 之後再字串結尾加上 .txt
    cout << filename << endl ;
    ifstream ifs( filename, std::ios::in);
    if ( !ifs.is_open() ) {
        cout << "Failed to open file.\n";
    } // if
    else {
        ifs >> x >> y ;            // x : 列 row  || y : 行 column
        for ( int i = 0 ; i < y ; i++ ) {
            for ( int j = 0 ; j < x ; j++ ) {
                char ch ;
                ifs >> ch ;
                v2.push_back( ch ) ;
            } // for

            v1.push_back( v2 ) ;
            v2.clear() ;
        } // for
    } // else

    ifs.close() ;

} // init()


void Maze::Search( int i, int j, bool & find) {

    if ( i < 0 || j < 0 || j >= x || i >= y ||  !( v1[i][j] == 'E' || v1[i][j] == 'G' ) ) return ; // 避免超過vector的大小
    if ( v1[i][j] == 'G' ) { // check goal reached?
        find = true ;
        return ;
    } // if()

    v1[i][j] = 'V' ;    // mark visited
    if ( !find ) Search( i, j+1, find ) ;  // go right
    if ( !find ) Search( i, j-1, find ) ;  // go left
    if ( !find ) Search( i+1, j, find ) ;  // go down
    if ( !find ) Search( i-1, j, find ) ;  // go up 
    
} // Search()

void Maze::SearchR( int i, int j, bool & find) {

    if ( i < 0 || j < 0 || j >= x || i >= y ||  !( v1[i][j] == 'E' || v1[i][j] == 'G' ) ) return ; // 避免超過vector的大小
    if ( v1[i][j] == 'G' ) { // check goal reached?
        find = true ;
        return ;
    } // if()

    v1[i][j] = 'R' ;    // mark route
    if ( !find ) SearchR( i, j+1, find ) ;  // go right
    if ( !find ) SearchR( i, j-1, find ) ;  // go left
    if ( !find ) SearchR( i+1, j, find ) ;  // go down
    if ( !find ) SearchR( i-1, j, find ) ;  // go up 
    if ( !find ) v1[i][j] = 'E' ;
    
} // SearchR()

void Maze::Search_For_N( int N, int i, int j, bool & find) {
    return ;
} // Search_For_N()

int main() {

    cout << "0. Quit || 1. One goal || 2. More goals\n" ;
    int command ;
    bool find = false ;
    // 0: quit 1: one goal 2: more goals
    while ( cin >> command && command ) {
        Maze mouse ;
        mouse.init() ;
        mouse.print() ;
        cout << endl ;
        mouse.Search( 0,0, find ) ;
        mouse.print() ;
        cout << endl ;
        cout << "0. Quit || 1. One goal || 2. More goals\n" ;
        find = false ;
    } // while

    system( "pause" ) ;

} // main()

