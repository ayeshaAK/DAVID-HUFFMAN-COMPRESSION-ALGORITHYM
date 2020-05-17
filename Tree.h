#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

struct HuffmanNode
{
public:
	char letter;
	int freq;
	string code;
	HuffmanNode* next;
	HuffmanNode* left;
	HuffmanNode* right;
	HuffmanNode();
	HuffmanNode(char, int, HuffmanNode*, HuffmanNode*, HuffmanNode*);
	bool isLeaf() const;
	void setCode(string);
    ~HuffmanNode();
};

class Queue
{
public:
	int size;
	HuffmanNode* head;
	HuffmanNode* tail;
	Queue();
	bool queueEmpty() const;
	void clear();
	void display()const;
	int getLength();
	string getCode(char d);
	void Enqueue(char, int);
	HuffmanNode* Enqueue(HuffmanNode*&);
	int min(HuffmanNode*);
	int max(HuffmanNode*);
	HuffmanNode* Dequeuemin();
	HuffmanNode* Dequeuemax();
	~Queue();
};


class BSTree
{
public:
	HuffmanNode* root;
	BSTree();
	void insert(HuffmanNode* a);
	bool find(char);
	bool remove(char);
	bool isEmpty();
	void setRootLetter();
	~BSTree();
};

/************************************* class HuffmanNode ***************************************/
HuffmanNode::HuffmanNode()
{
	char letter = '*';
	int freq = 0;
	next = NULL;
	right = NULL;
	left = NULL;
}
HuffmanNode::HuffmanNode(char character, int count, HuffmanNode* n, HuffmanNode* zero, HuffmanNode* one) {
	this->letter = character;
	this->freq = count;
	this->next = n->next;
	this->left = zero;
	this->right = one;
}
bool HuffmanNode::isLeaf() const
{
	return (left == NULL && right == NULL);
}
void HuffmanNode::setCode(string str) 
{
	this->code = str;
}
HuffmanNode::~HuffmanNode()
{
}

/************************************* class BSTree ***************************************/
BSTree::BSTree() : root(NULL)
{}

void BSTree::insert(HuffmanNode* a)
{
	if (a == NULL)
	{
		cout << "QUEUE IS EMPTY NOW. UNABLE TO INSERT." << endl;
		return;
	}
	if (isEmpty())
	{
		//cout << a->letter << "  root  " << a->freq << endl;
		HuffmanNode* temp = new HuffmanNode;
		temp->letter = a->letter;
		temp->freq = a->freq;
		temp->left = temp->right = NULL;
		root = temp;
		return;
	}
	HuffmanNode* temp1 = root;
	while (temp1 != NULL)
	{
		if ( temp1->left == NULL)
		{
			//cout << a->letter << "  1  " << a->freq << endl;
			HuffmanNode* temp2 = new HuffmanNode;
			temp2->letter = a->letter;
			temp2->freq = a->freq;
			temp1->left = temp2;
			return;
		}
		else if ( temp1->right == NULL)
		{
			//cout << a->letter << "  2  " << a->freq << endl;
			HuffmanNode* temp3 = new HuffmanNode;
			temp3->letter = a->letter;
			temp3->freq = a->freq;
			temp1->right = temp3;
			return;
		}
		else
		{
			if (temp1->freq > a->freq)
			{
				//cout << a->letter << "  7  " << a->freq << endl;
				temp1 = temp1->left;
			}
			else
			{
				//cout << a->letter << "  8  " << a->freq << endl;
				temp1 = temp1->right;
			}
		}
	}
}

bool BSTree::find(char d)
{
	HuffmanNode* temp1 = root;
	while (temp1 != NULL)
	{
		if (temp1->letter == d)
		{
			return true;
		}
		if (temp1->letter > d)
		{
			temp1 = temp1->left;
		}
		if (temp1->letter < d)
		{
			temp1 = temp1->right;
		}
	}return false;
}
bool BSTree::remove(char l)
{
	HuffmanNode* temp1 = root;
	while (temp1 != NULL)
	{
		if (temp1->letter == l)
		{
			delete temp1;
			temp1 = nullptr;
			return true;
		}
		if (temp1->letter > l)
		{
			temp1 = temp1->left;
		}
		if (temp1->letter < l)
		{
			temp1 = temp1->right;
		}
	}
	return false;
}

bool BSTree::isEmpty()
{
	return (root == NULL);
}

