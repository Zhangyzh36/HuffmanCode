#include "Huffman.hpp"

int main()
{
	string str = "asfnkjnfkjsa675ndkfsdmkl43s9vg8hdjfn009fdlfvkl43dsfcddcs8ikolja";
	cout << endl << "Bulid a huffman tree with string " << str << "." << endl;
	Huffman h(str);
	cout << "The structure of the tree:" << endl;
	h.printTree();
	h.printCode();
	cout << "encode asfnkjnfkjsa675ndkfsdmkl43s9vg8hdjfn009fdlfvkl43dsfcddcs8ikolja:" << endl;
	cout << h.encode(str) << endl;
	cout << "decode 1100100111100110110101101010110011:" << endl;
	cout << h.decode("1100100111100110110101101010110011") << endl;

	return 0;
}