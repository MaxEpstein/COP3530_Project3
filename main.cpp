#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(){
    //hash
    return 0;
}

void getFlightDataFromFile(){
    fstream file("2008.csv", ios::in);
    string names, line, data;
    vector<string> infoForDataStructures;
    if (file.is_open()){
        while(getline(file, names)){
            while (getline(file,line, ',')){
            infoForDataStructures.push_back(line);
        }
        }
    }
}