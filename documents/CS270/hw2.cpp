#include<iostream>
#include <sstream>
using namespace std;

class AVLTree {
    int data;
    struct AVLTree* left;
    struct AVLTree* right;
    int H;
    int getH(AVLTree * node);
    AVLTree* rightRotate(AVLTree * temp);
    AVLTree* leftRotate(AVLTree * temp);
    int getBalance(AVLTree * ND);

    public:
        AVLTree(int value);
        AVLTree* insert(AVLTree *node, int value);
        AVLTree* deleteN(AVLTree *R, int value);
        void PRE(AVLTree *R);
        void POST(AVLTree *R);
        void IN(AVLTree *R);
        void setH(int value);
        AVLTree* minValue();
}; 

AVLTree::AVLTree(int value){
    data = value;
    left = NULL;
    right = NULL;
    H = 1;
}

int AVLTree::getH(AVLTree * node) {
    return node == NULL ? 0 : node -> H;
} 

void AVLTree::setH(int value) {
    H = value + 1;
} 

AVLTree * AVLTree::rightRotate(AVLTree * temp) {
    AVLTree * newR = temp -> left;
    AVLTree * T = newR -> right;
    newR -> right = temp;
    temp -> left = T;
    temp -> setH(max(getH(temp -> left), getH(temp -> right)));
    newR -> setH(max(getH(newR -> left), getH(newR -> right)));
    return newR;
} 


AVLTree * AVLTree::leftRotate(AVLTree * temp) {
    AVLTree * newR = temp -> right;
    AVLTree * T = newR -> left;
    newR -> left = temp;
    temp -> right = T;
    temp -> setH(max(getH(temp -> left), getH(temp -> right)));
    newR -> setH(max(getH(newR -> left), getH(newR -> right)));
    
    return newR;
} 


int AVLTree::getBalance(AVLTree * NodeBalance) {
    return NodeBalance == NULL ? 0:getH(NodeBalance -> left) - getH(NodeBalance -> right);
} 


AVLTree * AVLTree::insert(AVLTree * node, int value) {
    if (node == NULL){
        AVLTree * newNode = new AVLTree(value);
        return newNode;
    }
    
    if (value < node -> data) {
        node -> left = insert(node -> left, value);
    }
    
    else if (value > node -> data) {
        node -> right = insert(node -> right, value);
    }
    else {
        return node;
    }
    
    node -> setH(max(getH(node -> left), getH(node -> right)));
    int balance = getBalance(node);
    if (balance > 1 && value < node -> left -> data)
        return rightRotate(node);
    
    if (balance < -1 && value > node -> right -> data)
        return leftRotate(node);
    
    if (balance > 1 && value > node -> left -> data) {
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    } 
    
    if (balance < -1 && value < node -> right -> data) {
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    } 
    
    return node;
} 

AVLTree * AVLTree::minValue() {
    AVLTree * current = this;
    while (current -> left != NULL) {
        current = current -> left;
    }
    
    return current;
} 



AVLTree * AVLTree::deleteN(AVLTree * R, int value) {
    if (R == NULL)
        return R;
    
    if (value < R -> data){
        R -> left = deleteN(R -> left, value);
    }
    else if (value > R -> data){
        R -> right = deleteN(R -> right, value);
    }
    else {
        
        if ((R -> left == NULL) || (R -> right == NULL)) {
            AVLTree * temp = R -> left ? R -> left : R -> right;
            
            if (temp == NULL) {
              temp = R;
              R = NULL;
            } 
            
            else 
              *R = * temp;
            delete(temp);
        } 
        else {
            AVLTree * temp = R -> right -> minValue();
            R -> data = temp -> data;
            R -> right = deleteN(R -> right, temp -> data);
        } 
    } 
    return R;
} 

void AVLTree::PRE(AVLTree * R) {
    if (R != NULL) {
        cout << R -> data << " ";
        PRE(R -> left);
        PRE(R -> right);
    } 
} 


void AVLTree::POST(AVLTree * R) {
    if (R != NULL) {
        POST(R -> left);
        POST(R -> right);
        cout << R -> data << " ";
    } 
} 


void AVLTree::IN(AVLTree * R) {
    if (R != NULL) {
        IN(R -> left);
        cout << R -> data << " ";
        IN(R -> right);
    } 
} 


int main() {
    AVLTree * R = NULL;
    int number;
    string input;
    getline(cin, input);
    
    for (unsigned int x = 0; x < input.length(); x++) {
        if (input.at(x) == 'A' || input.at(x) == 'a') {
            if( (input.at(x + 2) - '0') == 0 and (input.at(x + 3) - '0') == 0) 
            {number = 100;}
            else
            {
                if(input.at(x+3)==' ')
                {
                number = input.at(x + 2) - '0';
                number = (input.at(x + 1) - '0')*10 + number;
                }
                else
                {number = input.at(++x) - '0';
                }
            }
            
            R = R -> insert(R, number);
        } 
        
        else if (input.at(x) == 'D' || input.at(x) == 'd') {
            if( (input.at(x + 2) - '0') == 0 and (input.at(x + 3) - '0') == 0) 
            {number = 100;}
            else
            {
                if(input.at(x+3)==' ')
                {
                number = input.at(x + 2) - '0';
                number = (input.at(x + 1) - '0')*10 + number;
                }
                else
                {number = input.at(++x) - '0';
                }
            }
            R = R -> deleteN(R, number);
        } 
        
        else if (input.at(x) == 'I' || input.at(x) == 'i') {
            if (R == NULL)
                cout << "\n EMPTY";
            R -> IN(R);
        } 
        
        else if (input.at(x) == 'P' || input.at(x) == 'p') {
            if (input.at(x + 1) == 'R' || input.at(x) == 'r') {
                if (R == NULL)
                    cout << "\n EMPTY";
                R -> PRE(R);
            } 
            
            else if (input.at(x + 1) == 'O' || input.at(x) == 'o') {
                if (R == NULL)
                    cout << "EMPTY";
                R -> POST(R);
            } 
        } 
    } 
    return 0;
} 






