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

void Movie::write_bin(std::ofstream& file)
{
    if(file.is_open())
    {
        int title_size = title.size() +1;
        char* buf = new char[title_size];
        strcpy(buf,title.c_str());
        file.write(reinterpret_cast<const char*>(&title_size),sizeof(int));
        file.write(reinterpret_cast<const char*>(buf),sizeof(char)*title_size);
        delete [] buf;

        file.write(reinterpret_cast<const char*>(&length),sizeof(int));

        int tmp = actors.size();
        file.write(reinterpret_cast<const char*>(&tmp),sizeof(int));
        for(auto it=actors.begin(); it!=actors.end();it++)
        {
            int ms_name_size = it->name.size() +1;
            file.write(reinterpret_cast<const char*>(&ms_name_size),sizeof(int));
            char* buf = new char[ms_name_size];
            strcpy(buf,it->name.c_str());
            file.write(reinterpret_cast<const char*>(buf),sizeof(char)*ms_name_size);
            delete [] buf;

            file.write(reinterpret_cast<const char*>(&(it->age)),sizeof(int));
        }

    }
}

void Movie::read_bin(std::ifstream& file)
{
    if(file.is_open())
    {
        int title_size;
        file.read(reinterpret_cast<char*>(&title_size),sizeof(int));

        char* buf = new char[title_size];
        file.read(reinterpret_cast<char*>(buf),sizeof(char)*title_size);
        title = buf;
        delete [] buf;

        file.read(reinterpret_cast<char*>(&length),sizeof(int));

        int vec_len;
        file.read(reinterpret_cast<char*>(&vec_len),sizeof(int));
        actors.clear();
        for(int i=0; i < vec_len; i++)
        {
            int ms_name_size;
            file.read(reinterpret_cast<char*>(&ms_name_size),sizeof(int));
            char* buf = new char[ms_name_size];
            file.read(reinterpret_cast<char*>(buf),sizeof(char)*ms_name_size);
            MovieStar tmp;
            tmp.name=buf;
            delete [] buf;

            file.read(reinterpret_cast<char*>(&(tmp.age)),sizeof(int));
            actors.push_back(tmp);
        }
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

int Movie::GetLength()
{
    return length;
}
