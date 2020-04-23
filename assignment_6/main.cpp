/* File that runs the Huffman compression algorithm. The filenames for 
the original file and the compressed file are provided via the terminal.
the header file contains the class declarations for PartHuffTree 
and HuffmanCompress. 
Also contains some testing instances for PartHuffTree.
*/

#include <iostream>
#include <string>
#include <memory>
#include "hufftree.h"

using std::cout;	using std::endl;
using std::string;

int main(int argc, char **argv) {
	adt::PartHuffTree tree('a', 1);
	adt::PartHuffTree tree1('b', 1);
	adt::PartHuffTree tree3('c', 1);
	adt::PartHuffTree* merged = mergeTrees(tree, tree1);
	merged->print();
	cout << endl;
	adt::PartHuffTree merged_trees = *merged;

	// adt::PartHuffTree* merged1 = mergeTrees(merged_trees, tree3);
	// merged1->print();
	// cout << endl;
	// cout << endl;
	// adt::PartHuffTree merged1_trees = *merged1;
	// adt::PartHuffTree* merged2 = mergeTrees(merged1_trees, merged_trees);
	// merged2->print();
	// cout << endl;
	

	adt::HuffmanCompress huffman;
	// huffman.countChars(argv[1]);
	// huffman.makeEncodeTree();
	// huffman.printTree();
	// huffman.makeEncodeDecodeMaps();
	// huffman.encodeText();
	huffman.getEncoding(argv[1]);
	huffman.printText();
	// huffman.printEncodingMap();
	// huffman.printDecodingMap();
	// huffman.printEncodingMap();
	huffman.printEncodedText();
	// huffman.printTree();

	huffman.safeEncodedText(argv[2]);
	string original_text = huffman.decodeText(argv[2]);
	cout << "retrieved text: " << original_text << endl;
}