#include <iostream>
#define inMap(i,j,n,m) 0 <= i && i < n && 0 <= j && j < m
using namespace std;

void print_map(int *map[], int n, int m){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++)
            cout << map[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void fill_map(int *map[], int n, int m){
    int i = 0, j = m - 1, cnt = 1;
    map[i][j] = 1;
    bool flag = true;
    while(flag){
        flag = false;
        while(inMap(i,j - 1,n,m) && map[i][j - 1] == -1){
            j = j - 1;
            cnt++;
            flag = true;
            map[i][j] = cnt;
        }
        while(inMap(i + 1,j,n,m) && map[i + 1][j] == -1){
            i = i + 1;
            cnt++;
            flag = true;
            map[i][j] = cnt;
        }
        while(inMap(i,j + 1,n,m) && map[i][j + 1] == -1){
            j = j + 1;
            cnt++;
            flag = true;
            map[i][j] = cnt;
        }
        while(inMap(i - 1,j,n,m) && map[i - 1][j] == -1){
            i = i - 1;
            cnt++;
            flag = true;
            map[i][j] = cnt;
        }
    }
}

int main(){
    int n, m;
    cin >> n;
    cin >> m;

	if(n <= 0 || m <= 0){
		cout << "Please input the correct size!" << endl;
		return 0;
	}

    int i,j;
    int **map = new int*[n];
    for(i = 0; i < n; i++){
        map[i] = new int[m];
        for(j = 0; j < m; j++)
            map[i][j] = -1;
    }

    fill_map(map, n, m);

    print_map(map, n, m);

    for(i = 0; i < n; i++)
        delete[] map[i];
    delete[] map;

	return 0;
}