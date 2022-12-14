#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



//origin, destination, flight num, arrival delay

class graph{    
    private:
        // key = source
        // tuple: destination, delay, flight num
        // 0: destination, 1: delay, 2: flightNum for tuple index
        unordered_map<string, vector<tuple<string, int, int>>> airportMap;
        vector<tuple<string, int, int>> tempDataStorage;
        double avgDelay;
        int totalFlights;

    public:

        //

        graph(){
            avgDelay = 0.0;
            totalFlights = 0;
        };
        //tuple being passed: source, destination, delay, flightNum
        void addEdge(tuple<string, string, string, string> passedData){
            vector<tuple<string, int, int>> tempDataStorage = {};
            //get all data from every index of tuple
            string sourceAirport = get<0>(passedData);
            string destinationAirport = get<1>(passedData);
            int delayValue = stoi(get<2>(passedData));
            int flightNumber = stoi(get<3>(passedData)); 
            avgDelay += delayValue;
            totalFlights++;
            //find sourceAirport if already exists
            auto iteratorFindSource = airportMap.find(sourceAirport);
            if(iteratorFindSource != airportMap.end()){ //if already exists, add another tuple to the vector with required data
                tempDataStorage = iteratorFindSource->second;
                tempDataStorage.push_back(make_tuple(destinationAirport, delayValue, flightNumber));
                iteratorFindSource->second = tempDataStorage;
            }else{ //if doesnt exist, make new map key-value pair
                tempDataStorage.push_back(make_tuple(destinationAirport, delayValue, flightNumber));
                airportMap.insert({sourceAirport, tempDataStorage});
            }
        };

        // string getWorstAirport(string userAirport){

        // };

        double getAverageDelayTime(string userAirport){
            double tempDelay = 0.00;
            auto findAirportItr = airportMap.find(userAirport); //find iterator to given user airport
            if(findAirportItr != airportMap.end()){ //userAirport found, add up all delay tims in vector
                tempDataStorage = findAirportItr->second;
                for(int i = 0; i < tempDataStorage.size(); i++){
                    tempDelay += get<1>(tempDataStorage.at(i));
                }
            }else{
                return INT32_MAX; //avg delayTime very unlikely to be upwards of 2 billion, used for error checking
            }
            //for testing purposes
            //cout << "Total Delay " << tempDelay << " Size: " << tempDataStorage.size() << endl;
            return tempDelay / tempDataStorage.size();
        };

        double getAverageDelayTimeGivenTwoAirportInputs(string userSourceAirport, string userDestinationAirport){
            double tempDelay = 0.00;
            int counter = 0;
            auto findAirportItr = airportMap.find(userSourceAirport); //find iterator to given user airport
            if(findAirportItr != airportMap.end()){ //userAirport found, add up all delay tims in vector
                tempDataStorage = findAirportItr->second;
                for(int i = 0; i < tempDataStorage.size(); i++){
                    if(get<0>(tempDataStorage.at(i)) == userDestinationAirport){
                        tempDelay += get<1>(tempDataStorage.at(i));
                        counter++;
                    }
                }
                if(counter == 0){
                    return INT32_MAX;
                }
            }else{
                return INT32_MAX;
            }
            return tempDelay / counter;
        };

        double getTotalAvgDelay(){
            return (double)(avgDelay / totalFlights);
        }

        vector<string> allOriginAirports(){
            vector<string> returnVec;
            for (auto it = airportMap.begin(); it != airportMap.end(); it++){
                returnVec.push_back(it->first);
            }
            return returnVec;
        }

};