#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "graph.cpp"
#include "hash.cpp"

using namespace std;

int main(){
    //hash
    //graph
    graph ourGraph;

    getFlightDataFromFile(ourGraph);

    return 0;
}

//need to pass in graph and hash data types to initialize the data structures
void getFlightDataFromFile(graph theGraph){
    fstream file("Test.csv", ios::in);
    string entireLine, Month, Day, delayTime, origin, dest, flightNumber, dummyTest;
    string test;
    vector<string> holdingValues;
    vector<vector<string>> usefulData;
    //we want columns 15 (delay time), 17(origin/source), 18(destination)
    if (file.is_open()){
        while (file >> dummyTest){
            holdingValues.clear();

            getline(file, entireLine);

            istringstream s(entireLine);

            while (getline(s, test, ',')){
                holdingValues.push_back(dummyTest);

            }
            Month = holdingValues[1];
            Day = holdingValues[2];
            flightNumber = holdingValues[9];
            origin = holdingValues[16];
            dest = holdingValues[17];
            delayTime = holdingValues[15];

            vector<string> holdingValues2;
            holdingValues2.push_back(Month);
            holdingValues2.push_back(Day);
            holdingValues2.push_back(flightNumber);
            holdingValues2.push_back(origin);
            holdingValues2.push_back(dest);
            holdingValues2.push_back(delayTime);

            theGraph.addEdge(make_tuple(origin, dest, delayTime, flightNumber));

            usefulData.push_back(holdingValues2);

        }

    }
}