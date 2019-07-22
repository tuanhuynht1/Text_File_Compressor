#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "HuffmanBase.hpp"
#include <map>
#include <vector>
#include <string>
#include <stack>

class HuffmanTree: public HuffmanTreeBase{
    public:
        //tree methods
        HuffmanTree():  root(nullptr), n(0) {}
        bool empty(){return n == 0;}
        HuffmanNode* getRoot() {return root;}
        int size() {return n;}

        //Huffman code methods
        std::string compress(const std::string inputStr) override;
        std::string serializeTree() const override;
        std::string decompress(const std::string inputCode, const std::string serializedTree) override;
    private:
        //basic tree attributes
        HuffmanNode* root;
        int n;
        std::vector<HuffmanNode*> post_order_positions;
        //utility methods
        int leftOrRightNode(HuffmanNode* node);
        std::string encode(HuffmanNode* node);
        std::string bitToString(int bit);
        void postOrder(HuffmanNode* node, std::vector<HuffmanNode*>& positions);
};

#endif
