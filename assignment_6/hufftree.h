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
	// Special members, according to rule of three
	PartHuffTree(char character, int amount);
	~PartHuffTree();
	PartHuffTree::PartHuffTree(const PartHuffTree& rhs);
	PartHuffTree& operator = (const PartHuffTree& rhs);

	size_t getRootAmount() const;
	size_t getSize() const;
	friend std::unique_ptr<PartHuffTree>& merge(PartHuffTree& first,
												PartHuffTree& second);

	// HuffmanCompress is a friend, so it can acces private members
    friend class HuffmanCompress;
    // overload boolean operators, so we can put the trees in ordered collections
	friend bool operator <(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator <=(const PartHuffTree& lhs, const PartHuffTree& rhs);
private:
	HuffNode* root_ = nullptr;
	size_t size_ = 0;
	
	// print function for debugging purposes
	void print(HuffNode* node) const;
	// helper functions for copy constructor/assignment and destructor 
	void PartHuffTree::copy(const HuffNode*& node);
	void erase(HuffNode*& node);
	HuffNode* getRoot() const;
};


// Class that constructs a Huffman tree and encodes/decodes a file
class HuffmanCompress {
public:
	HuffmanCompress() {}
	
	void getEncoding(const std::string& file_name);
	void safeEncodedText(const char* compressed_file_name) const;

	// retrieve the original text from the compressed file as a string.
	// note: since this class goes out of scope when the program has finished,
	// we need to save the encoding map somehow, otherwise we can't
	// decode the compressed file.
	std::string decodeText(const char* compressed_file_name);

private:
	PartHuffTree tree_('\0', 0);
	std::string text_ = "";
	std::string encoded_text_ = "";
	std::map<char, int> char_occurrences_;
	std::map<char, std::string> encoding_map_;
	std::map<std::string, char> decoding_map_;

	void countChars(const std::string& file_name);
	std::string convertCharToBitstring(unsigned char nr) const;
	unsigned char convertBitstringToChar(std::string byte) const;
	void makeEncodeTree();
	void makeEncodeDecodeMaps();
	void encodeText();
};

}	// end namespace adt;
