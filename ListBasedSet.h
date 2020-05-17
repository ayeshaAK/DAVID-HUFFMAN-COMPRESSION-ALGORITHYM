#pragma once
#include<iostream>
#include<cstring>
using namespace std;

class Node{
public:
	char data;
	int freq;
	Node* next;
	Node() : data('\0'), freq(0), next(NULL)
	{}
	Node(char data, int f) : data(data), freq(f), next(NULL)
	{}
	Node(const Node& obj)
	{
		*this = obj;
	}
	const Node& operator=(const Node& obj)
	{
		if (this != &obj)
		{
			data = obj.data;
			freq = obj.freq;
			next = obj.next;
		}
		return *this;
	}
	~Node() {}
};
class ListBasedSet
{
public:
	//set based on linked list, returns false on insertion if element is already present
	Node* head;
	Node* pointer;
	ListBasedSet() :head(NULL), pointer(NULL)
	{}
	~ListBasedSet()
	{
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; // destroy the current node
			currNode = nextNode;
		}
	}
	ListBasedSet(const ListBasedSet& obj)
	{
		head = NULL;
		*this = obj;
	}
	const ListBasedSet& operator=(const ListBasedSet& obj)
	{
		if (this != &obj)
		{
			clear();
			Node* curr = obj.head;
			while (curr)
			{
				insert(curr->data, curr->freq);
				curr = curr->next;
			}
		}
		return *this;
	}
	bool isEmpty()const
	{
		return (head == NULL);
	}
	bool removeElement(char data) 
	{
		Node* prevNode = NULL;
		Node* currNode = head;
		while (currNode && !(currNode->data == data)) {
			prevNode = currNode;
			currNode = currNode->next;
		}
		if (currNode == NULL) {
			//cout << "Does not exist" << endl;
			return false;
		}
		if (prevNode) {
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		return true;
	}
	void display()const
	{
		if (isEmpty() == false)
		{
			Node* currNode = head;
			while (currNode != NULL)
			{
				cout << "Letter: " << currNode->data << " |  Frequency: " << currNode->freq << endl;
				currNode = currNode->next;
			}
			
		}
	}
	void clear()
	{
		Node* currNode = head;
		Node *cl = NULL;
		while (currNode != NULL) {
			cl = currNode;
			currNode = currNode->next;
			delete cl;
		}
		head = NULL;
	}

	bool insert(char x, int f)
	{
		Node* previous = NULL;
		Node* currNode = head;
		while (currNode != NULL)
		{
			if (currNode->data == x)
			{ // redundancy check
				return false;
			}
			previous = currNode;
			currNode = currNode->next;
		}
		Node* newNode = new Node(x,f);
		if (currNode == head)
		{
			head = newNode;
		}
		else
		{
			previous->next = newNode;
		}
		return true;
	}

	int size()
	{
		Node* node = head; int ind = 0;
		while (node != NULL) {
			node = node->next;
			ind++;
		}
		return ind;
	}
};