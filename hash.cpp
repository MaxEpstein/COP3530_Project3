#include <String>
#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

//HashNode is a node that contains the flight data of a single flight, it uses the origin airport as its hashKey
struct HashNode {
        public:
            //Hash Node is a Linked List Node
            //hashKey = hashed value of origin/source
            //Tuple Order is Origin, Destination, Delay, flight number
            string hashKey;
            tuple<string, string, int, string> flightData;
           

        //Default HashNode Constructor (NULL)
        HashNode(){
            this->hashKey = " ";
            get<0>(this->flightData) = " ";
            get<1>(this->flightData) = " ";
            get<2>(this->flightData) = -1;
            get<3>(this->flightData) = " ";
            
        }
        //Hash Node Constructor: hashKey, tuple, and next node
        HashNode(tuple<string, string, int, string> newFlightData, int newHashedKey){
            this->flightData = newFlightData;
            this->hashKey = newHashedKey;
       }
 };


//Hash Structure is a vector of head HashNodes
//Separate Chaining Collision resolution + some linear probing
class HashTable {
    public: 
        //Vector when initialized is 20, meaning there are 20 buckets in the hash map
        int const initialBucketListSize = 20; 
        //Vector is a list of the buckets, buckets are vectors of HashNodes 
        vector<vector<HashNode>> bucketList;
        //Load Factor (# of nodes/ # of buckets), if hashmap is 80% full rehash 
        double const maxLoadFactor = 0.80;
        double currentLoadFactor;
        double numberOfHashNodes;
        
    
    //HashTable Constructor, initializes bucketList to size 20 [aka there are 20 buckets/vectors]
    HashTable(){
        numberOfHashNodes = 0;
        currentLoadFactor = 0; 
        //Initializing bucketList (Aka the bucket vectors)
        bucketList.resize(initialBucketListSize);
    };

    
    void NewNode(tuple<string, string, int, string> newFlightData){
        tuple<string, string, int, string> tempData = newFlightData;

        //HashTable uses origin airport as hashed key
        string unhashedKey = get<0>(tempData);
        
        //Run Hash Function (Returns index for bucketList vector) Index is the hash value, bucketList.size is the number current number of buckets
        int hashedKey = HashFunction(unhashedKey, bucketList.size());
        bool placed = false; 
        if (bucketList[hashedKey].empty()){
            //If vector[hashKey] is empty, add a bucket's head node
            NewBucket(hashedKey, newFlightData, bucketList);
            placed = true;
        }
        else{ //**COLLISION OCCURRED**, two different types: same airport, different airport
            //If vector[hashedKey] is not empty, check if origin airport matches bucket head node's airport
            if (get<0>(newFlightData) == get<0>(bucketList[hashedKey][0].flightData)){ //same origin airport
                NewHashNode(hashedKey, newFlightData, bucketList);
                placed = true;
            }
            //If not linear probe to find next empty bucket
            else{
                for (int i = hashedKey + 1; i < bucketList.size(); i++){
                    if (bucketList[i].empty()){
                        NewBucket(i,newFlightData, bucketList);
                        placed = true;
                    }
                    else if (get<0>(bucketList[i][0].flightData) == get<0>(newFlightData)){
                        NewHashNode(i, newFlightData, bucketList);
                        placed = true;
                    }
                }
            }
        }
        if (placed == false){
             for (int i = 0; i < hashedKey; i++){
                    if (bucketList[i].empty()){
                        NewBucket(hashedKey,newFlightData, bucketList);
                        placed = true;
                        }
                }
            numberOfHashNodes++;
            return;
        }
        numberOfHashNodes++; //increment number of nodes to check load factor
        //Check load factor, if reached rehash

        int filledBuckets = 0;
        for (int i = 0; i < bucketList.size(); i++){
            if(bucketList[i].empty() == false){
                filledBuckets++;
            }
        }
        currentLoadFactor = ((double) filledBuckets) / bucketList.size();
        //cout << "Current load factor: " << currentLoadFactor << endl;
        if (currentLoadFactor >= maxLoadFactor){
            RehashTable(bucketList);
        }

    };
    
    //Initializes Bucket at key index
    void NewBucket(int key, tuple<string, string, int, string> newFlightData, vector<vector<HashNode>>& tempBucketList){
        tempBucketList[key].push_back(HashNode(newFlightData, key));
    };

    //Initializes regular hash node/collision node
    void NewHashNode(int key, tuple<string,string,int, string> newFlightData, vector<vector<HashNode>>& tempBucketList){
        tempBucketList[key].push_back(HashNode(newFlightData, key));
    };

