#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>
#include <algorithm>

using namespace std;

class Graph
{
    private:
        vector<vector<pair<int,int>>> graph;
    public:
        Graph() { };
        Graph(const Graph&) = default;
        int AddTop();
        void AddRib(int from, int to,int cost);
        bool member(int v) const;
        const vector<pair<int,int>> Neighbors(int v) const;
        int Vertices_count() const;
        void print() const;
};

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
    p[start]=-1;
    return p;
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


    g.AddRib(0,1,4);
    g.AddRib(0,2,2);
    g.AddRib(1,2,1);
    g.AddRib(1,3,5);
    g.AddRib(2,3,8);
    g.AddRib(2,4,10);
    g.AddRib(3,4,2);
    g.AddRib(3,5,6);
    g.AddRib(4,5,3);

    g.AddRib(1,0,4);
    g.AddRib(2,0,2);
    g.AddRib(2,1,1);
    g.AddRib(3,1,5);
    g.AddRib(3,2,8);
    g.AddRib(4,2,10);
    g.AddRib(4,3,2);
    g.AddRib(5,3,6);
    g.AddRib(5,4,3);

    g.print();
    cout<<endl;
    
    vector<int> p=bfs(g,0);
    for(int i=0;i<p.size();i++)
        cout<<i<<" "<<p[i]<<endl;

    vector<int> test;
//    copy(p.begin(),p.end(),back_inserter(test));

    for(int i=0;i<p.size();i++)
        cout<<i<<" "<<test[i]<<endl;
    return 0;
}
