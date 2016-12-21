#pragma once
#include "Node.h"
#include <string>
#include <cstring>

std::string prefix(std::string str1, std::string str2)
{
	std::string result;
	unsigned min_len =str1.size();
	if (min_len < str2.size())
		min_len = str2.size();
	for (unsigned i = 0; i < min_len; i++)
	{
		if (str1[i] == str2[i])
			result.push_back(str1[i]);
		else
			break;
	}
	return result;
}

template <typename V>
class RadixTree
{
	private:
		Node<V>* root;
		int size;
		Node<V>* insertNode(Node<V>* rootNode, std::string key, int& offset, int& prefix_size, int& child_index);
		void print(Node<V>* rootNode, std::string key) const;
		void deleteTree(Node<V>* rootNode);
		Node<V>* find(Node<V>* rootNode, std::string key) const;
		void remove(Node<V>* rootNode, std::string key);
	public:
		RadixTree();
		~RadixTree();
		void insert(const std::string& key, V value);
		void remove(const std::string& key);
		bool find(const std::string& key) const;
		V& operator[](const std::string& key);
		void print() const;
};

template<typename V>
RadixTree<V>::RadixTree() : root(nullptr), size(0)
{ }

template<typename V>
void RadixTree<V>::deleteTree(Node<V>* rootNode)
{
	if (rootNode == nullptr) 
		return;
	for (Node<V>* child : rootNode->children)
	{
			deleteTree(child);
			delete child;
	}
}

template<typename V>
RadixTree<V>::~RadixTree()
{
	deleteTree(root);
}

template<typename V>
Node<V>* RadixTree<V>::insertNode(Node<V>* rootNode, std::string key, int& offset, int& prefix_size, int& child_index)
{
	for (unsigned i=0;i<rootNode->children.size();i++)
	{
		int len = rootNode->children[i]->str.size();
		if (len == 0)
			continue;
		std::string pre = prefix(key, rootNode->children[i]->str);
		if (strncmp(rootNode->children[i]->str.c_str(), key.c_str(), len) == 0)
		{
			offset += len;
			return insertNode(rootNode->children[i], std::string(key.c_str() + len), offset, prefix_size, child_index);
		}
		if (pre.size() > 0)
		{
			prefix_size = pre.size();
			child_index = i;
			return rootNode;
		}
	}
	return rootNode;
}

template<typename V>
void RadixTree<V>::insert(const std::string& key, V value)
{
	if (!root)
	{
		root = new Node<V>(std::string(""), value);
	}
	if (root->children.size() == 0)
	{
		root->children.push_back(new Node<V>(key, value));
	}
	else
	{
		int offset = 0;
		int prefix_size = 0;
		int index = 0;
		Node<V>* rootNode = insertNode(root, key, offset, prefix_size, index);
			//insert node
		if (prefix_size != 0)
		{
			Node<V>* newNode = new Node<V>(key.substr(offset,prefix_size), rootNode->children[index]->strVal);
			rootNode->children[index]->str = std::string(rootNode->children[index]->str.c_str() + prefix_size);
			newNode->children.push_back(new Node<V>(std::string(key.c_str() + offset + prefix_size), value));
			newNode->children.push_back(rootNode->children[index]);
			rootNode->children[index] = newNode;
		}
			//insert leaf
		else
		{
			if (rootNode->children.size() == 0)
			{
				rootNode->children.push_back(new Node<V>(std::string(""), rootNode->strVal));
			}
			rootNode->children.push_back(new Node<V>(std::string(key.c_str() + offset), value));
		}
	}
	size++;
}

template<typename V>
void RadixTree<V>::remove(Node<V>* rootNode, std::string key)
{
	for (unsigned i = 0; i < rootNode->children.size(); i++)
	{
		if (rootNode->children[i]->children.size() == 0 && strcmp(rootNode->children[i]->str.c_str(), key.c_str()) == 0)
		{
			delete rootNode->children[i];
			rootNode->children.erase(rootNode->children.begin() + i);
			if (rootNode->children.size() == 1)
			{
				rootNode->str.append(rootNode->children[0]->str);
				rootNode->strVal = rootNode->children[0]->strVal;
				delete rootNode->children[0];
				rootNode->children.clear();
			}
			size--;
			return;
		}
		int len = rootNode->children[i]->str.size();
		if (strncmp(rootNode->children[i]->str.c_str(), key.c_str(), len) == 0)
		{
			return remove(rootNode->children[i], std::string(key.c_str() + len));
		}
	}
}

template<typename V>
void RadixTree<V>::remove(const std::string& key)
{
	remove(root, key);
}

template<typename V>
Node<V>* RadixTree<V>::find(Node<V>* rootNode, std::string key) const
{
	for (Node<V>* child : rootNode->children)
	{
		if (child->children.size() == 0 && strcmp(child->str.c_str(), key.c_str()) == 0)
		{
			return child;
		}
		int len = child->str.size();
		if (strncmp(child->str.c_str(), key.c_str(), len) == 0)
		{
			return find(child, std::string(key.c_str() + len));
		}
	}
	return nullptr;
}

template<typename V>
bool RadixTree<V>::find(const std::string& key) const
{
	if(find(root,key)==nullptr)
		return false;
	return true;
}

template<typename V>
V& RadixTree<V>::operator[](const std::string& key)
{
	return find(root, key)->strVal;
}

template<typename V>
void RadixTree<V>::print(Node<V>* rootNode, std::string key) const
{
	if (rootNode->children.size() == 0)
	{
		std::cout << key.c_str()<<" --> " << rootNode->strVal << std::endl;
	}
	else
	{
		for (auto child : rootNode->children)
		{
			print(child, key + child->str);
		}
	}
}

template<typename V>
void RadixTree<V>::print() const
{
	print(root, std::string(""));
}
