// Team16_10927124_10927143
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>
#include <ctime>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std ;
int numOfFile = 1 ;
void printTitle() {
    cout << "***********************************************\n" ;
    cout << " On-machine Exercise 05                       *\n" ;
    cout << " Mission 1: External Merge Sort on a Big File *\n" ;
    cout << " Mission 2: Construction of Primary Index     *\n" ;
    cout << "***********************************************\n" ;
} // end PrintTitle

class SecondaryStorge {

protected:
    typedef struct data {
        char putID[10], getID[10] ;
        float weight ;
    } dataType ;
    vector<dataType> dt ;
    string filenum ;

public:


    static bool cmp( data & a, data & b ) {
        return a.weight > b.weight ;
    } // cmp()

    bool input() {
        string filename, tempStr ;
        ifstream file ;
        cout << "Input a file number : " ;
        cin >> filenum ;
        cin.ignore() ;
        filename = "pairs" + filenum + ".bin" ;
        file.open( filename ) ;
        if ( file.is_open() ) {
            dataType dT ;
            vector<dataType> temp ;
            int counts = 0 ;
            while ( file.read( (char*) & dT, sizeof(dT) ) ) {
                temp.push_back( dT ) ;
                counts++ ;
                if ( counts == 200 ) {
                    sort( temp.begin(), temp.end(), cmp ) ;
                    filename =  "sorted" + filenum  + "_" + to_string(numOfFile) + ".bin" ;
                    numOfFile++;
                    ofstream out( filename, ios::binary ) ;
                    for( int i = 0 ; i < temp.size() ; i++ ){
                        out.write( (char*)& temp[i], sizeof(temp[i]) ) ;
                    } // for
                    out.close() ;
                    temp.clear() ;
                    counts = 0 ;
                } // if
            } // while

            if ( !temp.empty() ) {
                cout << "check" ;
                filename =  "sorted" + filenum + "_" + to_string(numOfFile) + ".bin" ;
                numOfFile++;
                ofstream out( filename, ios::binary ) ;
                for( int i = 0 ; i < temp.size() ; i++ ){
                    out.write( (char*)& temp[i], sizeof(temp[i]) ) ;
                } // for
                out.close() ;
                temp.clear() ;
            } // if

            numOfFile--;
            file.close() ;
            return true ;
        } // end if
        else {
            return false ;
        }
    } // readFile()


    void merge() {
        int temp = numOfFile ;
        string filename = "" ;
        int j = 1 ;

        for ( int i = 1 ; i <= numOfFile ; i += 2, j++  ) {
            ifstream file1, file2 ;
            string filename ;
            dataType dT1, dT2 ;
            filename = "sorted" + filenum + "_" + to_string(i) + ".bin" ;
            file1.open( filename ) ;
            if ( file1.is_open() ) {
                filename = "sorted" + filenum +"_" + to_string( numOfFile/2 ) + "_" + to_string(i+1) + ".bin" ;
                file2.open( filename ) ;
                if ( file2.is_open() ) {
                    filename = "sorted" + filenum + "_" + to_string( j ) + ".bin" ;
                    ofstream out( filename)
                    vector<dataType> tempData ;

                    while ( file1.read( (char*) & dT1, sizeof(dT1) ) && file2.read( (char*) & dT2, sizeof(dT2) ) ) {
                        if ( dT1.weight >= dT2.weight ) {
                            if ( !tempData.empty() ) {

                            }
                            else {

                            }
                        }
                        else {

                        }
                    }

                }
                else {
                    // odd filenum
                }
            }
            else {
                cout << "Error!\n" ;
            }


        }



    }

    void output() {
        string filename ;
        filename = "basic" + to_string(numOfFile) + ".bin" ;
        numOfFile++ ;
        ofstream out( filename, ios::binary ) ;

        for( int i = 0 ; i < mergedData.size() ; i++ ){
            out.write( (char*)& mergedData[i], sizeof(mergedData[i]) ) ;
        } // for

        out.close() ;

    } // output()

    void clear() {
        for ( int i = 0 ; i < dt.size() ; i++ ) {
            dt[i].clear() ;
        } // for
        dt.clear() ;
        mergedData.clear() ;
    } // clear()
    */
};


int main() {

    printTitle() ;
    int num ;
    SecondaryStorge ss ;
    ss.input() ;

} // end main
