#include <iostream>
#include <string>
#include <memory>
#include "hufftree.h"

using std::cout;	using std::endl;
using std::string;

int main() {
	adt::PartHuffTree tree('a', 1);
	adt::PartHuffTree tree1('b', 1);
	adt::PartHuffTree tree3('c', 1);
	std::shared_ptr<adt::PartHuffTree> merged = mergeTrees(tree, tree1);
	adt::PartHuffTree merged_trees = *merged;
	std::shared_ptr<adt::PartHuffTree> merged1 = mergeTrees(merged_trees, tree3);
	cout << "done!" << endl;
	adt::HuffNode* root = merged1->getRoot();
	merged1->print(root);
	merged1->erase(root);
	merged1->print(root);




	// adt::HuffmanCompress huffman;
	// huffman.getEncoding("somesentence.txt");
	// huffman.safeEncodedText("somesentence.bin");
}