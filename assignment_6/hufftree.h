#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace adt {

struct HuffNode {
	char character = '\0';
	int amount = 0;
	HuffNode* zero = nullptr;
	HuffNode* one = nullptr;
};

// Container for the subtrees with which we build the Huffman Tree
class PartHuffTree {
public:
	// Special members, according to rule of three
	PartHuffTree(char character, int amount);
	~PartHuffTree();
	PartHuffTree(const PartHuffTree& rhs);
	PartHuffTree& operator = (const PartHuffTree& rhs);
	void print() const;
	size_t getRootAmount() const;
	size_t getSize() const;
	;
	// // friend std::shared_ptr<PartHuffTree> mergeTrees(PartHuffTree& first,
 //                                                          PartHuffTree& second);
	friend PartHuffTree* mergeTrees(PartHuffTree& first, PartHuffTree& second);
	
	// HuffmanCompress is a friend, so it can acces private members
    friend class HuffmanCompress;
    // overload boolean operators, so we can put the trees in ordered collections
	friend bool operator <(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator ==(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator <=(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator >(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator >=(const PartHuffTree& lhs, const PartHuffTree& rhs);
private:
	HuffNode* root_ = nullptr;
	size_t size_ = 0;
	
	// helper functions for copy constructor/assignment, destructor and print()
	void copy(HuffNode*& copyable, HuffNode*& copy);
	void erase(HuffNode*& node);
	HuffNode* getRoot() const;
	void printTree(HuffNode* node) const;
};


// Class that constructs a Huffman tree and encodes/decodes a file
class HuffmanCompress {
public:
	HuffmanCompress() {}
	// counts how often characters occurs in a text
	void countChars(const std::string& file_name);
	// make the Huffman encoding tree
	void makeEncodeTree();
	void printTree() const;
	// generate encoding and decoding maps from the Huffman encoding tree
	void makeEncodeDecodeMaps();
	void printEncodingMap() const;
	void printDecodingMap() const;
	// encode the text string 
	void encodeText();
	void printText() const;
	void printEncodedText() const;
	
	void getEncoding(const std::string& file_name);

	void safeEncodedText(const char* compressed_file_name) const;

	// retrieve the original text from the compressed file as a string.
	// note: since this class goes out of scope when the program has finished,
	// we need to save the encoding map somehow, otherwise we can't
	// decode the compressed file.
	std::string decodeText(const char* compressed_file_name);

private:
	PartHuffTree tree_{'\0', 0};
	std::string text_ = "";
	std::string encoded_text_ = "";
	std::map<char, int> char_occurrences_;
	std::map<char, std::string> encoding_map_;
	std::map<std::string, char> decoding_map_;

	std::string convertCharToBitstring(unsigned char nr) const;
	unsigned char convertBitstringToChar(std::string byte) const;
	void makeEncodeDecodeMapsHelper(HuffNode*& node, std::string& bits);
};

}	// end namespace adt;
