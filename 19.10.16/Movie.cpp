#include "Movie.h"

void Movie::read(std::istream& file)
{
    char buf[100];
    file.getline(buf,100,'~');
    title=buf;
    file>>length;
    while(file.getline(buf,100,'~'))
    {
        int tmp_age;
        file>>tmp_age;
        MovieStar tmp{buf,tmp_age};
        actors.push_back(tmp);
    }
}

void Movie::write(std::ostream& file)
{
    file<<title<<" "<<length;
    for(int it=0; it<actors.size();it++)
    {
        actors[it].print(file);
    }
}

std::string Movie::GetTitle()
{
    return title;
}

std::vector<MovieStar> Movie::GetActors()
{
    return actors;
}
