#include <iostream>
#include <cmath>
#include<vector>
#include<time.h>

using namespace std;
int NUMBER = 1 ;
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
    Matrix C = fast_pow(A,n>>1);
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

unsigned long long Fib3(int n, unsigned long long a, unsigned long long b ) {
    Outer++ ;
    return ( n == 0? a: Fib3( n-1,b,a+b) ) ;
} // Fib3()

void Factor( unsigned long long n, unsigned long long & x1, unsigned long long & x2, bool type, bool tmp ) {

    Inner++ ;
    if ( Inner == 50 ) return ;
    if ( x1*x2 == n  ) return  ;
    else if( n % x1 == 0 ) {
        x2 = n/x1 ;
        return ;
    } // else if
    else if ( type || ( !type && ( n >> 1 ) % 2 == 0) ) {
        x1-=2 ;
    } // else if
    else {
        x1-- ;
    } // else
    Factor( n, x1, x2, type, tmp ) ;
} // Factor()

void Comb(int k, int n, int m, vector < int > list) {
    list.push_back(k - 1);
    for (int i = k; i <= (m - n) && n > 0; ++i)
        Comb(i + 1, n - 1, m, list);

    if (n == 0) {
        cout << "[ " << NUMBER++ << "] " ;
        for (int i = 0; i < list.size(); ++i)
            cout << list[i] << " " ;
        cout << endl;
    } // if
} // Comb()

int main() {

    cout << "0: Quit. 1: Iterative. 2:Recursive. 3.Combination.\n" ;

    int num = 0 ;
    Matrix A ;
    A.m[0][0] = 1, A.m[0][1] = 1, A.m[1][0] = 1, A.m[1][1] = 0 ;

    while ( cin >> num && num ) {
        if ( num == 2 ) { // Recursive
            cout << "Please enter a number between 1~92 .\n" ;
            cin >> num ;

            if ( num <= 92 && num >= 1 ) {
                for ( int i = 2 ; i <= num+1 ; i++ ) {
                    // unsigned long long temp = Fib1( 1 ) ; the time is too long
                    unsigned long long temp = Fib2( A, i ) ;
                    // unsigned long long temp = Fib3( i,0,1 ) ; the time is too long
                    bool type = 0, tmp = 0 ; // 0: even ; 1:odd
                    type = temp % 2 ;
                    unsigned long long x1, x2, times = 0 ;
                    x2 = x1 = sqrt(temp) ;
                    tmp = x1 % 2 ;
                    if ( i == 90 ) x1-- ;
                    else if ( ( type && !tmp ) ||  !type && ( temp >> 1 ) % 2 == 0 && tmp ) x1-- ;
                    while ( ! ( x1*x2 == temp ) ) {
                        Factor(temp,x1,x2,type,tmp ) ; // 最多跑50次遞迴
                        times += Inner ;
                        times-- ;
                        Inner = 0 ;
                    } // while

                    cout << "[" << i-1 << "] " << temp << " = "<< x1 << "*" << x2 << "     (Inner recursion: " << times << " times)\n" ;
                    // else cout << "[" << i-1 << "] " << temp << " =      (Inner recursion more than 10000000  times)\n" ;
                    Inner  = 0 ;
                } // for

                cout << "<Outer recursion: " << Outer << " times>\n" ;
                Outer = 0 ;
            } // if
            else cout << "Error! Wrong number range\n" ;
        } // if
        else if ( num == 1 ) { // Iterative
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
                    if ( i == 88 ) x1-- ;
                    else if ( ( type && !tmp ) ||  !type && ( fib[i] >> 1 ) % 2 == 0 && tmp ) x1-- ;
                    // if ( !type && ( fib[i] / 2 ) % 2 == 0 && tmp ) x1-- ;

                    while ( ! ( x1*x2 == fib[i]  ) ) {
                        Inner++ ;
                        if ( fib[i] % x1 == 0 )
                            x2 = fib[i] / x1 ;
                        else {
                            if ( type || (!type && ( fib[i] >> 1 ) % 2 == 0) ) x1 -= 2 ;
                            else x1-- ;
                        } // else

                    } // while

                    cout << "[" << i+1 << "] " << fib[i] << " = " << x1 << "*" << x2 << "     (Inner loop:" <<Inner<< " times)\n" ;
                    Inner = 0 ;
                } // for

                cout << "<Outer loop: " <<  (num <= 2 ? 0: num - 1 ) << " times>\n" ;
            } // if
            else cout << "Error! Wrong number range\n" ;
        } // else if
        else if ( num == 3 ) {
            int n;
            double start, end ;
            cout << "Please enter a number between 1~10 .\n" ;
            cin >> n;
            if ( n >=1 && n <=10) {
                vector < int > list;
                start = clock() ;
                for (int i = 0; i <= (10 - n) && n > 0; ++i)
                    Comb( i + 1, n - 1, 10, list);
                end = clock() ;
                cout  << "<Recursion: " << end - start << " ms>\n" ;
                NUMBER = 1 ;
            } // if
            else cout << "Error! Wrong number range\n" ;
        } // else if
        else cout << "Error! No this function!\n" ;

        cout << "0: Quit. 1: Iterative. 2:Recursive. 3.Combination.\n" ;
    }

    system("pause") ;
} // main()

