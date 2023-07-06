#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <thread>
#include <chrono>


/*
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/syscall.h>
*/

using namespace std ;

void BubbleSort(vector<int> & nums, int len ) {
	bool isSwapped = false ;
	int lastSwap = 0 ;
	int k = len - 1 ;
	for (int i = 0 ; i < len ; i++ ) {
		isSwapped = false;
		for (int j = 0; j < k; j++ ) {
			if (nums[j] > nums[j + 1] ) {
				nums[j] = nums[j] ^ nums[j + 1] ;
				nums[j + 1] = nums[j + 1] ^ nums[j] ;
				nums[j] = nums[j] ^ nums[j + 1] ;
				isSwapped = true ;

				lastSwap = j;
			}
		}
		if ( !isSwapped ) {
            break ;
        }
		k = lastSwap;
	}
}

void mergeSort( vector<int> &left, vector<int> &right, vector<int> &bars) {
    int nL = left.size();
    int nR = right.size();
    int j = 0 ;
    int k = 0 ;

    while (j < nL && k < nR) {
        if ( left[j] <= right[k] ) {
            bars.push_back(left[j]) ;
            ++j ;
        }
        else {
            bars.push_back(right[k]) ;
            ++k ;
        }
    }

    while (j < nL) {
        bars.push_back(left[j]) ;
        j++ ;
    }

    while (k < nR) {
        bars.push_back(right[k]) ;
        k++ ;
    }

}

