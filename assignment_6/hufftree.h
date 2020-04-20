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
	friend std::unique_ptr<PartHuffTree>& merge(PartHuffTree& first,
												PartHuffTree& second);
	void erase(HuffNode*& node);

    friend class HuffmanCompress;
	friend bool operator <(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator ==(const PartHuffTree& lhs, const PartHuffTree& rhs);
	friend bool operator <=(const PartHuffTree& lhs, const PartHuffTree& rhs);
private:
	HuffNode* root_ = nullptr;
	size_t size_;
};


// Class that constructs a Huffman tree and encodes/decodes a file
class HuffmanCompress {
public:
	HuffmanCompress();
	~HuffmanCompress();

	void getEncoding(const std::string& file_name);
	void safeEncodedText(const char* compressed_file_name) const;

	// retrieve the original text from the compressed file as a string.
	// note: since this class goes out of scope when the program has finished,
	// we need to save the encoding map somehow, otherwise we can't
	// decode the compressed file.
	std::string decodeText(const char* compressed_file_name);

private:
	PartHuffTree tree_;
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
