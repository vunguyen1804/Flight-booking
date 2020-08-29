#include "graph.h"

graph::graph(){
    infinity = numeric_limits<double>::infinity();
    parseAirport();
    parseAirline();
    createGraph();
}

graph::~graph(){
    airports.clear();
    airlines.clear();
    myGraph.clear();
    visited.clear();
    vec.clear();
    dist.clear();
}

void graph::parseAirline(){
    in.open("airlines.txt");
    vector<string> info(8);
    string line;
    size_t i = 0;
    while (getline(in, line)){
        if(!line.empty()){
            info[i++] = line;
        }else{
            airlines.insert(pair<size_t, airline> (stol(info[0]), airline(info)));
            i = 0;
        }
    }
    in.close();
}

void graph::parseAirport(){
    in.open("airports.txt");
    vector<string> info(12);
    string line;
    size_t i = 0;
    while (getline(in, line)){
        if(!line.empty()){
            info[i++] = line;
        }else{
            airport ar (info);
            airports[ar.airportId] = ar;
            i = 0;
        }
    }
    in.close();
}

void graph::createGraph(){
    in.open("graph.txt");
    // [0] (size_t) airport ID, [1] (string) airline ID.
    // [2] (size_t) destination airport ID, [3] (double) distance.
    string line, info[4];
    size_t i = 0 , source , pathVia, airlineId;
    double distance;
    myGraph.assign(airports.size(), vector<edge>());

    while(getline(in,line)){
        if(!line.empty()){
            info[i++] = line;
        }else{
            source = stol(info[0]);
            airlineId = stol(info[1]);
            pathVia = stol(info[2]);
            distance = stod(info[3]);
            myGraph[source].emplace_back( edge(airlineId, pathVia, distance) );
            i = 0;
        }
    }
    in.close();
}

bool graph::backTrack(vector<vertex> &result, const size_t &desti){
    // didn't find any path
    if(result.back().source != desti || result.size() < 2)
        return false;

    size_t pathVia = result.back().pathVia;

    for (size_t i = result.size() - 2 ; i != SIZE_MAX; --i)
        if(result[i].source == pathVia)
            pathVia = result[i].pathVia;
        else
            result.erase(result.begin() + i);

    return true;
}

bool graph::findPath(const size_t &source, const size_t &desti, vector<vertex> &result, const size_t &priority){

    searchPriority search = searchPriority::byDistance;
    if(priority == 3)
        search = searchPriority::byStops;

    result.clear();

    if(search == searchPriority::byStops)
        bfsSearch(source,desti,result);
    else
        dijkstra(source, desti, result);

    if(result.size() <= 1)
        return false;
    else
        return backTrack(result, desti);
}

void graph::dijkstra(const size_t &source, const size_t &desti, vector<vertex> &result){
    priority_queue<vertex> vertices;
    vertex topOfPQ;
    visited.clear();
    dist.clear();

    // Set distance of all vertices to infinity
    dist.assign(airports.size(), infinity);
    visited.assign(airports.size(),false);

    //Set distance of source vertex to 0, and add source vertex to PQ
    dist[source] = 0;
    vertices.push(vertex(source, source, 0, SIZE_MAX));

    while (!vertices.empty()){

        // Get vertex on top of PQ.
        topOfPQ = vertices.top();

        // Remove top vertex from PQ.
        vertices.pop();

        // Save unvisited vertex to vector result.
        if(!visited[topOfPQ.source])
            result.push_back(topOfPQ);

        // Add visited index
        visited[topOfPQ.source] = true;

        for(const auto &ed : myGraph[topOfPQ.source]){

            // if current vertex has not been visited and it's a shorter path to a target vertex.
            if(!visited[ed.destId] &&  dist[ed.destId] > (dist[topOfPQ.source] + ed.distance)){
                dist[ed.destId] = dist[topOfPQ.source] + ed.distance;
                vertices.push(vertex(ed.destId, topOfPQ.source , dist[ed.destId], ed.airlineId));
            }
        }

        // Stop searching when reaching the destination vertex.
        if (vertices.top().source == desti){
            result.push_back(vertices.top());
            break;
        }
    }
}

void graph::bfsSearch(const size_t &source, const size_t &desti, vector<vertex> &result){
    priority_queue<vertex> vertices;
    vertex topOfPQ;

    // reset visited vector
    visited.clear();
    visited.assign(airports.size(), false);


    // Set distance of all vertices to infinity
    dist.clear();
    dist.assign(myGraph.size(), infinity);

    //Set distance of source vertex to 0, and add source vertex to PQ
    dist[source] = 0;
    vertices.push(vertex(source, source, 0, SIZE_MAX));

    while (!vertices.empty()){

        // Get vertex on top of PQ.
        topOfPQ = vertices.top();

        // Remove top vertex from PQ.
        vertices.pop();

        // Save unvisited vertex to vector result.
        if(!visited[topOfPQ.source])
            result.push_back(topOfPQ);

        // Add visited index
        visited[topOfPQ.source] = true;

        for(const auto &ed : myGraph[topOfPQ.source]){

            if(!visited[ed.destId] &&  dist[ed.destId] > (dist[topOfPQ.source] + 1)){
                dist[ed.destId] = dist[topOfPQ.source] + 1;
                vertices.push(vertex(ed.destId, topOfPQ.source , dist[ed.destId], ed.airlineId));
            }
        }

        // Stop searching when reaching the destination vertex.
        if (vertices.top().source == desti){
            result.push_back(vertices.top());
            break;
        }
    }
}

//GETTERS:
string graph::getAirlineName(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).airlineName;
    return "Private";
}

string graph::getAirlineAlias(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).alias;
    return "N/A";
}

string graph::getAirlineCountry(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).country;
    return "N/A";
}

string graph::getAirlineCallSign(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).callSign;
    return "N/A";
}

string graph::getAirlineICAO(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).icaoCode;
    return "N/A";
}

string graph::getAirlineIATA(const size_t &airlineID){
    if(airlines.count(airlineID))
        return airlines.at(airlineID).iataCode;
    return "N/A";
}

void graph::initComboBoxes(QComboBox *&depart, QComboBox *&desti, QComboBox *&search){

    string IATA, name, city, country, cString;
    QString qStr;
    for(size_t i = 0 ; i < airports.size() ; i++){
        name = airports[i].airportName;
        IATA = airports[i].iataCode;
        //city = airports[i].city;
        country = airports[i].country;
        cString = IATA +" - " + country;
        qStr = QString::fromStdString(cString);
        depart->addItem(qStr);
        desti->addItem(qStr);
    }

    search->addItem("shorstest distance.");
    search->addItem("cheapest flights.");
    search->addItem("shortest time to get to destination.");
    search->addItem("least number of stops.");

}
