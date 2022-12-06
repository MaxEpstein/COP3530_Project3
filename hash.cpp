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
        HashNode::HashNode(){
            this->hashKey = " ";
            get<0>(this->flightData) = " ";
            get<1>(this->flightData) = " ";
            get<2>(this->flightData) = -1;
            get<3>(this->flightData) = " ";
            
        }
        //Hash Node Constructor: hashKey, tuple, and next node
        HashNode::HashNode(tuple<string, string, int, string> newFlightData, int newHashedKey){
            this->flightData = newFlightData;
            this->hashKey = newHashedKey;
       }

//===============Accessors==============//
       string HashNode::GetHashKey() const{
            return hashKey;
       }
    
       string HashNode::GetOriginAirport() const{
            return get<0>(flightData);
       }

       string HashNode::GetDestinationAirport() const{
            return get<1>(flightData);
       }
       
       int GetFlightDelayTime() const{
            return get<2>(flightData);
       }

       string HashNode::GetFlightNumber() const{
            return get<3>(flightData);
       }


//===============Setters==============//

        void SetHashKey(string newHashKey){
            this->hashKey = newHashKey;
        }

        void SetOriginAirport(string newOrigin){
            get<0>(this->flightData) = newOrigin;
        }

        void SetDestinationAirport(string newDestination){
            get<1>(this->flightData) = newDestination;
        }

        void SetFlightDelay(int newDelayTime){
            get<2>(this->flightData) = newDelayTime;
        }
        
        void SetNext(string newFlightNumber) {
            get<3>(this->flightData) = newFlightNumber;
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
    HashTable::HashTable(){
        numberOfHashNodes = 0;
        currentLoadFactor = 0; 
        //Initializing bucketList (Aka the bucket vectors)
        bucketList.resize(initialBucketListSize);
    };

    
    void HashTable::NewNode(tuple<string, string, int, string> newFlightData){
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
    void HashTable::NewBucket(int key, tuple<string, string, int, string> newFlightData, vector<vector<HashNode>>& tempBucketList){
        tempBucketList[key].push_back(HashNode())
    };

    //Initializes regular hash node/collision node
    void HashTable::NewHashNode(int key, tuple<string,string,int, string> newFlightData, vector<vector<HashNode>>& tempBucketList){

    };

    //If max load factor is reached, rehash the vector
    void HashTable::RehashTable(tuple<string,string,int, string> newFlightData ,vector<vector<HashNode>>& tempBucketList){

    };

    //Used to decide bucket index
    //Hash Function = Sum of ASCII Values % number of buckets
    int HashTable::HashFunction(string originAirport, int numberOfBuckets){
        //Adding sum of ascii values
        int sumOfASCII = 0;
        for (char i : originAirport){
            sumOfASCII += int(i);
        }
        return sumOfASCII % numberOfBuckets;
    }    
};

