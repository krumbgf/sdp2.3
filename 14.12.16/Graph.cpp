#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

class Graph
{
    private:
        vector<vector<pair<int,int>>> graph;
    public:
        Graph() { };
        int AddTop();
        void AddRib(int from, int to,int cost);
        bool member(int v) const;
        bool member(int, int) const;
        int Cost(int v1, int v2) const;
        const vector<pair<int,int>> Neighbors(int v) const;
        int Vertices_count() const;
        void print() const;
};

int Graph::Cost(int v1, int v2) const
{
    for (pair<int,int> p : graph[v1])
    {
        if(p.first == v2)
            return p.second;
    }
    return int();
}

int Graph::Vertices_count() const
{
    return graph.size();
}

int Graph::AddTop()
{
    graph.push_back(vector<pair<int,int>>());
    return graph.size()-1;
}

void Graph::AddRib(int from, int to,int cost)
{
    graph[from].push_back({to,cost});
}

bool Graph::member(int v1, int v2) const
{
    for(auto p : graph[v1])
    {
        if(p.first == v2)
            return true;
    }
    return false;
}

bool Graph::member(int v) const
{
    return v>=0 && v<graph.size();
}

const vector<pair<int,int>> Graph::Neighbors(int v) const
{
    return graph[v];
}

void Graph::print() const
{
    for(int i=0;i<graph.size(); i++)
    {
        cout<<i<<" : ";
        for(auto pr : graph[i])
        {
            cout<<"("<<pr.first<<" , "<<pr.second<<") ";
        }
        cout<<endl;
    }
}

vector<int> bfs(Graph g,int start)
{
    queue<int> vertices;
    vector<int> p(g.Vertices_count(),-1);

    if(!g.member(start))
        return p;
    vertices.push(start);

    while(!vertices.empty())
    {
        int curr_vertex = vertices.front();
        vertices.pop();
        auto neighbors = g.Neighbors(curr_vertex);
        for(pair<int,int> edge : neighbors)
        {
            if(p[edge.first]==-1)
            {
                p[edge.first]=curr_vertex;
                vertices.push(edge.first);
            }
        }
    }
    return p;
}

void Dijkstra(Graph g,int start, vector<int>& dist, vector<int>& p)
{
    auto cmp = [](pair<int,int> p1, pair<int,int> p2){ return p1.second > p2.second; };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> vertices(cmp);
    p.assign(g.Vertices_count(),-1);
    dist.assign(g.Vertices_count(),std::numeric_limits<int>::max());
    vector<bool> visited = vector<bool>(g.Vertices_count(), false);

    if(!g.member(start))
        return;

    vertices.push({start,0});
    dist[start]=0;

    while(!vertices.empty())
    {
        auto curr_vertex = vertices.top();
        vertices.pop();
        if(visited[curr_vertex.first])
            continue;
        visited[curr_vertex.first]=true;
        auto neighbors = g.Neighbors(curr_vertex.first);
        for(pair<int,int> edge : neighbors)
        {
            if(dist[curr_vertex.first] + edge.second < dist[edge.first])
            {
                p[edge.first]=curr_vertex.first;
                dist[edge.first]= dist[curr_vertex.first] + edge.second;
                vertices.push({edge.first,dist[edge.first]});
            }
        }
    }
}

int MST(Graph g,int start, vector<int>& p)
{
    auto cmp = [](pair<int,int> p1, pair<int,int> p2){ return p1.second > p2.second; };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> vertices(cmp);
    p.assign(g.Vertices_count(),-1);
    vector<int> dist(g.Vertices_count(),std::numeric_limits<int>::max());
    vector<bool> visited = vector<bool>(g.Vertices_count(), false);

    if(!g.member(start))
        return -1;

    vertices.push({start,0});
    dist[start]=0;

    while(!vertices.empty())
    {
        auto curr_vertex = vertices.top();
        vertices.pop();
        if(visited[curr_vertex.first])
            continue;
        visited[curr_vertex.first]=true;
        auto neighbors = g.Neighbors(curr_vertex.first);
        for(pair<int,int> edge : neighbors)
        {
            if(!visited[edge.first] && edge.second < dist[edge.first])
            {
                p[edge.first] = curr_vertex.first;
                dist[edge.first] = edge.second;
                vertices.push({edge.first, edge.second});
            }
        }
    }

    int result = 0;
    for(int i=0;i<p.size();i++)
    {
        if(p[i]!=-1)
        {
            result += g.Cost(i,p[i]);
        }
    }
    return result;
}

int main()
{
    Graph g;
    g.AddTop();
    g.AddTop();
    g.AddTop();
    g.AddTop();
    g.AddTop();
    g.AddTop();

    g.AddRib(0,1,1);
    g.AddRib(0,2,2);
    g.AddRib(1,2,3);
    g.AddRib(1,3,5);
    g.AddRib(2,3,8);
    g.AddRib(2,4,1);
    g.AddRib(3,4,2);
    g.AddRib(3,5,6);
    g.AddRib(4,5,3);

    g.AddRib(1,0,1);
    g.AddRib(2,0,2);
    g.AddRib(2,1,3);
    g.AddRib(3,1,5);
    g.AddRib(3,2,8);
    g.AddRib(4,2,1);
    g.AddRib(4,3,2);
    g.AddRib(5,3,6);
    g.AddRib(5,4,3);

    g.print();
    cout<<endl;

    vector<int> dist;
    vector<int> p;

    cout<<MST(g,0,p)<<endl;

    for(int i=0;i<p.size();i++)
        cout<<i<<" "<<p[i]<<endl;

    cout<<endl<<endl;
    Dijkstra(g,0,dist,p);

    for(int i=0;i<dist.size();i++)
        cout<<i<<" "<<dist[i]<<endl;

    return 0;
}
