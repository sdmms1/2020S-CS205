#define FILE_NAME "world_cities.csv"
#define NAME_LENGTH 35
#define ARR_LENGTH  1000
#define MIN(a,b) a > b? b:a
#define R 6371

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct city{
    string name;
    string country;
    double latitude{};
    double longitude{};
};

void trim(string &s){
     s.erase(0,s.find_first_not_of(' '));
     s.erase(s.find_last_not_of(' ') + 1);
}

vector<struct city*> arr;
void getCity(city cities[], string upper_name[], int len, city** city, bool* exit){
    string in;
    while(getline(cin,in)){
        arr.clear();

        trim(in);
        transform(in.begin(), in.end(), in.begin(), ::toupper);

        if(in == "BYE"){
            *exit = true;
            return;
        }

        if(in.size() < 3){
            cout << "Please input a string with length >= 3 :" << endl;
            continue;
        }

        int i;
        for(i = 0; i < len; i++){
            if(upper_name[i] == in){
                arr.clear();
                arr.push_back(&cities[i]);
                break;
            }
            if(upper_name[i].find(in) == string :: npos)
                continue;
            arr.push_back(&cities[i]);
        }

        if(arr.empty())
            cout << "There is no such city, please input a correct name again : " <<  endl;
        else if (arr.size() == 1){
            *city = arr[0];
            cout << "The city is " << arr[0]->name << ", " << arr[0]->country << endl;
            break;
        }else{
            cout << "Find several city as below : " << endl;
            for(i = 0; i < arr.size(); i++){
                cout << arr[i]->name << ", " << arr[i]->country << endl;
            }
            cout << "Please input the one you want : " << endl;
        }
    }
}

double calculate( double latitude1, double longitude1,
                    double latitude2, double longitude2){
    double phi1 = (90 - latitude1) * M_PI / 180;
    double phi2 = (90 - latitude2) * M_PI / 180;
    double theta1 = (longitude1) * M_PI / 180;
    double theta2 = (longitude2) * M_PI / 180;
    double c = sin(phi1) * sin(phi2) * cos(theta1 - theta2)
               + cos(phi1) * cos(phi2);
    double d = R * acos(c);

    return d;

}

int main(){

    ifstream fin(FILE_NAME);
    if(!fin.good()){
        cout << "File missing! Program exit!"<< endl;
        return 0;
    }

    city cities[ARR_LENGTH];
    string upper_name[ARR_LENGTH];
    int cnt = 0;
    int ignore = 0;
    string in;
    vector<string> arr;

    while(getline(fin,in)){

        arr.clear();

        if(cnt >= ARR_LENGTH)
            break;


        istringstream sin(in);
        string temp;
        while (getline(sin, temp, ',')){
            arr.push_back(temp);
        }

        if(arr.size() > 5 || arr[0].size() > NAME_LENGTH || arr[2].size() > NAME_LENGTH){
            ++ignore;
            continue;
        }

        cities[cnt].name = arr[0].substr(0,MIN(NAME_LENGTH,arr[0].length()));
        cities[cnt].country = arr[2].substr(0,MIN(NAME_LENGTH,arr[2].length()));
        cities[cnt].latitude = atof(arr[3].c_str());
        cities[cnt].longitude = atof(arr[4].c_str());

        upper_name[cnt] = cities[cnt].name;
        transform(upper_name[cnt].begin(),upper_name[cnt].end(),upper_name[cnt].begin(), ::toupper);
//        cout << cities[cnt].name << "|" << cities[cnt].country << "|" << cities[cnt].latitude << "|" << cities[cnt].longitude << endl;

        ++cnt;
    }

    if(cnt >= ARR_LENGTH)
        cout << "The input data is too much "  << ", only stores " << ARR_LENGTH << " pieces!"<< endl;
    else{
        cout << cnt << " pieces of data is stored."<< endl;
    }

    if(ignore > 0)
        cout << "In the process, " << ignore << " pieces of data is ignored because of the violation of the input format!" << endl;

    string u;
    city* first;
    city* second;
    bool exit = false;

    while(!exit){
        cout << "-----You can exit by input \"bye\" at any time-----" << endl;

        cout << "Please input the first city : " << endl;
        getCity(cities,upper_name, cnt, &first, &exit);

        if(exit)
            break;

        cout << "Please input the second city : " << endl;
        getCity(cities,upper_name, cnt, &second, &exit);

        if(exit)
            break;

        double d = calculate(first->latitude, first->longitude, second->latitude, second->longitude);
        cout << "The distance between " << first->name << " and " << second->name << " is " << d << "km." << endl;
    }


    cout << "SUCCESSFULLY EXIT" << endl;
    return EXIT_SUCCESS;
}