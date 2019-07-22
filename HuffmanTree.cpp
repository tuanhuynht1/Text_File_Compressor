#include "HuffmanTree.hpp"
#include "HeapQueue.hpp"
using namespace std;


string HuffmanTree::compress(const string inputStr){
    
    //fill frequency table using a map ADT
    map<char,size_t> freq_table;
    for(int i = 0; i < inputStr.size(); i++){
        //current char
        char c = inputStr[i];    

        //find char in the freq table
        auto iter = freq_table.find(c);

        //if iter is at the end the char is not in table, so we insert the new char 
        if(iter == freq_table.end()){  
            freq_table.insert(pair<char, size_t>(c,1));
        }
        //if char is found in the table, increment its freq
        else{
            iter->second++;
        }
    }

    //fill priority queue
    HeapQueue<HuffmanNode*,HuffmanNode::Compare> Q;
    //iterate throught the freq_table and fill que with HuffmanNode constructed using key value pairs
    for(auto i = freq_table.begin(); i != freq_table.end(); i++){
        HuffmanNode* new_node = new HuffmanNode(i->first,i->second);        
        Q.insert(new_node);
    }

    // have a vector of pointers to all the external nodes for uprooting
    vector<HuffmanNode*> leaves;
    leaves.reserve(freq_table.size());

    //start building the tree by combining nodes until there is only one node that contains all the nodes
    while(Q.size() != 1){
        //grabs the two lowest freq node 
        HuffmanNode* left = Q.min(); Q.removeMin(); //deque
        HuffmanNode* right = Q.min(); Q.removeMin(); //deque

        //save position of all the leaves in a pointer vector
        if(left->isLeaf()) leaves.push_back(left);
        if(right->isLeaf()) leaves.push_back(right);

        //create a placeholder node to hold these 2, and hold their sum
        size_t sum = left->getFrequency() + right->getFrequency();
        HuffmanNode* placeholder = new HuffmanNode('\0',sum, nullptr, left, right);

        //link the children to the parent
        left->parent = placeholder; right->parent = placeholder;
        Q.insert(placeholder);
    }

    //set the root of the tree to be the last node linking all the nodes in the priority queue
    root = Q.min();
    n = (2*leaves.size())-1;
    //sort the tree in pos order
    post_order_positions.clear(); post_order_positions.reserve(n);
    postOrder(root,post_order_positions);

    //iterate through each leaf to generate a huffman code for each char using the encode function
    map<char,string> codes;
    for (int i = 0; i < leaves.size(); i++){
        char character = leaves[i]->getCharacter();
        string code = encode(leaves[i]);
        codes.insert(pair<char, string>(character,code));   //insert into char-code map
    }

    //iterate through the input string again replacing each char with its huffman code 
    string outputStr;
    for(int i = 0; i < inputStr.size(); i++){
        auto iter = codes.find(inputStr[i]);
        outputStr += iter->second;
    }
    return outputStr;
}


string HuffmanTree::serializeTree() const{
    string outputStr;
    //iterate through post ordered list
    for (int i = 0; i < post_order_positions.size(); i++){
        //serialize with L and the char if node is external
        if(post_order_positions[i]->isLeaf()){
            outputStr += "L";
            outputStr += post_order_positions[i]->getCharacter();
        }
        //serialize with B if node branches off
        else{
            outputStr += "B"; 
        }
    }
    return outputStr;
}


string HuffmanTree::decompress(const string inputCode, const string serializedTree){
    //rebuild tree using the serial string and a stack
    stack<HuffmanNode*> S;
    for (int i = 0; i < serializedTree.size(); i++){
        //char for current node
        char c;
        if(serializedTree[i] == 'L'){
            i++; //skip over to actual letter 
            c = serializedTree[i];
            HuffmanNode* new_node = new HuffmanNode(c,0);
            S.push(new_node);
        }
        else if(serializedTree[i] == 'B'){
            //pop the top two nodes from stack
            HuffmanNode* right = S.top(); S.pop();
            HuffmanNode* left = S.top(); S.pop();

            //create a placeholder branching node to link the two nodes
            HuffmanNode* branch = new HuffmanNode('\0',0,nullptr,left,right);

            //link the two child nodes with their parents
            right->parent = branch; left->parent = branch;

            //push the branch back on the stack after linking all the nodes
            S.push(branch);
        }
    }

    //iterate through the inputCode along side the tree until char is found
    HuffmanNode* it = S.top();
    string outputStr;
    for(int i = 0; i < inputCode.size(); i++){
        char c = inputCode[i];
        //if 0, go down left branch
        if (c == '0'){
            it = it->left;
        }
        //if 1, go down right branch
        else if(c == '1'){
            it = it->right;
        }

        //after iteration, chech if iterator is at leaf, if so, reset iter, concat char
        if (it->isLeaf()){
            outputStr += it->getCharacter();
            it = S.top();
        }
    }
    //clear stack
    S.pop();
    return outputStr;
}



int HuffmanTree::leftOrRightNode(HuffmanNode* node){
    HuffmanNode* p = node->parent;
    if(p == nullptr){
        return -1;
    }
    else if (p->left == node){
        return 0;
    }
    else if (p->right == node){
        return 1;
    }
    return -1;
}

string HuffmanTree::encode(HuffmanNode* node){
    int digit = leftOrRightNode(node);
    if(digit == -1){
        return "";
    }
    else{
        return encode(node->parent) + bitToString(digit);
    }
}

string HuffmanTree::bitToString(int bit){
    switch(bit){
        case 1: return "1";
        default: return "0"; 
    }
}

void HuffmanTree::postOrder(HuffmanNode* node, vector<HuffmanNode*>& positions){
    //goes down the left branch of the subtree
    if(node->left != nullptr){
        postOrder(node->left, positions);
    }
    //goes down the right branch of the subtree
    if(node->right != nullptr){
        postOrder(node->right, positions);
    }
    //insert node to the end of the list after visiting both its children
    positions.push_back(node);
}