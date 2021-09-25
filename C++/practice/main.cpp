#include <iostream>
#include <cmath>

using namespace std;

long long Outer = 0, Inner = 0 ;
struct Matrix{
    unsigned long long m[2][2] ;
};

Matrix multi( Matrix A, Matrix B ) {

    Matrix C ;
    for ( int i = 0 ; i < 2 ; i++ )
        for ( int j = 0 ; j < 2 ; j++ ) {
            C.m[i][j] = 0 ;
            for ( int k = 0 ; k < 2 ; k++)
                C.m[i][j] += A.m[i][k] * B.m[k][j] ;
        } // for

    return C;
} // multi()

Matrix fast_pow( Matrix A, int n ) {
    Outer++ ;
    if ( n == 1 ) return A ;
    Matrix C = fast_pow(A,n/2);
    C = multi(C,C) ;
    if ( n % 2 ) return multi(C,A) ;
    return C ;

} // fast_pow()

unsigned long long Fib( int n ) {
    return ( ( n == 1 ) ? n : Fib(n-1) + Fib(n-2)) ; // 題目設定Fib從1開始並且為1
} // Fib()

unsigned long long Fib2(Matrix A, int n ) {
    return ( n == 1? n: fast_pow(A,n-1).m[0][0] ) ;
} // Fib2()

void Factor( unsigned long long n, unsigned long long & x1, unsigned long long & x2, bool type, bool tmp ) {

    Inner++ ;
    if ( Inner == 10000000 ) return ;
    if ( x1*x2 == n && n % x1 == 0 && n % x2 == 0 ) return  ;
    else if( n % x1 == 0 ) {
        x2 = n/x1 ;
        return ;
    } // else if
    else if ( type || (!type && ( n / 2 ) % 2 == 0) ) Factor( n, x1-=2, x2, type, tmp ) ;
    else Factor( n, x1-=1, x2, type, tmp ) ;

} // Factor()

int main() {

    cout << "0: Quit. 1: Recursive. 2:Iterative.\n" ;

    int num = 0 ;
    Matrix A ;
    A.m[0][0] = 1, A.m[0][1] = 1, A.m[1][0] = 1, A.m[1][1] = 0 ;

    while ( cin >> num && num ) {
        if ( num == 1 ) { // Recursive
            cout << "Please enter a number between 1~92 .\n" ;
            cin >> num ;
            if ( num <= 92 && num >= 1 ) {
                for ( int i = 2 ; i <= num+1 ; i++ ) {
                    unsigned long long temp = Fib2( A, i ) ;
                    bool type = 0, tmp = 0 ; // 0: even ; 1:odd
                    type = temp % 2 ;
                    unsigned long long x1, x2 ;
                    x2 = x1 = sqrt(temp) ;
                    tmp = x1 % 2 ;
                    if ( ( type && !tmp ) ||  !type && ( temp / 2 ) % 2 == 0 && tmp ) x1-- ;
                    Factor(temp,x1,x2,type,tmp) ;

                    if ( Inner < 10000000 ) cout << "[" << i-1 << "] " << temp << " = "<< x1 << "*" << x2 << "     (Inner recursion: " << Inner << " times)\n" ;
                    else cout << "[" << i-1 << "] " << temp << " =      (Inner recursion more than 10000000  times)\n" ;
                    Inner = 0 ;
                } // for

                cout << "<Outer recursion: " << Outer << " times>\n" ;
                Outer = 0 ;
            } // if
            else cout << "Error! Wrong number range\n" ;
        } // if
        else if ( num == 2 ) { // Iterative
            cout << "Please enter a number between 1~92 .\n" ;
            cin >> num ;
            if ( num <= 92 && num >= 1 ) {

                unsigned long long fib[92] ;
                fib[0] = 1, fib[1] = 2 ;
                for ( int i = 2 ; i < 92 ; i++ )
                    fib[i] = fib[i-1] + fib[i-2] ;

                for ( int i = 0 ; i < num ; i++ ) {

                    bool type = 0, tmp = 0 ; // 0: even ; 1:odd
                    type = fib[i] % 2 ;
                    unsigned long long x1, x2 ;
                    x2 = x1 = sqrt(fib[i]) ;
                    tmp = x1 % 2 ;
                    if ( ( type && !tmp ) ||  !type && ( fib[i] / 2 ) % 2 == 0 && tmp ) x1-- ;
                    // if ( !type && ( fib[i] / 2 ) % 2 == 0 && tmp ) x1-- ;

                    while ( ! ( x1*x2 == fib[i] && fib[i] % x1 == 0 && fib[i] % x2 == 0 ) ) {
                        Inner++ ;
                        if ( fib[i] % x1 == 0 )
                            x2 = fib[i] / x1 ;
                        else {
                            if ( type || (!type && ( fib[i] / 2 ) % 2 == 0) ) x1 -= 2 ;
                            else x1-- ;
                        } // else

                    } // while

                    /*
                    while ( 1 )  {
                        Inner++ ;
                        if ( Inner > 1000000000 ) break ;

                        if ( fib[i] % x1 == 0 ) {
                            x2 = x1 ;
                            if ( x1 * x2  == fib[i] ) break ;
                            else {
                                if ( type ) x2 +=2 ;
                                else x2++ ;
                                while ( !( fib[i] % x2 == 0 && x2 * x1 == fib[i]  ) && x1 * x2 < fib[i]  )  {
                                    Inner++ ;
                                    if ( Inner > 1000000000 ) break ;
                                    if ( type ) x2 +=2 ;
                                    else x2++ ;
                                } // while

                                if ( fib[i] ==  x1 * x2 ) break ;
                                else {
                                    if ( type ) x1-=2 ;
                                    else x1-- ;
                                } // else
                            } // else

                        } // if
                        else {
                            if ( type ) x1-=2 ;
                            else x1-- ;
                        } // else
                        // cout << x1 << " " << x2 << "\n" ;

                    } // while
                        /*
                        while( fib[i] % x1 ) {
                            x1-- ;
                            Inner++ ;
                        } // while

                        x2 = x1 ;
                        if ( x1 * x2 != fib[i] ) x2++ ;
                        else break ;

                        while( fib[i]%x2 && x1 * x2 <= fib[i] ) {
                            x2++ ;
                            Inner++ ;
                        } // while

                        if ( x1 * x2 != fib[i] ) x1-- ;
                        else break ;
                        Inner++;
                    } // while
                    //*/

                    cout << "[" << i+1 << "] " << fib[i] << " = " << x1 << "*" << x2 << "     (Inner loop:" <<Inner<< " times)\n" ;
                    Inner = 0 ;
                } // for

                cout << "<Outer loop: " <<  (num <= 2 ? 0: num - 1 ) << " times>\n" ;
            } // if
            else cout << "Error! Wrong number range\n" ;
        } // else if
        else cout << "Error! No this function!\n" ;

        cout << "0: Quit. 1: Recursive. 2:Iterative.\n" ;
    }

    return 0 ;
} // main()
