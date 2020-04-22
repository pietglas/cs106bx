/* Contains the declarations of two classes, PartHuffTree and 
HuffmanCompress, needed for the Huffman compressing algorithm. 

TODO: 
- see comment at HuffmanCompress::decodeText(). 
- merge two trees and return a smart pointer instead of a raw
pointer. Current attempt didn't work, so I implemented the 
merging with raw pointers. 
- currently the Huffman tree is generated with a priority queue,
based on std::vector. This has bad performance (see assignment 5).
*/

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
	// TODO: save decoding_map_ in the compressed file, otherwise
	// we can't decode the text later when this class goes out
	// of scope.
	std::string decodeText(const char* compressed_file_name);

private:
	PartHuffTree tree_{'\0', 0};
	std::string text_ = "";
	std::string encoded_text_ = "";
	size_t extra_bits_ = 0;
	std::map<char, int> char_occurrences_;
	std::map<char, std::string> encoding_map_;
	std::map<std::string, char> decoding_map_;

	// some helper functions 
	std::string convertCharToBitstring(unsigned char nr) const;
	unsigned char convertBitstringToChar(std::string byte) const;
	void makeEncodeDecodeMapsHelper(HuffNode*& node, std::string& bits);
};

}	// end namespace adt;
