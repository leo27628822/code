// Team16_10927124_10927143
// 10927124徐翊華
#include <iostream>
#include <stdio.h>
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
#include <stack>
#include <iomanip>
#include <time.h>

#define MAX 200
#define LL long long

#define WEIGHT first
#define INDEX second

using namespace std ;

class Input{
protected:
    string newFileName = "",  oldFileName = "" ;

public:
    void Command(){
        cout << "\n\n***********************************************" << endl ;
        cout << "On-machine Exercise 05                        *" << endl ;
        cout << "Mission 1: External Merge Sort on a Big File *" << endl ;
        cout << "Mission 2: Construction of Primary Index      *" << endl ;
        cout << "***********************************************" << endl ;
    } // end Command

    bool FileName(){
        string fileNum = "" ;
        ifstream file ;

        while( true ){
            cout << endl << "Input a file number [0]Quit :" ;
            cin >> fileNum ;
            if( fileNum == "0" ) return false ;

            oldFileName = "pairs" + fileNum + ".bin" ;
            file.open( oldFileName ) ;
            if( file.is_open() ){
                newFileName = "sorted" + fileNum ;
                file.close() ;

                string name = newFileName + ".bin" ;
                file.open(name) ;

                if( file.is_open() ){
                    remove(name.c_str()) ;
                    file.close() ;
                } // end if

                return true ;
            } // end if

            cout << oldFileName << " does not exist!" << endl ;
        } // sure the file exist
    } // end FileName
}; // end class Input

class ExternalSort: public Input{
private:
    struct Data{
        char putID[10] ;
        char getID[10] ;
        float weight = -1 ;
    };

    Data data ;
    int total = 0 ;

    vector< pair<float, int> > catalog;

public:
    void Initial(){
        vector<Data> list ;

        ifstream inFile ;
        ofstream outFile ;
        inFile.open(oldFileName) ;

        string name ;

        inFile.seekg(0, ios::end);
        LL sum = inFile.tellg() / sizeof(Data);

        inFile.seekg(0, ios::beg);
        for( ; sum > 0 ; total++ ){
            name = newFileName + "_0_" + to_string(total) + ".bin";

            // INPUT
            if(sum >= MAX) list.resize(MAX) ;
            else list.resize(sum);

            sum -= MAX ;

            inFile.read( (char *) &list[0], list.capacity()*sizeof(Data));

            BubbleSort(list) ;

            // OUTPUT
            list.resize(list.size());
            outFile.open(name, ios::out | ios::binary | ios_base::trunc) ;
            outFile.write((char *) &list[0],sizeof(Data)*list.size());
            outFile.close();
        } // end for

        inFile.close() ;

        cout << "\nThe internal sort is completed. Check the initial sorted runs!" << endl << endl ;
    } // end Initial

    void BubbleSort(vector<Data> &list){
        for( int i = 0 ; i < list.size() - 1 ; i++ )
            for( int y = 0 ; y < list.size() - i - 1 ; y++ )
                if(list[y].weight < list[y+1].weight )
                    swap(list[y], list[y+1]) ;
    } // end BubbleSort

    // Merge Two File
    void MergeSort(ifstream &inFile1, ifstream &inFile2 ,ofstream &outFile){
        vector<Data> file1, file2, out ;

        inFile1.seekg(0, ios::end);
        inFile2.seekg(0, ios::end);
        LL T_num1 = inFile1.tellg() / sizeof(Data) ;
        LL T_num2 = inFile2.tellg() / sizeof(Data) ;

        inFile1.seekg(0, ios::beg);
        inFile2.seekg(0, ios::beg);

        while( file1.size() != 0 || file2.size() != 0 || T_num1 > 0 || T_num2 > 0 ){

            // MAKE UP TO 200
            if(file1.size() == 0 && T_num1 > 0){
                if( T_num1 >= MAX ) file1.resize(MAX);
                else file1.resize(T_num1);
                inFile1.read( (char *) &file1[0], file1.capacity() * sizeof(Data)) ;
                T_num1 -= MAX ;
            } // end if

            if(file2.size() == 0 && T_num2 > 0){
                if( T_num2 >= MAX ) file2.resize(MAX);
                else file2.resize(T_num2);
                inFile2.read( (char *) &file2[0], file2.capacity() * sizeof(Data)) ;
                T_num2 -= MAX ;
            } // end if


            // INSERT OUT
            if( file1.size() != 0 && file2.size() != 0 ){
                if(file1[0].weight < file2[0].weight){
                    out.push_back(file2[0]) ;
                    file2.erase(file2.begin()) ;
                } // end if

                else{
                    out.push_back(file1[0]) ;
                    file1.erase(file1.begin()) ;
                } // end else
            } // end if

            else{
                if( file1.size() == 0 ){
                    out.push_back(file2[0]) ;
                    file2.erase(file2.begin()) ;
                } // end if

                else{
                    out.push_back(file1[0]) ;
                    file1.erase(file1.begin()) ;
                } // end else
            } // end else

            if(out.size() == MAX || (file1.size() == 0 && file2.size() == 0)){
                out.resize(out.size()) ;
                outFile.write( (char *) &out[0],sizeof(Data)*out.size()) ;
                out.clear() ;
            } // end if
        } // end while

        file1.clear() ;
        file2.clear() ;
    } // end MergeSort

