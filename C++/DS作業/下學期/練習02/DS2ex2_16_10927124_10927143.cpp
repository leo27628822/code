// Team16_10927124徐翊華 10927143王胤迦
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>

using namespace std ;

string command = "", file_name = "" ;

struct Inf{
    int index = 0 ;
    string school_name = "" ;
    string deparment_name = "" ;
    string Day_Night = "" ;
    string level = "" ;
    int student_num = 0 ;
};

vector<Inf> role, original ;
Inf inf ;

ifstream file ;

void InputCommand(){
    do{     // check if input command is correct
        cout << "*****  Search Tree Utilities   *****" << endl ;
        cout << "**  0. Quit                       **" << endl ;
        cout << "**  1. Build 2-3 tree             **" << endl ;
        cout << "**  2. Build AVL tree             **" << endl ;
        cout << "************************************" << endl ;
        cout << endl << "Input a command(0, 1, 2, 3): " ;
        cin >> command ;
        if(command != "0" && command != "1" && command != "2" && command != "3")
            cout << endl << endl << "Command does not exist!" << endl << endl ;
    } while (command != "0" && command != "1" && command != "2" && command != "3") ;
}

void InputFileName(){
    cout << endl << "Input a file number (e.g., 201, 202, ...): " ;
    cin >> file_name ;
    file_name = "input" + file_name + ".txt" ;

    file.open( file_name ) ;

    while( !file.is_open() ){   // ensure the .txt open
        cout << file_name << " does not exist!" << endl ;
        cout << endl << "Input a file number (e.g., 101, 102, ...): " ;
        cin >> file_name ;
        file_name = "input" + file_name + ".txt" ;
        file.open( file_name ) ;
    } // sure the file exist

    file.close() ;
}

string Correct_num( string buffer ){
    string a = "" ;
    for( int i = 0 ; i < buffer.size() ; i++ )
        if( isdigit(buffer[i]) ) a += buffer[i] ;
    return a ;
}

void ReadFile(){
    role.clear() ;
    original.clear() ;

    ifstream file ;
    string title, s_num ;
    char buffer[1024] ;
    int num = 1  ;

    file.open( file_name ) ;

    file.getline(buffer, sizeof(buffer)) ;
    file.getline(buffer, sizeof(buffer)) ;
    file.getline(buffer, sizeof(buffer)) ;

    while( !file.eof() ){
        inf.index = num ;   // 設定唯一序號

        for( int i = 0 ; i < 7 ; i++ ){
            file.getline(buffer, sizeof(buffer), '\t') ;
            title = buffer ;

            if( i == 0 && title == "" ){    //換行後什麼資料都沒有的情況
                file.close() ;
                return ;
            }

            if( i == 1 ) inf.school_name = buffer ;
            if( i == 3 ) inf.deparment_name = buffer ;
            if( i == 4 ) inf.Day_Night = buffer ;
            if( i == 5 ) inf.level = buffer ;
            if( i == 6 ) {
                s_num = Correct_num(buffer) ;
                inf.student_num = stoi(s_num) ;
            }
        }

        file.getline(buffer, sizeof(buffer)) ;
        role.push_back(inf) ;
        num++ ;
    }

    original = role ;

    file.close() ;
}


class Two_Three_Tree{
private:

    struct Tree{
        vector<vector<pair<int, string>>> school;
        Tree *left, *middle, *right, *father = NULL ;
    };

    vector<pair<int, string>> content ;
    Tree *head = NULL ;

public:
    void Insert(){
        bool equal = false ;

        if( head == NULL ){
            head = new Tree() ;
            content.push_back(make_pair(role[0].index, role[0].school_name)) ;
            head -> school.push_back(content) ;
            return ;
        } // if()

        Tree *cur = FindInsert( equal ) ;

        if( equal ){
            int i = 0  ;
            for( ; cur -> school[i][0].second != role[0].school_name ; i++ ) ;
            cur -> school[i].push_back(make_pair(role[0].index, role[0].school_name)) ;
            return ;
        }

        else{
            // push new slot
            content.clear() ;
            content.push_back(make_pair(role[0].index, role[0].school_name)) ;
            cur -> school.push_back(content) ;
            Sort(cur) ;

            if( cur -> school.size() == 3 ) Split(cur, NULL, NULL, NULL, NULL) ;
        }

    }

