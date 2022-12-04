#include <String>
#include <tuple>
#include <vector>
#include <iostream>
#define CAPACITY 100000
using namespace std;

//HashNode is a node in a linked list/bucket 

struct HashNode {
        public:
            //Hash Node is a Linked List Node
            //Tuple Order is Origin, Destination, Delay
            string hashKey;
            tuple<string, string, int> flightData;
            HashNode* next;

        //Default HashNode Constructor (NULL)
        HashNode::HashNode(){
            this->hashKey = " ";
            get<0>(this->flightData) = " ";
            get<1>(this->flightData) = " ";
            get<2>(this->flightData) = -1;
            this->next = nullptr;
        }
        //Hash Node Constructor: hashKey, tuple, and next node
        HashNode::HashNode(string dateFlightNumberKey, tuple<string, string, int> newFlightData, HashNode* next){
            this->hashKey = dateFlightNumberKey;
            this->flightData = newFlightData;
            this->next = next;
       }

//===============Accessors==============//
       string HashNode::getHashKey() const{
            return hashKey;
       }
    
       string HashNode::getOriginAirport() const{
            return get<0>(flightData);
       }

       string HashNode::getDestinationAirport() const{
            return get<1>(flightData);
       }
       
       int getFlightDelayTime() const{
            return get<2>(flightData);
       }

        HashNode* getNext() const{
        return next;
    }

//===============Setters==============//

        void setHashKey(string newHashKey){
            this->hashKey = newHashKey;
        }

        void setOriginAirport(string newOrigin){
            get<0>(this->flightData) = newOrigin;
        }

        void setDestinationAirport(string newDestination){
            get<1>(this->flightData) = newDestination;
        }

        void setFlightDelay(int newDelayTime){
            get<2>(this->flightData) = newDelayTime;
        }
        
        void setNext(HashNode* newNext) {
                this->next = newNext;
        }
        
 };

 struct KeyHashFunction{
    public:
        //New newDate/Flight Number needed to hash
        string newDateFlightNumber;
 };

//Hash Structure is a vector of head HashNodes
//Separate Chaining Collision resolution
class HashTable {
    public: 
        //Vector when initialized is 20, meaning there are 20 buckets in the hash map
        int const initialBucketListSize = 20; 
        //Vector is a list of the buckets, buckets are heads for linked lists 
        vector<HashNode*> bucketList;
        //Load Factor (# of nodes/ # of buckets), if hashmap is 80% full rehash 
        double const maxLoadFactor = 0.80;
        double currentLoadFactor;
        double numberOfHashNodes;
        
    
    //Creates empty vector of size initialBucket
    HashTable::HashTable(){
        numberOfHashNodes = 0;
        currentLoadFactor = 0; 
    
        //Initializing bucketList with empty nodes
        for (int i = 0; i < initialBucketListSize; i++){
            HashNode* tempHash = new HashNode();
            bucketList.push_back(tempHash);
        }
    };

    
    void HashTable::newNode(string newDateFlightNumber, tuple<string, string, int> newFlightData){
        //Set Functions

        //Run Hash Function (Returns index for bucketList vector) Index is the hash value
        //Either new linked list node or linked list head (bucket node/ collision node)

        //Change head/bucket node data in vector[index]
        

    };
    
    //Initializes Bucket
    void HashTable::newBucket(string newDataFlightNumber, tuple<string, string, int> newFlightData){

    };

    //Initializes regular hash node/collision node
    void HashTable::newHashNode(string newDataFlightNumber, tuple<string,string,int> newFlightData){

    };
    
};

