#pragma once
#include <iostream>

template <typename T>

class  Node
{
public:
	T data;
    Node<T>* next;
	
	Node(T DATA = NULL, Node<T>* NEXT = nullptr) { data = DATA; next = NEXT; }
	Node(Node<T> &Node2) { data = node2.data; next = nullptr; }
	//операторы сравнения
	bool operator< (const Node<T>& N) const { return (data<N.data); }
	bool operator> (const  Node<T>& N) const { return (data>N.data); }
	bool operator!= (const  Node<T>& N) const { return !(*this == N); }
	bool operator==(const Node<T>& N) const { return (data == N.data && next == N.next); }
};