int main() {
    clock_t start, end ;
    double cpu_time_used ;
    string name, input_file, output_file ;
    vector<int> num ;
    int k ;
    int method ;
    int N ;

    while ( 1 ) {
        cout << "Input Filename:(1,10,50,100)\n" ;
        while( cin >> name && name != "1" && name != "10" && name != "50" && name != "100" ) {
            if ( name == "-1" ) return 0 ;
            cout << "Input Error!\n" << endl ;
            cout << "Input Filename:(1,10,50,100)\n" ;
        }

        input_file = "input_" + name + "w.txt" ;

        if ( input_file == "input_1w.txt" )
            num.reserve(10000) ;
        else if ( input_file == "input_10w.txt" )
            num.reserve(100000) ;
        else if ( input_file == "input_50w.txt" )
            num.reserve(500000) ;
        else if ( input_file == "input_100w.txt" )
            num.reserve(1000000) ;
        else {
            cout << "Input Error!\n" << endl ;
            continue ;
        }

        cout << "Input K:\n" ;
        while ( cin >> k &&  k < 1 || k > 100 ) {
            if ( k == -1 ) return 0 ;
            cout << "Input Error!\n" << endl ;
            cout << "Input K:\n" ;
        }

        cout << "Input Method:(1, 2, 3, 4)\n" ;
        while ( cin >> method &&  method < 1 || method > 4 ) {
            if ( method == -1 ) return 0 ;
            cout << "Input Error!\n" ;
            cout << "Input Method:(1, 2, 3, 4)\n" ;
        }

        fstream input ;
        input.open( input_file ) ;
        if ( !input.is_open()) {
            cout << "Fail to open!\n" ;
            input.close() ;
            continue ;
        }

        int data ;
        int i = 0 ;
        while ( !input.eof() ) {
            input >> data ;
            if ( input.fail() ) break ;
            num.insert( num.begin()+i, data ) ;
            ++i ;
        }

        if ( method == 1 ) {
            start = clock() ;
            BubbleSort( num, num.size() ) ;
            end = clock() ;
        }
        else {
            start = clock() ;
            int each_slice = num.size() / k ;
            vector<vector<int>> vector_set ;
            vector<int> temp ;
            for ( int j = 0 ; j < k-1 ; j++) {
                temp.clear() ;
                temp.shrink_to_fit() ;
                temp.reserve( each_slice ) ;
                move( begin(num)+j*each_slice, std::begin(num)+(j+1)*each_slice, back_inserter(temp));
                vector_set.push_back( temp ) ;
            }

            temp.clear() ;
            temp.shrink_to_fit() ;
            temp.reserve( num.size() - (k-1)*each_slice ) ;
            for ( int j = 0 ; j < num.size() - (k-1)*each_slice ; j++ ) {
                temp.push_back( num[j+(k-1)*each_slice] ) ;
            }

            vector_set.push_back( temp ) ;

            temp.clear() ;
            temp.shrink_to_fit() ;

            if ( method == 2 ) {
                for ( int j = 0 ; j < vector_set.size() ; j++ ) {
                    BubbleSort( vector_set[j], vector_set[j].size() ) ;
                }

                vector<vector<int>> temp_vector_set ;
                do {
                    temp_vector_set.clear() ;
                    temp_vector_set.shrink_to_fit() ;
                    for ( int j = 0 ; j < vector_set.size() ; j+=2 ) {
                        if ( j+1 < vector_set.size() ) {
                            temp.clear() ;
                            temp.shrink_to_fit() ;
                            temp.reserve( vector_set[j].size() + vector_set[j+1].size() ) ;
                            mergeSort( vector_set[j], vector_set[j+1], temp ) ;
                            temp_vector_set.push_back( temp ) ;
                        }
                        else {
                            temp_vector_set.push_back( vector_set[j] ) ;
                        }
                    }
                    vector_set.clear() ;
                    vector_set.shrink_to_fit() ;
                    copy(std::begin(temp_vector_set), std::end(temp_vector_set), std::back_inserter(vector_set));
                } while ( temp_vector_set.size() != 1 ) ;

                num.clear() ;
                num.shrink_to_fit() ;
                copy(std::begin(temp_vector_set[0]), std::end(temp_vector_set[0]), std::back_inserter(num));
                temp.clear() ;
                temp.shrink_to_fit() ;
                end = clock() ;
            }
            else if ( method == 4 ) {
                vector<thread> threads ;
                for ( int j = 0 ; j < vector_set.size() ; j++ ) {
                    threads.push_mingw64back( thread( BubbleSort, vector_set[j], vector_set[j].size() ) ) ;
                }

                for ( int j = 0 ; j < threads.size() ; j++ ) {
                    threads[j].join() ;
                }

                threads.clear() ;
                threads.shrink_to_fit() ;
                vector<vector<int>> temp_vector_set ;
                do {
                    temp_vector_set.clear() ;
                    temp_vector_set.shrink_to_fit() ;
                    for ( int j = 0 ; j < vector_set.size() ; j+=2 ) {
                        if ( j+1 < vector_set.size() ) {
                            temp.clear() ;
                            temp.shrink_to_fit() ;
                            temp.reserve( vector_set[j].size() + vector_set[j+1].size() ) ;
                            threads.push_back( thread( mergeSort, vector_set[j], vector_set[j+1], temp ) ) ;
                            // mergeSort( vector_set[j], vector_set[j+1], temp ) ;
                            temp_vector_set.push_back( temp ) ;
                        }
                        else {
                            temp_vector_set.push_back( vector_set[j] ) ;
                        }
                    }

                    for ( int j = 0 ; j < threads.size() ; j++ ) {
                        threads[j].join() ;
                    }
                    cout << "threads.size() = " << threads.size() << endl ;
                    vector_set.clear() ;
                    vector_set.shrink_to_fit() ;
                    copy(std::begin(temp_vector_set), std::end(temp_vector_set), std::back_inserter(vector_set));
                } while ( temp_vector_set.size() != 1 ) ;

                num.clear() ;
                num.shrink_to_fit() ;
                copy(std::begin(temp_vector_set[0]), std::end(temp_vector_set[0]), std::back_inserter(num));
                temp.clear() ;
                temp.shrink_to_fit() ;
                end = clock() ;
            }
        }
        ofstream output ;
        output_file = "input_" + name + "w_output" + to_string( method ) + ".txt" ;
        output.open( output_file ) ;
        output << "Sort : " << endl ;
        for ( int i = 0 ; i < num.size() ; i++ ) {
            output << num[i] << endl ;
        }

        auto now = chrono::system_clock::now();
        time_t end_time = chrono::system_clock::to_time_t(now);
        cpu_time_used = ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC ;
        output << "CPU Time : " << cpu_time_used << endl ;
        output << "Output Time : " << ctime(&end_time) ;

        num.clear() ;
        num.shrink_to_fit() ;
        input.close() ;
        output.close() ;
    }

 	return 0 ;
}