    //If max load factor is reached, rehash the vector
    void RehashTable(vector<vector<HashNode>>& tempBucketList){
        //cout << "rehashing" << endl;
        vector<vector<HashNode>> newBucketList;
        newBucketList.resize(tempBucketList.size() * 2);

        //Rehash keys in old hash table
        string tempAirport;
        int rehashKey;
        //currentIndex keeps track of current index of tempBucketList
        int currentIndex = 0; 
        for (auto i : tempBucketList){
            if (i.empty() == false){
                tempAirport = get<0>(i[0].flightData);
                rehashKey = HashFunction(tempAirport, newBucketList.size());
                bool placed = false; 
                //check if newBucketList[rehashKey] is empty
                if (newBucketList[rehashKey].empty()){
                    //if it is, initialize with old bucket vector
                    newBucketList[rehashKey] = tempBucketList[currentIndex];
                    placed = true;
                }
                else {
                    //if it isn't, linear probe to find next
                    for (int j = rehashKey + 1; j < newBucketList.size(); j++){
                        if(newBucketList[j].empty()){
                            newBucketList[j] = tempBucketList[currentIndex];
                            placed = true;
                        }
                    }
                }
                if (placed == false){
                    for (int x = 0; x < rehashKey; x++){
                        if (newBucketList[x].empty()){
                            newBucketList[x] = tempBucketList[currentIndex];
                            placed = true;
                        }
                    }
                }
            }
            currentIndex++;
        }


        //clearing/freeing up memory from bucketList
        for (int j = 0; j < tempBucketList.size(); j++){
            tempBucketList[j].clear(); 
        }
        tempBucketList.clear();
        //initialize with newBucketList
        tempBucketList = newBucketList;
        //clearing/freeing up memory from bucketList
        for (int j = 0; j < newBucketList.size(); j++){
            newBucketList[j].clear(); 
        }
        newBucketList.clear();
    };

    //Used to decide bucket index
    //Hash Function = Sum of ASCII Values % number of buckets
    int HashFunction(string originAirport, int numberOfBuckets){
        //Adding sum of ascii values
        int sumOfASCII = 0;
        for (int i = 0; i < originAirport.size(); i++){
            sumOfASCII += int(originAirport[i]);
        }
        //cout << "airport: " << originAirport << " ascii val: " << sumOfASCII << " buckets: " << numberOfBuckets << endl;
        return sumOfASCII % numberOfBuckets;
    }

    //Function that gets the average delay arrival time from an inputted airport
    double GetAirportAverageDelay(string inputAirport){
        double sumOfAirportDelays = 0.00;
        double averageDelay = 0.00;
        //Hash the inputAirport to get index in HashTable
        int index = HashFunction(inputAirport, bucketList.size());
        //cout << "Airport: " << inputAirport << " Bucket size " << bucketList.size() << " Index: " << index << endl;
        int numberOfFlights = 0;
        bool found = false;
        //Check HashTable index in the bucketList, if it is the correct airport, sum the delays
        if (inputAirport == get<0>(bucketList[index][0].flightData)){ 
            for(int i = 0; i < bucketList[index].size(); i++){
                sumOfAirportDelays += get<2>(bucketList[index][i].flightData); //Sum all the flight delays from inputAirport
                numberOfFlights++;
                found = true;
            }
            averageDelay = sumOfAirportDelays / bucketList[index].size();
        }
        else{ //If isn't a collision occurred during intializing, linear probe to find correct airport
            for (int j = index + 1; j < bucketList.size(); j++){
                if(bucketList[j].empty() == false){
                    if(inputAirport == get<0>(bucketList[j][0].flightData)){
                        for (int k = 0; k < bucketList[j].size(); k++){
                            sumOfAirportDelays += get<2>(bucketList[j][k].flightData); //Sum all the flight delays from inputAirport
                            numberOfFlights++;
                        }
                        averageDelay = sumOfAirportDelays / bucketList[j].size();
                        found = true;
                        break;
                    }
                }
            }
            if (found == false){
                for (int x = 0; x < index; x++){
                    if(bucketList[x].empty() == false){
                        if(inputAirport == get<0>(bucketList[x][0].flightData)){
                            for (int k = 0; k < bucketList[x].size(); k++){
                                sumOfAirportDelays += get<2>(bucketList[x][k].flightData); //Sum all the flight delays from inputAirport
                                numberOfFlights++;
                            }
                            averageDelay = sumOfAirportDelays / bucketList[x].size();
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
        if (found == false){
             //cout << "There are no connection flights from " << inputAirport;
            return INT32_MAX;
        }
        return averageDelay; 
    }

    double GetAirportDelayBetweenAirports(string origin, string destination){
        double sumOfAirportDelays = 0.00;
        double averageDelay = 0.00;
        //Hash the inputAirport to get index in HashTable
        int originIndex = HashFunction(origin, bucketList.size());
        //numberOfFlights is the number of flights from origin to destination
        int numberOfFlights = 0;
        
        //Check HashTable index in the bucketList, if it is the correct airport, sum the delays
        if (origin == get<0>(bucketList[originIndex][0].flightData)){ 
            for(int i = 0; i < bucketList[originIndex].size(); i++){
                if (destination == get<1>(bucketList[originIndex][i].flightData)){
                    sumOfAirportDelays += get<2>(bucketList[originIndex][i].flightData); //Sum all the flight delays from origin to destination
                    numberOfFlights++; //add to number of flights between airports
                }
            }
            averageDelay = sumOfAirportDelays / numberOfFlights;
        }
        else{ //If isn't a collision occurred during intializing, linear probe to find correct airport
            for (int j = originIndex + 1; j < bucketList.size(); j++){
                if(bucketList[j].empty() == false){
                    if(origin == get<0>(bucketList[j][0].flightData)){
                        for (int k = 0; k < bucketList[j].size(); k++){
                            if (destination == get<1>(bucketList[j][k].flightData)){ //check destination of flight
                                sumOfAirportDelays += get<2>(bucketList[j][k].flightData); //Sum all the flight delays from origin to destination
                                numberOfFlights++;
                            }
                        }
                        averageDelay = sumOfAirportDelays / numberOfFlights;
                    }
                }
            }
        }

        //If no connecting flight inform users, return -1
        if (numberOfFlights = 0){
           // cout << "There are no connection flights from " << origin << " to " << destination << endl;
            return INT32_MAX;
        }
        return averageDelay;
    }

};

