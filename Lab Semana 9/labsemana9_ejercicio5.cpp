#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

class BinaryTree{
    public:
        BinaryTree();
        Node** getRoot();
        Node* createNode(int data);
        void addNode(Node** current, Node* newNode);
        void findNode(Node** current, int data);
        void printTree(Node** current);
    private:
        Node* root;
};

BinaryTree::BinaryTree(){
    root = nullptr;
}

Node** BinaryTree::getRoot(){
    return &root;
}

Node* BinaryTree::createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void BinaryTree::addNode(Node** current, Node* newNode){
    if (*current == nullptr) *current = newNode;
    else{
        Node* aux = *current;
        if (newNode->data <= aux->data) addNode(&aux->left, newNode);
        else addNode(&aux->right, newNode);
    }
}

void BinaryTree::findNode(Node** current, int data){
    Node* aux = *current;
    if (aux == nullptr) cout << "\nElemento -" << data << "- no encontrado.";
    else if (data == aux->data) cout << "\nNodo " << data << " encontrado.";
    else if (data <= aux->data) findNode(&aux->left, data);
    else findNode(&aux->right, data);
}

void BinaryTree::printTree(Node** current){
    if (*current == nullptr) return;
    Node* aux = *current;
    printTree(&aux->left);
    cout << aux->data << " - ";
    printTree(&aux->right);
}

int main(){
    BinaryTree tree;
    
    cout << endl;
    tree.addNode(tree.getRoot(), tree.createNode(5));
    tree.addNode(tree.getRoot(), tree.createNode(43));
    tree.addNode(tree.getRoot(), tree.createNode(87));
    tree.addNode(tree.getRoot(), tree.createNode(3));
    tree.addNode(tree.getRoot(), tree.createNode(92));
    tree.addNode(tree.getRoot(), tree.createNode(1));
    tree.addNode(tree.getRoot(), tree.createNode(2));
    tree.printTree(tree.getRoot());
    
    cout << endl;
    tree.findNode(tree.getRoot(), 3);
    tree.findNode(tree.getRoot(), 100);
    tree.findNode(tree.getRoot(), 92);
    tree.findNode(tree.getRoot(), 7);
    tree.findNode(tree.getRoot(), 87);
}