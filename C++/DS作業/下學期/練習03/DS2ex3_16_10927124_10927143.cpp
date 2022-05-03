// Team16_10927124_10927143
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>
#include <iomanip>
#include <cmath>
#include <time.h>

using namespace std ;

double START, END ;

string filenum ;

void printTitle() {
    cout << "*****    Hash Table Builder    *****\n" ;
    cout << "**  0. Quit                       **\n" ;
    cout << "**  1. Linear probing             **\n" ;
    cout << "**  2. Double probing             **\n" ;
    cout << "**  3. Quadratic probing          **\n" ;
    cout << "************************************\n" ;
    cout << "Input a command(0, 1, 2, 3): " ;
} // end PrintTitle

class FileProcess {

protected:
    typedef struct data {
        char id[10], name[10] ;
        unsigned char score[6] ;
        float average ;
    } dataType ;
    vector<dataType> dt ;

public:

    bool input() {
        string filename, tempStr ;
        ifstream file ;
        cout << "Input a file number : " ;
        cin >> filenum ;
        cin.ignore() ;
        filename = "input" + filenum + ".bin" ;
        file.open( filename ) ;
        if ( file.is_open() ) {
            file.close() ;
            readbin( filename ) ;

        } // end if
        else {
            file.close() ;
            filename = "input" + filenum + ".txt" ;
            if ( readtxt( filename ) ) {
                transferToBinary( filename ) ;
            } // if
            else {
                cout << "\n### " << filename << " does not exist! ###\n\n" ;
                return false ;
            } // else
        } // end else

        return true ;
    } // readFile()

    bool readtxt( string filename ) {
        ifstream file ;
        string tempStr ;
        file.open( filename ) ;
        if ( !file.is_open() ) {
            return false ;
        } // end if
        else {

            while ( !file.eof() ) {
                getline( file, tempStr ) ;
                if ( file.fail() ) {
                    break ;
                } // if

                vector<string> words ;
                string delimiter = "\t";
                size_t pos ;

                while ( ( pos = tempStr.find(delimiter) ) != string::npos ) {
                    words.push_back( tempStr.substr(0, pos) ) ;
                    tempStr.erase( 0, pos + delimiter.length() ) ;
                } // end while
                words.push_back( tempStr.substr(0, pos) ) ;

                dataType dT ;
                strcpy( dT.id, words[0].c_str() ) ;
                strcpy( dT.name, words[1].c_str() ) ;
                for ( int i = 0 ; i < 6 ; i++ ) {
                    dT.score[i] = (unsigned char)stoi( words[i+2] ) ;
                } // for
                dT.average = stof( words[8] );

                dt.push_back( dT ) ;
                words.clear() ;
            } // end while

            file.close() ;

            return true ;
        } // end else
    } // readtxt()

    void transferToBinary( string filename ) {
        filename = "input" + filenum + ".bin" ;
        ofstream out( filename, ios::binary ) ;
        for ( int i = 0 ; i < dt.size() ; i++ ) {
            out.write( (char*)&dt[i], sizeof(dt[i]) ) ;
        } // while
        out.close() ;
    } // transferToBinary

    void readbin( string filename ) {
        dataType dT ;
        ifstream in( filename, ios::in|ios::binary) ;
        while ( in.read( (char*)&dT, sizeof(dT) ) ) {
            dt.push_back( dT ) ;
        } // while
        in.close() ;
    } // readbin()
};

class Hash:public FileProcess {

protected:
    typedef struct content {
        string id, name ;
        int score[6] ;
        float average ;
        bool exists = false ;
        int hvalue ;
    } hashType ;
    vector<hashType> linearHash ;
    float success = 0 ;

public:

    int getSize() {
        return dt.size() ;
    } // getSize()

    void clear() {
        while ( !linearHash.empty() ) {
            linearHash.pop_back() ;
        } // while
        linearHash.clear() ;
        while ( !dt.empty() ) {
            dt.pop_back() ;
        } // while
        dt.clear() ;
        success = 0 ;
    } // clear()

    unsigned long long findPrime( int n ) {

        unsigned long long i,j;
        i = ( unsigned long long ) n;
        while( true ){
            i++;
            for ( j = 2 ; j <= i ; j++ ) {
                if( i == j ) {
                    return i;
                } // if
                if( i % j == 0 ) {
                    break;
                } // if
            } // for
        } // while
    } // findPrime()

    void build() {
        unsigned long long size = findPrime( ( (int)(dt.size() * 1.2) ) ) ;

        linearHash.resize( size ) ;

        for ( int i = 0 ; i < dt.size() ; i++ ) {
            hashType ht ;
            ht.id = dt[i].id ;
            ht.name = dt[i].name ;
            for( int j = 0 ; j < 6 ; j++ ) {
                ht.score[j] = (int)dt[i].score[j] ;
            } // for
            ht.average = dt[i].average ;
            int key = hash( dt[i].id ) ;
            ht.hvalue = key ;
            ht.exists = true ;

            for ( ; linearHash[key].exists != false ; key = (key+1) % linearHash.size(), success++ )
            ;
            success++ ;
            linearHash[key] = ht ;
        } // for
    } // build()

