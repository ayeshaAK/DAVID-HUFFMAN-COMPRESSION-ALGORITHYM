#include<iostream>
#include<cstring>
#include <fstream>
#include"ListBasedSet.h"
#include"Tree.h"
using namespace std;


/*
 * Prints a menu of choices for the user and reads/returns the user's response.
 */
char menu() 
{
	cout << endl;
	cout << "1) Size of File in bytes." << endl;
	cout << "2) Number of Unique Characters. " << endl;
	cout << "3) Build character frequency table." << endl;
	cout << "4) Print tree Inorderly." << endl;
	cout << "5) Build Huffman Encoding Table" << endl;
	cout << "6) Encode data." << endl;
	cout << endl;
	cout << "C) Compress file" << endl;
	cout << "Q) quit" << endl;
	cout << endl;

	char choice;
	cin >> choice;
	return choice;
}

void buildHuffmanTable(HuffmanNode* root)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (root->isLeaf())
	{
		cout << root->letter << "              " << root->code << endl;
	}

	buildHuffmanTable(root->left);
	buildHuffmanTable(root->right);
}

void codeQueue(HuffmanNode* root, Queue &q)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (root->isLeaf())
	{
		q.Enqueue(root);
	}

	codeQueue(root->left,q);
	codeQueue(root->right,q);
}

void inOrder(HuffmanNode* root)
{
	if (root != NULL)
	{
		inOrder(root->left);
		cout << root->letter << ":" << root->freq << " ";
		inOrder(root->right);
	}
}

void encode(HuffmanNode* root, string str)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (root->isLeaf()) 
	{
		root->setCode(str);
	}

	encode(root->left, str + "0");
	encode(root->right, str + "1");
}

void setRootFreq( HuffmanNode* a )
{
	if (a->left == NULL || a->right == NULL)
	{
		a->freq = 0;
	}
	else
	{
		a->freq = a->left->freq + a->right->freq;
	}

}

int main()
{
	//STEP1:  Calculate the original size of the file in bits.

	streampos begin, end;
	ifstream myfile("original.txt", ios::binary);
	begin = myfile.tellg();
	myfile.seekg(0, ios::end);
	end = myfile.tellg();
	myfile.close();
	streamoff size = (end - begin);

	//STEP2: Find out how many unique characters are there in the file.

	ListBasedSet l1;
	char letter; int unique_char = 0;
	ifstream myfile1("original.txt");
	if (myfile1.is_open())
	{
		myfile1 >> noskipws;
		while (!myfile1.eof())
		{
			myfile1 >> letter;
			if (l1.insert(letter, 0))
			{
				unique_char++;
			}
		}
	}
	else cout << "Unable to open file." << endl;
	myfile1.close();


	//STEP3: Find the frequency of each character. (print characters and their frequencies)

	char a, b;
	ifstream myfile2("original.txt");
	if (myfile2.is_open())
	{
		myfile2 >> noskipws;
		l1.pointer = l1.head;
		for (int i = 0; i < unique_char; i++)
		{
			a = l1.pointer->data;
			myfile2.clear();
			myfile2.seekg(0, ios::beg);
			while (!myfile2.eof())
			{
				myfile2 >> b;
				if (a == b)
				{
					l1.pointer->freq++;
				}

			}
			l1.pointer = l1.pointer->next;
		}
	}
	else cout << "Unable to open file." << endl;
	myfile2.close();


	Queue myqueue;
	l1.pointer = l1.head;
	for (int i = 0; i < unique_char; i++)
	{
		myqueue.Enqueue(l1.pointer->data, l1.pointer->freq);
		l1.pointer = l1.pointer->next;
	}


//STEP4: Build Huffman tree using Ordered Queues.Print the tree inorderly(including ‘ * ’)

	for (int i = unique_char; i > 1; i--)
	{

		HuffmanNode* temproot = new HuffmanNode;
		temproot->letter = '*';							//SETTING ROOT'S LETTER TO '*'
		temproot->freq = 0;								//SETTING ROOT'S LETTER TO '0'

		HuffmanNode* temp1 = new HuffmanNode;
		HuffmanNode* temp2 = new HuffmanNode;

		temp1 = myqueue.Dequeuemin();				    //GETTING 1ST MIN FREQ LETTER     
		temp2 = myqueue.Dequeuemin();				    //GETTING 2ND MIN FREQ LETTER

		temproot->left = temp1;
		temproot->right = temp2;

		setRootFreq(temproot);							//ROOT'S FREQ = (FREQ LEFTCHILD + FREQ RIGHTCHILD)

		myqueue.Enqueue(temproot);				        //ENQUEUEING THE ROOT BACK INTO THE PRIORITY QUEUE

	}

	HuffmanNode* tree = new HuffmanNode;
	tree = myqueue.Dequeuemin();

//STEP5: Construct a Huffman Table which will contain a character and its corresponding encoding. Print this table.

	Queue code_queue;
	encode(tree, "");
	codeQueue(tree, code_queue);

//Step6: Store encoding of each character in a separate file called encoded.txt and print the size of encoded.txt file in bits.

	string file_string = "";
	ifstream myfile4("original.txt");
	if (myfile4.is_open())
	{
		myfile4 >> noskipws;
		while (!myfile4.eof())
		{
			myfile4 >> letter;
			file_string = file_string + letter;
		}
	}
	else cout << "Unable to open file." << endl;
	myfile4.close();


	string filecode = "";
	ofstream myfile3("encoded.txt");
	if (myfile3.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			filecode = code_queue.getCode(file_string[i]);
			myfile3 << filecode;
		}
	}
	else cout << "Unable to open file";
	myfile3.close();


	streampos begin1, end1;
	ifstream myfile5("encoded.txt", ios::binary);
	begin1 = myfile5.tellg();
	myfile5.seekg(0, ios::end);
	end1 = myfile5.tellg();
	myfile5.close();
	streamoff size1 = (end1 - begin1);

	while (true) {
		char choice = menu();
		if (choice == 'Q' || choice == 'q') {
			break;
		}
		else if (choice == '1') {
			cout << "Size of ""original.txt"" is : " << size << " bytes.\n";
			cout << "Size of ""encoded.txt"" is : " << size1 << " bytes.\n";
		}
		else if (choice == '2') {
			cout << "UNIQUE CHARACTERS : " << unique_char << endl;
		}
		else if (choice == '3') {
			cout << "FREQUENCY TABLE : " << endl;
			code_queue.display();
		}
		else if (choice == '4') {
			cout << endl << endl << "INORDER HUFFMAN TREE : " << endl;
			inOrder(tree);
			cout << endl;
		}
		else if (choice == '5') {
			cout << "HUFFMAN TABLE :" << endl << "CHARACTER    | CODE " << endl;
			buildHuffmanTable(tree);
			
		}
		else if (choice == '6') {
			cout << "Done." << endl;
			encode(tree, "");
			
		}
		else if (choice == 'C' || choice == 'c') {
			cout << "Done." << endl;
		}
		else
		{
			cout << endl << endl <<  "WRONG INPUT!" << endl << endl;
		}
	}

	return 0;

}