    Tree *FindInsert( bool &equal ){
        Tree *front = NULL;
        for ( Tree *temp = head ; temp != NULL ;){
            int i = 0 ;
            for( ; i < temp -> school.size() ; i++ ){
                if( temp -> school[i][0].second < role[0].school_name ){
                    break ;
                }

                else if( temp -> school[i][0].second == role[0].school_name ){
                    equal = true ;
                    return temp ;
                }
            } // end inner for

            front = temp ;

            if( temp -> school.size() == 1 ){
                if( i == 0 ) temp = temp -> left ;
                if( i == 1 ) temp = temp -> right ;
            }

            else if( temp -> school.size() == 2 ){
                if( i == 0 ) temp = temp -> left ;
                if( i == 1 ) temp = temp -> middle ;
                if( i == 2 ) temp = temp -> right ;
            }
        } // end outer for

        return front ;
    } // end FindInsert

    void Sort( Tree *ptr ){
        for( int x = 0 ; x < ptr -> school.size() ; x++ ){
            for( int y = 0 ; y < ptr -> school.size() ; y++ )
                if( ptr -> school[x][0].second > ptr -> school[y][0].second )
                    swap( ptr -> school[x], ptr -> school[y] ) ;
        }
    }

    void Split( Tree *ptr, Tree *left, Tree *mid1, Tree *mid2, Tree *right ){

        Tree *n1, *n2, *p ;
        n1 = new Tree() ;
        n2 = new Tree() ;

        // setting *p
        if( ptr == head ) p = new Tree() ;
        else p = ptr -> father ;

        // put into n1, n2, p
        n1 -> school.push_back(ptr->school[0]) ;
        n2 -> school.push_back(ptr->school[2]) ;
        p -> school.push_back(ptr->school[1]) ;

        Sort(p) ;

        // setting father pointer
        n1 -> father = p ;
        n2 -> father = p ;

        // if ptr is not LeafNode
        if( !(ptr -> left == NULL && ptr -> middle == NULL && ptr -> right == NULL) ){
            n1 -> left = left ;
            n1 -> right = mid1 ;
            n2 -> left = mid2 ;
            n2 -> right = right ;

            left -> father = n1 ;
            mid1 -> father = n1 ;
            mid2 -> father = n2 ;
            right -> father = n2 ;
        } // end if

        // if ptr is head
        if( ptr == head ){
            p -> left = n1 ;
            p -> right = n2 ;
            head = p ;
        } // end if

        else if( p -> school.size() == 3 ){

            if( ptr == p -> left )
                Split(p, n1, n2, p->middle, p->right) ;

            if( ptr == p -> middle )
                Split(p, p->left, n1, n2, p->right) ;

            if( ptr == p -> right )
                Split(p, p->left, p->middle, n1, n2) ;
        } // end else if

        else {
            if( ptr == p -> left ){
                p -> left = n1 ;
                p -> middle = n2 ;
            } // end if

            else {  // ptr == p -> right
                p -> middle = n1 ;
                p -> right = n2 ;
            } // end else

        } // end else
    }

    void Output(){
        // calculate Tree High
        int high = 0 ;
        for( Tree *temp = head ; temp != NULL ; temp = temp -> left, high++ ) ;
        cout << "Tree Hight : " << high << endl << endl ;

        // output the information
        int index = 1;

        for( int x = 0 ; x < head -> school.size() ; x++ ){
            for( int y = 0 ; y < head -> school[x].size() ; y++ ){
                cout << index << " : "  ;
                SearchFile(head -> school[x][y].first) ;
                index++ ;
            }
        }

        cout << endl << endl ;
    } // end Output

    void SearchFile(int index){
        int i = 0 ;
        for( i = 0 ; i < original.size() && original[i].index != index ; i++ ) ;
        cout << "[ " << original[i].index << " ]\t" << original[i].school_name << "\t"
        << original[i].deparment_name << "\t"
        << original[i].Day_Night << "\t" << original[i].level
        << "\t" << original[i].student_num << endl ;

    } // end SearchFile

