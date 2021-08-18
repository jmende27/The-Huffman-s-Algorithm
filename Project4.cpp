#include <time.h>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
using namespace std;
#include "Project4.h"

void insert(Node* n, vector<Node*>& list);
void updateHuffmanCode(vector<Node*>& l, Node* n);
void chToHuff(map <char, string>& map, Node* root);




int main() {

	ifstream infile;
	ofstream outfile;
	char ch, chr;
	map <char, int> charMap;
	map <char, int>::iterator it;
	map <char, string> huffmanCode;
	vector <Node*> list;
	Node* tmpNode, * first, * second, * newNode, * tmp;
	string huffman;
	time_t start, end;
	start = time(NULL);

	//opening input file
	infile.open("inputText.txt");
	if (!infile.is_open()) {
		cout << "Unable to open file" << endl;
		exit(1);
	}
	cout << "Input file opened successfully " << endl;

	//Reading input file and gathering characters and frequencies
	while (!infile.eof()) {
		infile >> noskipws >> ch;

		//Did not find in hashmap, so insert new character
		if (charMap.find(ch) == charMap.end()) {
			charMap.insert(make_pair(ch, 1));
		}
		//found in hashmap, incrementing frequency for that character
		else {
			charMap[ch]++;
		}
	}
	infile.close();




	//Making every (already sorted) character & its frequency into a node and saving all nodes in list
	list.clear();
	it = charMap.begin();
	while (it != charMap.end()) {
		tmpNode = new Node(it->first, it->second);
		insert(tmpNode, list);
		it++;
	}
	if (list.size() < 0) {
		cout << "Error, List size is less than 0! " << endl;
	}



	//Creating Huffman Tree
	while (list.size() != 1) {
		first = list[0];
		second = list[1];

		//Create new node with key that is a dummy character '@'
		//and value from the combined frequencies of 2 nodes
		newNode = new Node('@', first->getFrequency() + second->getFrequency());
		newNode->setChildren(first, second);

		//Remove first 2 nodes of list that have already been combined
		list.erase(list.begin());
		list.erase(list.begin());

		//To newNode, add binary 0 to left subtree and binary 1 to right subtree
		updateHuffmanCode(list, newNode);

		//Insert node is list organzied from least to greatest frequency
		insert(newNode, list);
	}




	//Putting leaf nodes (characters) back in a map (huffman code)
	//To find character huffman codes easier
	chToHuff(huffmanCode, list[0]);


	if (list.size() == 1) {
		cout << "Huffman Binary Tree Successfull" << endl;



		//Encrypting input file using huffmanCode map
		infile.open("inputText.txt");
		outfile.open("Encrypted.txt");
		if (!infile.is_open()) {
			cout << "Unable to open input file again" << endl;
			exit(1);
		}

		//Reading input file again
		while (!infile.eof()) {
			infile >> ch;
			//encrypt input file
			outfile << huffmanCode[ch];
		}
		cout << "Input file has been encrypted successfully as: 'Encrypted.txt' " << endl;
		infile.close();
		outfile.close();
	}
	else	{
		cout << "Error! Huffman Tree was not created successfully! " << endl;
	}



	//Decrypting output file now
	infile.open("Encrypted.txt");
	outfile.open("Decrypted.txt");
	if (!infile.is_open()) {
		cout << "Unable to open 'Encrypted' file" << endl;
		exit(1);
	}
	cout << "Encrypted file opened successfully" << endl;

	tmp = list[0];
	//Reading 'Encrypted' file
	while (!infile.eof()) {
		infile >> chr;

		//Move left if character is 0
		if (chr == '0')
			tmp = tmp->getLeftCh();

		//Move right if character is 1
		if (chr == '1')
			tmp = tmp->getRightCh();

		//if character is leaf node, save value to decripted file
		if (tmp->getLeftCh() == NULL && tmp->getRightCh() == NULL) {
			outfile << tmp->getCharacter();
			tmp = list[0];
		}
	}
	infile.close();
	outfile.close();
	cout << "Decoded the encrypted file sucessfully as 'Decrypted.txt'" << endl;



	end = time(NULL);
	cout << "Time taken: " << difftime(end, start) << endl;


	return 0;
}










	//Keep list organized from least to greatest frequencies
	void insert(Node* n, vector<Node*>& list)	{
		list.push_back(n);
		Node* tmp;

		for (int i = list.size() - 1; i > 0; i--) {
			if (list[i]->getFrequency() < list[i - 1]->getFrequency()) {
				//swap them
				tmp = list[i];
				list[i] = list[i - 1];
				list[i - 1] = tmp;
			}
			else
				break;
		}
	}



	void updateHuffmanCode(vector<Node*>& l, Node* n)	{
		queue<Node*> rightQ, leftQ;

		if (n == NULL)
			return;

	//pre-pend left subtree with 0
		if (n->getLeftCh() != NULL) {
			leftQ.push(n->getLeftCh());

			Node* p;
			while (!leftQ.empty()) {
				//check left subtree
				p = leftQ.front();
				p->setCode("0");
				leftQ.pop();

				if (p->getLeftCh() != NULL)
					leftQ.push(p->getLeftCh());
				if (p->getRightCh() != NULL)
					leftQ.push(p->getRightCh());
			}
		}

	//pre-pend right subtree with 1
		if (n->getRightCh() != NULL) {

			rightQ.push(n->getRightCh());

			Node* p;
			while (!rightQ.empty()) {
				p = rightQ.front();
				rightQ.pop();
				p->setCode("1");

				if (p->getLeftCh() != NULL) {
					rightQ.push(p->getLeftCh());
				}

				if (p->getRightCh() != NULL) {
					rightQ.push(p->getRightCh());
				}
			}
		}
	}




	//Put leaf nodes back in a map
	void chToHuff(map <char, string>& map, Node* root) {
		queue <Node* > q;

		if (root == NULL)
			return;

		else
		{
			q.push(root);
			Node* p;
			while (!q.empty()) {
				p = q.front();
				q.pop();

				if (p == NULL)
					continue;

				if (p->getLeftCh() == NULL && p->getRightCh() == NULL)
					map.insert(make_pair(p->getCharacter(), p->getCode()));
				else
				{
					//save children to queue
					q.push(p->getLeftCh());
					q.push(p->getRightCh());
				}
			}
		}
	}
