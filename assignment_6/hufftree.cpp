#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <queue>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "hufftree.h"

using std::cout;    using std::endl;

namespace adt {


PartHuffTree::PartHuffTree(char character, int amount): size_{1} {
	root_ = new HuffNode;
	root_->character = character;
	root_->amount = amount;
	root_->one = nullptr;
	root_->zero = nullptr;
}

PartHuffTree::~PartHuffTree() {
	PartHuffTree::erase(root_);
}

PartHuffTree::PartHuffTree(const PartHuffTree& rhs) {
    HuffNode* rhs_root = rhs.getRoot();
    PartHuffTree::copy(rhs_root, root_);
    size_ = rhs.getSize();
}

size_t PartHuffTree::getSize() const {
    return size_;
}

size_t PartHuffTree::getRootAmount() const {return root_->amount;}

// helper function for copy constructor / assignment
void PartHuffTree::copy(HuffNode*& copyable, HuffNode*& copy) {
    if (copyable != nullptr) {
        copy = new HuffNode;
        copy->character = copyable->character;
        copy->amount = copyable->amount;
        PartHuffTree::copy(copyable->zero, copy->zero);
        PartHuffTree::copy(copyable->one, copy->one);
    }
}

// helper function for destructor 
void PartHuffTree::erase(HuffNode*& node) {
	if (node != nullptr) {
        HuffNode* node_zero = node->zero;
        HuffNode* node_one = node->one;
        delete node;
        node = nullptr;     // dereference pointer, for print()
		PartHuffTree::erase(node_zero);
		PartHuffTree::erase(node_one);
	}
}

PartHuffTree& PartHuffTree::operator =(const PartHuffTree& rhs) {
    HuffNode* rhs_root = rhs.getRoot();
    PartHuffTree::copy(rhs_root, root_);
    size_ = rhs.getSize();
    return *this;
}

bool operator <(const PartHuffTree& lhs, const PartHuffTree& rhs) {
    if (lhs.root_->amount < rhs.root_->amount)
        return true;
    else
        return false;
}

bool operator ==(const PartHuffTree& lhs, const PartHuffTree& rhs) {
    if (lhs.root_->amount == rhs.root_->amount)
        return true;
    else
        return false;
}

bool operator <=(const PartHuffTree& lhs, const PartHuffTree& rhs) {
    if (lhs < rhs || lhs == rhs)
        return true;
    else
        return false;
}

bool operator >(const PartHuffTree& lhs, const PartHuffTree& rhs){
    if (!(lhs <= rhs))
        return true;
    else
        return false;
}

bool operator >=(const PartHuffTree& lhs, const PartHuffTree& rhs) {
    if (!(lhs < rhs))
        return true;
    else
        return false;
}

// Helper function for printing
void PartHuffTree::printTree(HuffNode* node) const {
    if (node != nullptr) {
        cout << "character: " << node->character << endl;
        cout << "size: " << node->amount << endl;
        PartHuffTree::printTree(node->zero);
        PartHuffTree::printTree(node->one);
    }
}

void PartHuffTree::print() const {
    PartHuffTree::printTree(root_);
}

HuffNode* PartHuffTree::getRoot() const {
    return root_;
}

// std::shared_ptr<PartHuffTree> mergeTrees(PartHuffTree& first,
//                                                           PartHuffTree& second) {
//     std::shared_ptr<PartHuffTree> new_tree = std::make_shared<PartHuffTree>('\0', 0);
//     new_tree->root_->amount = first.root_->amount + second.root_->amount;
//     new_tree->root_->zero = first.root_;
//     new_tree->root_->one = second.root_;
//     new_tree->size_ = first.size_ + second.size_ + 1;
//     return new_tree;
// }

// merge two trees by adding a new root, making the roots of the 
// arguments its children
PartHuffTree* mergeTrees(PartHuffTree& first, PartHuffTree& second) {
    PartHuffTree* new_tree = new PartHuffTree('\0', 0);
    new_tree->root_->amount = first.root_->amount + second.root_->amount;
    new_tree->root_->zero = first.root_;
    new_tree->root_->one = second.root_;
    new_tree->size_ = first.size_ + second.size_ + 1;
    return new_tree;
}



// Count how often each character occurs in a particular text, save
// as key-value pair in a dictionary. Save the text in a string.
void HuffmanCompress::countChars(const std::string& file_name) {
    std::ifstream textfile(file_name);
    if (!textfile) {
        cout << "An error occurred, maybe the pathfile is wrong?" << endl;
    }
    else {
        char character = '\0';
        while (textfile.get(character)) {
            if (!char_occurrences_.try_emplace(character, 1).second) 
                ++char_occurrences_[character];
            text_ += character;     // save text as a string (not good for large files..)
        }
    }
}

// Converts a numerical byte (unsigned char) to a string representing
// a byte
std::string HuffmanCompress::convertCharToBitstring(unsigned char nr) const {
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
unsigned char HuffmanCompress::convertBitstringToChar(std::string byte) const {
    unsigned char c = 0;
    for (int i = 0; i != 8; i++) {
        c <<= 1;
        if (byte[i] == '1') c |= 1;
    }
    return c;
}

// use the character count to generate a Huffman tree
void HuffmanCompress::makeEncodeTree() {
    // PQueueHeap pqueue;  // to do: overload <, ==, >= for PartHuffTree,
    // template PQueueHeap
    std::priority_queue<PartHuffTree, std::vector<PartHuffTree>,
                        std::greater<PartHuffTree>> pqueue; // need to reverse ordering
    for (auto& pair : char_occurrences_) {
        PartHuffTree new_tree{pair.first, pair.second};
        pqueue.emplace(new_tree);
    }
    while (pqueue.size() > 1) {
        PartHuffTree first_elt = pqueue.top();
        pqueue.pop();
        PartHuffTree second_elt = pqueue.top();
        pqueue.pop();  
        pqueue.emplace(*mergeTrees(first_elt, second_elt));
    }
    tree_ = pqueue.top();
}

void HuffmanCompress::printTree() const {
    tree_.print();
}

// Helper function for encoding dictionary from the Huffman tree, moving from the 
// leftmost node to the rightmost node. 
void HuffmanCompress::makeEncodeDecodeMapsHelper(HuffNode*& node, std::string& bits) {
    if (node != nullptr) {
        if (node->character != '\0') {
            encoding_map_.emplace(node->character, bits);
            decoding_map_.emplace(bits, node->character);
        }
        else {
            HuffNode* node_zero = node->zero;
            bits += '0';
            HuffmanCompress::makeEncodeDecodeMapsHelper(node_zero, bits);
            bits.pop_back();

            HuffNode* node_one = node->one;
            bits += '1';
            HuffmanCompress::makeEncodeDecodeMapsHelper(node_one, bits);
            bits.pop_back();
        }
    }
}

// generates encoding dictionary from the Huffman tree
void HuffmanCompress::makeEncodeDecodeMaps() {
    std::string bits;
    HuffmanCompress::makeEncodeDecodeMapsHelper(tree_.root_, bits);
}

void HuffmanCompress::printEncodingMap() const {
    for (auto& pair : encoding_map_)
        cout << "letter: " << pair.first << ", bits: " << pair.second << endl;
}

void HuffmanCompress::printDecodingMap() const {
    for (auto& pair : decoding_map_)
        cout << "bits: " << pair.first << ", letter: " << pair.second << endl;
}

// encode the text, safe in member string encoded_text_
void HuffmanCompress::encodeText() {
    // convert text to a string of 0's and 1's, using Huffman encoding
    for (auto& character : text_) {
        // for each character, determine its encoding
        std::string value = encoding_map_[character];
        encoded_text_ += value;
    }
    // add 0's until the length of the encoded text is divisibly by 8
    while (encoded_text_.size() % 8 != 0) {
        encoded_text_ += '0';
        ++extra_bits_;
    }
}
void HuffmanCompress::printText() const {
    cout << "original text: " << text_ << endl;
}

void HuffmanCompress::printEncodedText() const {
    cout << "encoded text: " << encoded_text_ << endl;
}

// get the encoding for the text by using private methods
void HuffmanCompress::getEncoding(const std::string& file_name) {
    HuffmanCompress::countChars(file_name);
    HuffmanCompress::makeEncodeTree();
    HuffmanCompress::makeEncodeDecodeMaps();
    HuffmanCompress::encodeText();
}

// Encode the text using our dictionary and save it to a binary file
void HuffmanCompress::safeEncodedText(const char* compressed_file_name) const {
    std::queue<char> characters;
    // reserve memory for the encoded text
    size_t size_file = encoded_text_.size() / 8;
    unsigned char * encoded_text_as_bytes = new unsigned char [size_file];
    // keep track of the index
    size_t ctr = 0;
    for (auto& bit : encoded_text_) {
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
            unsigned char byte = HuffmanCompress::convertBitstringToChar(str_byte);
            encoded_text_as_bytes[ctr] = byte;
            ++ctr;
        }
    }
    // write the bytes to a binary file
    if (std::FILE* compressed_file = std::fopen(compressed_file_name, "wb")) {
        std::fwrite(encoded_text_as_bytes, 1, size_file, compressed_file);
        std::fclose(compressed_file);
    }
    else
        cout << "an error occured when trying to open the new file" << endl;
    // free the memory
    delete[] encoded_text_as_bytes;
}

// retrieves the data from the compressed file and returns a string with the
// original text
std::string HuffmanCompress::decodeText(const char* compressed_file_name) {
    if (std::FILE* compressed_file = std::fopen(compressed_file_name, "rb")) {
        // seek end to get the size of the file and allocate memory
        std::fseek(compressed_file, 0, SEEK_END);
        size_t size_file = std::ftell(compressed_file);
        unsigned char * encoded_text_as_bytes = new unsigned char [size_file];
        // seek to start and read from file
        std::fseek(compressed_file, 0, SEEK_SET);
        std::fread(encoded_text_as_bytes, 1, size_file, compressed_file);
        std::fclose(compressed_file);
        // convert data to a string
        std::string encoded_text = "";
        for (size_t i = 0; i != size_file; i++)
            encoded_text +=
                HuffmanCompress::convertCharToBitstring(encoded_text_as_bytes[i]);
        delete[] encoded_text_as_bytes;
        // convert bitstring to text, using decoding_map_
        text_ = "";
        std::string word_or_sign;
        size_t i = 0;
        while (i != encoded_text.size() - extra_bits_) {
            if (decoding_map_.find(word_or_sign) == decoding_map_.end()) {
                word_or_sign += encoded_text[i];
                i++;
            }
            else {
                text_ += decoding_map_[word_or_sign];
                word_or_sign = "";
            }
        }
        return text_;
    }
    else
        return std::string("couldn't open compressed file");
}


}   // end namespace adt
