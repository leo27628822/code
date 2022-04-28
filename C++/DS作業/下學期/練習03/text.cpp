// 10927124畗嘱地
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>
#include <iomanip>


using namespace std ;

string file_num = "", file_name = "" ;

struct Inf{
    char id[10] ;
    char name[10] ;
    unsigned char score[6] ;
    float average ;
};

Inf inf ;

class Input{

private:
    vector<Inf> student ;

public:
    string command ;

    void Command(){
        do{     // check if input command is correct
            cout << endl << endl ;
            cout << "*****    Hash Table Builder    *****" << endl ;
            cout << "**  0. Quit                       **" << endl ;
            cout << "**  1. Linear probing             **" << endl ;
            cout << "**  2. Double probing             **" << endl ;
            cout << "************************************" << endl ;
            cout << endl << "Input a command(0, 1, 2): " ;
            cin >> command ;
            if(command != "0" && command != "1" && command != "2")
                cout << endl << endl << "Command does not exist!" << endl << endl ;
        } while (command != "0" && command != "1" && command != "2") ;
    } // end Command

    void ReadTxt(){
        student.clear() ;

        ifstream file ;
        char buffer[10] ;
        string temp ;

        file.open( file_name ) ;

        while( !file.eof() ){
            for( int i = 0 ; i < 8 ; i++ ){
                file.getline(buffer, sizeof(buffer), '\t' ) ;
                temp = buffer ;

                if( i == 0 && temp == "" ){    //传︽ぐ或戈常⊿Τ薄猵
                    file.close() ;
                    return ;
                } // EOF

                if( i == 0 ) strcpy(inf.id, buffer) ;
                else if( i == 1 ) strcpy(inf.name, buffer) ;
                else inf.score[i-2] = (unsigned char)stoi(temp) ;
            } // end of a line

            file.getline(buffer, sizeof(buffer)) ;
            temp = buffer ;
            inf.average = stof(temp) ;

            student.push_back(inf) ;
        } // end of input file

        file.close() ;
    } // end of ReadTxt

    void TxtToBin(){
        ReadTxt() ;
        file_name = "input" + file_num + ".bin" ;

        ofstream file(file_name, ios::binary) ;

        for( int index = 0 ; index < student.size() ; index++ ){
            file.write((char*)&student[index], sizeof(student[index])) ;
        } // end input

        file.close() ;
    } // end TxtToBin

    void FileName(){
        ifstream file ;
        string temp ;

        while( true ){
            cout << endl << "Input a file number (e.g., 301, 302, ...): " ;
            cin >> file_num ;

            file.open( "input" + file_num + ".bin" ) ;

            if( file.is_open() ){   // ensure the .bin open
                file.close() ;
                file_name = "input" + file_num + ".bin" ;
                return ;
            } // end opne .bin

            file.open( "input" + file_num + ".txt" ) ;

            if( file.is_open() ){   // ensure the .txt open
                file.close() ;
                file_name = "input" + file_num + ".txt" ;
                TxtToBin() ;
                return ;
            } // end of .txt

            cout << file_name << " does not exist!" << endl ;

        } // sure the file exist
    } // end FileName()

}; // end class Input

class ReadBin{
public:
    enum Situation{ used, unused } ;

    struct Content{
        int hvalue = -1 ;
        string id = "" ;
        string name = "" ;
        int score[6] = {0};
        float average = 0.0;
        Situation situation = unused ;
    };

    Content content ;
    vector<Content> table ;
    vector<Inf> list ;

    float datasize = 0 ;

    ReadBin(){
        ifstream file(file_name, ios::binary) ;
        for( int index = 0 ; file.peek() != EOF ; index++ ){
            list.push_back(inf) ;
            file.read((char*)&list[index], sizeof(list[index]));
        }

        file.close() ;

        for( int i = 0 ; i < NextPrime(ceil((float)list.size()*1.2)) ; i++ ) table.push_back(content) ;
        datasize = list.size() ;
    } // end constructor

    bool IsPrime( int num ){
        for( int i = 2 ; i < num ; i++ ){
            if( num % i == 0 ) return false ;   // not prime
        }

        return true ;   // is prime
    } // end IsPrime

    int NextPrime( int num ){
        for( ; !IsPrime(num) ; num++ ) ;
        return num ;
    } // end NextPrime

    int Hash( string key ){
        unsigned long long total = 1 ;

        for( int i = 0 ; i < key.size() ; i++ )
            total *= (int)key[i] ;

        return total % table.size() ;

    } // end Hash
};

class Linear: private ReadBin{

public:
    float success = 0;

