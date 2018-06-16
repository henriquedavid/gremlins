#include "storagepooltest.h"
/*
void StoragePoolTest(const StoragePool& _pool, std::time_t _timeLimit )
{
    // [1] Setup random numbers generator for memory size , say [100 ,2000] bytes .
    // [2] Setup random numbers generator for time intervals , say [1 ,100] units .
    // [3] Create the pirority queue std :: priority_queue ‘ pq ’ and
    // insert some events comprising the simulation .
    // Assuming there is a class Event that creates a pair address / time - stamp .
    // Run simulation fot the time set by the client .
    for (std::time_t t(0); t < _timeLimit; ++t)
    {
        while (!pq.empty()) { // Run while we have events pending or time to run .
            Event ev = pq.top(); // Access the event with the smallest time - stamp .
            if (event.getTimeStamp() > t) break; // Do nothing . Still some time left .
        }
        // When we got here , the top event has run out of time .
        pq.pop(); // Remove event from priority queue .
        _pool.Free(ev.getMemoryPtr()); // Calling free operator .
        delete ev;
    }
    auto memSize = getRandomForSize();
    void* const add = _p.Allocate( memSize );
    auto elapsedTime = getRandomTimeInterval();
    std :: time_t releaseTime = t + elapsedTime ; // Set time stamp some time from now .
    pq.push(new Event(add , releaseTime)); // Creating a new simulation event .
    // Here you might want to show the memory map on the screen ,
    // or write it to a log file , for debugging purpose .
}
*/
