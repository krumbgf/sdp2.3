#include <vector>
#include <iostream>

template <typename T>
class MaxHeap
{
    public:
        MaxHeap(unsigned n) { arr.reserve(n); }
        MaxHeap(std::initializer_list<T> v) { arr=v; Heapify();}
        MaxHeap(std::vector<T>&& vec_rvref) : arr(std::move(vec_rvref))
        {
            Heapify();
        }
        MaxHeap(const std::vector<T>& vec_ref) : arr(vec_ref)
        {
            Heapify();
        }
        MaxHeap() = default;
        MaxHeap(const MaxHeap&) = default;
        MaxHeap& operator=(const MaxHeap&) = default;


        void Add(T value);
        void RemoveTop();
        std::vector<T>&& Sort();

        T GetMaxElement();
        std::vector<T> Get_Copy();
        std::vector<T>&& Get_Move();
        void print()
        {
            for(T value : arr)
                std::cout<<value<<" ";
            std::cout<<std::endl;
        }


    protected:
    private:
        std::vector<T> arr;

        unsigned Parent(unsigned);
        unsigned LeftChild(unsigned);
        unsigned RightChild(unsigned);

        void SiftUp(unsigned);
        void SiftDown(unsigned,unsigned);
        void Heapify();
};

template<typename T>
T MaxHeap<T>::GetMaxElement()
{
    return arr.front();
}

template<typename T>
unsigned MaxHeap<T>::Parent(unsigned n)
{
    if(n!=0)
        return (n - 1) / 2;
    else
        return 0;
}

template<typename T>
unsigned MaxHeap<T>::LeftChild(unsigned n)
{
    return 2 * n + 1;
}

template<typename T>
unsigned MaxHeap<T>::RightChild(unsigned n)
{
    return 2 * n + 2;
}

template<typename T>
void MaxHeap<T>::Add(T value)
{
    arr.push_back(value);
    SiftUp(arr.size()-1);
}

template<typename T>
void MaxHeap<T>::SiftUp(unsigned n)
{
    unsigned p = Parent(n);
    if(n==0 || arr[n]<=arr[p])
        return;

    std::swap(arr[n],arr[p]);
    SiftUp(p);
}

template<typename T>
void MaxHeap<T>::SiftDown(unsigned n, unsigned size)
{
    unsigned l = LeftChild(n);
    unsigned r = RightChild(n);
    unsigned max_index;
    if(r>=size)
    {
        if(l>=size)
            return;
        else
            max_index = l;
    }
    else
    {
        arr[l]>=arr[r] ? max_index = l : max_index = r;
    }

    if(arr[n]<arr[max_index])
    {
        std::swap(arr[n],arr[max_index]);
        SiftDown(max_index,size);
    }
}

template<typename T>
void MaxHeap<T>::RemoveTop()
{
    if(!arr.empty())
    {
        std::swap(arr[0],arr.back());
        arr.pop_back();
        SiftDown(0,arr.size());
    }
}

template<typename T>
void MaxHeap<T>::Heapify()
{
    int i = Parent(arr.size()-1);
    for( ;i>=0;i--)
        SiftDown(i,arr.size());
}

template<typename T>
std::vector<T>&& MaxHeap<T>::Sort()
{
    int n = arr.size();
    for(int i=0;i<n-1;i++)
    {
        std::swap(arr[0],arr[n-i-1]);
        SiftDown(0,arr.size()-i-1);
    }
    return std::move(arr);
}

template <typename T>
std::vector<T>&& MaxHeap<T>::Get_Move()
{
    return std::move(arr);
}

template <typename T>
std::vector<T> MaxHeap<T>::Get_Copy()
{
    return arr;
}

int main()
{
/*    MaxHeap<int> h = {10,8,7,7,6,3,2,0,1};
    h.Add(11);
    h.print();
    h.RemoveTop();
    h.print(); */

    MaxHeap<int> h = {4,6,2,8,9,2,10};

    std::vector<int> s_vec;
    s_vec = h.Sort();

    for(int v : s_vec)
        std::cout<<v<<" ";
    std::cout<<"\n";

    return 0;
}
