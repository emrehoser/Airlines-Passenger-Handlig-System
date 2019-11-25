//
// Created by student on 10.11.2018.
//
#include "Passenger.h"

Passenger::Passenger(int arriveTime, int departureTime, int lTime, int sTime, bool vip, bool online) {
    this->arriveTime = arriveTime;
    this->departureTime = departureTime;
    this->lTime = lTime;
    this->sTime = sTime;
    this->vip = vip;
    this->online = online;
    this->exTime = arriveTime+lTime;

}
Passenger::Passenger() {
    this->arriveTime =0;
    this->departureTime = 0;
    this->lTime = 0;
    this->sTime = 0;
    this->vip= 0;
    this->online =0;
    this->exTime =0;
}

Passenger::~Passenger() {

}

