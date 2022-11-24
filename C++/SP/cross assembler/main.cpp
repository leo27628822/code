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
    vector <string> tb1, tb2, tb3, tb4, tb5, tb6, tb7 ;     // tb5~tb7:symbol, integer/real, string
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
    bool isWhiteSpace( char c ) ;
    bool isDelimeter( char c ) ;

};


int main( int argc, char* argv[] ) {

    Input input ;
    input.readTable() ;
    input.input() ;
    //*
    for ( int i = 0 ; i < input.token.size() ; i++ ) {
        cout << input.token[i].token << " " << input.token[i].tb_Num << " " << input.token[i].tb_Index << "\n" ;
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
    file.open( "SICXE_input.txt" ) ;
    if ( !file.is_open() ) cout << "### File does not exists! ###\n" ;
    else {

        while ( file.peek() != EOF ) {
            string tempStr = "" ;
            getline( file, tempStr ) ;
            // cout << tempStr << "\n" ;
            string buffer = "" ;
            bool comment = false ;
            for ( char c:tempStr ) {


                if ( comment ) {
                    if ( c != '\n' ) {
                        buffer += c ;
                        continue ;
                    }
                    else comment = false ;
                }

                // char is whitespace
                if ( !comment && isWhiteSpace(c) ) {

                    if ( buffer.empty() ) continue ;
                    // buffer has token need to store
                    else {
                        int tb_Num = 1 ;
                        int index = findToken( buffer, tb_Num ) ;
                        if ( index == 99999 ) {             // not found
                            insertToken( buffer ) ;         // add to tb5~tb7
                        }
                        else {
                            insertToken( buffer, tb_Num, index ) ;      // found
                        }

                        buffer.clear() ;
                        buffer = "" ;
                    }
                }
                else if ( isDelimeter(c) ) {
                /*
                check if buffer empty
                */
                    if ( !buffer.empty() ) {
                        int tb_Num = 1 ;

                        int index = findToken( buffer, tb_Num ) ;
                        if ( index == 99999 ) insertToken( buffer ) ;
                        else insertToken( buffer, tb_Num, index ) ;
                        buffer.clear() ;
                        buffer = "" ;
                    }

                    if ( c == '.'  ) {
                        comment = true ;
                        continue ;
                    }
                    string t = "" ;
                    t += c ;
                    for ( int i = 0 ; i < tb4.size() ; i++ ) {
                        if ( t == tb4[i] ) {
                            insertToken( t, 4, i ) ;
                        }
                    }
                }
                else {
                    buffer += c ;
                }
            }
        }
    }

    file.close() ;
}

void Input::insertToken( string name, int table, int index ) {     // add to token table
    dataType tk ;
    tk.token = name ;
    tk.tb_Num = table ;
    tk.tb_Index = index ;
    token.push_back( tk ) ;
}

void Input::insertToken( string name ) {                           // add to tb5~tb7

    bool integer = false ;
    int sum = 0 ;
    for ( char c : name ) {
        if ( c >= '0' && c <= '9' ) {
            integer = true ;
            cout << name << endl ;
        }
        sum += (int)c ;
    }

    int hash_key = sum % 100, tb_Num ;
    bool done = false ;

    if ( !token.empty() && token[token.size()-1].token == "'" && token[token.size()-3].token != "'" ) {
        tb_Num = 7 ;
        while ( !done ) {
            if ( tb7[hash_key].empty() ) {
                tb7[hash_key] = name ;
                done = true ;
            }
            else hash_key++ ;
            if ( hash_key >= tb7.size() ) hash_key = 0 ;
        }
    }
    else if ( integer ) {
        tb_Num = 6 ;
        while ( !done ) {
            if ( tb6[hash_key].empty() ) {
                tb6[hash_key] = name ;
                done = true ;
            }
            else hash_key++ ;
            if ( hash_key >= tb6.size() ) hash_key = 0 ;
        }
    }
    else {

        tb_Num = 5 ;

        while ( !done ) {
            if ( tb5[hash_key].empty() ) {
                tb5[hash_key] = name ;
                done = true ;
            }
            else hash_key++ ;
            if ( hash_key >= tb5.size() ) hash_key = 0 ;
        }
    }

    insertToken( name, tb_Num, hash_key ) ;
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

    return 99999 ;
}

bool Input::isWhiteSpace( char c ) {
    if ( c == ' ' || c == '\n' || c == '\t' ) return true ;
    else return false ;
}

bool Input::isDelimeter( char c ) {
    string t = "" ;
    t += c ;

    for ( int i = 0 ; i < tb4.size() ; i++ ) {
        if ( t == tb4[i] ) return true ;
    }
    return false ;
}


