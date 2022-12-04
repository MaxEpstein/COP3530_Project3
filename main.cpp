#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>

#include "graph.cpp"
#include "hash.cpp"

using namespace std;

int main(){
    //hash
    //graph
    return 0;
}

void getFlightDataFromFile(){
    fstream file("test.csv", ios::in);
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