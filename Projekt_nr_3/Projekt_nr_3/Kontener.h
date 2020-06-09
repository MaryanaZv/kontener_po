#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Kontener
{
public:

	Kontener();
	~Kontener();

	int GetSize();

	void clear();

	void dodajNaPoczatek(T data);
	void dodajNaKoniec(T data);

	void wyrzucPierwszyElem();
	void wyrzucOstatniElem();

	void dodajElem(T data, int index);
	void wyrzucElem(int index);

	void DodajElementMenu();
	void WyrzucElementMenu();

	T& operator [] (const int index);
	bool operator == (const Kontener& L);
	Kontener<T>& operator= (const Kontener& L);
	Kontener<T>& operator+=(const Kontener& inny_kont);

private:

	template <typename T>
	class Node {
	public:

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		~Node() {}

		T data;
		Node* pNext;
		Node* pPrev;
	};

	Node <T>* head;
	Node <T>* tail;
	int Size;
};

template <typename T>
Kontener <T>::Kontener()
{
	head = nullptr;
	tail = nullptr;
	Size = 0;
}

template <typename T>
Kontener <T>::~Kontener()
{
	clear();
}

template<typename T>
int Kontener<T>::GetSize()
{
	return Size;
}

template<typename T>
void Kontener<T>::clear()
{
	while (Size)
	{
		wyrzucPierwszyElem();
	}
}

