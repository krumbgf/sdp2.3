#include<iostream>
#include<cassert>
#include<fstream>
using namespace std;

template <typename T>
struct node
{
    T inf;
    node<T>* link;

    node() : link(NULL) {}
    node(T what) : inf(what), link(NULL) {}
};

template <typename T>
class queue
{
private:
    node<T>* first;
    node<T>* current;
    node<T>* last;
    unsigned size;

public:
    queue()
    {
        first = NULL;
        current = NULL;
        last = NULL;
        size = 0;
    }

    queue(const queue& ot) : first(NULL), last(NULL) , current (NULL) , size(0)
    {
        current = ot.first;
        while(current)
        {
            push(current->inf);
            current = current->link;
        }
    }

    void del()
    {
        current = first;
        while(current != NULL){
            node<T>* temp = current;
            current = temp->link;
            delete temp;
        }
    }

    ~queue()
    {
        del();
    }

     queue& operator=(const queue& rhs)
    {
        if(this != &rhs)
        {

        del();
        first = NULL;
        current = NULL;
        last = NULL;
        size = 0;
        current = rhs.first;
        while(current)
        {
            push(current->inf);
            current = current->link;
        }

        }
    }

    void push(const T what)
    {
        if(size == 0)
        {

            first = new node<T>(what);
            last = first;
            size++;
        }
        else
        {


        node<T>* temp = new node<T>(what);
        last->link = temp;
        last = temp;
        size++;
        }
    }


    T pop()
    {
        T val = first->inf;
        node<T>* old = first;
        first = first->link;
        delete old;
        size--;
        return val;

    }

    void print()
    {
        current = first;
        while(current)
        {
            cout<<current->inf<<endl;
            current = current->link;
        }
    }

    void load(istream& in)
    {
        if(in)
        {
            del();
            T val;
            while(!in.eof())
            {
                in>>val;
                if(in)
                {
                    push(val);
                }
                else break;
            }
        }
        else
        {
            cerr<<"Error!"<<endl;
        }
}
    void store(ostream& out)
    {
        if(out)
        {
            current = first;
            while(current)
            {
                out<<current->inf<<endl;
                current = current->link;
            }
        }
        else
        {
            cerr<<"Error!"<<endl;
        }
    }

};

int main()
{
    queue<int> q;

    ifstream file;
    file.open("f1.txt");
    ofstream file2("f2.txt");

    q.load(file);
    q.store(file2);
    q.print();
    file.close();
    file2.close();
    return 0;
}
