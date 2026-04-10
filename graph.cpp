#include "graph.h"

Graph::Graph()
{

}
void Graph::addvertex(const string &name, QPointF p)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end())
    {
        vertex *v;
        v = new vertex(name, p);
        work[name] = v;
        return;
    }
    cout << "\nVertex already exists!";
}
void Graph::deleteNode(string n)
{
    vmap::iterator itr = work.find(n);
    work.erase(itr);

}
QPointF Graph:: getPos(string n)
{
    return work[n]->pos;
}
bool Graph::addedge(const string& from, const string& to, double cost)
{
    if(work.find(from) == work.end() || work.find(to) == work.end())
    {
        cout << "Node Doesn't exist" << endl;
        return false;
    }
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    pair<int, vertex *> edge = make_pair(cost, t);
    f->adj.push_back(edge);
    t->adj.push_back(make_pair(cost, f)); // Add edge from 'to' to 'from'
    return true;
}
void Graph:: saveNodes(string text)
{
    ofstream o;
    o.open(text);
    if(o.fail())
        exit(1);
    map<string, vertex *>::iterator it = work.begin();
    while(it != work.end())
    { o << it->second->name << " " << it->second->pos.x() << " " << it->second->pos.y() << endl;
        it++;
    }
    o.close();
}

void Graph:: saveEdges(string text)
{
    ofstream o;
    o.open(text);
    if(o.fail())
        exit(1);
    map<string, vertex *>::iterator it = work.begin();
    while(it != work.end())
    {
        vector<vertex::ve> ::iterator it2 = it->second->adj.begin();
        while(it2 != it->second->adj.end())
        {
            o << it->first << " " << it2->second->name << endl;
            it2++;
        }
        it++;
    }
    o.close();
}
void Graph:: loadNodes(string text)
{
    ifstream i;
    i.open(text);
    if(i.fail())
        exit(1);
    string n;
    QPointF p;
    while(i >> n)
    {
        qreal x;
        i >> x;
        qreal y;
        i >> y;
        p = QPointF(x, y);
        addvertex(n, p);
    }
    i.close();
}
void Graph:: loadEdges(string text)
{
    ifstream i;
    i.open(text);
    if(i.fail())
        exit(1);
    string n1, n2;
    while(i >> n1)
    {

        i >> n2;
        addedge(n1, n2, 10);
    }
    i.close();
}

Graph::vertex* Graph:: getVertex(string n)
{
    return work[n];
}
vector<string> Graph::AStar(const string& start, const string& goal) {
    unordered_map<vertex*, int> costSoFar;
    unordered_map<vertex*, vertex*> cameFrom;
    PriorityQueue frontier;
    vertex* startVertex = work[start];
    vertex* goalVertex = work[goal];

    frontier.put(startVertex, 0);
    cameFrom[startVertex] = startVertex;
    costSoFar[startVertex] = 0;

    while (!frontier.empty()) {
        vertex* current = frontier.get();

        if (current == goalVertex) {
            break;
        }

        for (auto &edge : current->adj) {
            int newCost = costSoFar[current] + edge.first;
            if (!costSoFar.count(edge.second) || newCost < costSoFar[edge.second]) {
                costSoFar[edge.second] = newCost;
                int priority = newCost + edge.first; // heuristic
                frontier.put(edge.second, priority);
                cameFrom[edge.second] = current;
            }
        }
    }

    // Reconstruct path
    vector<vertex*> path;
    vertex* current = goalVertex;
    while (current != startVertex) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(startVertex);
    reverse(path.begin(), path.end());

    vector<string> p;
    for(auto &v : path)
    {
        p.push_back(v->name);
    }
    return p;
}
