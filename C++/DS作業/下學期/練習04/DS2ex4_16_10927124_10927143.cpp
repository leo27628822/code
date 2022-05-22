// Team16_10927124_10927143
// 10927124ฎ}ึ๖ตุ
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <utility>
#include <stack>
#include <ctime>
#include <queue>
#include <iomanip>

#define ID first
#define WEIGHT second

using namespace std ;

class Input{
protected:
    struct Inf{
        char putID[10] ;
        char getID[10] ;
        float weight ;
    };

    Inf inf ;
    vector<Inf> list ;

    string file_num = "" ;

public:
    string Command(){
        string command ;
        while( true ){    // check if input command is correct
            cout << "******    Influence on a graph   ******" << endl ;
            cout << "**  0. Quit                          **" << endl ;
            cout << "**  1. Build adjacency lists         **" << endl ;
            cout << "**  2. Compute influence values      **" << endl ;
            cout << "***************************************" << endl ;
            cout << endl << "Input a command(0, 1, 2): " ;
            cin >> command ;

            if(command != "0" && command != "1" && command != "2")
                cout << endl << endl << "Command does not exist!" << endl << endl ;

            else return command ;
        } // end while
    } // end Command

    void File(){
        ifstream file ;
        string file_name = "" ;

        while( true ){
            cout << endl << "Input a file number (e.g., 401, 402, ...): " ;
            cin >> file_num ;
            file_name = "pairs" + file_num + ".bin" ;
            file.open( file_name ) ;
            if( file.is_open() ){
                ReadBin(file_name) ;
                return;
            } // end if

            cout << file_name << " does not exist!" << endl ;
        } // sure the file exist
    } // end FileName

    void ReadBin(string file_name){
        ifstream file(file_name, ios::binary) ;
        for( int index = 0 ; file.peek() != EOF ; index++ ){
            list.push_back(inf) ;
            file.read((char*)&list[index], sizeof(list[index]));
        } // end for

        file.close() ;
    } // end ReadBin

}; // end class Input

class ADJ:public Input{
private:
    enum Situation{ visited, unvisited } ;

    struct Content{
        string putID = "" ;
        vector<pair<string, float>> adj_suc ;
        Situation situation = unvisited ;
    };

    vector<Content> adj_pre ;
    Content content ;

    struct Data{
        string putID = "" ;
        vector<string> successor ;
    };

    vector<Data> predecessor ;
    Data data ;

public:
    void Insert(){
        while( list.size() > 0 ){
            int pre; // pre = predecessor

            // add list[0].putID to vector putID
            for( pre = 0 ; pre < adj_pre.size() && adj_pre[pre].putID != list[0].putID ; pre++ ) ;
            if( pre == adj_pre.size() ){
                adj_pre.push_back(content) ;
                adj_pre[pre].putID = list[0].putID ;
            } // end find predecessor

            // add list[0].getId to vector putID[getID]
            adj_pre[pre].adj_suc.push_back(make_pair(list[0].getID, list[0].weight)) ;

            // add list[0].getId to vector putID
            for( pre = 0 ; pre < adj_pre.size() && adj_pre[pre].putID != list[0].getID ; pre++ ) ;
            if( pre == adj_pre.size() ){
                adj_pre.push_back(content) ;
                adj_pre[pre].putID = list[0].getID ;
            } // end find predecessor

            list.erase(list.begin()) ; // delete the first list
        } // end for, end vector list

        Sort() ;
    } // end Insert

    void Sort(){
        // sort putID
        for( int x = 0 ; x < adj_pre.size() ; x++ )
            for( int y = x+1 ; y < adj_pre.size() ; y++ )
                if( adj_pre[x].putID > adj_pre[y].putID ) swap(adj_pre[x], adj_pre[y]) ;

        // sort Weight
        for( int index = 0 ; index < adj_pre.size() ; index++ ){
            for( int x = 0 ; x < adj_pre[index].adj_suc.size() ; x++ ){
                for( int y = x+1 ; y < adj_pre[index].adj_suc.size() ; y++ ){
                    if( adj_pre[index].adj_suc[x].WEIGHT < adj_pre[index].adj_suc[y].WEIGHT ) swap(adj_pre[index].adj_suc[x], adj_pre[index].adj_suc[y]) ;
                    if( adj_pre[index].adj_suc[x].WEIGHT == adj_pre[index].adj_suc[y].WEIGHT)
                        if( adj_pre[index].adj_suc[x].ID > adj_pre[index].adj_suc[y].ID )
                            swap(adj_pre[index].adj_suc[x], adj_pre[index].adj_suc[y]) ;
                } // end inner for
            } // end middle for
        } // end outer for

    } // end Sort

