#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "hufftree.h"

namespace adt {


PartHuffTree::PartHuffTree(char character, int amount): size_{1} {
	root_ = new HuffNode;
	root_->character = character;
	root_->amount = amount;
	root_->one = nullptr;
	root_->zero = nullptr;
}

PartHuffTree::~PartHuffTree() {
	PartHuffTree::erase();
}

size_t PartHuffTree::getRootAmount() const {return root_->amount;}

static PartHuffTree*& PartHuffTree::merge(PartHuffTree& first, PartHuffTree& second) {
	std::unique_ptr<PartHuffTree> new_tree(new PartHuffTree);
	new_tree->root_->amount = first.amount + second.amount;
	new_tree->root_->one = first.root_;
	new_tree->root_->two = second.root_;

	return new_tree;
}

void PartHuffTree::erase(HuffNode*& node=root_) {
	if (node != nullptr) {
		PartHuffTree::erase(node->one);
		PartHuffTree::erase(node->two);
		delete node;
	}
}





void HuffTree::encodeFile(std::string& file_name) {

}

const std::map<char, std::string> HuffTree::getEncoding() const {

}


};