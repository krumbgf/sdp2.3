#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Movie.h"

using namespace std;

int main()
{
    Movie m;
    std::vector<MovieStar> actors;
    ifstream file_i("f1.txt");
    if(file_i.is_open())
    {
        m.read(file_i);
    }
    cout<<m.GetActors().size();
    ofstream file_o("f2.txt");
    m.write(file_o);

    return 0;
}