    int hash( string key ) {
        unsigned long long sum = 1 ;
        for ( int i = 0 ; i < key.size() ; i++ ) {
            sum *= (int)key[i] ;
        }
        return sum % linearHash.size() ;
    } // hash()

    void calculate() {
        cout << "\n\nHash Table X has been created.\n\n" ;

        float unsuccess = 0 ;

        for( int i = 0 ; i < linearHash.size() ; i++ ){
            int temp = i ;

            while( linearHash[temp].exists == true ){
                temp++ ;
                unsuccess++ ;
                if( temp == linearHash.size() ) temp = 0 ;
            } // while

        } // for

        cout << "unsuccessful search: " ;
        cout << fixed << setprecision(4) << unsuccess / linearHash.size() ;
        cout << " comparisons on a average.\n\n" ;

        cout << "successful search: " ;
        cout << success / dt.size() ;
        cout << " comparisons on a average.\n\n";

    } // calculate()

    void writeData() {
        ofstream file ;
        file.open( "linear" + filenum + ".txt" ) ;

        file << "--- Hash Table X --- (linear probing)\n" ;

        for( int i = 0 ; i < linearHash.size() ; i++ ){

            if( linearHash[i].exists == false ){
                file << "[" << i << "]" << endl ;
            } // if
            else{
                file << "[" << i << "]" ;
                file << "\t" << linearHash[i].hvalue ;
                file << "\t" << linearHash[i].id ;
                file << "\t" << linearHash[i].name ;
                file << "\t" << linearHash[i].average << "\n" ;
            } // else
        } // end output

        file.close() ;

    } // writeData

};

class DHash:public FileProcess {

private:
    typedef struct content {
        string id, name ;
        int score[6] ;
        float average ;
        bool exists = false ;
        int hvalue ;
    } hashType ;
    vector<hashType> doubleHash ;
    float success = 0 ;
    long long highStep ;

public:

    void clear() {
        while(!dt.empty()) {
            dt.pop_back() ;
        } // while
        dt.clear() ;
        while(!doubleHash.empty()){
            doubleHash.pop_back() ;
        } // while
        doubleHash.clear() ;
        success = 0 ;
        highStep = 0 ;
    } // clear()

    unsigned long long findPrime( int n ) {
        unsigned long long i,j;
        i = ( unsigned long long ) n;
        while( true ){
            i++;
            for ( j = 2 ; j <= i ; j++ ) {
                if( i == j ) {
                    return i;
                } // if
                if( i % j == 0 ) {
                    break;
                } // if
            } // for
        } // while
    } // findPrime()

    int hash( string key ) {
        unsigned long long sum = 1 ;
        for ( int i = 0 ; i < key.size() ; i++ ) {
            sum *= (int)key[i] ;
        }
        return sum % doubleHash.size() ;
    } // hash()

    void build() {
        unsigned long long size = findPrime( ( (int)(dt.size() * 1.2) ) ) ;

        doubleHash.resize( size ) ;

        highStep = findPrime( dt.size() / 3 ) ;
        for ( int i = 0 ; i < dt.size() ; i++ ) {
            hashType ht ;
            ht.id = dt[i].id ;
            ht.name = dt[i].name ;
            for( int j = 0 ; j < 6 ; j++ ) {
                ht.score[j] = (int)dt[i].score[j] ;
            } // for
            ht.average = dt[i].average ;
            int steps = step( dt[i].id  ) ;
            int key = hash( dt[i].id ) ;
            ht.hvalue = key ;
            ht.exists = true ;

            for ( ; doubleHash[key].exists != false ; key = ( key + steps ) % doubleHash.size(), success++ )
            ;
            success++ ;
            doubleHash[key] = ht ;
        } // for
    } // build()

    long long step( string key ) {
        unsigned long long sum = 1 ;

        for( int i = 0 ; i < key.size() ; i++ )
            sum *= (int)key[i] ;

        return highStep - ( sum % highStep ) ;
    } // step()

    void calculate() {
        cout << "\n\nHash Table Y has been created.\n\n" ;

        cout << "successful search: " ;
        cout << fixed << setprecision(4) << success / dt.size() ;
        cout << " comparisons on a average.\n\n";
    } // calculate()

    void writeData() {
        ofstream file ;
        file.open( "double" + filenum + ".txt" ) ;

        file << "--- Hash Table Y --- (double hash)\n" ;

        for( int i = 0 ; i < doubleHash.size() ; i++ ) {

            if( doubleHash[i].exists == false ){
                file << "[" << i << "]" << endl ;
            } // if
            else{
                file << "[" << i << "]" ;
                file << "\t" << doubleHash[i].hvalue ;
                file << "\t" << doubleHash[i].id ;
                file << "\t" << doubleHash[i].name ;
                file << "\t" << doubleHash[i].average << "\n" ;
            } // else
        } // end output

        file.close() ;
    } // writeData
};

