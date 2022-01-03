// DS1101ex5_20_10927143_10927141
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

string title ;

struct Node{
    int student, teacher, graduate ;
    string school, major, DN_en, DN_ch, RK_en, RK_ch ;
};

class Tree {
    private :
        int height ;
    public :
        struct TreeNode {
            Node node ;
            TreeNode * left ;
            TreeNode * right ;
        };
        TreeNode * root ;
        int getHeight( TreeNode * ) ;
        int Height() {
            return getHeight( root ) ;
        } // end if

        Tree() {
            root = NULL ;
            height = 0 ;
        } // end Tree

        ~Tree() {
            delete root ;
            root = NULL ;
        } // end ~Tree

        void createTree1( vector<Node> tree ) ;
        void createTree2( vector<Node> tree ) ;
        bool isEmpty() {
            return root == NULL ;
        } // end isEmpty

        TreeNode * getRoot() {
            return root ;
        } // end getRoot

        void setRoot( TreeNode * node ) {
            root = node ;
        } // end setRoot

        void init() {
            root = NULL ;
        } // end init

        TreeNode * search_name2( string name, TreeNode * temp, bool & find ) {
            if ( temp == NULL ) return temp ;
            if ( temp -> node.school == name ) {
                find = true ;
                return temp ;
            } // end if
            if ( !find ) return search_name2( name, temp -> left, find ) ;
            if ( !find ) return search_name2( name, temp -> right, find ) ;
            return temp ;
        } // end

        void search_name( string name, TreeNode * tempPtr, int & i, bool & find ) ;
        void search_graduate( int number, TreeNode * tempPtr, int & i, bool & find ) ;
        bool delete_name( string name, int & i ) ;
        void process( string name, TreeNode * tempPtr, TreeNode * prePtr, TreeNode * deletePtr, int & i ) ;
        void process2( string name, TreeNode * tempPtr, TreeNode * prePtr, TreeNode * deletePtr ) ;
};

