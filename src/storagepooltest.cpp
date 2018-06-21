#include "storagepooltest.h"
#include <random>
#include <queue>
#include <ctime>

using bytes = char;

class Event{

    public:
        bytes* address;
        std::time_t time;

        Event(bytes* address_, std::time_t time_){
            address = address_;
            time = time_;
        }

        ~Event(){
            delete address;
        }

        std::time_t getTimeStamp(){
            return time;
        }

        void* getMemoryPtr(){
            return address;
        }

        bool operator<( const Event & ev2 ) const{
            return time < ev2.time;
        }

};

/// Setup random numbers generator for memory size , say [100 ,2000] bytes.
int getRandomForSize(){
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
    std::uniform_int_distribution<int>::param_type bytes_(100, 2000);
    dis.param(bytes_);

    return dis(gen);

}

/// Setup random numbers generator for time intervals , say [1 ,100] units.
std::time_t getRandomTimeInterval(){
    std::mt19937 gen;
    std::uniform_int_distribution<std::time_t> dis;
    std::uniform_int_distribution<std::time_t>::param_type times_(1, 100 );
    dis.param(times_);

    return dis(gen);
}

void StoragePoolTest( StoragePool& _pool, std::time_t _timeLimit )
{

    // Create the pirority queue std::priority_queue ‘pq’ and insert some events comprising the simulation.
    std::priority_queue<Event> pq;

    // Run simulation fot the time set by the client .
    for (std::time_t t(0); t < _timeLimit; ++t)
    {
        // Run while we have events pending or time to run.
        while (!pq.empty()) {

            // Access the event with the smallest time - stamp.
            Event ev = pq.top();

            // Do nothing. Still some time left.
            if (ev.getTimeStamp() > t) break;
        
            // When we got here , the top event has run out of time .

            // Remove event from priority queue .
            pq.pop();

            // Calling free operator.
            _pool.Free(ev.getMemoryPtr()); 

            //delete ev;
        }
    

        auto memSize = getRandomForSize();

        bytes* const add = reinterpret_cast<bytes*>(_pool.Allocate( memSize ));  

        auto elapsedTime = getRandomTimeInterval();

        // Set time stamp some time from now.
        std::time_t releaseTime = t + elapsedTime;

        // Creating a new simulation event.
        pq.push(Event(add , releaseTime)); 
    }


}