void BSTree::setRootLetter()
{

	this->root->letter = '*';

}

BSTree::~BSTree()
{

}


/************************************* class BSTree ***************************************/

Queue::Queue()
{
	size = 0;
	head = NULL;
	tail = NULL;
}

bool Queue::queueEmpty()const
{
	return (head == NULL);
}

string Queue::getCode(char d)
{
	HuffmanNode* temp1 = head;
	while (temp1 != NULL)
	{
		if (temp1->letter == d)
		{
			return temp1->code;
		}
		temp1 = temp1->next;
	}
}

void Queue::Enqueue(char d, int f)
{
	if (queueEmpty())
	{
		head = new HuffmanNode;
		head->letter = d;
		head->freq = f;
		head->next = NULL;
		tail = head;
		size++;
		return;
	}
	HuffmanNode* temp = new HuffmanNode;
	tail->next = temp;
	temp->letter = d;
	temp->freq = f;
	temp->next = NULL;
	tail = temp;
	size++;
	return;
}

HuffmanNode* Queue::Enqueue(HuffmanNode* &a)
{
	if (queueEmpty())
	{
		head = new HuffmanNode;
		head->letter = a->letter;
		head->freq = a->freq;
		head->code = a->code;
		head->right = a->right;
		head->left = a->left;
		size++;
		head->next = NULL;
		tail = head;
		return head;
	}
	HuffmanNode* temp = new HuffmanNode;
	tail->next = temp;
	temp->letter = a->letter;
	temp->freq = a->freq;
	temp->code = a->code;
	temp->left = a->left;
	temp->right = a->right;
	size++;
	temp->next = NULL;
	tail = temp;
	return temp;
}
int Queue::max(HuffmanNode* cNode)
{
	if (cNode)
	{
		int max = cNode->freq;
		HuffmanNode* temp = cNode;
		while (temp)
		{
			if (max < (temp->freq))
			{
				max = temp->freq;
			}
			temp = temp->next;
		}
		return max;
	}
}
HuffmanNode* Queue::Dequeuemax()
{
	HuffmanNode* prevNode = NULL;
	HuffmanNode* currNode = head;
	int maximum = max(currNode);
	while (currNode && !(currNode->freq == maximum))
	{
		prevNode = currNode;
		currNode = currNode->next;
	}
	if (currNode == NULL) {
		cout << "QUEUE IS EMPTY." << endl;
		return false;
	}
	if (prevNode) {

		prevNode->next = currNode->next;
		return currNode;
	}
	else {
		head = currNode->next;
		return currNode;
	}
}

int Queue::min(HuffmanNode* cNode)
{
	if (cNode)
	{
		int min = cNode->freq;
		HuffmanNode* temp = cNode;
		while (temp)
		{
			if (min > (temp->freq))
			{
				min = temp->freq;
			}
			temp = temp->next;
		}
		return min;
	}
}
HuffmanNode* Queue::Dequeuemin()
{
	HuffmanNode* prevNode = NULL;
	HuffmanNode* currNode = head;
	int minimum = min(currNode);
	while (currNode && !(currNode->freq == minimum))
	{
		prevNode = currNode;
		currNode = currNode->next;
	}
	if (currNode == NULL) {
		cout << "QUEUE IS EMPTY." << endl;
		return currNode;
	}
	if (prevNode) {

		prevNode->next = currNode->next;
		return currNode;
	}
	else {
		head = currNode->next;
		return currNode;
	}
}
void Queue::clear()
{
	if (queueEmpty())
	{
		cout << "List is Already cleared" << endl;
		return;
	}
	HuffmanNode* temp;
	temp = head;
	while (temp != NULL)
	{
		head = head->next;
		delete temp;
		size--;
		temp = head;
	}
	head = tail;
	return;

}
void Queue::display()const
{
	if (queueEmpty() == false)
	{
		HuffmanNode* currNode = head;
		while (currNode != NULL)
		{
			cout << "Letter: " << currNode->letter << " |  Frequency: " << currNode->freq << endl;
			currNode = currNode->next;
		}

	}
}
int Queue::getLength()
{
	int numOfItems = 0;
	HuffmanNode* temp = head;
	while (temp != NULL)
	{
		numOfItems++;
		temp = temp->next;
	}
	return numOfItems;
}

Queue::~Queue()
{
	HuffmanNode* temp;
	temp = head;
	while (temp != NULL)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}