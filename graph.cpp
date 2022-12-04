#include <unordered_map>
using namespace std;



//origin, destination, flight num, arrival delay

class graph{    
    private:
        // key = source
        // tuple: destination, delay, flight num
        unordered_map<string, vector<tuple<string, int, int>>> airportMap;

    public:
        graph();
        //tuple being passed: source, destination, delay, flightNum
        void addEdge(tuple<string, string, string, string> passedData){
            vector<tuple<string, int, int>> tempPassedDataStorage;
            //get all data from every index of tuple
            string sourceAirport = get<0>(passedData);
            string destinationAirport = get<1>(passedData);
            int delayValue = stoi(get<2>(passedData));
            int flightNumber = stoi(get<3>(passedData)); 
            //find sourceAirport if already exists
            auto iteratorFindSource = airportMap.find(sourceAirport);
            if(iteratorFindSource != airportMap.end()){ //if already exists, add another tuple to the vector with required data
                tempPassedDataStorage = iteratorFindSource->second;
                tempPassedDataStorage.push_back(make_tuple(destinationAirport, delayValue, flightNumber));
                iteratorFindSource->second = tempPassedDataStorage;
            }else{ //if doesnt exist, make new map key-value pair
                tempPassedDataStorage.push_back(make_tuple(destinationAirport, delayValue, flightNumber));
                airportMap.emplace(sourceAirport, tempPassedDataStorage);
            }
        };

};