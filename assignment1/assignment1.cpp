//
// Created by sdmms on 2020/3/4.
//

#include <iostream>
#include <string>
#include <math.h>


using namespace std;

void calculate(char*, double, double, char*, double, double);
bool getCity(char*);
bool isNum(char);
bool getData(double*, double*);

int main(){
    char city1[1024];
    char city2[1024];
    double latitude1;
    double latitude2;
    double longitude1;
    double longitude2;

    cout << "The first city: ";
    if(!getCity(city1)){
        cout << "Please enter a correct city name" << endl;
        return 0;
    }

    cout << "The latitude and longitude of first city: ";
    if(!getData(&latitude1, &longitude1)){
        cout << "Please input the right latitude and longitude in the format \"num1 num2\"" << endl;
        return 0;
    }

    cout << "The second city: ";
    if(!getCity(city2)){
        cout << "Please enter a correct city name" << endl;
        return 0;
    }

    cout << "The latitude and longitude of second city: ";
    if(!getData(&latitude2, &longitude2)){
        cout << "Please input the right latitude and longitude in the format \"num1 num2\"" << endl;
        return 0;
    }

    calculate(city1,latitude1,longitude1,city2,latitude2,longitude2);
    return 0;
}

bool isNum(char a){
    if(a < '0' || a > '9')
        return false;
    else
        return true;
}

bool getData(double* a, double* b){
    char* arr;
    cin.get(arr, 1024).get();
    //printf("*%s*", arr);
    if(!isNum(*arr) && *arr != '-')
        return false;

    if(*arr == '-'){
        if(!isNum(*(arr + 1)))
            return false;
    }

    *a = atof (arr);
    arr++;

    bool dot = false;
    do{
        if(isNum(*arr))
            continue;
        else{
            if(*arr == ' '){
                arr++;
                break;
            }else if(*arr == '.' && !dot){
                dot = true;
                arr++;
                if(!isNum(*arr))
                    return false;
            } else
                return false;
        }
    }while(*(++arr));

    if(!*arr)
        return false;
    else{

        if(*arr == '-'){
            if(!isNum(*(arr + 1)))
                return false;
        }

        *b = atof(arr);
        arr++;

        if(!*arr)
            return true;

        bool dot = false;
        do{
            if(isNum(*arr))
                continue;
            else if(*arr == '.' && !dot){
                dot = true;
                arr++;
                if(!isNum(*arr))
                    return false;
            } else
                return false;

        }while(*(++arr));
    }

    if(*a < -90 ||*a > 90)
        return false;
    else if (*b < -180 || *b > 180)
        return false;
    else
        return true;
}

bool getCity(char* city){
    cin.get(city, 1024).get();

    do{
        if((*city >= 'a' && *city <= 'z') || (*city >= 'A' && *city <= 'Z')
            ||*city == ' ' || *city == ',')
            continue;
        return false;
    }while(*(++city));
    return true;
}

void calculate(char* city1, double latitude1, double longitude1,
               char* city2, double latitude2, double longitude2){
    const int R = 6371;
    const double PI = M_PI / 180;
    double phi1 = (90 - latitude1) * M_PI / 180;
    double phi2 = (90 - latitude2) * M_PI / 180;
    double theta1 = (longitude1) * M_PI / 180;
    double theta2 = (longitude2) * M_PI / 180;
    double c = sin(phi1) * sin(phi2) * cos(theta1 - theta2)
               + cos(phi1) * cos(phi2);
    double d = R * acos(c);

    //printf("%.2f %.2f %.2f %.2f\n", latitude1, longitude1, latitude2, longitude2);
    printf("The distance between %s and %s is %.2f km",
           city1,  city2,  d);

}