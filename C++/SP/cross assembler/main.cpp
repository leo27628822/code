#include <bits/stdc++.h>

using namespace std ;

class Input {

private:

    struct dataType{
    string token = "" ;
    int tb_Num = 0 ;
    int tb_Index = 0 ;
    };

public:
    vector <dataType> token ;
    vector <string> tb1, tb2, tb3, tb4, tb5, tb6, tb7 ; // tb5~tb7:symbol, integer/real, string
    Input() {
        tb5.resize(100) ;
        tb6.resize(100) ;
        tb7.resize(100) ;
    }
    void readTable() ;
    void input() ;
    void insertToken( string token, int table, int index ) ;
    void insertToken( string token ) ;
    int findToken( string token, int & tb_Num ) ;

};


int main( int argc, char* argv[] ) {


    Input input ;
    input.readTable() ;
    input.input() ;

    /*
    for ( int i = 0 ; i < input.token.size() ; i++ ) {
        cout << input.token[i].tb_Index << "\n" ;
    }
    //*/

    return 0 ;
}

void Input::readTable() {

    ifstream file ;
    string filename ;

    // read table1
    filename = "Table1.table" ;
    file.open( filename ) ;

    if ( !file.is_open() ) cout << "### File: " << filename << " does not exist! ###\n" ;
    else {

        string tempStr = "" ;

        while ( !file.eof() ) {

            getline( file, tempStr ) ;

            if ( file.fail() ) {
                    break ;
            } // if

            tb1.push_back( tempStr ) ;
        }
    }

    file.close() ;

    // read tb2 ;

    filename = "Table2.table" ;
    file.open( filename ) ;

    if ( !file.is_open() ) cout << "### File: " << filename << " does not exist! ###\n" ;
    else {

        string tempStr = "" ;

        while ( !file.eof() ) {

            getline( file, tempStr ) ;

            if ( file.fail() ) {
                    break ;
            } // if

            tb2.push_back( tempStr ) ;
        }
    }

    file.close() ;

    // read table3

    filename = "Table3.table" ;
    file.open( filename ) ;

    if ( !file.is_open() ) cout << "### File: " << filename << " does not exist! ###\n" ;
    else {

        string tempStr = "" ;

        while ( !file.eof() ) {

            getline( file, tempStr ) ;

            if ( file.fail() ) {
                    break ;
            } // if

            tb3.push_back( tempStr ) ;
        }
    }

    file.close() ;

    // read table4

    filename = "Table4.table" ;
    file.open( filename ) ;

    if ( !file.is_open() ) cout << "### File: " << filename << " does not exist! ###\n" ;
    else {

        string tempStr = "" ;

        while ( !file.eof() ) {

            getline( file, tempStr ) ;

            if ( file.fail() ) {
                    break ;
            } // if

            tb4.push_back( tempStr ) ;
        }
    }

    file.close() ;

}

void Input::input() {

    ifstream file ;
    file.open( "SIC_input.txt" ) ;
    if ( !file.is_open() ) cout << "### File does not exists! ###\n" ;
    else {

        while ( !file.eof() ) {
            string tempStr = "" ;
            getline( file, tempStr ) ;
            // cout << tempStr << "\n" ;
            for ( char c:tempStr ) {
                string buffer = "" ;

                // char is whitespace
                if ( c == ' ' || c == '\n' ) {
                    if ( buffer.empty() ) continue ;
                    // buffer has token need to store
                    else {
                        int tb_Num = 1 ;
                        int index = findToken( buffer, tb_Num ) ;
                        if ( index != -1 ) {
                            insertToken( buffer, tb_Num, index ) ;
                        }
                        else {
                            insertToken( buffer ) ;         // add to tb5~tb7
                        }

                        buffer = "" ;
                        buffer.clear() ;
                    }
                }
                else {
                    string t;
                    t = c ;
                    for ( int i = 0 ; i < tb4.size() ; i++ ) {
                        if ( t == tb4[i] ) {
                            // add buffer to token
                            if ( !buffer.empty() ) {
                                int tb_Num = 1 ;
                                int index = findToken( buffer, tb_Num ) ;
                                insertToken( buffer, tb_Num, index ) ;
                                buffer = "" ;
                                buffer.clear() ;
                            }

                            insertToken( t, 4, i ) ;
                        }
                    }

                    buffer += c ;
                }
            }
        }
    }

    file.close() ;
}

void Input::insertToken( string token, int table, int index ) {     // add to token table
    dataType tk ;
    tk.token = token ;
    tk.tb_Num = table ;
    tk.tb_Index = index ;
    Input::token.push_back( tk ) ;
}

void Input::insertToken( string token ) {                           // add to tb5~tb7

    bool integer = false ;
    int sum = 0 ;
    for ( char c : token ) {
        if ( c >= '0' && c <= '9' ) integer = true ;
        else integer = false ;
        sum += (int)c ;
    }

    int index = sum % 100, tb_Num ;
    bool done = false ;
    if ( integer ) {
        tb_Num = 6 ;
        while ( !done ) {
            if ( tb6[index].empty() ) {
                tb6[index] = token ;
                done = true ;
            }
            else index++ ;
            if ( index >= tb6.size() ) index = 0 ;
        }
    }
    else if ( Input::token[Input::token.size()-1].token == "'" ) {
        tb_Num = 7 ;
        while ( 1 ) {
            if ( tb7[index].empty() ) {
                tb7[index] = token ;
                done = true ;
            }
            else index++ ;
            if ( index >= tb7.size() ) index = 0 ;
        }
    }
    else {
        tb_Num = 5 ;
        while ( 1 ) {
            if ( tb5[index].empty() ) {
                tb5[index] = token ;
                done = true ;
            }
            else index++ ;
            if ( index >= tb5.size() ) index = 0 ;
        }
    }

    insertToken( token, tb_Num, index ) ;
}

int Input::findToken( string token, int & tb_Num ) {

    for ( int i = 0 ; i < tb1.size() ; i++ ) {
        if ( token == tb1[i] ) {
            tb_Num = 1 ;
            return i ;
        }
    }

    for ( int i = 0 ; i < tb2.size() ; i++ ) {
        if ( token == tb2[i] ) {
            tb_Num = 2 ;
            return i ;
        }
    }

    for ( int i = 0 ; i < tb3.size() ; i++ ) {
        if ( token == tb3[i] ) {
            tb_Num = 3 ;
            return i ;
        }
    }

    return -1 ;
}

