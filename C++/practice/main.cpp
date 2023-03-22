#include <iostream>

using namespace std ;

int main() {
    int count = 5 ;
    int a = 0 ;
    a = count++ + 1  ;
    a = ++count + 1 ;
    cout << a << " " << count << endl ;
}
