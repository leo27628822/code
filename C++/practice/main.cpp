#include<iostream>
#include<vector>
#include<time.h>

using namespace std;

void Comb(int k, int n, int m, vector < int > list);

int main() {
    int n;
    double start, end ;
    cin >> n;

    vector < int > list;
    start = clock() ;
    for (int i = 0; i <= (10 - n) && n > 0; ++i) {
        Comb( i + 1, n - 1, 10, list);
    } // for
    end = clock() ;
    cout  << "Recursion: " << end - start << " ms\n" ;
    system("pause");
    return 0;
} // main()

void Comb(int k, int n, int m, vector < int > list) {

    list.push_back(k - 1);
    for (int i = k; i <= (m - n) && n > 0; ++i)
        Comb(i + 1, n - 1, m, list);


    if (n == 0) {

        for (int i = 0; i < list.size(); ++i)
            cout << list[i] << " " ;
        cout << endl;
    } // if
} // Comb()