    void WriteData(){
        int total = 0 ;

        ofstream file ;
        file.open("pairs"+file_num+".adj") ;

        file << "<<< There are " << adj_pre.size() << " IDs in total. >>>" << endl ;

        for( int index = 0 ; index < adj_pre.size() ; index++ ){
            file << "[" << setw(3) << index+1 << "] " << adj_pre[index].putID << ": " << endl;

            for( int i = 0 ; i < adj_pre[index].adj_suc.size() ; i++ ){
                file << "\t(" << setw(2) << i+1 << ") " ;
                file << adj_pre[index].adj_suc[i].ID << "," << setw(6) << adj_pre[index].adj_suc[i].WEIGHT ;
                if( (i+1) % 10 == 0 ) file << endl ;
            } // end input successor

            file << endl ;
        } // end input predecessor

        for( int index = 0 ; index < adj_pre.size() ; index++ ) total += adj_pre[index].adj_suc.size() ;
        file << "<<< There are " << total << " nodes in total. >>>" << endl ;

        file.close() ;

        cout << "<<< There are " << adj_pre.size() << " IDs in total. >>>" << endl << endl ;
        cout << "<<< There are " << total << " nodes in total. >>>" << endl << endl ;
    } // end WriteData

    void Clear(){
        adj_pre.clear() ;
        list.clear() ;
    } // end Clear

    void NumInfluence(){
        for( int index = 0 ; index < adj_pre.size() ; index++ )
            BFS(adj_pre[index].putID) ;

        // SORT
        for( int x = 0 ; x < predecessor.size() ; x++ )
            for( int y = x+1 ; y < predecessor.size() ; y++ )
                if( predecessor[x].successor.size() < predecessor[y].successor.size() )
                    swap(predecessor[x], predecessor[y]) ;

        for( int index = 0 ; index < predecessor.size() ; index++ ){
            for( int x = 0 ; x < predecessor[index].successor.size() ; x++ )
                for( int y = x+1 ; y < predecessor[index].successor.size() ; y++ )
                    if( predecessor[index].successor[x] > predecessor[index].successor[y] ) swap(predecessor[index].successor[x], predecessor[index].successor[y]) ;
        } // end for

    } // end NumInfluence


    void BFS(string pre){
        queue<string> q ;
        q.push(pre);
        predecessor.push_back(data) ;
        unsigned long end = predecessor.size()-1 ;
        predecessor[end].putID = pre ;

        while( !q.empty() ){
            int target ;
            for( target = 0 ; adj_pre[target].putID != q.front() ; target++ ) ;
            adj_pre[target].situation = visited ;

            // put all the putID from adj_pre[target] into queue
            // target is a predecessor
            // suc means successor
            for( int suc = 0 ; suc < adj_pre[target].adj_suc.size() ; suc++ ){

                // avoid put visited vertex into vector
                if( Unvisited(adj_pre[target].adj_suc[suc].ID ) ){

                    // avoid put added vertex into vector
                    if( !Added(adj_pre[target].adj_suc[suc].ID)){
                        adj_pre[target].situation = visited ;
                        string getID = adj_pre[target].adj_suc[suc].ID ;
                        q.push(getID) ;
                        predecessor[end].successor.push_back(getID) ;
                    } // end if

                } // end if

            } // end for


            q.pop() ;
        } // end while

        for( int i = 0 ; i < adj_pre.size() ; i++ )
            adj_pre[i].situation = unvisited ;

    } // end BFS

    bool Added( string id ){
        int i ;
        unsigned long end = predecessor.size()-1 ;
        for( i = 0 ; i < predecessor[end].successor.size() && predecessor[end].successor[i] != id ; i++ ) ;
        if( i < predecessor[end].successor.size() ) return true ;
        else return false ;
    } // end Added

    bool Unvisited( string id ){
        int i ;
        for( i = 0 ; adj_pre[i].putID != id ; i++ ) ;
        if( adj_pre[i].situation == unvisited ) return true ;
        else return false ;
    } // end Unvisited

    void WriteNumData(){
        ofstream file ;
        file.open("pairs"+file_num+".cnt") ;

        file << "<<< There are " << predecessor.size() << " IDs in total. >>>" << endl ;

        for( int index = 0 ; index < predecessor.size() ; index++ ){
            file << "[" << setw(3) << index+1 << "] " << predecessor[index].putID ;
            file << "(" << predecessor[index].successor.size() << "): " << endl ;

            for( int i = 0 ; i < predecessor[index].successor.size() ; i++ ){
                file << "\t(" << setw(2) << i+1 << ") " << predecessor[index].successor[i];
                if( (i+1) % 10 == 0 ) file << endl ;
            } // end input successor

            file << endl ;
        } // end input predecessor

        file.close() ;

        cout << "<<< There are " << predecessor.size() << " IDs in total. >>>" << endl << endl ;
    } // end WriteNumData

    void NumClear(){
        predecessor.clear() ;
    } // end NumClear
};

int main() {
    Input input ;
    ADJ adj ;

    while(true){
        string command = input.Command() ;

        if( command == "0" ) break ;

        if( command == "1" ){
            adj.Clear() ;
            adj.File() ;
            adj.Insert() ;
            adj.WriteData() ;
        } // end command1

        if( command == "2" ){
            adj.NumClear() ;
            adj.NumInfluence() ;
            adj.WriteNumData() ;
        } // end command2

    } // end progammimg
} // end main