int Tree::getHeight( TreeNode * temp ) {
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

void Tree::search_name( string name, TreeNode * tempPtr, int & i, bool & find ) {
    if ( tempPtr == NULL ) return ;
    if ( tempPtr -> node.school == name ) {
        find = true ;
        cout << "[" << i+1 << "]\t" << tempPtr -> node.school << "\t" << tempPtr -> node.major << "\t" ;
        cout << tempPtr -> node.DN_en << " " << tempPtr -> node.DN_ch << "\t" << tempPtr -> node.RK_en << " " ;
        cout << tempPtr -> node.RK_ch << "\t" << tempPtr -> node.student << "\t" << tempPtr -> node.teacher << "\t" ;
        cout << tempPtr -> node.graduate << "\n" ;
        i++ ;
    } // end if
    if ( name < tempPtr -> node.school ) search_name( name, tempPtr -> left, i, find ) ;
    else search_name( name, tempPtr -> right, i, find ) ;
} // end search_name

void Tree::search_graduate( int number, TreeNode * tempPtr, int & i, bool & find ) {
    if ( tempPtr == NULL ) return ;
    if ( tempPtr -> node.graduate >= number ) {
        find = true ;
        cout << "[" << i+1 << "]\t" << tempPtr -> node.school << "\t" << tempPtr -> node.major << "\t" ;
        cout << tempPtr -> node.DN_en << " " << tempPtr -> node.DN_ch << "\t" << tempPtr -> node.RK_en << " " ;
        cout << tempPtr -> node.RK_ch << "\t" << tempPtr -> node.student << "\t" << tempPtr -> node.teacher << "\t" ;
        cout << tempPtr -> node.graduate << "\n" ;
        i++ ;
        search_graduate( number, tempPtr -> left, i, find ) ;
    } // end if
    search_graduate( number, tempPtr -> right, i, find ) ;
} // end search_name

bool Tree::delete_name( string name, int & i ) {
    TreeNode * tempPtr = getRoot(), * prePtr = NULL , * deletePtr = NULL ;

    while ( tempPtr != NULL && tempPtr -> node.school != name ) {
        prePtr = tempPtr ;
        if ( name < tempPtr -> node.school ) tempPtr = tempPtr -> left ;
        else tempPtr = tempPtr -> right ;
    } // end while
    //bool find = false ;
    //tempPtr = search_name2( name, tempPtr, find ) ;

    if ( tempPtr != NULL ) {
        deletePtr = tempPtr ;
        if ( tempPtr != getRoot() ) process( name, tempPtr, prePtr, deletePtr, i ) ;
        else {
            cout << "[" << i+1 << "]\t" << root -> node.school << "\t" << root -> node.major << "\t" ;
            cout << root -> node.DN_en << " " << root -> node.DN_ch << "\t" << root -> node.RK_en << " " ;
            cout << root -> node.RK_ch << "\t" << root -> node.student << "\t" << root -> node.teacher << "\t" ;
            cout << root -> node.graduate << "\n" ;
            i++ ;
            if ( root -> left == NULL && root -> right == NULL ) {
                root = NULL ;
            } // end if
            else if ( root -> left != NULL && root -> right == NULL ) {
                TreeNode * temp = root ;
                root = root -> left ;
                delete temp ;
            } // else if
            else if ( root -> left == NULL && root -> right != NULL ) {
                TreeNode * temp = root ;
                root = root -> right ;
                delete temp ;
                temp = NULL ;
                if ( root -> node.school == name ) delete_name( name, i ) ;
            } // else if
            else {

                TreeNode * pre , * temp = root ;
                pre = temp ;
                temp = temp -> right ;
                if ( temp -> node.school == name ) {
                    temp -> left = root -> left ;
                    root = root -> right ;
                } // end if
                else {
                    while ( temp -> left != NULL ) {
                        pre = temp ;
                        temp = temp -> left ;

                    } // while

                    root -> node = temp -> node ;

                    if ( temp -> right != NULL ) pre -> left = temp -> right ;
                    delete temp ;
                    temp = NULL ;
                } // end else

                delete_name( name, i ) ;
            } // end else
        } // end else
        return true ;
    } // end if
    else return false ;
} // end delete_name

void Tree::process( string name, TreeNode * tempPtr, TreeNode * prePtr, TreeNode * deletePtr, int & i ) {
    TreeNode * temp = deletePtr ;
    cout << "[" << i+1 << "]\t" << deletePtr -> node.school << "\t" << deletePtr -> node.major << "\t" ;
    cout << deletePtr -> node.DN_en << " " << deletePtr -> node.DN_ch << "\t" << deletePtr -> node.RK_en << " " ;
    cout << deletePtr -> node.RK_ch << "\t" << deletePtr -> node.student << "\t" << deletePtr -> node.teacher << "\t" ;
    cout << deletePtr -> node.graduate << "\n" ;
    i++ ;
    if ( temp -> left == NULL && temp -> right != NULL ) {
        if ( temp -> node.school < prePtr -> node.school ) {
            prePtr -> left = temp -> right ;
            temp = prePtr -> left ;
        } // end if
        else {
            prePtr -> right = temp -> right ;
            temp -> left = temp -> right = NULL ;
            delete temp ;
            temp = prePtr -> right ;
        } // end else
        if ( temp -> node.school == name ) {
            deletePtr = temp ;
            process( name, temp, prePtr, deletePtr, i ) ;
        } // end if
    } // end if   DONE!
    else if ( temp -> left != NULL && temp -> right == NULL ) {
        if ( prePtr -> node.school < deletePtr ->node.school) prePtr -> right = deletePtr -> left ;
        else prePtr -> left = deletePtr -> left ;
        deletePtr ->left = deletePtr -> right = NULL ;
        delete deletePtr ;
    } // end else if
    else if ( temp -> left != NULL && temp -> right != NULL ) {
        TreeNode * pre = temp ;
        temp = temp -> right ;
        if ( temp -> node.school == name ) {
            temp -> left = pre -> left ;
            deletePtr = temp ;
            process( name, temp, prePtr, deletePtr, i ) ;
        } // end if
        else process2( name, temp, prePtr, deletePtr ) ;
    } // end else
    else {
        if ( deletePtr -> node.school < prePtr -> node.school ) prePtr ->left = NULL ;
        else prePtr -> right = NULL ;
        deletePtr -> left = deletePtr -> right = NULL ;
        delete deletePtr ;
        deletePtr = NULL ;
    } // end else
} // end process

void Tree::process2( string name, TreeNode * tempPtr, TreeNode * prePtr, TreeNode * deletePtr ) {
    TreeNode * temp = tempPtr ;

    if ( temp -> left != NULL ) {
        TreeNode * pre = temp ;

        while ( temp -> left != NULL ) {
            pre =temp ;
            temp = temp -> left ;
        } // end while

        deletePtr -> node = temp -> node ;
        if ( temp -> right != NULL ) pre -> left = temp -> right ;
        delete temp ;
        temp = NULL ;
    } // end if
    else {
        if ( deletePtr -> node.school > prePtr -> node.school ) prePtr -> right = temp ; // temp -> left == NULL
        else prePtr -> left = temp ;
        temp -> left = deletePtr -> left ;
        deletePtr -> left = deletePtr -> right = NULL ;
        delete deletePtr ;
        deletePtr = NULL ;
    } // end else
} // end process2

bool Read_File( vector <Node> & data ) {
    data.clear() ;
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
    cout << "* 4. Removal by School Name                  *\n" ;
    cout << "**********************************************\n" ;
    cout << "Input a command(0, 1-4):" ;
} // end PrintTitle

int main() {

    int command = 0 ;
    vector <Node> data ;
    PrintTitle() ;
    Tree tree1, tree2 ;
    bool check = false, find = false ;
    while ( cin >> command && command ) {

        cin.ignore() ;
        if ( command == 1 && Read_File( data ) ) {
            check = true ;
            tree1.init() ;
            tree2.init() ;
            /*
            for ( int i = 0 ; i < data.size() ; i++ ) {
                cout << "[" << i+1 << "]\t" << data[i].school << "\t" << data[i].major << "\t" ;
                cout << data[i].DN_en << " " << data[i].DN_ch << "\t" << data[i].RK_en << " " ;
                cout << data[i].RK_ch << "\t" << data[i].student << "\t" << data[i].teacher << "\t" ;
                cout << data[i].graduate << "\n" ;
            } // end for
            */
            tree1.createTree1( data ) ;
            tree2.createTree2( data ) ;
            cout << "\nTree height {School name} = " << tree1.Height() << "\n" ;
            cout << "\nTree height {Number of graduates} = " << tree2.Height() << "\n" ;
        } // end if
        else if ( command == 2 ) {
            if ( !check ) cout << "\nPlease choose command 1 first!\n" ;
            else {
                int number ;
                cout << "Input the number of graduates:" ;
                while ( cin >> number && number < 0 ) {
                    cout << "\n### the input number " << number << " is not a decimal number! ###\n" ;
                    cout << "Input the number of graduates:" ;
                } // end while
                cin.ignore() ;
                int i = 0 ;
                tree2.search_graduate( number, tree2.getRoot(), i, find ) ;
                if ( !find ) cout << "There is no match!\n" ;
            } // end else
        } // end else if
        else if ( command == 3 ) {
            if ( !check ) cout << "\nPlease choose command 1 first!\n" ;
            else {
                string name ;
                cout << "Input a school name:" ;
                getline( cin, name ) ;
                int i = 0 ;
                tree1.search_name( name, tree1.getRoot(), i, find ) ;
                if ( !find ) cout << "There is no match!\n" ;
            } // end else
        } // end else if
        else if ( command == 4 ) {
            if ( !check ) cout << "\nPlease choose command 1 first!\n" ;
            else {
                string name ;
                cout << "Input a school name:" ;
                getline( cin, name ) ;
                int i = 0 ;
                if ( tree1.delete_name( name, i ) ) {

                    for ( int i = 0 ; i < data.size() ; i++ ) {
                        if ( data[i].school == name  ) {
                            data.erase( data.begin() + i ) ;
                            i-- ;
                        } // end if
                    } // end for
                    tree2.init() ;
                    tree2.createTree2( data ) ;
                } // end if
                else cout << "There is no match!\n" ;
                cout << "\nTree height {School name} = " << tree1.Height() << "\n" ;
                cout << "\nTree height {Number of graduates} = " << tree2.Height() << "\n" ;
            } // end else
        } // end else
        else cout << "\nCommand does not exist!\n" ;
        find = false ;
        cout << "\n" ;
        PrintTitle() ;

    } // end while

    system("pause") ;
} // main()
