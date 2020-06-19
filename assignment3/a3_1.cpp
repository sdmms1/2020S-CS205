#include <iostream>
using namespace std;

void check(bool *map[], int *bullet[], int n, int m, int k){
    int i,j,d;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            for(d = 0; d < k; d++){
                int x = bullet[d][0];
                int y = bullet[d][1];
                int dx = bullet[d][2];
                int dy = bullet[d][3];

                if(dx != 0 && dy != 0){
                    int a = (i - x) / dx;
                    int b = (j - y) / dy;
                    if(a == b && a >= 0){
                        map[i][j] = true;
                        break;
                    }
                }else if(dx != 0){
                    int a = (i - x) / dx;
                    int b = j - y;
                    if(a >= 0 && b == 0){
                        map[i][j] = true;
                        break;
                    }
                }else if(dy != 0 ){
                    int a = i - x;
                    int b = (j - y) / dy;
                    if(b >= 0 && a == 0){
                        map[i][j] = true;
                        break;
                    }
                }
            }
        }
    }
}

bool inputCorrect(int a, int b){
	if(a < -1 || a > 1 || b < -1 || b > 1)
		return false;
	
	if(a == 0 && b == 0)
		return false;
	
	return true;
}

int main(){
    int n,m,k,i,j;
    cin >> n;
    cin >> m;
    cin >> k;

	if(n <= 0 || m <= 0 || k < 0){
		cout << "Please input the correct data!" << endl;
		return 0;
	}

    bool **map = new bool*[n];
    for(i = 0; i < n; i++){
        map[i] = new bool [m];
        for(j = 0; j < m; j++)
            map[i][j] = false;
    }

    int **bullet = new int*[k];
    for(i = 0; i < k; i++){
        bullet[i] = new int[4];
        cin >> bullet[i][0];
        cin >> bullet[i][1];
        cin >> bullet[i][2];
        cin >> bullet[i][3];
		if(!inputCorrect(bullet[i][2],bullet[i][3])){
			cout << "Please input the correct direction!" << endl;
			return 0;
		}
    }

    check(map, bullet, n, m, k);

    int cnt = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            if(!map[i][j])
                cnt++;
        }
    }
    cout << cnt << endl;

    for(i = 0; i < n; i++)
        delete[] map[i];
    delete[] map;

    for(i = 0; i < m; i++)
        delete[] bullet[i];
    delete[] bullet;
	
	return 0;
}