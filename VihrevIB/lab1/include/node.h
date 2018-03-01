#pragma once
#include <iostream>

template <typename T>

class  Node
{
public:
	T data;
	Node* next;
	Node(T d = NULL; Node<T>* n = nullptr) { data = d; next = n; }
	Node(Node<T> &Node2) { data = node2.data; next = nullptr; }
	bool operator==(const Node<T>& node2) const { return (data == node2.data && next == node2.next); }
};