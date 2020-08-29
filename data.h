#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <queue>
#include <stack>
using namespace std;

struct vertex {
    size_t source, pathVia, airlineId;
    double distance;

    vertex(){
        pathVia = SIZE_MAX;
        distance = 0;
    }

    vertex(const size_t &source, const size_t pathVia, const double &distance,
           const size_t &airlineId){
        this->source = source;
        this->distance = distance;
        this->pathVia = pathVia;
        this->airlineId = airlineId;
    }

    vertex(const vertex &other){
        copy(other);
    }

    vertex operator = (const vertex &other){
        if(this != &other)
            copy(other);
        return *this;
    }

    void copy(const vertex &other){
        this->source = other.source;
        this->distance = other.distance;
        this->pathVia = other.pathVia;
        this->airlineId = other.airlineId;
    }

    friend
    bool operator > (const vertex &first, const vertex &second){
        return first.distance < second.distance ;
    }

    friend
    bool operator < (const vertex &first, const vertex &second){
        return first.distance > second.distance ;
    }

    friend
    bool operator == (const vertex &first, const vertex &second){
        return first.source == second.source;
    }

    friend
    bool operator != (const vertex &first, const vertex &second){
        return first.source != second.source;
    }
};


struct edge{
    size_t destId, airlineId;
    double distance;

    edge(const size_t &airlineId, const size_t destId, const double &distance){
        this->airlineId = airlineId;
        this->destId = destId;
        this->distance = distance;
    }

    edge operator = (const edge &other ){
        this->airlineId = other.airlineId;
        this->destId = other.destId;
        this->distance = other.distance;
        return *this;
    }
};

struct airline{

    size_t airlineId;
    string airlineName, alias, iataCode, icaoCode, callSign, country;
    bool isActive;
    friend
    bool operator < ( const airline &first, const airline &second) {
        return first.airlineName < second.airlineName;
    }

    friend
    bool operator > ( const airline &first, const airline &second) {
        return first.airlineName > second.airlineName;
    }

    friend
    bool operator == ( const airline &first, const airline &second) {
        return first.airlineName == second.airlineName;
    }

    airline(vector<string> info){
        this->airlineId = stoul(info[0]);
        this->airlineName = info[1];
        this->alias = info[2];
        this->iataCode = info[3];
        this->icaoCode = info[4];
        this->callSign = info[5];
        this->country = info[6];
        this->isActive = (info[7] == "Y") ? true : false;
    }

    airline operator = (const airline &other){
        this->airlineId = other.airlineId;
        this->airlineName = other.airlineName;
        this->alias = other.alias;
        this->iataCode = other.icaoCode;
        this->icaoCode = other.icaoCode;
        this->callSign = other.callSign;
        this->country = other.country;
        this->isActive = other.isActive;

        return *this;
    }

    ~airline(){
        airlineId = 0;
        airlineName.clear();
        alias.clear();
        iataCode.clear();
        icaoCode.clear();
        callSign.clear();
        country.clear();
        isActive = false;
    }
};

struct airport{

    size_t airportId;
    string airportName, city, country, iataCode, icaoCode, dataSource;
    double longitude, ladtitude, altitude;
    int timeZone;
    char daylightSavingCode;

    friend
    bool operator < ( const airport &first, const airport &second) {
        return first.airportId < second.airportId;
    }

    friend
    bool operator > ( const airport &first, const airport &second) {
        return first.airportId > second.airportId;
    }

    airport(){

    }

    airport(vector<string> info){
        this->airportId = stoul(info[0]);
        this->airportName = info[1];
        this->city = info[2];
        this->country = info[3];
        this->iataCode = info[4];
        this->icaoCode = info[5];
        this->ladtitude = stod(info[6]);
        this->longitude = stod(info[7]);
        this->altitude = stod(info[8]);
        this->timeZone = stoi(info[9]);
        this->daylightSavingCode = info[10][0];
        this->dataSource = info[11];
    }

    ~airport(){
        airportName.clear();
        city.clear();
        country.clear();
        iataCode.clear();
        icaoCode.clear();
        dataSource.clear();
        airportId = 0;
        longitude = ladtitude = altitude = 0;
        timeZone = -99;
        daylightSavingCode = 0;
    }

};

#endif // DATA_H






