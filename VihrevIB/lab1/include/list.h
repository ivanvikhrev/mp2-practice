#include "Node.h"
// Циклический список с головой //
template<typename T>
class Rlist
{
private:
	Node<T>* head;
public:
	//Конструкторы и деструктор
	Rlist();
	Rlist(const List<T>& list2);
	~Rlist();

	//Методы
	Rlist& operator=(const List<T>& list2);
	void InsertToTail(); // Вставка в конец
	void Insert();       // Вставка в упорядоченный список
	Node<T>* GetHead() const { return head; } // указатель на голову
	void Clean(); // 
};

template <typename T>
Rlist<T>::Rlist()
{
	head = new Node<T>;
	head->next = head;
}

template <typename T>
Rlist::Rlist(const List<T>& list2) :Rlist()
{

}

template <class T>
Rlist<T>::~Rlist()
{
	Clean();
	delete head;
}

template <class T>
Rlist& Rlist<T>::operator=(const List<T>& list2)
{

}

template <class T>
void Rlist<T>::InsertToTail()
{

}

template <class T>
void Rlist<T>::Insert()
{

}

template <class T>
void Rlist<T>::Clean()
{
	Node<T>* curr = head->next;
	while (curr != head)
	{
		Node<T>* temp = curr->next;
		delete curr;
		curr = temp;
	}
	head->next = head;
}
