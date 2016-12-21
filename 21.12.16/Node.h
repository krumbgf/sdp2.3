#pragma once
#include <string>
#include <vector>
template <typename V>
struct Node
{
	std::string str;
	V strVal;
	std::vector<Node<V>*> children;
	Node(std::string s, V v) : str(s), strVal(v) { }
	Node() = default;
	Node(const Node&) = default;
	Node& operator=(const Node&) = default;
};
