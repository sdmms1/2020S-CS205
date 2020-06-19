#include <iostream>
#include <fstream>
#include <vector>
#include "utf8.c"
using namespace std;

struct block{
    string hex_start;
    string hex_end;
    unsigned int start;
    unsigned int end;
    string name;
};

unsigned int toDecimal(char a){
    a = toupper(a);
    unsigned int index = (unsigned int) a;
    if(index >= 48 && index <= 57)
        return index - 48;
    else
        return index - 55;
}

unsigned int toNum(string str){
    unsigned int i, result = 0;
    for(i = 0; i < str.size(); i++)
        result = result * 16 + toDecimal(str[i]);
    return result;
}

bool read_block_info(block arr[], int *n, string fileName){
    ifstream fin(fileName);
    if(!fin.good()){
        cout << "File missing! Program exit!"<< endl;
        return false;
    }
    string in;
    while(getline(fin,in)){
        if(in[0] == '#' || in.size() <= 1)
            continue;

        int space = in.find_first_of(' ');
        arr[*n].name = in.substr(space + 1);

        int dot = in.find_first_of('.');
        arr[*n].hex_start = in.substr(0,dot);
        arr[*n].start = toNum(arr[*n].hex_start);
        arr[*n].hex_end = in.substr(dot + 2, dot);
        arr[*n].end = toNum(arr[*n].hex_end);
        (*n)++;
    }
    return true;
}

int search(block arr[], unsigned char* p, int *len, int n){
    unsigned int cp = utf8_to_codepoint(p, len);
    if (cp) {
        int i;
        for(i = 0; i < n; i++){
            if(cp < arr[i].start)
                return i - 1;
        }
        return n - 1;
    } else {
        return -1;
    }
}

void print_max_block(const int cnt[], block arr[], int n, int no_block){

    int i, max = 0;
    for(i = 0; i < n; i++){
        if(cnt[i] > max)
            max = cnt[i];
    }

    if(max <= 0)
        cout << "Please give the valid data!" << endl;
    else{
        vector<int> temp;
        for(i = 0; i < n; i++){
            if(cnt[i] == max){
                temp.push_back(i);
            }
        }
        for(i = 0; i < temp.size(); i++)
            cout << arr[temp[i]].name << endl;
    }
}

int main(int argc, char** fileName){

    block arr[300];
    int n = 0;
    if(!read_block_info(arr, &n, "Blocks.txt"))
        return 0;

    int no_block = 0;
    int cnt[300];

    char a[1000000];
    while (cin.getline(a,1000000)){
        auto* p = (unsigned char *)a;
        int len = 0;
        while (*p) {
            int index = search(arr,p, &len, n);
            if (index != -1) {
                cnt[index]++;
                p += len;
            } else {
                no_block++;
                p++;
            }
        }
    }

    print_max_block(cnt, arr, n, no_block);

    return EXIT_SUCCESS;
}