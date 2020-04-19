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




// Count how often each character occurs in a particular text, save
// as key-value pair in a dictionary. Save the text in a string. 
void HuffTree::countChars(std::string& file_name) {
    std::ifstream textfile(file_name);
    if (!textfile) {
        cout << "An error occurred, maybe the pathfile is wrong?" << endline;
    }
    else {
        char character = '';
        while (textfile.get(character)) {
            if (!char_occurrences_.try_emplace(std::make_pair(character, 1)).second) {
                ++char_occurrences_.[character];
                text_ += character;     // save text as a string
            }
        }
    }
}

// Converts a numerical byte (unsigned char) to a string representing
// a byte
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

// convert a string representing a byte (for instance, "01001001") 
// to an actual byte
unsigned char HuffTree::convertBitstringToChar(std::string byte) {
    unsigned char c = 0;
    for (int i = 0; i != 8; i++) {
        c <<= 1;
        if (byte[i] == '1') c |= 1;
    }
    return c;
}

// use the character count to generate a Huffman tree
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

// Generate an encoding dictionary from the Huffman tree
void HuffTree::makeEncodeMap() {
    HuffNode* ctr = tree_.root_;
    std::string bits = "";
    if (ctr->zero == nullptr && ctr->one == nullptr) 
        encoding_map_.emplace(std::make_pair(ctr->character, bits));
    else {
        if (ctr->zero != nullptr) {
            ctr = ctr->zero;
            bits += '0';
            HuffTree::makeEncodeMap();
            bits -= '0';
        }
        if (ctr->one != nullptr) {
            ctr = ctr->one;
            bits += '1';
            HuffTree::makeEncodeMap();
            bits -= '1';
        }
    }
}

void HuffTree::encodeText() {
    // convert text to a string of 0's and 1's, using Huffman encoding
    for (character : text_) {
        // for each character, determine its encoding
        std::string value = encoding_map_[character];
        encoded_text_ += value;
    }
    // add 0's until the length of the encoded text is divisibly by 8
    while (encoded_text_.size() % 8 != 0)
        encoded_text_ += '0';
}

// Encode the text using our dictionary and save it to a binary file
void HuffTree::safeEncodedText(std::string compressed_file_name) const {
    std::queue characters;
    // reserve memory for the encoded text
    size_t size_file = encoded_text_.size() / 8;
    unsigned char * encoded_text_as_bytes = new unsigned char [size_file];
    // keep track of the index
    ctr = 0;    
    for (bit : encoded_text_) {
        characters.push(bit);
        // if we added 8 'bits' to the queue, make a new byte
        if (characters.size() == 8) {
            std::string str_byte;
            // empty the queue
            while (!characters.empty()) {
                str_byte += characters.front();
                characters.pop();
            }
            // convert the string representing the byte to an actual byte
            unsigned char byte = HuffTree::convertBitstringToChar(str_byte);
            encoded_text_[ctr] = byte;
            ++ctr;
        }
    }
    // write the bytes to a binary file
    std::ofstream compressed_file(compressed_file_name, std::ios:binary);
    if (compressed_file) 
        compressed_file.write(encoded_text_, size_file);
    else 
        cout << "an error occured when trying to open the new file" << endl;

    // free the memory
    delete[] encoded_text_;
}

std::string HuffTree::retrieveEncodedText() {
    
}


};