template <typename T>
void Kontener <T>::dodajNaPoczatek(T data)
{
	if (Size > 1)
	{
		Node <T>* temp = head;
		head = new Node <T>(data, head);
		temp->pPrev = head;
	}
	else if (Size == 1)
	{
		head = new Node <T>(data, head);
		tail->pPrev = this->head;
	}
	else
	{
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void Kontener <T>::dodajNaKoniec(T data)
{
	if (Size > 1)
	{
		Node <T>* temp = tail;
		tail = new Node <T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	else if (Size == 1)
	{
		tail = new Node <T>(data, nullptr, tail);
		head->pNext = this->tail;
	}
	else
	{
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void Kontener <T>::wyrzucPierwszyElem()
{
	if (Size > 1)
	{
		Node <T>* temp = head;
		head = head->pNext;
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = head;
		tail = head = head->pNext;
		delete temp;
	}

	Size--;
}

template <typename T>
void Kontener <T>::wyrzucOstatniElem()
{
	if (Size > 1)
	{
		Node <T>* temp = tail;
		tail = tail->pPrev;
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = tail;
		tail = head = tail->pPrev;
		delete temp;
	}

	Size--;
}

template <typename T>
void Kontener <T>::dodajElem(T data, int index)
{
	if (index == 0) dodajNaPoczatek(data);

	else if (index == Size || index > Size) dodajNaKoniec(data);

	else if (index <= Size / 2)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext, previous);

		previous->pNext = newNode;
		Node<T>* next = newNode->pNext;
		next->pPrev = newNode;

		Size++;
	}

	else if (index > Size / 2)
	{
		Node<T>* next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{
			next = next->pPrev;
		}

		Node<T>* newNode = new Node<T>(data, next, next->pPrev);

		next->pPrev = newNode;
		Node<T>* previous = newNode->pPrev;
		previous->pNext = newNode;

		Size++;
	}
}

template <typename T>
void Kontener <T>::wyrzucElem(int index)
{
	if (index == 0)
		wyrzucPierwszyElem();

	else if (index == Size - 1 || index > Size)
		wyrzucOstatniElem();

	else if (index <= Size / 2)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		Node<T>* next = toDelete->pNext;
		delete toDelete;
		next->pPrev = previous;

		Size--;
	}

	else if (index > Size / 2)
	{
		Node<T>* next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{
			next = next->pPrev;
		}

		Node<T>* toDelete = next->pPrev;
		next->pPrev = toDelete->pPrev;
		Node<T>* previous = toDelete->pPrev;
		delete toDelete;
		previous->pNext = next;

		Size--;
	}
}

template <typename T>
T& Kontener <T>::operator[] (const int index) {
	if (index < 0 || index > Size - 1)
		throw string("spoza zakresu.");

	else if (index <= Size / 2) {
		int Sizeer = 0;
		Node <T>* current = this->head;

		while (current != nullptr)
		{
			if (Sizeer == index) return current->data;
			current = current->pNext;
			Sizeer++;
		}
	}

	else {
		int Sizeer = Size - 1;
		Node <T>* current = this->tail;

		while (current != nullptr)
		{
			if (Sizeer == index) return current->data;
			current = current->pPrev;
			Sizeer--;
		}
	}
}

template<typename T>
void Kontener<T>::DodajElementMenu()
{
	int index;
	cout << "\nProsze napisac index: ";
	cin >> index;

	if (index < 0 || index >= Size + 1)
		throw invalid_argument("Nieprawidlowy index.");

	else if (index == Size)
	{
		int data;
		cout << "\nProsze wpisac nowe dane: ";
		cin >> data;
		dodajNaKoniec(data);
		return;
	}
	else if (index == 0)
	{
		int data;
		cout << "\nProsze wpisac nowe dane: ";
		cin >> data;
		dodajNaPoczatek(data);
		return;
	}

	int i = 0;

	Node <T>* Ins = head;

	while (i < index)
	{
		Ins = Ins->pNext;
		i++;
	}

	Node <T>* PrevIns = Ins->pPrev;

	Node <T>* temp = new Node<T>;

	cout << "\nProsze wpisac nowe dane: ";
	cin >> temp->data;

	if (PrevIns != 0 && Size != 1)
		PrevIns->pNext = temp;

	temp->pNext = Ins;
	temp->pPrev = PrevIns;
	Ins->pPrev = temp;

	Size++;
}

template<typename T>
void Kontener<T>::WyrzucElementMenu()
{
	int index;
	cout << "\nProsze napisac index: ";
	cin >> index;

	if (index < 0 || index >= Size)
		throw exception("Nieprawidlowy index.");

	else if (index == 0)
	{
		wyrzucPierwszyElem();
		return;
	}

	else if (index == Size - 1)
	{
		wyrzucOstatniElem();
		return;
	}

	int i = 0;

	Node <T>* Del = head;

	while (i < index)
	{
		Del = Del->pNext;
		i++;
	}

	Node <T>* PrevDel = Del->pPrev;

	Node <T>* AfterDel = Del->pNext;

	if (PrevDel != 0 && Size != 1)
		PrevDel->pNext = AfterDel;

	if (AfterDel != 0 && Size != 1)
		AfterDel->pPrev = PrevDel;

	if (index == 0)
		head = AfterDel;
	if (index == Size)
		tail = PrevDel;

	delete Del;

	Size--;
}

template<typename T>
bool Kontener<T>::operator==(const Kontener& L)
{
	if (Size != L.Size) {
		cout << "Rozne rozmiary." << endl;
		return false;
	}

	Node <T>* t1, * t2;

	t1 = head;
	t2 = L.head;

	while (t1 != 0)
	{
		if (t1->data != t2->data) {
			cout << "Rozne dane." << endl;
			return false;
		}

		t1 = t1->pNext;
		t2 = t2->pNext;
	}
	cout << "Kontenery sa jednakowe." << endl;
	return true;
}

template<typename T>
Kontener<T>& Kontener<T>::operator=(const Kontener& L)
{
	if (this == &L)
		return *this;

	this->~Kontener();

	Node <T>* temporar = L.head;

	while (temporar != 0)
	{
		dodajNaKoniec(temporar->data);
		temporar = temporar->pNext;
	}

	return *this;
}

template<typename T>
Kontener<T>& Kontener<T>::operator+=(const Kontener& inny_kont) {

	Kontener<T>* temp = new Kontener<T>(inny_kont);

	if (head == nullptr)
		head = temp->head;
	else
		this->tail->pNext = temp->head;

	Node <T>* tempor = inny_kont.head;

	while (tempor != 0)
	{
		dodajNaKoniec(tempor->data);
		tempor = tempor->pNext;
	}

	return *this;
}