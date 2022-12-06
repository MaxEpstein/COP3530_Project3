#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <ctime>
#include <chrono>

#include "graph.cpp"
#include "hash.cpp"

using namespace std;

//clock reference https://stackoverflow.com/questions/15235218/c-timer-milliseconds

void getFlightDataFromFile(graph &theGraph);
void getFlightDataFromFile(HashTable &theHash);

int main(){
    //hash
    //graph

    graph ourGraph;
    HashTable hash;

    auto graphStart = chrono::steady_clock::now();
    getFlightDataFromFile(ourGraph);
    auto graphEnd = chrono::steady_clock::now();
    auto graphElapsed = chrono::duration_cast<std::chrono::microseconds>(graphEnd - graphStart);

    cout << "Graph initialization time: " << graphElapsed.count() << " microseconds" << endl;

    auto hashStart = chrono::steady_clock::now();
    getFlightDataFromFile(hash);
    auto hashEnd = chrono::steady_clock::now();
    auto hashElapsed = chrono::duration_cast<std::chrono::microseconds>(hashEnd - hashStart);

    cout << "HashTable initialization time: " << hashElapsed.count() << " microseconds" << endl;

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

        auto start = chrono::steady_clock::now();
        double averageDelayTime = ourGraph.getAverageDelayTime(userAirport);
        auto end = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);


        if (averageDelayTime == INT32_MAX){
            cout << "No Data Found. Airport Does Not Exist" << endl;
        }
        else 
            cout << "The average delay for a flight out of " << userAirport << " is: " << averageDelayTime << " minutes (graph)" << endl;
        

        //running with hashmap
        start = chrono::steady_clock::now();
        double averageDelayTime2 = hash.GetAirportAverageDelay(userAirport);
        end = chrono::steady_clock::now();
        auto elapsed2 = chrono::duration_cast<std::chrono::microseconds>(end - start);


        if (averageDelayTime2 == INT32_MAX){
            cout << "No Data Found. Airport Does Not Exist" << endl;
        }
        else 
            cout << "The average delay for a flight out of " << userAirport << " is: " << averageDelayTime2 << " minutes (hashmap)" << endl;

        cout << "Time Elapsed using Graph: " << elapsed.count() << " microseconds" << endl;
        cout << "Time Elapsed using HashMap: " << elapsed2.count() << " microseconds" << endl;

        cout << " " << endl;
        cout << " " << endl;
        }

        if (userInput == 3){
            cout << "Please input the origin airport's abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
            cin >> userAirport;
            string dest;
            cout << "Please input the destination airport's abreviation (ex: MCO, ATL, MIA) that you would like to calculate" << endl;
            cin >> dest;

            auto start = chrono::steady_clock::now();
            double averageDelayTime = ourGraph.getAverageDelayTimeGivenTwoAirportInputs(userAirport, dest);
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);

            if (averageDelayTime == INT32_MAX){
                cout << "No Data Found. Flight Route Does Not Exist" << endl;
            }
            else 
                cout << "The average delay for a flight out of " << userAirport << " going to " << dest << " is: " << averageDelayTime << " minutes (graph)" << endl;

                //running with hashmap
            start = chrono::steady_clock::now();
            double averageDelayTime2 = hash.GetAirportDelayBetweenAirports(userAirport, dest);
            end = chrono::steady_clock::now();
            auto elapsed2 = chrono::duration_cast<std::chrono::microseconds>(end - start);


            if (averageDelayTime2 == INT32_MAX){
                cout << "No Data Found. Flight Route Does Not Exist" << endl;
            }
            else 
                cout << "The average delay for a flight out of " << userAirport << " going to " << dest << " is: " << averageDelayTime << " minutes (hashmap)" << endl;

            cout << "Time Elapsed using Graph: " << elapsed.count() << " microseconds" << endl;
            cout << "Time Elapsed using HashMap: " << elapsed2.count() << " microseconds" << endl;
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
    fstream file("Data/NewTest.csv", ios::in);

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
            //cout << "Flight Number: " << flightNumber << " origin: " << origin << " dest: " << dest << " delay: " << delayTime << endl;
            usefulData.push_back(holdingValues2);

        }

    }
}

void getFlightDataFromFile(HashTable &theHash){
    fstream file("Data/NewTest.csv", ios::in);

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
            theHash.NewNode(make_tuple(origin, dest, stoi(delayTime), flightNumber));

            //used for testing
            //cout << "Flight Number: " << flightNumber << " origin: " << origin << " dest: " << dest << " delay: " << delayTime << endl;
            usefulData.push_back(holdingValues2);

        }

    }
}