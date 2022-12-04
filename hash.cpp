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

        //Hash Node Constructor: hashKey, tuple, and next node
       HashNode::HashNode(string dateFlightNumberKey, tuple<string, string, int> newFlightData, HashNode* next){
            this->hashKey = dateFlightNumberKey;
            this->flightData = newFlightData;
            this->next = next;
       }

//===============Accessors==============//
       string getHashKey() const{
            return hashKey;
       }
    
       string getOriginAirport() const{
            return get<0>(flightData);
       }

       string getDestinationAirport() const{
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

//Hash Structure is a vector of head HashNodes.
class HashMap {
    public: 
        //Vector is a list of the bucket heads
        vector<HashNode*> bucketList;
        double loadFactor;
        int numberOfHashNodes; 
    
    //Adds a new pointer to a head hashNode
    void newBucket(string newDateFlightNumber, tuple<string, string, int> newFlightData){
        //Set Functions
        

    };
    

    
};

