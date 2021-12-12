// DS1101ex5_20_10927143_10927141
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

string title ;

struct Node {
    int student, teacher, graduate ;
    string school, major, DN_en, DN_ch, RK_en, RK_ch ;
};

class Tree {
    private :
        int height ;
        struct TreeNode {
            Node node ;
            TreeNode * left ;
            TreeNode * right ;
        };
        TreeNode * root ;
    public :
        int getHeight( TreeNode * ) ;
        int Height() {
            return getHeight( root ) ;
        } // end if

        Tree() {
            root = NULL ;
            height = 0 ;
        } // end Tree

        ~Tree() {

        } // end ~Tree

        void createTree1( vector<Node> tree ) ;
        void createTree2( vector<Node> tree ) ;
        bool isEmpty() {
            return root == NULL ;
        } // end isEmpty

        TreeNode * getRoot() {
            return root ;
        } // end getRoot

        void setRoot() ;
        void preorder() ;
        void inorder() ;
        void postorder() ;
        int getleftheight() ;
        int getrightgeight() ;
        void init() {
            root = NULL ;
        } // end init

};

Tree::getHeight( TreeNode * temp ) {
    int lh, rh ;
    if ( !temp ) return 0 ;
    else {
        lh = getHeight( temp -> left ) ;
        rh = getHeight( temp -> right ) ;
        return  lh > rh ? lh+1 : rh+1 ;
    } // end else
} // end getHeight


void Tree::createTree1( vector<Node> tree ) {
    for ( int i = 0 ; i < tree.size() ; i++ ) {
        TreeNode * newPtr = new TreeNode ;
        TreeNode * tempPtr = root ;
        newPtr -> node = tree[i] ;
        newPtr -> right = newPtr -> left = NULL ;
        if ( isEmpty() ) root = newPtr ;
        else {
            while ( true ) {
                if ( newPtr -> node.school < tempPtr -> node.school ) { // or A.compare(B) < 0
                    if ( tempPtr -> left == NULL ) {
                        tempPtr -> left = newPtr ;
                        break ;
                    } // end if
                    else tempPtr = tempPtr -> left;
                } // end if
                else {
                    if ( tempPtr -> right == NULL ) {
                        tempPtr -> right = newPtr ;
                        break ;
                    } // end if
                    else tempPtr = tempPtr -> right ;
                } // end else
            } // end while
        } // end else
    } // end for
} // end createTree1

void Tree::createTree2( vector<Node> tree ) {
    for ( int i = 0 ; i < tree.size() ; i++ ) {
        TreeNode * newPtr = new TreeNode ;
        TreeNode * tempPtr = root ;
        newPtr -> node = tree[i] ;
        newPtr -> right = newPtr -> left = NULL ;
        if ( isEmpty() ) root = newPtr ;
        else {
            while ( true ) {
                if ( newPtr -> node.graduate < tempPtr -> node.graduate ) {
                    if ( tempPtr -> left == NULL ) {
                        tempPtr -> left = newPtr ;
                        break ;
                    } // end if
                    else tempPtr = tempPtr -> left;
                } // end if
                else {
                    if ( tempPtr -> right == NULL ) {
                        tempPtr -> right = newPtr ;
                        break ;
                    } // end if
                    else tempPtr = tempPtr -> right ;
                } // end else
            } // end while
        } // end else
    } // end for
} // end createTree2

bool Read_File( vector <Node> & data ) {
    int tempint ;
    string filename, tempstr ;
    ifstream file ;
    Node node ;

    cout << "\nInput a file number:" ;
    cin >> filename ;
    cin.ignore() ;
    filename = "input" + filename + ".txt" ;
    file.open( filename ) ;
    if ( !file.is_open() ) {
        cout << "\n### " << filename << " does not exist! ###\n" ;
        cout << "\nThere is no data!\n" ;
        return false ;
    } // end if

    getline( file, tempstr ) ;
    getline( file, tempstr ) ;
    getline( file, title ) ;

    while ( !file.eof() ) {
        file >> tempstr >> node.school >> tempstr >> node.major >> node.DN_en ;
        file >> node.DN_ch >> node.RK_en >> node.RK_ch >> node.student >> node.teacher ;
        file >> node.graduate >> tempstr >> tempstr >> tempstr >> tempstr ;
        if ( file.fail() ) break;
        data.push_back( node ) ;
    } // end while

    file.close() ;
    return true ;
} // end Read_File

void PrintTitle() {
    cout << "*** University Graduate Information System ***\n" ;
    cout << "* 0. Quit                                    *\n" ;
    cout << "* 1. Create Two Binary Search Trees          *\n" ;
    cout << "* 2. Search by Number of Graduates           *\n" ;
    cout << "* 3. Search by School Name                   *\n" ;
    cout << "**********************************************\n" ;
    cout << "Input a command(0, 1-3):" ;
} // end PrintTitle

int main() {

    int command = 0 ;
    vector <Node> data ;
    PrintTitle() ;
    Tree tree1, tree2 ;
    while ( cin >> command && command ) {

        cin.ignore() ;
        if ( command == 1 && Read_File( data ) ) {
            tree1.init() ;
            tree2.init() ;
            cout << title << "\n" ;
            for ( int i = 0 ; i < data.size() ; i++ ) {
                cout << "[" << i+1 << "]\t" << data[i].school << "\t" << data[i].major << "\t" ;
                cout << data[i].DN_en << " " << data[i].DN_ch << "\t" << data[i].RK_en << " " ;
                cout << data[i].RK_ch << "\t" << data[i].student << "\t" << data[i].teacher << "\t" ;
                cout << data[i].graduate << "\n" ;
            } // end for


            tree1.createTree1( data ) ;
            tree2.createTree2( data ) ;
            cout << "\nTree height {School name} = " << tree1.Height() << "\n" ;
            cout << "\nTree height {Number of graduates} = " << tree2.Height() << "\n" ;

        } // end if
        else if ( command == 2 ) {
            cout << ;
            cin >> ;
        } // end else if
        else if ( command == 3 ) {
            cout << ;
            cin >> ;
        } // end else if
        else cout << "\nCommand does not exist!\n" ;
        data.clear() ;
        cout << "\n" ;
        PrintTitle() ;

    } // end while

    system("pause") ;
} // main()
