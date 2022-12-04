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
    fstream file("2008.csv", ios::in);
    string source, destination, delayTime;
    vector<string> infoForDataStructures;
    if (file.is_open()){
        while(getline(file, source)){
            while (getline(file,destination, ',')){
            infoForDataStructures.push_back(destination);
        }
        }
    }
}