    void Search( vector<int> &school, string key){
        if( key == "*" ){
            for( int i = 0 ; i < original.size() ; i++)
                school.push_back(original[i].index) ;
        } // end if

        else{
            Tree *cur = Search(head, key) ;
            if( cur == NULL ) return ;

            int x = 0 ;
            for(; key != cur -> school[x][0].second ; x++) ;
            for( int y = 0 ; y < cur -> school[x].size() ; y++)
                school.push_back(cur -> school[x][y].first) ;
        } // end else
    }

    Tree *Search( Tree *cur, string key){
        if( cur == NULL ) return NULL ;

        int i = 0 ;
        for( ; i < cur -> school.size() ; i++ ){
            if( cur -> school[i][0].second < key ){
                break ;
            }

            else if( cur -> school[i][0].second == key ){
                return cur ;
            }
        } // end inner for

        if( cur -> school.size() == 1 ){
            if( i == 0 ) return Search(cur -> left, key) ;
            if( i == 1 ) return Search(cur -> right, key) ;
        }

        else if( cur -> school.size() == 2 ){
            if( i == 0 ) return Search(cur -> left, key) ;
            if( i == 1 ) return Search(cur -> middle, key) ;
            if( i == 2 ) return Search(cur -> right, key) ;
        }

        return cur ;
    } // end Search

    void Clear(){
        content.clear();
        Clear(head) ;
    } // end Clear

    void Clear( Tree *root ){
        if( root == NULL ) {
            return ;
        }

        else if( root -> left == NULL ){
            root -> school.clear() ;
            root -> father = NULL ;
            root = NULL ;
            delete root ;
            return ;
        } // end if

        else if( root != NULL ){
            Clear( root -> left ) ;
            Clear( root -> middle ) ;
            Clear( root -> right ) ;
            root -> school.clear() ;
            root -> father = NULL ;
            root = NULL ;
            delete root ;
            return ;
        } // end else1

    } // end Clear

    bool HaveData(){
        if( head == NULL ) return false ;
        else return true ;
    } // end HaveData
};

class AVL{

private:
    struct Tree{
        vector<int> school ;
        string key = "" ;
        int hight = 1 ;
        Tree *left = NULL ;
        Tree *right = NULL;
    };

    Tree *head = NULL ;


public:
    void Insert(){
        head = Insert(head) ;
    } // end Insert for main

    Tree *Insert( Tree *cur ){

        // check the Location of Insert

        if( cur == NULL ){
            cur = new Tree ;
            cur -> school.push_back(role[0].index) ;
            cur -> key = role[0].deparment_name ;
            return cur ;
        } // end if

        else if( role[0].deparment_name < cur -> key ) cur -> left = Insert(cur -> left) ;

        else if( role[0].deparment_name > cur -> key ) cur -> right = Insert(cur -> right) ;

        else {
            cur -> school.push_back(role[0].index) ;
            return cur ;
        }

        // check the height
        cur -> hight = 1 + max(Height(cur->left), Height(cur -> right)) ;

        // balance factor
        int BF = 0 ;
        if( cur != NULL ) BF = Height(cur->left) - Height(cur->right) ;

        // four situations

        // LL
        if( BF == 2 && role[0].deparment_name < cur -> left -> key )
            return RightRotation(cur) ;

        // RR
        if( BF == -2 && role[0].deparment_name > cur -> right -> key )
            return LeftRotation(cur) ;

        // LR
        if( BF == 2 && role[0].deparment_name > cur -> left -> key ){
            cur -> left = LeftRotation(cur -> left) ;
            return RightRotation(cur) ;
        } // end LR

        // RL
        if( BF == -2 && role[0].deparment_name < cur -> right -> key ){
            cur -> right = RightRotation(cur -> right) ;
            return LeftRotation(cur) ;
        } // end RL

        return cur ;

    } // end Insert for


    int Height( Tree *cur ){
        if( cur == NULL ) return 0 ;
        else return cur -> hight ;
    } // end Height

    Tree *LeftRotation( Tree *cur ){
        Tree *center = cur -> right ;
        Tree *newLeft = center -> left ;

        center -> left = cur ;
        cur -> right = newLeft ;

        cur -> hight = 1 + max( Height(cur->left), Height(cur->right) ) ;
        center -> hight = 1 + max( Height(center->left), Height(center->right) ) ;

        return center ;

    } // end Left Rotation

