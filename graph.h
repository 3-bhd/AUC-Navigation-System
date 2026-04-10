#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <QPointF>
#include <queue>
#include <unordered_map>

using namespace std;
class Graph
{

public:
    struct vertex {
        typedef pair<int, vertex*> ve;
        vector<ve> adj; //cost of edge, destination vertex
        string name;
        QPointF pos;
        vertex(string s, QPointF p) : name(s), pos(p) {}
    };
    struct PriorityQueue {
        typedef pair<int, vertex*> PQElement;
        priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

        inline bool empty() const { return elements.empty(); }

        void put(vertex *v, int priority) {
            elements.emplace(priority, v);
        }

        vertex* get() {
            vertex* v = elements.top().second;
            elements.pop();
            return v;
        }
    };
    Graph();
    typedef map<string, vertex*> vmap;
    vmap work;
    void addvertex(const string&, QPointF p);
    bool addedge(const string& from, const string& to, double cost);
    void saveNodes(string text);
    void saveEdges(string text);
    void loadNodes(string text);
    void loadEdges(string text);
    void deleteNode(string n);
    QPointF getPos(string n);
    vertex* getVertex(string n);
    vector<string> AStar(const string& start, const string& goal);
    void print() {
        for (vmap::iterator it = work.begin(); it != work.end(); ++it) {
            cout << "Vertex: " << it->first << endl;
            cout << "Adjacent vertices: ";
            for (vector<vertex::ve>::iterator jt = it->second->adj.begin(); jt != it->second->adj.end(); ++jt) {
                cout << jt->second->name << " ";
            }
            cout << endl;
        }
    }
};





#endif // GRAPH_H
