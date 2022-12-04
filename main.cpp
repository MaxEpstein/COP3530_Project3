#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "graph.cpp"
#include "hash.cpp"

using namespace std;
void getFlightDataFromFile(graph theGraph);
int main(){
    //hash
    //graph
    graph ourGraph;

    getFlightDataFromFile(ourGraph);

    string userAirport;
    cout << "Welcome to the Flight Delay Calculator" << endl;
    cout << "Please input the airport abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
    cin >> userAirport;
    double averageDelayTime = 6.00;
    //ourGraph.getAverageDelayTime(userAirport);

    if (averageDelayTime == INT32_MAX){
        cout << "No Data Found. Airport Does Not Exist" << endl;
    }
    else 
        cout << "The average delay for a flight out of: " << userAirport << " is " << averageDelayTime << " minutes" << endl;

    return 0;
}

//need to pass in graph and hash data types to initialize the data structures
void getFlightDataFromFile(graph theGraph){
    fstream file("Test.csv", ios::in);

    string entireLine, Month, Day, delayTime, origin, dest, flightNumber, dummy;
    string test;

    vector<string> holdingValues;
    vector<vector<string>> usefulData;
    //we want columns 15 (delay time), 17(origin/source), 18(destination)
    if (file.is_open()){
        getline(file,entireLine);
        while (getline(file, entireLine)){
            holdingValues.clear();

            stringstream s(entireLine);

            while (getline(s, test, ',')){
                holdingValues.push_back(test);

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

            //used for testing
            cout << "Flight Number: " << flightNumber << " origin: " << origin << " dest: " << dest << " delay: " << delayTime << endl;

            usefulData.push_back(holdingValues2);

        }

    }
}