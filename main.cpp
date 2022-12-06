#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

#include "graph.cpp"
//#include "hash.cpp"

using namespace std;
void getFlightDataFromFile(graph &theGraph);
int main(){
    //hash
    //graph
    graph ourGraph;

    getFlightDataFromFile(ourGraph);

    string userAirport;
    int userInput;
    cout << "*****************************************************************************************" << endl;
    cout << "Welcome to the Flight Delay Calculator" << endl;
    cout << "*****************************************************************************************" << endl;
    while (userInput != 4){
        cout << "What would you like to do?" << endl;
        cout << "1. List Available Airports" << endl;
        cout << "2. Get Average Delay Time From Airport" << endl;
        cout << "3. Get Average Delay Time Between Two Airports" << endl;
        cout << "4. Exit" << endl;
        cin >> userInput;

        if (userInput == 1){

        }
        if (userInput == 2){
            cout << "Please input the airport abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
            cin >> userAirport;
            double averageDelayTime = ourGraph.getAverageDelayTime(userAirport);

        if (averageDelayTime == INT32_MAX){
            cout << "No Data Found. Airport Does Not Exist" << endl;
        }
        else 
            cout << "The average delay for a flight out of " << userAirport << " is: " << averageDelayTime << " minutes" << endl;
            cout << " " << endl;
            cout << " " << endl;
        }
        if (userInput == 3){
            cout << "Please input the origin airport's abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
            cin >> userAirport;
            string dest;
            cout << "Please input the destination airport's abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
            cin >> dest;
            double averageDelayTime = ourGraph.getAverageDelayTimeGivenTwoAirportInputs(userAirport, dest);

            if (averageDelayTime == INT32_MAX){
                cout << "No Data Found. Airport Does Not Exist" << endl;
            }
            else 
                cout << "The average delay for a flight out of " << userAirport << " going to " << dest << " is: " << averageDelayTime << " minutes" << endl;
            cout << " " << endl;
            cout << " " << endl;
        }
        if (userInput == 4){
            break;
        }
    }
    
    return 0;
}

//need to pass in graph and hash data types to initialize the data structures
void getFlightDataFromFile(graph &theGraph){
    fstream file("NewTest.csv", ios::in);

    string entireLine, Month, Day, delayTime, origin, dest, flightNumber, dummy;
    string test;

    vector<string> holdingValues;
    vector<vector<string>> usefulData;
    //we want columns 15 (delay time), 17(origin/source), 18(destination)
    int i = 0;
    if (file.is_open()){
        getline(file,entireLine);
        while (getline(file, entireLine)){
            holdingValues.clear();

            stringstream s(entireLine);

            while (getline(s, test, ',')){
                holdingValues.push_back(test);

            }
            Month = holdingValues[0];
            Day = holdingValues[1];
            flightNumber = holdingValues[2];
            origin = holdingValues[4];
            dest = holdingValues[5];
            delayTime = holdingValues[3];

            vector<string> holdingValues2;
            holdingValues2.push_back(Month);
            holdingValues2.push_back(Day);
            holdingValues2.push_back(flightNumber);
            holdingValues2.push_back(origin);
            holdingValues2.push_back(dest);
            holdingValues2.push_back(delayTime);
            if (!isdigit(delayTime[0]) && delayTime[0] != '-')
                continue;
            theGraph.addEdge(make_tuple(origin, dest, delayTime, flightNumber));

            //used for testing
            cout << "Flight Number: " << flightNumber << " origin: " << origin << " dest: " << dest << " delay: " << delayTime << endl;
            usefulData.push_back(holdingValues2);

        }

    }
}