#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <queue>
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
        void RemoveTop(int);
        bool member(int v) const;
        bool member(int, int) const;
        int Cost(int v1, int v2) const;
        const vector<pair<int,int>> Neighbors(int v) const;
        int Vertices_count() const;
        void print() const;
};

void Graph::RemoveTop(int v)
{
    if(v<graph.size())
    {
        graph[v]= vector<pair<int,int>>();

        for_each(graph.begin(),graph.end(),[v](vector<pair<int,int>>& neighbors)
                 {
                     neighbors.erase(remove_if(neighbors.begin(),neighbors.end(),[v](pair<int,int>& edge)
                               {
                                    return edge.first==v;
                               })
                               , neighbors.end());
                 });
    }
}

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

void graphFromFile(ifstream& file, Graph& g, map<string, int>& vert_map)
{
    string name;
    int cost,v1,v2;
    while(!file.eof())
    {
        file>>name;
        if(vert_map.find(name)==vert_map.end())
        {

            v1 = g.AddTop();
            vert_map.insert({name,v1});
        }
        else
        {
            v1 = vert_map[name];
        }

        file>>name;
        if(vert_map.find(name)==vert_map.end())
        {
            v2 = g.AddTop();
            vert_map.insert({name,v2});
        }
        else
        {
            v2 = vert_map[name];
        }

        file>>cost;
        g.AddRib(v1,v2,cost);
        g.AddRib(v2,v1,cost);
    }

}

int shortestWay(Graph& g, int start, int end, vector<int>& way)
{
    auto cmp = [](pair<int,int> p1, pair<int,int> p2){ return p1.second > p2.second; };
    priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> vertices(cmp);
    vector<int> p(g.Vertices_count(),-1);
    vector<int> dist(g.Vertices_count(),std::numeric_limits<int>::max());
    vector<bool> visited = vector<bool>(g.Vertices_count(), false);

    if(!g.member(start))
        return -1;

    vertices.push({start,0});
    dist[start]=0;

    while(!vertices.empty())
    {
        auto curr_vertex = vertices.top();
        if(curr_vertex.first==end)
            break;

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
    int curr_vertex = end;
    while(p[curr_vertex]!=-1)
    {
        way.push_back(curr_vertex);
        curr_vertex=p[curr_vertex];
    }
    way.push_back(start);
    reverse(way.begin(),way.end());
    return dist[end];
}

int main()
{
    map<string,int> vertices_map;
    ifstream in_file("graph.txt");
    Graph g;
    graphFromFile(in_file,g,vertices_map);
    g.print();
    cout<<endl;
    for(auto pr : vertices_map)
    {
        cout<<pr.first<<" "<<pr.second<<endl;
    }
    int n;
    cin>>n; string v1,v2;
    for(int i=0;i<n;i++)
    {
        cin>>v1;
        if(vertices_map.find(v1)!=vertices_map.end())
            g.RemoveTop(vertices_map[v1]);
    }
    cin>>v1>>v2;

    vector<int> way;
    cout<<shortestWay(g,vertices_map[v1],vertices_map[v2], way)<<endl;
    for(auto v : way)
    {
        cout<<v<<"-->";
    }
    return 0;
}
