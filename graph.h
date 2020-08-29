#ifndef GRAPH_H
#define GRAPH_H
#include "data.h"
#include <QComboBox>
#include <QString>
#include <QWebEnginePage>

enum searchPriority {byDistance, byCost, byStops, byTime};

class graph{
public:

    graph();
    ~graph();
    bool findPath(const size_t &source, const size_t &desti,vector<vertex> &result, const size_t &priority);

    // API for GUI:
    void initComboBoxes(QComboBox *&depart, QComboBox *&desti, QComboBox *&search);

    // AIRPORT-GETTERS:
    double getLat(const size_t &airportId){ return airports[airportId].ladtitude;}
    double getLon(const size_t &airportId){ return airports[airportId].longitude;}
    int getTimeZone(const size_t &airportId){ return airports[airportId].timeZone;}
    string getAirportName(const size_t &airportId){ return airports.at(airportId).airportName;}
    string getAITA(const size_t &airportId){ return airports[airportId].iataCode;}
    string getICAO(const size_t &airportId){ return airports[airportId].icaoCode;}
    string getCountry(const size_t &airportId){ return airports[airportId].country;}
    string getCity(const size_t &airportId){ return airports[airportId].city;}
    char getDSTCode(const size_t &airportId){ return airports[airportId].daylightSavingCode;}

    // AIRLINE-GETTERS:
    string getAirlineName(const size_t &airlineID);
    string getAirlineAlias(const size_t &airlineID);
    string getAirlineCountry(const size_t &airlineID);
    string getAirlineCallSign(const size_t &airlineID);
    string getAirlineICAO(const size_t &airlineID);
    string getAirlineIATA(const size_t &airlineID);

protected:
    void dijkstra(const size_t &source, const size_t &desti, vector<vertex> &result);
    void bfsSearch(const size_t &source, const size_t &desti, vector<vertex> &result);
    void parseAirline();
    void parseAirport();
    void createGraph();

private:

    map<size_t,airport> airports;    // <airport ID, airport info>
    map<size_t,airline> airlines;    // <airline ID, airline  info>
    vector<vector<edge>> myGraph;    // adjacency list
    double infinity;
    ifstream in;
    vector<bool> visited;
    vector<edge> vec;
    vector<double> dist;

    bool backTrack(vector<vertex> &result, const size_t &desti);
};
#endif // GRAPH_H
