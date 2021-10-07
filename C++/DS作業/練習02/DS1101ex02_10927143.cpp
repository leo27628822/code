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
    void print() {  // 運用迭代遍歷
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

    void Search() ;
    bool isPath_() ;

private:


};


void Maze::init() {
    cout << "Input a file number : ( e.g., 201, 202, ...... ) : " ;
    int num ;
    stringstream ss ;
    string filename = "input" ;
    cin >> num ;
    ss << filename << num ; // 將字串和數字一起丟進去字串流
    ss >> filename ;               // 將流內的字串丟回 filename
    filename += ".txt" ;           // 之後再字串結尾加上 .txt
    cout << filename << endl ;
    ifstream ifs( filename, std::ios::in);
    if ( !ifs.is_open() ) {
        cout << "Failed to open file.\n";
    } // if
    else {
        ifs >> x >> y ;               // x : 列 row  || y : 行 column
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

int main() {

    cout << "0. Quit || 1. One goal || 2. More goals\n" ;
    int command ;
    // 0: quit 1: one goal 2: more goals
    while ( cin >> command && command ) {
        Maze mouse ;
        mouse.init() ;
        mouse.print() ;
        cout << "0. Quit || 1. One goal || 2. More goals\n" ;
    } // while

        /*
        cout << "Input a file number : ( e.g., 201, 202, ...... ) : " ;
        int num ;
        stringstream ss ;
        string filename = "input" ;
        cin >> num ;
        ss << filename << num ; // 將字串和數字一起丟進去字串流
        ss >> filename ;               // 將流內的字串丟回 filename
        filename += ".txt" ;           // 之後再字串結尾加上 .txt
        cout << filename << endl ;
        ifstream ifs( filename, std::ios::in);
        if ( !ifs.is_open() ) {
            cout << "Failed to open file.\n";
        } // if
        else {
            ifs >> mouse.x >> mouse.y ;
            mouse.init( ifs, mouse.x, mouse.y ) ;
            ifs.close() ;
        } // else

        ifs.close() ;
        ss.str( "" ) ;
        ss.clear() ;
    } // while

    system( "pause" ) ;
    /*
    stringstream ss ;
    ifstream ifs("input201.txt", std::ios::in);
    if ( !ifs.is_open() ) {
        cout << "Failed to open file.\n";
    } // if
    else {
        int x,y ;
        ifs >> x >> y ;
        for ( int i = 0 ; i < x ; i++ )
        cout << x << y << endl ;
        ifs.close() ;
    }
    ifs.close() ;

    ss.str( "" ) ;
    ss.clear() ;
    return 0;
    */

}