class QHash:public FileProcess {
private:
    typedef struct content {
        string id, name ;
        int score[6] ;
        float average ;
        bool exists = false ;
        int hvalue ;
    } hashType ;
    vector<hashType> quadraticHash ;
    float success = 0 ;

public:
    int getSize() {
        return dt.size() ;
    } // getSize()

    int hash( string key ) {
        unsigned long long sum = 1 ;
        for ( int i = 0 ; i < key.size() ; i++ ) {
            sum *= (int)key[i] ;
        }
        return sum % quadraticHash.size() ;
    } // hash()

    unsigned long long findPrime( int n ) {
        unsigned long long i,j;
        i = ( unsigned long long ) n;
        while( true ){
            i++;
            for ( j = 2 ; j <= i ; j++ ) {
                if( i == j ) {
                    return i;
                } // if
                if( i % j == 0 ) {
                    break;
                } // if
            } // for
        } // while
    } // findPrime()

    void clear() {
        while ( !quadraticHash.empty() ) {
            quadraticHash.pop_back() ;
        } // while
        quadraticHash.clear() ;
        while ( !dt.empty() ) {
            dt.pop_back() ;
        } // while
        dt.clear() ;
        success = 0 ;
    } // clear()

    void build() {
        unsigned long long size = findPrime( ( (int)(dt.size() * 1.2) ) ) ;

        quadraticHash.resize( size ) ;
        for ( int i = 0 ; i < dt.size() ; i++ ) {
            hashType ht ;
            ht.id = dt[i].id ;
            ht.name = dt[i].name ;
            for( int j = 0 ; j < 6 ; j++ ) {
                ht.score[j] = (int)dt[i].score[j] ;
            } // for
            ht.average = dt[i].average ;
            int key = hash( dt[i].id ) ;
            ht.hvalue = key ;
            ht.exists = true ;

            int temp = key, probes = 0 ;
            for ( int num = 1 ; quadraticHash[temp].exists != false ; temp = (int)(key+pow(num,2)) % quadraticHash.size(), success++,num++,probes++ ) {
                if ( probes == quadraticHash.size() ) {
                    cout << "Fail : [" << temp << "]" << endl ;
                    break ;
                } // if
            } // for

            success++ ;
            quadraticHash[temp] = ht ;
        } // for
    } // build()

    void calculate() {
        cout << "\n\nHash Table Z has been created.\n\n" ;

        float unsuccess = 0 ;
        for( int index = 0 ; index < quadraticHash.size() ; index++ ){
            int probe = 0, temp = index ;
            if( quadraticHash[index].exists == true ) {
                int num = 1 ;
                while( quadraticHash[temp].exists != false ){
                    temp = index + pow(num, 2) ;
                    num++ ;
                    probe++ ;
                    if( temp >= quadraticHash.size() ) temp = temp % quadraticHash.size() ;
                    if ( probe == quadraticHash.size() ) {
                        break ;
                    } // if
                } // end while

                unsuccess += probe ;
            } // end if
        } // end unsuccess
        cout << "unsuccessful search: " ;
        cout << fixed << setprecision(4) << unsuccess / quadraticHash.size() ;
        cout << " comparisons on a average.\n\n" ;

        cout << "successful search: " ;
        cout << success / dt.size() ;
        cout << " comparisons on a average.\n\n";

    } // calculate()

    void writeData() {
        ofstream file ;
        file.open( "quadratic" + filenum + ".txt" ) ;

        file << "--- Hash Table Z --- (linear probing)\n" ;

        for( int i = 0 ; i < quadraticHash.size() ; i++ ){

            if( quadraticHash[i].exists == false ){
                file << "[" << i << "]" << endl ;
            } // if
            else{
                file << "[" << i << "]" ;
                file << "\t" << quadraticHash[i].hvalue ;
                file << "\t" << quadraticHash[i].id ;
                file << "\t" << quadraticHash[i].name ;
                file << "\t" << quadraticHash[i].average << "\n" ;
            } // else
        } // end output

        file.close() ;

    } // writeData

};

int main() {

    printTitle() ;
    Hash h ;
    DHash dh ;
    QHash qh ;

    int command ;
    while ( cin >> command && command ) {

        if ( command == 1 ) {
            if ( h.input() ) {
                START = clock() ;
                h.build() ;
                h.calculate() ;
                END = clock() ;
                h.writeData() ;
                cout << (END-START) / (double)h.getSize() << endl ;
            } // if
        } // if
        else if ( command == 2 ) {
            if ( dh.input() ) {
                dh.build() ;
                dh.calculate() ;
                dh.writeData() ;
            } // if
        } // else if
        else if ( command == 3 ) {
            if ( qh.input() ) {
                START = clock() ;
                qh.build() ;
                qh.calculate() ;
                END = clock() ;
                qh.writeData() ;
                cout << (END-START) / (double)qh.getSize() << endl ;
            } // if
        } // else if
        else {
            cout << "\nCommand does not exist!\n\n" ;
        } // else

        printTitle() ;
        h.clear() ;
        dh.clear() ;
        qh.clear() ;
    } // while

    return 0 ;
} // main()
