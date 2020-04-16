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

class HuffTree {
public:
	HuffTree();
	~HuffTree();

	void encodeFile(std::string& file_name);
	const std::map<char, std::string> getEncoding() const;

private:
	PartHuffTree tree_;
	std::map<char, int> char_occurrences_;
	std::map<char, std::string> encoding_map_;
};

}	// end namespace adt;