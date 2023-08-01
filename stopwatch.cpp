#include "stopwatch.h"

#include <cstring>

namespace TrafficGenerator 
{

Stopwatch::Stopwatch ()
{
    isFromStopToStart = false;
    isWorked = false;
    isStopped = false;
    deltaTime = 0;
    std::memset (&curTime, 0, sizeof (timespec));
    std::memset (&startTime, 0, sizeof (timespec));
    std::memset (&stopTime, 0, sizeof (timespec));
    std::memset (&deltaStop, 0, sizeof (timespec));
    std::memset (&time, 0, sizeof (StpwtchTime));
}

void Stopwatch::start (void)
{
    if (!isWorked)
    {
        clock_gettime (CLOCK_MONOTONIC_RAW, &startTime);
        isWorked = true;
    } 
    
    if (isFromStopToStart)
    {
        clock_gettime (CLOCK_MONOTONIC_RAW, &curTime);
        deltaStop.tv_sec = (curTime.tv_sec - stopTime.tv_sec);
        deltaStop.tv_nsec = (curTime.tv_nsec - stopTime.tv_nsec);
        isFromStopToStart = false;
    }
    isStopped = false;
}
   
StpwtchTime Stopwatch::get ()
{
    if (!isFromStopToStart && isWorked)
    {
        clock_gettime (CLOCK_MONOTONIC_RAW, &curTime);
        deltaTime = (curTime.tv_sec - startTime.tv_sec - deltaStop.tv_sec) * 1000000 + 
                            (curTime.tv_nsec - startTime.tv_nsec - deltaStop.tv_nsec) / 1000;
        if (deltaTime != 0)
            conversion ();
    } 
    return time;
}

void Stopwatch::stop ()
{
    if (!isStopped)
    {
        clock_gettime (CLOCK_MONOTONIC_RAW, &stopTime);
        struct timespec deltaTmp;
        deltaTmp.tv_sec = stopTime.tv_sec - startTime.tv_sec;
        deltaTmp.tv_nsec = stopTime.tv_nsec - startTime.tv_nsec;
        deltaTime = (deltaTmp.tv_sec * 1000000) + (deltaTmp.tv_nsec / 1000);
        if (deltaTime != 0)
            conversion ();
        isStopped = true;
        isFromStopToStart = true;
    }
}

void Stopwatch::reset ()
{
    stop ();
    std::memset (&startTime, 0, sizeof (timespec));
    std::memset (&stopTime, 0, sizeof (timespec));
    std::memset (&time, 0, sizeof (StpwtchTime));
    std::memset (&deltaStop, 0, sizeof (timespec));
    isWorked = false;
    isStopped = true;
    isFromStopToStart = false;
} 

void Stopwatch::conversion ()
{
    time.s = deltaTime / 1000000;
    deltaTime %= 1000000;
    time.ms = deltaTime / 1000;
    time.us = deltaTime % 1000;
    time.min = time.s / 60;
    time.s %= 60;
    time.hour = time.min / 60;
    time.min %= 60;
}

} /// namespace TrafficGenerator
