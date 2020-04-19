#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace adt {

struct HuffNode {
	char character;
	int amount;
	HuffNode* zero;
	HuffNode* one;
};

// Container for the subtrees with which we build the Huffman Tree
class PartHuffTree {
public:
	PartHuffTree(char character, int amount);
	~PartHuffTree();

	size_t getRootAmount() const;
	static std::unique_ptr<PartHuffTree>& merge(PartHuffTree& first, PartHuffTree& second);
	void erase();

private:
	HuffNode* root_;
	size_t size_;
	
	friend class HuffTree;
};


// Class that constructs a Huffman tree and encodes/decodes a file
class HuffTree {
public:
	HuffTree();
	~HuffTree();

	void countChars(std::string& file_name);
	std::string convertCharToBitstring(unsigned char nr);
	unsigned char convertBitstringToChar(std::string byte);
	void makeEncodeTree();
	void makeEncodeMap();
	void encodeText() const;

private:
	PartHuffTree tree_;
	std::map<char, int> char_occurrences_;
	std::map<char, std::string> encoding_map_;
};

}	// end namespace adt;
