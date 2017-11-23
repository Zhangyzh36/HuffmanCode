#include "Huffman.hpp"

/*
private:
	int numOfChar;
	int root;
	priorityQueue q(comp);
	Node *huffmanTree;
	map<char, string> dict;
*/

Huffman::Huffman(const string &str)
{
	int len = str.length();
	root = -1;
	for (int i = 0; i < len; ++i)
		dict[str[i]] = "";

	numOfChar = dict.size();
	huffmanTree = new Node[2 * numOfChar - 1];

	int k = 0;
	for (map<char,string>::iterator it = dict.begin(); it != dict.end(); ++it)
	{
		huffmanTree[k].ch = it->first;
		huffmanTree[k].freq = 0;
		k++; 	
	}

	for (int i = 0; i < len; ++i)
		huffmanTree[queryChar(str[i])].freq++;

	for (int i = 0; i < numOfChar; ++i)
		q.push(huffmanTree[i]);
	buildHuffmanTree(str);
}


//编码
string Huffman::encode(const string &str)
{
	string res = "";
	for (int i = 0; i < str.length(); ++i)
		res += dict[str[i]];
	return res;
}


//解码
string Huffman::decode(const string &str)
{
	string res = "";
	int curPtr = root;

	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '0')
			curPtr = huffmanTree[curPtr].left;
		else if (str[i] == '1')
			curPtr = huffmanTree[curPtr].right;

		if (huffmanTree[curPtr].left == -1 && huffmanTree[curPtr].right == -1)
		{	
			res += huffmanTree[curPtr].ch;
			curPtr = root;
		}
	}

	return res;
}

void Huffman::printCode()
{
	for (map<char, string>::iterator it = dict.begin(); it != dict.end(); ++it)
		cout << it->first << ":" << it->second << endl;
}

void Huffman::printTree()
{
	showTree(root, 1);
}

Huffman::~Huffman()
{
	if (huffmanTree)
		delete[] huffmanTree;
	huffmanTree = NULL;
}

void Huffman::buildHuffmanTree(const string &str)
{
	for (int i = numOfChar; i < 2 * numOfChar - 1; ++i)
	{
		int index1 = queryNode(q.top());
		q.pop();
		int index2 = queryNode(q.top());
		q.pop();
		huffmanTree[i].freq = huffmanTree[index1].freq + huffmanTree[index2].freq;
		huffmanTree[i].left = index1;
		huffmanTree[i].right = index2;
		huffmanTree[index1].parent = huffmanTree[index2].parent = i;
		q.push(huffmanTree[i]);
	}

	for (int i = 0; i < 2 * numOfChar - 1; ++i)
		if (huffmanTree[i].parent == -1)
		{	
			root = i;
			break;
		}

	for (int i = 0; i < numOfChar; ++i)
	{
		char ch = huffmanTree[i].ch;
		int curPtr = i;
		string code = "";
		while (huffmanTree[curPtr].parent != -1)
		{
			if (huffmanTree[huffmanTree[curPtr].parent].left == curPtr)
				code = "0" + code;
			else 
				code = "1" + code;
			curPtr = huffmanTree[curPtr].parent;
		}

		dict[ch] = code;
	}
}

void Huffman::showTree(int root, int spaces)
{
	if (root == -1)
		return;

	showTree(huffmanTree[root].right, spaces + 9);

	for (int i = 0; i < spaces; ++i)
		cout << " ";

	if (huffmanTree[root].ch == '\0')
		cout << setw(4) << huffmanTree[root].freq << endl;
	else
		cout << huffmanTree[root].ch << ":" << setw(2) << huffmanTree[root].freq << endl;

	showTree(huffmanTree[root].left, spaces + 9);
}

int Huffman::queryChar(const char &ch)
{
	for (int i = 0; i < numOfChar; ++i)
		if (huffmanTree[i].ch == ch)
			return i;

	return -1;
}

int Huffman::queryNode(const Node &node)
{
	for (int i = 0; i < 2 * numOfChar - 1; ++i)
		if (huffmanTree[i] == node)
			return i;

	return -1;
}