// DS1101ex3_20_10927143_10927141
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

bool isOperator_( char ch ) ;
bool isOperand_( char ch ) ;


struct Node {
    bool type ; // 0 : operand  | 1 : operator
    string name ;
    double value = 0.0 ;
    int priority = 0 ; // operand = 0 | +,- = 1 | *,/ = 2
};

class Stack {

    public :
        bool isEmpty() ;
        void push( Node n ) ;
        void pop() ;
        Node getTop() ;
        void init() ;
        void reverse() ;
        void print() {
            if ( !alist.empty() ) {
                for ( auto it : alist ) {
                    cout << it.name << ", " ;
                } // for
            } // if
        } // print()
        list<Node> alist ;
};

bool Stack::isEmpty() {
    return alist.empty() ;
}

void Stack::push( Node n ) {
    alist.push_front( n ) ;
}

void Stack::pop() {
    alist.pop_front() ;
}

Node Stack::getTop() {
    return alist.front() ;
}

void Stack::init() {
    alist.clear() ;
}

void Stack::reverse() {
    alist.reverse() ;
}

bool isOperator_( char ch ) {
    /*
    if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) return true ;   // + - * /
    else return false ;
    */
    return ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) ;
} // isOperator_()

bool isOperand_( char ch ) {
    /*
    if ( ch >= '0' && ch <= '9' ) return true ;
    else return false ;
    */
    return ( ch >= '0' && ch <= '9' ) ;
} // isOperand_()

int toInt( string str ) {
    return stoi( str ) ;
} // toInt()

int check( string & str, Stack & tmp ) {
    bool num = false, parenthesis = false, oper = false ;
    Stack temp ;
    string s ;
    Node nd ;
    for ( char ch : str ) {
        if ( isOperand_( ch ) ) {  // ch = num ?
            if ( parenthesis == true )  {
                cout << "Error 3 : there is one extra operand.\n" ;
                return 0 ;
            } // if
            else {
                s.push_back(ch) ;
                num = true ;
                oper = false ;
            } // else
        } // if
        else if ( isOperator_( ch ) ) {  // ch = +-*/ ?
            if ( num == false || oper == true ) {
                cout << "Error 3 : there is one extra operator.\n" ;
                return 0 ;
            } // if
            else {
                if ( !s.empty() ) {
                    nd.name = s ;
                    nd.value = (double)toInt( s ) ;
                    nd.type = 0 ;
                    tmp.push( nd ) ;
                    s = "" ;
                    s.clear() ;
                } // if

                s.push_back(ch) ;
                nd.name = s ;
                nd.type = 1 ;
                if ( ch == '+' || ch == '-' ) nd.priority = 1 ;
                else nd.priority = 2 ;
                tmp.push( nd ) ;
                s = "" ;
                s.clear() ;
                parenthesis = num = false ;
            } // else
        } // else if
        else if ( ch == '(' || ch == ')' ) {

            if ( !s.empty() ) {
                nd.name = s ;
                nd.value = (double)toInt( s ) ;
                nd.type = 0 ;
                tmp.push( nd ) ;
                s = "" ;
                s.clear() ;
            } // if

            s.push_back( ch ) ;
            nd.name = s ;
            nd.type = 1 ;
            nd.priority = 0 ;
            tmp.push( nd ) ;
            s = "" ;
            s.clear() ;

            if ( ch == '(' ) {
                if ( num == true ) {
                    cout << "Error 3 : there is one extra operand.\n" ;
                    return 0 ;
                } // if

                temp.push( nd ) ;
            } // if
            else if ( ch == ')' ) {
                if ( oper == true ) {
                    cout << "Error 3 : there is one extra operator.\n" ;
                    return 0 ;
                } // if
                else if ( temp.isEmpty() ) {
                    cout << "Error 2 : there is one extra close parenthesis.\n" ;
                    return 0 ;
                } // if
                else {
                    temp.pop() ;
                    parenthesis = true ;
                } // esle
            } // esle if
        } // else if
        else {
            cout << "Error 1 : " << ch << " is not a legitimate character.\n" ;
            return 0 ;
        } // else
    } // for

    if ( !s.empty() ) {
        nd.name = s ;
        nd.value = (double)toInt( s ) ;
        nd.type = 0 ;
        tmp.push( nd ) ;
    } // if
    if ( !temp.isEmpty() ) {
        cout << "Error 2 : there is one extra open parenthesis.\n" ;
        return 0 ;
    } // if
    else return 1 ;
} // check()