    void Merge(){
        ifstream inFile1, inFile2 ;
        ofstream outFile ;
        string name1, name2, outname ;

        for( int num = 0 ; total != 0 ; num++ ){
            // 總共有total個檔案，一次讀兩個檔案所以+2，i+1判斷檔案總數是否為奇數
            int i = 0 ;
            for( ; i+1 < total ; i = i+2 ){
                name1 = newFileName + '_' + to_string(num) + '_' + to_string(i) + ".bin" ;
                name2 = newFileName + '_' + to_string(num) + '_' + to_string(i+1) + ".bin" ;
                inFile1.open(name1) ;
                inFile2.open(name2) ;

                outname = newFileName + '_' + to_string(num+1) + '_' + to_string(i/2) + ".bin" ;

                outFile.open(outname, ios::out | ios::binary | ios_base::trunc) ;

                MergeSort(inFile1, inFile2, outFile) ;

                inFile1.close() ;
                inFile2.close() ;
                outFile.close() ;

                remove(name1.c_str());
                remove(name2.c_str());
            } // end for

            // total 95
            // 0 1 2 3 4 5 ...... 90 91 92 93 94
            // 0   1   2   ...... 45    46    47，重新命名94變47
            // 95 -> 48 -> 24
            if(total % 2 == 1){
                name1 = newFileName + "_" + to_string(num) + "_" + to_string(total-1) + ".bin" ;
                name2 = newFileName + "_" + to_string(num+1) + "_" + to_string((total-1)/2) + ".bin" ;
                rename(name1.c_str(), name2.c_str()) ;
                total = total / 2 + 1 ;
            }

            else total = total / 2 ;

            printf("Now there are %d runs.\n\n", total) ;

            if( total == 1 ){
                name1 = newFileName + "_" + to_string(num+1) + "_" + to_string(total-1) + ".bin" ;
                name2 = newFileName + ".bin" ;
                rename(name1.c_str(), name2.c_str()) ;
                total = 0 ;
                break ;
            }
        } // end for

    } // end Merge

    void CreatIndex(){
        cout << "<Primary index>: (key, offset)" << endl << endl ;

        vector<Data> list ;

        ifstream inFile ;
        newFileName += ".bin" ;
        inFile.open(newFileName) ;
        inFile.seekg(0, ios::end);

        LL sum = inFile.tellg() / sizeof(Data);
        inFile.seekg(0, ios::beg);

        cout << "SUM :" << sum << endl ;
        int start = 0 ;
        while( sum > 0 ){

            // INPUT
            if(sum >= MAX) list.resize(MAX) ;
            else list.resize(sum);
            sum -= MAX ;

            inFile.read( (char *) &list[0], list.capacity()*sizeof(Data));

            for( int i = 0 ; i < list.size() ; i++, start++ ){
                if( catalog.size() == 0 || catalog.back().WEIGHT != list[i].weight )
                    catalog.push_back(make_pair(list[i].weight, start)) ;

            } // end for

        } // end for

        inFile.close() ;

        for( int i = 0 ; i < catalog.size() ; i++ )
            cout << "[" << i+1 << "]  (" << catalog[i].WEIGHT << ", " << catalog[i].INDEX << ")" << endl ;

        cout << endl << endl ;
    } // end CreatIndex

    void Search(){
        float key ;
        while(true){
            cout << endl << endl ;
            cout << "Input a real number in [0,1]: " ;
            cin >> key ;
            if( key >= 0 && key <= 1 ) break ;
            cout << "### It is NOT in [0,1]" << endl << endl ;
        } // end while

        int i = 0 ;
        while(i < catalog.size() && key < catalog[i].WEIGHT) i++ ;

        vector<Data> list ;

        ifstream inFile ;
        inFile.open(newFileName) ;
        inFile.seekg(0, ios::end);

        LL sum ;
        if( i == catalog.size() ) sum = inFile.tellg() / sizeof(Data);
        else sum = catalog[i+1].INDEX ;

        inFile.seekg(0, ios::beg);

        int start = 1 ;
        while( sum > 0 ){
            // INPUT
            if(sum >= MAX) list.resize(MAX) ;
            else list.resize(sum);
            sum -= MAX ;

            inFile.read( (char *) &list[0], list.capacity()*sizeof(Data));

            for( int i = 0 ; i < list.size() ; i++, start++ )
                cout << "[" << start << "]\t"
                    << list[i].putID << "\t" << list[i].getID << "\t" << list[i].weight << endl ;

            list.clear() ;
        } // end while

        inFile.close();
    }

    void Clear(){
        catalog.clear() ;
    } // end Clear



}; // end class ExternalSort

int main() {
    Input input ;

    ExternalSort es;

    clock_t instart, inend, exstart, exend ;
    LL internal, external, total ;
    while(true){
        input.Command() ;

        if( !es.FileName() ) break ;

        else{
            cout << "\n\n########################################################" << endl ;
            cout << "Mission 1: External merge sort" << endl ;
            cout << "########################################################" << endl ;
            instart = clock() ;
            es.Initial() ;
            inend = clock() ;

            exstart = clock() ;
            es.Merge() ;
            exend = clock() ;
            internal = inend - instart ;
            external = exend - exstart ;
            total = internal + external ;
            cout << "The execution time ...\n" << endl ;
            printf("Internal Sort = %lld ms\n", internal) ;
            printf("External Sort = %lld ms\n", external) ;
            printf("Total Execution Time = %lld ms\n\n", total) ;

            system("pause") ;

            cout << "\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
            cout << "Mission 2: Build the primary index" << endl ;
            cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n" << endl ;
            es.CreatIndex() ;
            es.Clear() ;
//            system("pause") ;
//
//            cout << "\n\n########################################################" << endl ;
//            cout << "Mission 3: Search" << endl ;
//            cout << "########################################################" << endl ;
//            es.Search() ;

        }
    } // end progammimg
} // end main


