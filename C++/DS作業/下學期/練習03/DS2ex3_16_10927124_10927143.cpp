// Team16_10927124_10927143
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>

using namespace std ;

string filenum ;

void printTitle() {
    cout << "*****    Hash Table Builder    *****\n" ;
    cout << "**  0. Quit                       **\n" ;
    cout << "**  1. Linear probing             **\n" ;
    cout << "**  2. Double probing             **\n" ;
    cout << "************************************\n" ;
    cout << "Input a command(0, 1, 2): " ;
} // end PrintTitle

class Hash {

private:
    typedef struct data {

        char id[10], name[10] ;
        unsigned char score[6] ;
        float average ;

    } dataType ;
    vector<dataType> data ;

public:

    void Input() {
        string filename, tempStr ;
        ifstream file ;
        cout << "Input a file number : " ;
        cin >> filenum ;
        cin.ignore() ;
        filename = "input" + filenum + ".bin" ;
        file.open( filename ) ;
        if ( file.is_open() ) {
            cout << "file is open!\n" ;
            file.close() ;
        } // end if
        else {
            filename = "input" + filenum + ".txt" ;
            if ( readtxt( filename ) ) {
                transferToBinary( filename ) ;
            } // if
            else {
                cout << "\n### " << filename << " does not exist! ###\n\n" ;
            } // else
        } // end else

    } // readFile()

    bool readtxt( string filename ) {
        ifstream file ;
        string tempStr ;
        if ( !file.is_open() ) {
            return false ;
        } // end if
        else {
            while ( !file.eof() ) {
                getline( file, tempStr ) ;
                if ( file.fail() ) {
                    break ;
                } // if

                string delimiter = "\t";
                vector<string> words ;
                size_t pos ;
                while ( ( pos = tempStr.find(delimiter) ) != string::npos ) {
                    words.push_back( tempStr.substr(0, pos) ) ;
                    tempStr.erase( 0, pos + delimiter.length() ) ;
                } // end while

                dataType dT ;
                strcpy( dT.id, words[0].c_str() ) ;
                strcpy( dT.name, words[1].c_str() ) ;
                for ( int i = 0 ; i < 6 ; i++ ) {
                    dT.score[i] = (unsigned char)stoi( words[i+2] ) ;
                } // for

                dT.average = stof( words[8] );

                dt.push_back( dT ) ;
                dT.clear() ;
            } // end while

            file.close() ;

            return true ;
        } // end else
    } // readtxt()

    void clear() {
        data.clear() ;
    } // clear()

};

int main() {

    printTitle() ;
    Hash hh ;

    int command ;
    while ( cin >> command && command ) {

        hh.Input() ;

        if ( command == 1 ) {
            hh.
        } // if
        else if ( command == 2 ) {

        } // else if
        else {
            cout << "\nCommand does not exist!\n" ;
        } // else

        printTitle() ;
        hh.clear() ;
    } // while

    return 0 ;
}
