#include <iostream>
#include <queue>
#include "Passenger.h"
#include <fstream>
using namespace std;
enum typee{
    arriving=1,
    luggages=2,
    securitys=3,
};
struct arrive{
    bool operator()(const Passenger &pas1,const Passenger &pas2){
        return pas2.arriveTime < pas1.arriveTime;
    }
};
struct departure{
    bool operator()(const Passenger &pas1,const Passenger &pas2){
        if(pas1.departureTime!=pas2.departureTime)
            return pas2.departureTime < pas1.departureTime;
        else
            return pas2.arriveTime < pas1.arriveTime;
    }
};


struct event{
    Passenger p ;

    int time;

    typee type;
    event(Passenger p,int time,typee type){
        this->time = time;
        this->p = p;
        this->type = type;
    }

};
struct t{
    bool operator()(const event &e1,const event &e2){
        if( e1.time!=e2.time)
            return e2.time < e1.time;
        else if(e1.type!=e2.type)
            return e2.type > e1.type;
        else
            return e2.p.arriveTime < e1.p.arriveTime;
    }
};
int main(int argc, char* argv[]) {
    priority_queue<event,vector<event>, t> eq;

    int pN, lN, sN,aT,dT,lT,sT,now;
    bool vp=0;
    bool onl=1;
    char vp1,onl1;
    ofstream output(argv[2]);
    ifstream myfile;
    myfile.open(argv[1]);
    myfile >> pN;
    myfile >> lN;
    myfile >> sN;
    //priority_queue<Passenger, vector<Passenger>, arrive> pQ1;
    vector<Passenger> pq;
    for(int i = 0; i<pN;i++){
        myfile>>aT;
        myfile>>dT;
        myfile>>lT;
        myfile>>sT;
        myfile>>vp1;
        myfile>>onl1;
        if(vp1 == 'V')
            vp = 1;
        if(onl1 == 'L')
            onl = 0;
        Passenger p(aT,dT,lT,sT,vp,onl);
        pq.push_back(p);
        event e(p,p.arriveTime,arriving);
        eq.push(e);
        vp = 0;
        onl= 1;
    }

    //11111111111111
    queue<Passenger> lq;
    queue<Passenger> sq;
    float wt=0;
    int isn=0;
    while(!eq.empty()){
        event e = eq.top();
        eq.pop();
        now = e.time;
        if(e.type == securitys){
            sN++;
            if(!sq.empty()){
                eq.push(event(sq.front(),now+sq.front().sTime,securitys));
                sq.pop();
                sN--;
            }
            wt+=now-e.p.arriveTime;
            if(now>e.p.departureTime){
                isn++;
            }
        }
        if(e.type == luggages){
            lN++;

            sq.push(e.p);
            if(!lq.empty()){
                eq.push(event(lq.front(),now+lq.front().lTime,luggages));
                lq.pop();
                lN--;
            }
            if(sN>0){
                eq.push(event(sq.front(),now+sq.front().sTime,securitys));
                sq.pop();
                sN--;
            }

        }
        if(e.type == arriving){
            lq.push(e.p);
            if(lN>0){
                eq.push(event(lq.front(),now+lq.front().lTime,luggages));
                lq.pop();
                lN--;
            }



        }
    }
    output<<wt/pN<<" "<<isn<<endl;

    //222222222222222222


    for(int i = 0;i<pq.size();i++){
        eq.push(event(pq[i],pq[i].arriveTime,arriving));
    }
    priority_queue<Passenger,vector<Passenger>,departure> lq2;
    priority_queue<Passenger,vector<Passenger>,departure> sq2;
    float wt2=0;
    int isn2=0;

    while(!eq.empty()){
        event e = eq.top();
        eq.pop();
        now = e.time;
        if(e.type == securitys){
            sN++;
            if(!sq2.empty()){
                eq.push(event(sq2.top(),now+sq2.top().sTime,securitys));
                sq2.pop();
                sN--;
            }
            wt2+=now-e.p.arriveTime;
            if(now>e.p.departureTime){
                isn2++;
            }
        }
        if(e.type == luggages){
            lN++;
            sq2.push(e.p);
            if(!lq2.empty()){
                eq.push(event(lq2.top(),now+lq2.top().lTime,luggages));
                lq2.pop();
                lN--;
            }
            if(sN>0){
                eq.push(event(sq2.top(),now+sq2.top().sTime,securitys));
                sq2.pop();
                sN--;
            }

        }
        if(e.type == arriving){
            lq2.push(e.p);
            if(lN>0){
                eq.push(event(lq2.top(),now+lq2.top().lTime,luggages));
                lq2.pop();
                lN--;
            }



        }
    }
    output<<wt2/pN<<" "<<isn2<<endl;

    //333333333333333
    for(int i = 0;i<pq.size();i++){
        eq.push(event(pq[i],pq[i].arriveTime,arriving));
    }
    queue<Passenger> lq3;
    queue<Passenger> sq3;
    float wt3=0;
    int isn3=0;
    while(!eq.empty()) {
        event e = eq.top();
        eq.pop();
        now = e.time;
        if (e.type == securitys) {
            sN++;
            if (!sq3.empty()) {


                eq.push(event(sq3.front(), now + sq3.front().sTime, securitys));
                sq3.pop();
                sN--;

            }
            wt3 += now - e.p.arriveTime;
            if (now > e.p.departureTime) {
                isn3++;
            }
        }
        if (e.type == luggages) {
            lN++;


            if (!lq3.empty()) {
                eq.push(event(lq3.front(), now + lq3.front().lTime, luggages));
                lq3.pop();
                lN--;
            }

            if (e.p.vip == 1) {
                wt3 += now - e.p.arriveTime;
                if (now > e.p.departureTime) {
                    isn3++;
                }
            } else {
                sq3.push(e.p);
            }
            if (sN > 0 &&!sq3.empty()) {
                eq.push(event(sq3.front(), now + sq3.front().sTime, securitys));
                sq3.pop();
                sN--;
            }


        }
        if (e.type == arriving) {
            lq3.push(e.p);
            if (lN > 0) {
                eq.push(event(lq3.front(), now + lq3.front().lTime, luggages));
                lq3.pop();
                lN--;
            }

        }
    }
    output<<wt3/pN<<" "<<isn3<<endl;

    //444444444444444444
    for(int i = 0;i<pq.size();i++){
        eq.push(event(pq[i],pq[i].arriveTime,arriving));
    }
    priority_queue<Passenger,vector<Passenger>,departure> lq4;
    priority_queue<Passenger,vector<Passenger>,departure> sq4;
    float wt4=0;
    int isn4=0;
    while(!eq.empty()) {
        event e = eq.top();
        eq.pop();
        now = e.time;
        if (e.type == securitys) {
            sN++;
            if (!sq4.empty()) {


                eq.push(event(sq4.top(), now + sq4.top().sTime, securitys));
                sq4.pop();
                sN--;

            }
            wt4 += now - e.p.arriveTime;
            if (now > e.p.departureTime) {
                isn4++;
            }
        }
        if (e.type == luggages) {
            lN++;


            if (!lq4.empty()) {
                eq.push(event(lq4.top(), now + lq4.top().lTime, luggages));
                lq4.pop();
                lN--;
            }

            if (e.p.vip == 1) {
                wt4 += now - e.p.arriveTime;
                if (now > e.p.departureTime) {
                    isn4++;
                }
            } else {
                sq4.push(e.p);
            }
            if (sN > 0 &&!sq4.empty()) {
                eq.push(event(sq4.top(), now + sq4.top().sTime, securitys));
                sq4.pop();
                sN--;
            }


        }
        if (e.type == arriving) {
            lq4.push(e.p);
            if (lN > 0) {
                eq.push(event(lq4.top(), now + lq4.top().lTime, luggages));
                lq4.pop();
                lN--;
            }

        }
    }
    output<<wt4/pN<<" "<<isn4<<endl;
    //555555555555555
    for(int i = 0;i<pq.size();i++){
        eq.push(event(pq[i],pq[i].arriveTime,arriving));
    }
    queue<Passenger> lq5;
    queue<Passenger> sq5;
    double wt5=0;
    int isn5=0;
    while(!eq.empty()){
        event e = eq.top();
        eq.pop();
        now = e.time;
        if(e.type == securitys){
            sN++;
            if(!sq5.empty()){
                eq.push(event(sq5.front(),now+sq5.front().sTime,securitys));
                sq5.pop();
                sN--;
            }
            wt5+=(double)(now-e.p.arriveTime);
            if(now>e.p.departureTime){
                isn5++;
            }
        }
        if(e.type == luggages){
            lN++;


            if(!lq5.empty()){
                eq.push(event(lq5.front(),now+lq5.front().lTime,luggages));
                lq5.pop();
                lN--;
            }
            sq5.push(e.p);
            if(sN>0&&!sq5.empty()){
                eq.push(event(sq5.front(),now+sq5.front().sTime,securitys));
                sq5.pop();
                sN--;
            }

        }
        if(e.type == arriving) {
            if(e.p.online == 1){
                sq5.push(e.p);
                if(sN>0&&!sq5.empty()){
                    eq.push(event(sq5.front(),now+sq5.front().sTime,securitys));
                    sq5.pop();
                    sN--;
                }

            }
            else {

                lq5.push(e.p);
                if (lN > 0&&!lq5.empty()) {
                    eq.push(event(lq5.front(), now + lq5.front().lTime, luggages));
                    lq5.pop();
                    lN--;
                }

            }



        }
    }
    output<<wt5/pN<<" "<<isn5<<endl;
    //66666666666666666
    for(int i = 0;i<pq.size();i++){
        eq.push(event(pq[i],pq[i].arriveTime,arriving));
    }
    priority_queue<Passenger,vector<Passenger>,departure> lq6;
    priority_queue<Passenger,vector<Passenger>,departure> sq6;
    double wt6=0;
    int isn6=0;
    while(!eq.empty()){
        event e = eq.top();
        eq.pop();
        now = e.time;
        if(e.type == securitys){
            sN++;
            if(!sq6.empty()){
                eq.push(event(sq6.top(),now+sq6.top().sTime,securitys));
                sq6.pop();
                sN--;
            }
            wt6+=(double)(now-e.p.arriveTime);
            if(now>e.p.departureTime){
                isn6++;
            }
        }
        if(e.type == luggages){
            lN++;


            if(!lq6.empty()){
                eq.push(event(lq6.top(),now+lq6.top().lTime,luggages));
                lq6.pop();
                lN--;
            }
            sq6.push(e.p);
            if(sN>0&&!sq6.empty()){
                eq.push(event(sq6.top(),now+sq6.top().sTime,securitys));
                sq6.pop();
                sN--;
            }

        }
        if(e.type == arriving) {
            if(e.p.online == 1){
                sq6.push(e.p);
                if(sN>0&&!sq6.empty()){
                    eq.push(event(sq6.top(),now+sq6.top().sTime,securitys));
                    sq6.pop();
                    sN--;
                }

            }
            else {

                lq6.push(e.p);
                if (lN > 0&&!lq6.empty()) {
                    eq.push(event(lq6.top(), now + lq6.top().lTime, luggages));
                    lq6.pop();
                    lN--;
                }

            }



        }
    }
    output<<wt6/pN<<" "<<isn6<<endl;


    myfile.close();




    return 0;
}