    Tree *RightRotation( Tree *cur ){
        Tree *center = cur -> left ;
        Tree *newLeft = center -> right ;

        center -> right = cur ;
        cur -> left = newLeft ;

        cur -> hight = 1 + max( Height(cur->left), Height(cur->right) ) ;
        center -> hight = 1 + max( Height(center->left), Height(center->right) ) ;

        return center ;

    } // end Right Rotation

    void Output(){
        // calculate Tree High
        cout << "Tree Hight : " << head -> hight << endl << endl ;

        // output the information

        for( int i = 0 ; i < head -> school.size() ; i++ ){
            cout << i+1 << " : "  ;
            SearchFile(head -> school[i]) ;
        } // end for

        cout << endl << endl ;
    } // end Output


    void SearchFile(int index){
        int i = 0 ;
        for( i = 0 ; original[i].index != index ; i++ ) ;
        cout << "[ " << original[i].index << " ]\t" << original[i].school_name << "\t"
        << original[i].deparment_name << "\t"
        << original[i].Day_Night << "\t" << original[i].level
        << "\t" << original[i].student_num << endl ;

    } // end SearchFile

    void Clear(){
        Clear(head) ;
    } // end Clear

    void Clear( Tree *root ){
        if( root == NULL ) {
            return ;
        } // end if

        else if( root -> left == NULL ){
            root -> school.clear() ;
            root = NULL ;
            delete root ;
            return ;
        } // end else if

        else if( root != NULL ){
            Clear( root -> left ) ;
            Clear( root -> right ) ;
            root -> school.clear() ;
            root = NULL ;
            delete root ;
            return ;
        } // end else

    } // end Clear

    void Search(vector<int> &department, string key){
        if( key == "*" ){
            for( int i = 0 ; i < original.size() ; i++)
                department.push_back(original[i].index) ;
        } // end if

        else{
            Tree *cur = Search(head, key) ;
            if( cur == NULL ) return ;
            department = cur -> school ;
        } // end else
    } // end Search

    Tree *Search(Tree *cur, string key){
        if( cur == NULL ) return NULL ;
        else if( key == cur -> key ) return cur ;
        else if( key < cur -> key ) return Search(cur -> left, key) ;
        else return Search(cur -> right, key) ;
    } // end Search

    bool HaveData(){
        if( head == NULL ) return false ;
        else return true ;
    } // end HaveData
};


int main(){
    InputCommand() ;
    Two_Three_Tree two_three_tree ;
    AVL avl ;

    while( command != "0" && command != "1" ){
        cout << "\nPlease input '1' at the first time.\n\n" ;
        InputCommand() ;
    }

    while( command != "0" ){
        if( command == "1" ){
            two_three_tree.Clear() ;
            two_three_tree = *new Two_Three_Tree() ;

            InputFileName() ;
            ReadFile() ;
            original = role ;

            while( role.size() != 0 ){
                two_three_tree.Insert() ;
                role.erase(role.begin()) ;
            } // end while

            two_three_tree.Output() ;
        } // end commamd1

        else if( command == "2" ){
            avl.Clear() ;
            avl = *new AVL() ;

            role = original ;
            while( role.size() != 0 ){
                avl.Insert() ;
                role.erase(role.begin()) ;
            } // end while

            avl.Output() ;
        } // end commamd2

        else if( command == "3" ){
            if( !two_three_tree.HaveData() ) cout << "Please enter command 1 first." << endl ;

            else if( !avl.HaveData() ) cout << "Please enter command 2 first." << endl ;

            else{
                vector<int> school, department, both ;
                string key1, key2 ;

                cout << endl << "KEY1 : " ;
                cin >> key1 ;
                two_three_tree.Search(school, key1) ;

                cout << endl << "KEY2 : " ;
                cin >> key2 ;
                avl.Search(department, key2) ;

                for( int x = 0 ; x < school.size() ; x++ )
                    for( int y = 0 ; y < department.size() ; y++ )
                        if( school[x] == department[y] )
                            both.push_back(school[x]) ;

                cout << endl ;
                for( int i = 0 ; i < both.size() ; i++ )
                    two_three_tree.SearchFile(both[i]) ;

                cout << endl << endl ;

                school.clear();
                department.clear() ;
                both.clear() ;
            } // end else

        } // end commamd3

        InputCommand() ;
    }
}
