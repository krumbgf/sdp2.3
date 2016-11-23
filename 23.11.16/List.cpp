#include <iostream>
using namespace std;

template <typename T>
struct node
{
    T data;
    node<T>* next;
};

template <typename T>
class List
{
    private :
        node<T>* first, *last;
        size_t _size;
    public:
        class Iterator
        {
            private :
                friend List;
                node<T>* ptr;
                Iterator(node<T>* oth) : ptr(oth) { }
            public :
                Iterator() : ptr(nullptr) { }
                Iterator(const Iterator& oth) : ptr(oth.ptr) { }
                Iterator& operator=(const Iterator& rhs)
                {
                    if(&rhs!=this)
                        ptr = rhs.ptr;
                }
                bool operator!=(const Iterator& rhs) const { return rhs.ptr!=ptr; }
                bool operator==(const Iterator& rhs) const { return rhs.ptr==ptr; }
                Iterator operator+(size_t n) const
                {
                    Iterator tmp = ptr;
                    for(size_t i = 0; i<n;i++)
                        tmp++;
                    return tmp;
                }

                Iterator operator++() { ptr=ptr->next; return *this; }
                Iterator operator++(int) { auto cpy = *this; ptr=ptr->next; return cpy; }
                T& operator*() { return ptr->data; }
                T* operator->() { return &(ptr->data); }
        };

        List() : first(nullptr), last(nullptr), _size(0)
        { }
        List(const List&);
        List(List&& oth) : first(oth.first), last(oth.last), _size(oth._size)
        {
            oth.first = oth.last = nullptr;
            oth._size = 0;
        }
        List& operator=(const List&);
        List& operator=(List&& rhs)
        {
            while(first!=nullptr)
                pop_front();

            first=rhs.first;
            last=rhs.last ;
            _size=rhs._size;
            rhs.first = rhs.last = nullptr;
            rhs._size = 0;
        }
        ~List();
        const Iterator begin() const;
        const Iterator end() const;
        T front() const;
        T back () const ;
        void push_back(T);
        void push_front(T);
        void pop_back();
        void pop_front();
        void insert_after(Iterator, T);
        void erase(Iterator);
        void erase(Iterator, Iterator);
        size_t size() const;
        List split(size_t n);

};

template <typename T>
size_t List<T>::size() const
{
    return _size;
}

template <typename T>
T List<T>::back() const
{
    return last->data;
}

template <typename T>
T List<T>::front() const
{
    return first->data;
}

template <typename T>
const typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(first);
}

template <typename T>
const typename List<T>::Iterator List<T>::end() const
{
    return Iterator(nullptr);
}

template <typename T>
void List<T>::push_back(T value)
{
    if(first==nullptr)
    {
        first = new node<T>;
        first->data = value;
        first->next = nullptr;
        last = first;
    }
    else
    {
        node<T>* new_elem = new node<T>;
        new_elem->data = value;
        new_elem->next = nullptr;
        last->next = new_elem;
        last = new_elem;
    }
    _size++;
}

template <typename T>
void List<T>::push_front(T value)
{
    if(first==nullptr)
    {
        first = new node<T>;
        first->data = value;
        first->next = nullptr;
        last = first;
    }
    else
    {
        node<T>* new_elem = new node<T>;
        new_elem->data = value;
        new_elem->next = first;
        first = new_elem;
    }
    _size++;
}

template <typename T>
void List<T>::insert_after(Iterator pos, T value)
{
    node<T>* new_elem = new node<T>;
    new_elem->data = value;
    new_elem->next = pos.ptr->next;
    pos.ptr->next = new_elem;
    _size++;
}

template <typename T>
void List<T>::erase(Iterator pos)
{
    if(pos==first)
        pop_front();
    else
    {
        node<T>* prev = first;
        while(prev->next!=pos.ptr)
        {
            prev=prev->next;
        }
        prev->next = pos.ptr->next;
        delete pos.ptr;
    _size--;
    }
}

template <typename T>
void List<T>::erase(const Iterator f, const Iterator l)
{
    node<T>* prev = first;
    node<T>* tmp;
    if(f.ptr!=first)
    {
        while(prev->next!=f.ptr)
        {
            prev=prev->next;
        }
        tmp = prev->next;
        prev->next = l.ptr;
    }
    else
    {
        tmp = first;
        first = l.ptr;
    }

    while(tmp!=l.ptr)
    {
        node<T>* tmp2 = tmp->next;
        delete tmp;
        tmp = tmp2;
        _size--;
    }
}

template <typename T>
void List<T>::pop_back()
{
    node<T>* tmp = first;
    while(tmp->next->next!=nullptr)
    {
        tmp=tmp->next;
    }
    delete last;
    last = tmp;
    last->next = nullptr;
    _size--;
}

template <typename T>
void List<T>::pop_front()
{
    node<T>* second = first->next;
    delete first;
    first = second;
    _size--;
}

template <typename T>
List<T>::List(const List& oth) : first(nullptr), last(nullptr), _size(0)
{
    for(auto i =oth.first;i!=nullptr;i=i->next)
    {
        push_back(i->data);
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& rhs)
{
    if(&rhs!=this)
    {
        while(first!=nullptr)
            pop_front();

        for(auto i =rhs.first;i!=nullptr;i=i->next)
        {
            push_back(i->data);
        }
    }
}

template <typename T>
List<T> List<T>::split(size_t n)
{
    List l;
    l.first = first;
    l.last = last;
    for(int i=0;i<n;i++)
    {
        last = l.first;
        l.first=l.first->next;
    }
    last->next=nullptr;
    l._size = _size-n;
    _size = n;
    if(_size==0)
    {
        first = last = nullptr;
    }
    return l;
}

template <typename T>
List<T>::~List()
{
    while(first!=nullptr)
        pop_front();
}

template <typename T>
List<T> Merge(const List<T>& l1, const List<T>& l2)
{
    auto it1 = l1.begin();
    auto it2 = l2.begin();
    List<T> result;
    while(true)
    {
        if(*it1<=*it2)
        {
            result.push_back(*it1);
            if(++it1==l1.end())
                break;
        }
        else
        {
            result.push_back(*it2);
            if(++it2==l2.end())
                break;
        }
    }
    
    while(it1!=l1.end())
    {
        result.push_back(*it1);
        it1++;
    }

    while(it2!=l2.end())
    {
        result.push_back(*it2);
        it2++;
    }
    return result;
}

template <typename T>
void MergeSort(List<T>& l)
{
    if(l.size() < 2)
        return;
    List<T> l1 = l.split(l.size()/2);
    MergeSort(l1);
    MergeSort(l);
    l=move(Merge(l1,l));
}

int main()
{
    List<int> l;
    l.push_back(4);
    l.push_back(3);
    l.push_back(8);
    l.push_back(5);
    l.push_back(2);
    l.push_back(4);
    l.push_back(1);

    MergeSort(l);

    for(auto i = l.begin();i!=l.end();++i)
    {
        cout<<*i<<" ";
    }

    return 0;
}
