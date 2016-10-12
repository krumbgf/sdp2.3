#include<iostream>
#include<cassert>
#include<string.h>
using namespace std;

template <typename T>
class stack
{
    private:
        T* arr;
        int current;
        int size;

    public:
        stack(int s = 10) : size(s), current(0)
        {
            arr = new T[size];
            assert(arr != NULL);
        }

        stack (const stack& oth)
        {
            size=oth.size;
            current=oth.current;
            arr = new T[size];
            memcpy(arr,oth.arr,size);
        }

        stack& operator=(const stack& rhs)
        {
            if(this != &rhs)
            {
                delete [] arr;
                size=rhs.size;
                current=rhs.current;
                arr = new T[size];
                memcpy(arr,rhs.arr,size);
            }
        }

        ~stack()
        {
            delete [] arr;
        }

        void push(const T what)
        {
            if(size>current){
                arr[current] = what;
                current++;
            } else {
                T* temp = new T[2*size];
                assert(temp != NULL);
                for(int i = 0; i<size; i++){
                    temp[i] = arr[i];
                }
                size = 2*size;
                delete [] arr;
                arr = temp;

                arr[current++] = what;
            }

        }

        T pop ()
        {
            if(!isEmpty()){
                current--;
                return arr[current];
            }
            cout<<"The stack is empty."<<endl;
            T dummy;
            return dummy;
        }

        T top()
        {
            if(!isEmpty())
                return arr[current-1];

            cout<<"The stack is empty."<<endl;
            T dummy;
            return dummy;
        }

        bool isEmpty()const
        {
            return current == 0;
        }

};

int main ()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;



    return 0;
}
