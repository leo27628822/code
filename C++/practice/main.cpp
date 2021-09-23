#include <iostream>
#include <cmath>

using namespace std;

int Outer = 0, Inner = 0 ;
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

int main() {

    cout << "0: Quit. 1: Recursive. 2:Iterative.\n" ;

    unsigned long long fib[92] ;
    fib[0] = 1, fib[1] = 2 ;
    for ( int i = 2 ; i < 92 ; i++ )
        fib[i] = fib[i-1] + fib[i-2] ;

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
                    cout << "[" << i-1 << "] " << temp << " = X*Y     (Inner loop: xxx times)\n" ;
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
                for ( int i = 0 ; i < num ; i++ ) {
                    cout << "[" << i+1 << "] " << fib[i] << " = x1*x2     (Inner loop:xxx times)\n" ;
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
