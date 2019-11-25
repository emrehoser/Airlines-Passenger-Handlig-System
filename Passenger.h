//
// Created by student on 10.11.2018.
//

#ifndef UNTITLED_PASSENGER_H
#define UNTITLED_PASSENGER_H

#include <iostream>
using namespace std;
class Passenger{
public:
    int arriveTime;
    int departureTime;
    int lTime;
    int sTime;
    int exTime=arriveTime+lTime;
    bool vip;
    bool online;
    Passenger(int arriveTime,int departureTime,int lTime,int sTime,bool vip,bool online);
    Passenger();



    ~Passenger();
};
#endif //UNTITLED_PASSENGER_H
