#ifndef HUFFNAB_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
using namespace std;

const int maxint = ~(1 << 31);

typedef struct HuffmanNode {
	HuffmanNode(char _ch = '\0', int _freq = maxint, int _left = -1, int _right = -1, int _parent = -1)
			   : ch(_ch), freq(_freq), left(_left), right(_right), parent(_parent) {}
	bool operator==(const HuffmanNode &other)
	{
		return ch == other.ch && freq == other.freq && left == other.left && right == other.right && parent == other.parent;
	}
	friend bool operator<(const HuffmanNode &n1, const HuffmanNode &n2){
		return n1.freq > n2.freq;
	}
	char ch;
	int freq;
	int left;
	int right;
	int parent;
}Node;

typedef priority_queue<Node> priorityQueue;

class Huffman{
public:
	Huffman(const string &str);
	string encode(const string &str);
	string decode(const string &str);
	void printCode();
	void printTree();
	~Huffman();
private:
	int numOfChar;
	int root;
	priorityQueue q;
	Node *huffmanTree;
	map<char, string> dict;
	void buildHuffmanTree(const string &str);
	void showTree(int root, int spaces);
	int queryChar(const char &ch);
	int queryNode(const Node &node);
};

#endif 