    int listSize(){
        return list.size() ;
    }

    void Insert(){
        int key = Hash(list[0].id) ;

        content.id = list[0].id ;
        content.name = list[0].name ;
        for( int i = 0 ; i < 6 ; i++ ) content.score[i] = list[0].score[i] ;
        content.average = list[0].average ;
        content.situation = used ;
        content.hvalue = key ;

        for( ; table[key].situation != unused ; key = (key+1) % table.size(), success++ ) ;

        success++ ;
        table[key] = content ;     // update table

        list.erase(list.begin()) ;
    } // end Insert

    void Output(){
        cout << endl << endl << "Hash Table X has been created." << endl << endl ;

        float unsuccess = 0 ;

        for( int index = 0 ; index < table.size() ; index++ ){
            int gap = 0, temp = index ;
            if( table[index].situation == used ) {
                while( table[temp].situation != unused ){
                    temp++ ;
                    gap++ ;
                    if( temp >= table.size() ) temp = temp - table.size() ;
                }
                unsuccess += gap ;
            }
        }

        cout << "unsuccessful search: " ;
        cout << fixed << setprecision(4) << unsuccess/table.size() ;
        cout << " comparisons on a average." << endl << endl ;

        cout << "successful search: " ;
        cout << fixed << setprecision(4) << success/datasize ;
        cout << " comparisons on a average." << endl << endl ;

        WriteData() ;
    } // end Output

    void WriteData(){
        ofstream file ;
        file.open("linear"+file_num+".txt") ;

        file << "--- Hash Table X --- (linear probing)" << endl ;

        for( int i = 0 ; i < table.size() ; i++ ){
            if( table[i].situation == unused ){
                file << "[" << i << "]" << endl ;
            } // ignore empty

            else{
                file << "[" << i << "]" ;
                file << "\t" << table[i].hvalue ;
                file << "\t" << table[i].id ;
                file << "\t" << table[i].name ;
                file << "\t" << table[i].average << endl ;
            }
        } // end output

        file.close() ;
    } // end WriteData
}; // end of class Linear Probing

class Double: private ReadBin{
public:
    float success = 0;
    long long hightStep = 0 ;

    Double(){
        hightStep = NextPrime(ceil((float)list.size()/3)) ;
    } // end constructor

    int listSize(){
        return list.size() ;
    }

    long long Step( string key ){
        unsigned long long total = 1 ;

        for( int i = 0 ; i < key.size() ; i++ )
            total *= (int)key[i] ;

        return hightStep - (total % hightStep) ;
    } // end Step

    void Insert(){
        int key = Hash(list[0].id) ;

        content.id = list[0].id ;
        content.name = list[0].name ;
        for( int i = 0 ; i < 6 ; i++ ) content.score[i] = list[0].score[i] ;
        content.average = list[0].average ;
        content.situation = used ;
        content.hvalue = key ;

        int step = Step(list[0].id) ;
        for( ; table[key].situation != unused ; key = (key+step) % table.size(), success++) ;

        success++ ;
        table[key] = content ;     // update table

        list.erase(list.begin()) ;
    } // end Insert

    void Output(){
        cout << endl << endl << "Hash Table Y has been created." << endl << endl ;

        cout << "successful search: " ;
        cout << fixed << setprecision(4) << success/datasize ;
        cout << " comparisons on a average." << endl << endl ;
        WriteData() ;
    } // end Output

    void WriteData(){
        ofstream file ;
        file.open("double"+file_num+".txt") ;

        file << "--- Hash Table X --- (double probing)" << endl ;

        for( int i = 0 ; i < table.size() ; i++ ){
            if( table[i].situation == unused ){
                file << "[" << i << "]" << endl ;
            } // ignore empty

            else{
                file << "[" << i << "]" ;
                file << "\t" << table[i].hvalue ;
                file << "\t" << table[i].id ;
                file << "\t" << table[i].name ;
                file << "\t" << table[i].average << endl ;
            }
        } // end output

        file.close() ;
    }
};

int main() {
    Input input ;
    input.Command() ;

    while( input.command != "0" ){
        input.FileName() ;

        if( input.command == "1" ){
            Linear l_Hash ;
            while( l_Hash.listSize() != 0 ) l_Hash.Insert() ;
            l_Hash.Output() ;
        } // end command1

        if( input.command == "2" ){
            Double d_Hash ;
            while( d_Hash.listSize() != 0 ) d_Hash.Insert() ;
            d_Hash.Output() ;
        } // end command2

        input.Command() ;
    } // end progammimg
} // end main
