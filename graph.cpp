#include <unordered_map>
using namespace std;



//origin, destination, flight num, arrival delay

class graph{    
    private:
        // key = source
        // tuple: destination, delay, flight num
        unordered_map<string, vector<tuple<string, int, int>>> airport;

    public:
        graph();
        //
        void addEdge(tuple<string, string, string> passedData){
            
        };

};