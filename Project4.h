#include <iostream>

class Node {

private:
	char ch;
	int freq;
	Node* left;
	Node* right;
	string code;

public:
	Node();
	Node(const char& c, const int& f);
	void setChildren(Node* l, Node* r);
	char getCharacter() { return ch; };
	int getFrequency() { return freq; };
	Node* getLeftCh() { return left; };
	Node* getRightCh() { return right; }
	string getCode() { return code; }
	void setCode(string c);
	Node& operator=(const Node& j);

};

Node::Node() {
	freq = 0;
	left = right = NULL;
}
Node::Node(const char& c, const int& f) {
	ch = c;
	freq = f;
	left = right = NULL;
}
void Node::setChildren(Node* l, Node* r) {
	left = l;
	right = r;
}

void Node::setCode(string c) {
	code = c + code;
}

Node& Node::operator=(const Node& j) {
	if (this != &j) {
		ch = j.ch;
		freq = j.freq;
		left = j.left;
		right = j.right;
	}
	return *this;
}