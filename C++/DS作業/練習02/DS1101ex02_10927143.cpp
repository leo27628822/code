// 10927143 王胤迦
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int goalx[10] = {0}, goaly[10] = {0} ;
int xi = 0, yi = 0 ;

class Maze {

public:
    int x,y ;
    vector< vector<char> > v1 ;
    vector< char > v2 ;
    bool init( string filename ) ;
    void print() {  // 運用迭代器遍歷
        vector< vector<char> >::iterator it2 = v1.begin() ;
        while ( it2 != v1.end() ) {
            vector< char >::iterator it = (*it2 ).begin() ;
            while ( it != (*it2).end() ) {
                cout << *it << " " ;
                it++ ;
            } // while

            cout << "\n" ;
            it2++ ;
        } // while

        cout << "\n" ;
    } // print()

    void Search( int i, int j, bool & find ) ;
    void SearchR( int i, int j, bool & find ) ;
    void Search_For_N( int & N, int i, int j, bool & find) ;
    void Search_For_N_R( int & N, int i, int j, bool & find) ;
    void Get_Next_Pt( int i, int j, int ni, int nj, int dir ) ;
};


bool Maze::init( string filename ) {
    v1.clear() ;
    xi = yi = 0 ;
    for ( int i = 0 ; i < 10 ; i++ ) {
        goalx[i] = 0 ;
        goaly[i] = 0 ;
    } // for

    ifstream ifs( filename, std::ios::in);
    if ( !ifs.is_open() ) {
        cout << "Failed to open file.\n";
        return false ;
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
    return true ;

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
    if ( !find ) SearchR( i+1, j, find ) ;  // go down
    if ( !find ) SearchR( i, j-1, find ) ;  // go left
    if ( !find ) SearchR( i-1, j, find ) ;  // go up 
    if ( !find ) v1[i][j] = 'E' ;
    
} // SearchR()

void Maze::Search_For_N( int & N, int i, int j, bool & find ) {
    if ( i < 0 || j < 0 || j >= x || i >= y ||  !( v1[i][j] == 'E' || v1[i][j] == 'G' ) ) return ; // 避免超過vector的大小
    if ( v1[i][j] == 'G' ) { // check goal reached?
        // cout << i << " " << j << " " << N << endl ;
        int *p = std::find( goalx, goalx + 9, i ), *q = std::find( goaly, goaly + 9, j ) ;
        if ( p == goalx + 9 || q == goaly + 9 ) N-- ;
        goalx[xi++] = i ;
        goaly[yi++] = j ;
        if ( !N ) {
            find = true ;
            return ;
        } // if
    } // if()

    if ( v1[i][j] != 'G' ) v1[i][j] = 'V' ;    // mark visited but avoid 'G'
    if ( !find ) Search_For_N( N, i, j+1, find ) ;  // go right
    if ( !find ) Search_For_N( N, i, j-1, find ) ;  // go left
    if ( !find ) Search_For_N( N, i-1, j, find ) ;  // go up 
    if ( !find ) Search_For_N( N, i+1, j, find ) ;  // go down
    
} // Search_For_N()

void Maze::Search_For_N_R( int & N, int i, int j, bool & find) {
    //*
    
    if ( i < 0 || j < 0 || j >= x || i >= y ||  !( v1[i][j] == 'E' || v1[i][j] == 'G' ) ) return ; // 確認下一步是否合法和避免超過vector的大小
    
    if ( v1[i][j] == 'G' ) { // check goal reached?
        int *p = std::find( goalx, goalx + 9, i ), *q = std::find( goaly, goaly + 9, j ) ;     // 確認找到的 G 不重複
        if ( p == goalx + 9 || q == goaly + 9 ) {
            cout << i << " " << j << " " << v1[i][j] << endl;
            N-- ;
            goalx[xi++] = i ;
            goaly[yi++] = j ;
            find  = true ;
        }

        if ( N == 0 ) {
            find = true ;
            return ;
        } // if
    } // if
    
    if ( v1[i][j] != 'G' ) v1[i][j] = 'R' ;           // mark route
    if ( N!=0 ) {
        Search_For_N_R( N, i, j+1, find ) ;  // go right
        Search_For_N_R( N, i, j-1, find ) ;  // go left
        Search_For_N_R( N, i-1, j, find ) ;  // go up 
        Search_For_N_R( N, i+1, j, find ) ;  // go down 
    } // if

    if ( !find && v1[i][j] != 'G' ) v1[i][j] = 'E' ;
    //cout << i << " " << j << " " << v1[i][j] << endl ;
    //*/
} // Search_For_N_R()

int main() {

    cout << "0. Quit || 1. One goal || 2. More goals\n" ;
    int command ;
    bool find = false ;
    // 0: quit 1: one goal 2: more goals
    while ( cin >> command && command ) {
        if ( command == 1) {
            cout << "Input a file number : ( e.g., 201, 202, ...... ) : " ;
            int num ;
            stringstream ss ;
            string filename = "input" ;
            cin >> num ;
            ss << filename << num ;        // 將字串和數字一起丟進去字串流
            ss >> filename ;               // 將流內的字串丟回 filename
            filename += ".txt" ;           // 之後再字串結尾加上 .txt
            Maze mouse ;
            if ( mouse.init( filename ) ) {
                // mouse.print() ;
                mouse.Search( 0,0, find ) ;
                mouse.print() ;
                find = false ;
                mouse.init( filename ) ;
                mouse.SearchR( 0, 0, find) ;
                if ( find ) mouse.print() ;
            } // if
        } // if
        else if ( command == 2 ) {
            cout << "Input a file number : ( e.g., 201, 202, ...... ) : " ;
            int num ;
            stringstream ss ;
            string filename = "input" ;
            cin >> num ;
            ss << filename << num ;        // 將字串和數字一起丟進去字串流
            ss >> filename ;               // 將流內的字串丟回 filename
            filename += ".txt" ;           // 之後再字串結尾加上 .txt
            Maze mouse ;
            if ( mouse.init( filename ) ) {
                cout << "Number of G (goals) : " ;
                cin >> num ;
                if ( num == 1 ) {
                    mouse.Search( 0,0, find ) ;
                    mouse.print() ;
                    find = false ;
                    mouse.init( filename ) ;
                    mouse.SearchR( 0, 0, find) ;
                    if ( find ) mouse.print() ;
                } // if
                else if ( num >= 2 ) {
                    int temp = num ;
                    mouse.Search_For_N( num, 0, 0, find ) ;
                    num = temp ;
                    mouse.print() ;
                    find = false ;
                    mouse.init( filename ) ;
                    mouse.Search_For_N_R( num, 0, 0, find ) ;
                    if ( 1 ) mouse.print() ;
                } // else if
            } // if
        } // else if

        cout << "0. Quit || 1. One goal || 2. More goals\n" ;
        find = false ;
    } // while

} // main()

