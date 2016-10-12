#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

template <class Type>
struct node
{
	Type 			data;
	node<Type>*   	link;
};

template <class Type>
class Stack
{
	private :
			node<Type>*		_top;
			int				_size;

	public:
					Stack();
					~Stack();
			void	push(Type);
			Type	pop();
			Type    top();
			int		size();
};

template <class Type>
Stack<Type>::Stack()
{
    _top		=	NULL;
	_size    =	0;
}

template <class Type>
int	Stack<Type>::size()
{
	return _size;
}

template <class Type>
void Stack<Type>::push(Type v)
{
	if(_top==NULL)
	{
		_top			=	new node<Type>;
		_top->data   =	v;
		_top->link 	=	NULL;
		_size++;
	}
	else
	{
		node<Type>* newElement 	= 	new node<Type>;
		newElement->data 		= 	v ;
		newElement->link		=   _top;
		_top						=	newElement;
		_size++;
	}
}
template <class Type>
Type Stack<Type>::pop()
{
	assert(_size!=0);
	node<Type>* tmp 	= _top;
	Type r			= _top->data;
	_top 			= _top->link;
	delete tmp;
	_size--;
	return r;
}

template <class Type>
Type Stack<Type>::top()
{
	assert(_size!=0);
	return _top->data;
}

template <class Type>
Stack<Type>::~Stack()
{
	while(_top!=NULL)
	{
		pop();
    }
}

int main()
{
	Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;
    cout<<s.pop()<<endl;




	return 0;
}