void toPostfix( Stack & st1, Stack & st2 ) {
    Stack op ;
    op.init() ;
    for ( auto it : st1.alist ) {
        if ( it.type == 0 ) st2.push( it ) ;
        else { //  + - * / ( )
            if ( op.isEmpty() ) op.push( it ) ;
            else {
                if ( it.name == "(" ) {
                    op.push( it ) ;
                } // if
                else if ( it.name == ")" ) {
                    while ( op.getTop().name != "(" ) {
                        st2.push( op.getTop() ) ;
                        op.pop() ;
                    } // while

                    op.pop() ;
                } // else if
                else {  // +-*/
                    while ( !op.isEmpty() && it.priority <= op.getTop().priority && op.getTop().priority != 0 ) {
                        st2.push( op.getTop() ) ;
                        op.pop() ;
                    } // while

                    op.push(it) ;
                } // else
            } // else
        } // else
    } // for

    while ( !op.isEmpty() ) {
        if ( op.getTop().name != "(" ) st2.push(op.getTop() ) ;
        op.pop() ;
    } // while
} // toPostfix()

double postfix_Answer( Stack & st2 ) {
    double a,b ;
    Node nd ;
    Stack num ;

    for ( auto it : st2.alist ) {
        if ( it.type == 0 ) num.push( it ) ;
        else {
            if ( it.name == "+" ) {
                a = num.getTop().value ;
                num.pop() ;
                b = num.getTop().value ;
                num.pop() ;
                nd.value = b+a ;
                num.push( nd ) ;
            } // if
            else if ( it.name == "-" ) {
                a = num.getTop().value ;
                num.pop() ;
                b = num.getTop().value ;
                num.pop() ;
                nd.value = b-a ;
                num.push( nd ) ;
            } // else if
            else if ( it.name == "*" ) {
                a = num.getTop().value ;
                num.pop() ;
                b = num.getTop().value ;
                num.pop() ;
                nd.value = b*a ;
                num.push( nd ) ;
            } // else if
            else if ( it.name == "/" ) {
                a = num.getTop().value ;
                if ( a == 0 ) return -999999.0 ;
                num.pop() ;
                b = num.getTop().value ;
                num.pop() ;
                nd.value = b/a ;
                num.push( nd ) ;
            } // else if
        } // else
    } // for

    return num.getTop().value ;
} // postfix_Answer

int main() {
    int n ;
    string str ;
    Stack st1, st2 ; // st1 : original infix formula st2 : postfix formula
    cout << "0:quit 1: infix2postfix calculator.\n" ;
    while ( cin >> n && n ) {
        st1.init() ;
        st2.init() ;
        cin.ignore() ;  // or cin.get() to remove '\n' in buffer
        if ( n != 1 ) cout << "Wrong number! Please try again.\n" ;
        else {
            cout << "Input an infix expression : " ;
            getline( cin, str ) ;
            str.erase( std::remove( str.begin(), str.end(), ' ' ), str.end() ) ; // erase all spaces
            cout << "Input: " << str << "\n" ;
            if ( check( str, st1 ) ) {

                if ( st1.getTop().type == 1 && st1.getTop().priority != 0 ) cout << "Error 3 : there is one extra operator.\n" ;
                else {
                    st1.reverse() ;
                    // st1.print() ;
                    // cout << endl ;
                    cout << "It is a legitimate infix expression.\n" ;
                    toPostfix( st1, st2 ) ;
                    cout << "Postfix expression : " ;
                    st2.reverse() ;
                    st2.print() ;
                    cout << "\n" ;
                    double ans = postfix_Answer( st2 ) ;
                    if ( ans == -999999.0 ) cout << "Error 4 : divisor equals to 0.\n" ;
                    else cout << "The answer of postfix formula is : " << fixed << setprecision(2) << ans << "\n" ;
                } // else
            } // if
        } // else

        cout << "0:quit 1: infix2postfix calculator.\n" ;
    } // while

    system("pause") ;
} // main()
