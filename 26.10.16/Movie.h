#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <fstream>
#include <vector>
#include <string.h>
struct MovieStar
{
    std::string name;
    int age;
    void print(std::ostream& file) { file<<name<<" "<<age;}
};

class Movie
{
    public:
        Movie() = default;
        Movie(const Movie& other) = default;
        Movie& operator=(const Movie& other) = default;

        void read(std::istream&);
        void write(std::ostream&);

        void read_bin(std::ifstream&);
        void write_bin(std::ofstream&);

        std::string GetTitle();
        int GetLength();
        std::vector<MovieStar> GetActors();
    protected:
    private:
        std::string title;
        int length;
        std::vector<MovieStar> actors;
};

#endif // MOVIE_H
