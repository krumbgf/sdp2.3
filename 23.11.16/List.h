#ifndef _LIST_H_
#define _LIST_H_

template <typename T>
struct Box
{
	Box(T d, Box<T>* ptr) : data(d), next(ptr){ }
	Box(){ }
	T data;
	Box<T> *next;
};

template <typename T>
class List
{
private:
	Box<T>* first, *last;
	size_t _size;
public:
	class Iterator
	{
	private:
		friend List;
		Box<T>* ptr;
		Iterator(Box<T>* oth) : ptr(oth) { }
	public:
		Iterator(const Iterator& oth) : ptr(oth.ptr) { }
		Iterator& operator=(const Iterator& rhs)
		{
			if (&rhs != this)
				ptr = rhs.ptr;

			return *this;
		}
		bool operator!=(const Iterator& rhs) const { return !(*this==rhs); }
		bool operator==(const Iterator& rhs) const
		{
			if (this == &rhs)
				return true;
			return rhs.ptr == ptr;
		}
		Iterator operator+(size_t n) const
		{
			Iterator tmp = ptr;
			for (size_t i = 0; i<n; i++)
				tmp++;
			return tmp;
		}

		Iterator operator++() { ptr = ptr->next; return *this; }
		Iterator operator++(int) { auto cpy = *this; ptr = ptr->next; return cpy; }
		T& operator*() const { return ptr->data; }
		T* operator->() const { return &(ptr->data); }
	};

	List() : _size(0), first(nullptr), last(nullptr) { }
	List(const List&);
	List(List&& oth);
	List& operator=(const List&);
	List& operator=(List&& rhs);
	~List();

	Iterator begin() const;
	Iterator end() const;
	T front() const;
	T back() const;
	Iterator push_back(T);
	Iterator push_front(T);
	Iterator insert_after(const Iterator&, T);
	void pop_back();
	void pop_front();
	void erase(const Iterator&);
	void erase(const Iterator&,const Iterator&);
	size_t size() const;

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
typename List<T>::Iterator List<T>::begin() const
{
	return Iterator(first);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const
{
	return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::push_back(T value)
{
	if (first == nullptr)
	{
		first = new Box<T>(value, nullptr);
		last = first;
		_size++;
		return Iterator(first);
	}
	else
	{
		Box<T>* new_elem = new Box<T>(value, nullptr);
		last->next = new_elem;
		last = new_elem;
		_size++;
		return Iterator(last);
	}

}

template <typename T>
typename List<T>::Iterator List<T>::push_front(T value)
{
	if (first == nullptr)
	{
		first = new Box<T>(value,nullptr);
		last = first;
		_size++;
		return Iterator(first);
	}
	else
	{
		Box<T>* new_elem = new Box<T>(value,first);
		first = new_elem;
		_size++;
		return Iterator(first);
	}
}

template <typename T>
typename List<T>::Iterator List<T>::insert_after(const Iterator& pos, T value)
{
	Box<T>* new_elem = new Box<T>(value,pos.ptr->next);
	pos.ptr->next = new_elem;
	_size++;
	return Iterator(new_elem);
}

template <typename T>
void List<T>::erase(const Iterator& pos)
{
	if (pos == first)
		pop_front();
	else
	{
		Box<T>* prev = first;
		while (prev->next != pos.ptr)
		{
			prev = prev->next;
		}
		prev->next = pos.ptr->next;
		delete pos.ptr;
		_size--;
		if (_size == 0)
		{
			first = last = nullptr;
		}
	}
}

template <typename T>
void List<T>::erase(const Iterator& f, const Iterator& l)
{
	Box<T>* prev = first;
	Box<T>* tmp;
	if (f.ptr != first)
	{
		while (prev->next != f.ptr)
		{
			prev = prev->next;
		}
		tmp = prev->next;
		prev->next = l.ptr;
	}
	else
	{
		tmp = first;
		first = l.ptr;
	}

	while (tmp != l.ptr)
	{
		Box<T>* tmp2 = tmp->next;
		delete tmp;
		tmp = tmp2;
		_size--;
	}
	if (_size == 0)
	{
		first = last = nullptr;
	}
}

template <typename T>
void List<T>::pop_back()
{
	Box<T>* tmp = first;
	if (_size > 1)
	{
		while (tmp->next->next != nullptr)
		{
			tmp = tmp->next;
		}
	}
	delete last;
	last = tmp;
	last->next = nullptr;
	_size--;
	if (_size == 0)
	{
		first = last = nullptr;
	}
}

template <typename T>
void List<T>::pop_front()
{
	Box<T>* second = first->next;
	delete first;
	first = second;
	_size--;
	if (_size == 0)
	{
		first = last = nullptr;
	}
}

template <typename T>
List<T>::List(const List& oth) : first(nullptr), last(nullptr), _size(0)
{
	for (auto i = oth.first; i != nullptr; i = i->next)
	{
		push_back(i->data);
	}
}

template <typename T>
List<T>& List<T>::operator=(const List& rhs)
{
	if (&rhs != this)
	{
		while (first != nullptr)
			pop_front();

		for (auto i = rhs.first; i != nullptr; i = i->next)
		{
			push_back(i->data);
		}
	}
}

template <typename T>
List<T>& List<T>::operator=(List&& rhs)
{
    while (first != nullptr)
        pop_front();

    first = rhs.first;
    last = rhs.last;
    _size = rhs._size;
    rhs.first = rhs.last =nullptr;
    rhs._size = 0;
}

template <typename T>
List<T>::List(List&& oth) : first(oth.first), last(oth.last), _size(oth._size)
{
    oth.first = oth.last = nullptr;
    oth._size = 0;
}

template <typename T>
List<T>::~List()
{
	while (first != nullptr)
		pop_front();
}

#endif // !_LIST_H_
