#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
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





void HuffTree::countChars(std::string& file_name) {
    std::ifstream textfile(file_name);
    if (!textfile) {
        cout << "An error occurred, maybe the pathfile is wrong?" << endline;
    }
    else {
        char character = '';
        while (textfile.get(character)) {
            if (!char_occurrences_.try_emplace(std::make_pair(character, 1)).second)
                ++char_occurrences_.[character];
        }
    }
}

std::string HuffTree::convertCharToBitstring(unsigned char nr) {
    int value = (int)nr;
    std::string byte = "";
    for (int i = 7; i != -1; i--) {
        if (value - (int)pow(2, i) >= 0) {
            byte += '1';
            value -= (int)pow(2, i);
        }
        else
            byte += '0';
    }
    return byte;
}

unsigned char HuffTree::convertBitstringToChar(std::string byte) {
    unsigned char c = 0;
    for (int i = 0; i != 8; i++) {
        c <<= 1;
        if (byte[i] == '1') c |= 1;
    }
    return c;
}

void HuffTree::makeEncodeTree() {
    //PQueueHeap pqueue;  // to do: overload <, ==, >= for PartHuffTree, template PQueueHeap
    std::priority_queue<PartHuffTree> pqueue;
    for (auto& pair : char_occurrences_) {
        PartHuffTree new_tree{pair.first, pair.second};
        pqueue.emplace(new_tree);
    }
    while (pqueue.size() > 1) {
        std::unique_ptr<PartHuffTree> tree_ptr;
        PartHuffTree first_elt = pqueue.top();
        pqueue.pop();
        PartHuffTree second_elt = pqueue.top();
        pqueue.pop();
        tree_ptr = PartHuffTree::merge(first_elt, second_elt);
        pqueue.emplace(*tree_ptr);
    }
    tree_ = pqueue.top();
}

void HuffTree::makeEncodeMap() {
    HuffNode* ctr = tree_.root_;
    std::string bits = "";
    if (ctr->one == nullptr && ctr->two == nullptr) 
        encoding_map_.emplace(std::make_pair(ctr->character, bits));
    else {
        
    }
}

void HuffTree::encodeText() const {
    // 1. create a map with the encoding of each character, provided by the
    // Huffman Tree
    //
    // 2. create a string representing the text
    //
    // 3. convert blocks of 8 'bits' to a byte, write those bytes to binary file.
}


};
