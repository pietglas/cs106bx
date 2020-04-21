#include <iostream>
#include <string>
#include <memory>
#include "hufftree.h"

using std::cout;	using std::endl;
using std::string;

int main(int argc, char **argv) {
	// adt::PartHuffTree tree('a', 1);
	// adt::PartHuffTree tree1('b', 1);
	// adt::PartHuffTree tree3('c', 1);
	// std::shared_ptr<adt::PartHuffTree> merged = mergeTrees(tree, tree1);
	// adt::PartHuffTree merged_trees = *merged;

	// std::shared_ptr<adt::PartHuffTree> merged1 = mergeTrees(merged_trees, tree3);
	// merged1->print(merged1->getRoot());
	// cout << endl;
	// adt::PartHuffTree merged1_trees = *merged1;
	// std::shared_ptr<adt::PartHuffTree> merged2 = mergeTrees(merged1_trees, merged_trees);
	// merged2->print(merged2->getRoot());
	
	// // adt::PartHuffTree copy_tree = *merged1;
	// // adt::HuffNode* copy_root = copy_tree.getRoot();
	// // cout << "copied the tree" << endl;
	// // copy_tree.print(copy_root);

	adt::HuffmanCompress huffman;
	huffman.countChars(argv[1]);
	huffman.makeEncodeTree();
	string bits = "";
	adt::HuffNode* root = huffman.getTree().getRoot();
	huffman.makeEncodeDecodeMaps(root, bits);
	// huffman.getEncoding(argv[1]);
	// huffman.safeEncodedText(argv[2]);
}