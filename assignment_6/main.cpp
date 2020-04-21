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
	adt::HuffNode* root = merged1->getRoot();
	merged1->print(root);
	
	adt::PartHuffTree copy_tree = *merged1;
	adt::HuffNode* copy_root = copy_tree.getRoot();
	cout << "copied the tree" << endl;
	copy_tree.print(copy_root);




	// adt::HuffmanCompress huffman;
	// huffman.getEncoding("somesentence.txt");
	// huffman.safeEncodedText("somesentence.bin");
}