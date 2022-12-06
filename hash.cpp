#include <String>
#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

//HashNode is a node 
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
                    NewBucket(hashedKey,newFlightData, bucketList);
                    placed = true;
                    }
                }
            }
        }
        if (placed == false){
            RehashTable(newFlightData, bucketList); //after rehash, just return
            numberOfHashNodes++;
            return;
        }
        numberOfHashNodes++; //increment number of nodes to check load factor
        //Check load factor, if reached rehash
        currentLoadFactor = (double) numberOfHashNodes / bucketList.size();
        if (currentLoadFactor >= maxLoadFactor){
            RehashTable(newFlightData, bucketList);
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
    void RehashTable(tuple<string,string,int, string> newFlightData ,vector<vector<HashNode>>& tempBucketList){
        vector<vector<HashNode>> newBucketList;
        newBucketList.resize(tempBucketList.size() * 2);

        int newKey = HashFunction(get<0>(newFlightData), newBucketList.size());
        if (newBucketList[newKey].empty()){
            //If vector[hashKey] is empty, add a bucket's head node
            NewBucket(newKey, newFlightData, newBucketList);
        }
        else{ //**COLLISION OCCURRED**, two different types: same airport, different airport
            //If vector[hashedKey] is not empty, check if origin airport matches bucket head node's airport
            if (get<0>(newFlightData) == get<0>(newBucketList[newKey][0].flightData)){ //same origin airport
                NewHashNode(newKey, newFlightData, newBucketList);
            }
            //If not linear probe to find next empty bucket
            else{
                for (int i = newKey + 1; i < newBucketList.size(); i++){
                if (newBucketList[i].empty()){
                    NewBucket(newKey,newFlightData, newBucketList);
                    }
                }
            }
        }

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
                }
                else {
                    //if it isn't, linear probe to find next
                    for (int i = rehashKey + 1; i < newBucketList.size(); i++){
                        if(newBucketList[i].empty()){
                            newBucketList[i] = tempBucketList[currentIndex];
                        }
                    }
                }
            }
            currentIndex++;
        }

        //clear old bucketList
        bucketList.clear();
        //initialize with newBucketList, increment numberOfHashNodes
        numberOfHashNodes++;
        bucketList = newBucketList;
    };

    //Used to decide bucket index
    //Hash Function = Sum of ASCII Values % number of buckets
    int HashFunction(string originAirport, int numberOfBuckets){
        //Adding sum of ascii values
        int sumOfASCII = 0;
        for (int i = 0; i < originAirport.size(); i++){
            sumOfASCII += int(originAirport[i]);
        }
        return sumOfASCII % numberOfBuckets;
    }

    //Function that gets the average delay arrival time from an inputted airport
    double GetAirportAverageDelay(string inputAirport){
        double sumOfAirportDelays = 0.00;
        double averageDelay = 0.00;
        //Hash the inputAirport to get index in HashTable
        int index = HashFunction(inputAirport, bucketList.size());

        //Check HashTable index in the bucketList, if it is the correct airport, sum the delays
        if (inputAirport == get<0>(bucketList[index][0].flightData)){ 
            for(int i = 0; i < bucketList[index].size(); i++){
                sumOfAirportDelays += get<2>(bucketList[index][i].flightData);
            }
            averageDelay = sumOfAirportDelays / bucketList[index].size();
        }
        else{ //If isn't a collision occurred during intializing, linear probe to find correct airport
            for (int j = index + 1; j < bucketList.size(); j++){
                if(bucketList[j].empty() == false){
                    if(inputAirport == get<0>(bucketList[j][0].flightData)){
                        for (int k = 0; k < bucketList[j].size(); k++){
                            sumOfAirportDelays += get<2>(bucketList[j][k].flightData);
                        }
                        averageDelay = sumOfAirportDelays / bucketList[j].size();
                    }
                }
            }
        }
        return averageDelay; 
    }    
};

