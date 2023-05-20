#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

class BinaryTree{
    public:
        BinaryTree();
        Node* getRoot();
        void insertNode(int data);
        void printPreOrder(Node* current);
        void printInOrder(Node* current);
        void printPostOrder(Node* current);
        bool depthSearch(Node* current, int data);
        bool breadthSearch(int data);
    private:
        Node* root;
        Node* createNode(int data);
};

int main(){
    BinaryTree tree;
    tree.insertNode(1);
    tree.insertNode(2);
    tree.insertNode(3);
    tree.insertNode(4);
    tree.insertNode(5);
    tree.insertNode(6);
    tree.insertNode(7);
    cout << "\n Pre-Order: ";
    tree.printPreOrder(tree.getRoot());
    cout << "\n In-Order: ";
    tree.printInOrder(tree.getRoot());
    cout << "\n Post-Order: ";
    tree.printPostOrder(tree.getRoot());
    cout << endl;

    int array[] = {21, 18, 6, 9, 10, 7, 19, 15, 12, 5};
    BinaryTree tree2;
    for(int i = 0; i < (sizeof(array) / sizeof(int)); i++) tree2.insertNode(array[i]);
    cout << "\n Pre-Order: ";
    tree2.printPreOrder(tree2.getRoot());
    cout << "\n In-Order: ";
    tree2.printInOrder(tree2.getRoot());
    cout << "\n Post-Order: ";
    tree2.printPostOrder(tree2.getRoot());
    cout << endl;

    cout << "\n\tBusqueda por profundidad - Arbol 1:";
    if (tree.depthSearch(tree.getRoot(), 5)) cout << "\n Nodo 5 encontrado.";
    else cout << "\n Nodo -5- no encontrado.";
    if (tree.depthSearch(tree.getRoot(), 11)) cout << "\n Nodo 11 encontrado.";
    else cout << "\n Nodo -11- no encontrado.";
    if (tree.depthSearch(tree.getRoot(), 3)) cout << "\n Nodo 3 encontrado.";
    else cout << "\n Nodo -3- no encontrado.";
    cout << endl;

    cout << "\n\tBusqueda por amplitud - Arbol 1:";
    if (tree.breadthSearch(5)) cout << "\n Nodo 5 encontrado.";
    else cout << "\n Nodo -5- no encontrado.";
    if (tree.breadthSearch(11)) cout << "\n Nodo 11 encontrado.";
    else cout << "\n Nodo -11- no encontrado.";
    if (tree.breadthSearch(3)) cout << "\n Nodo 3 encontrado.";
    else cout << "\n Nodo -3- no encontrado.";
    cout << endl;
    
    cout << "\n\tBusqueda por profundidad - Arbol 2:";
    if (tree2.depthSearch(tree2.getRoot(), 7)) cout << "\n Nodo 7 encontrado.";
    else cout << "\n Nodo -7- no encontrado.";
    if (tree2.depthSearch(tree2.getRoot(), 8)) cout << "\n Nodo 8 encontrado.";
    else cout << "\n Nodo -8- no encontrado.";
    if (tree2.depthSearch(tree2.getRoot(), 12)) cout << "\n Nodo 12 encontrado.";
    else cout << "\n Nodo -12- no encontrado.";
    cout << endl;

    cout << "\n\tBusqueda por amplitud - Arbol 2:";
    if (tree2.breadthSearch(7)) cout << "\n Nodo 7 encontrado.";
    else cout << "\n Nodo -7- no encontrado.";
    if (tree2.breadthSearch(8)) cout << "\n Nodo 8 encontrado.";
    else cout << "\n Nodo -8- no encontrado.";
    if (tree2.breadthSearch(12)) cout << "\n Nodo 12 encontrado.";
    else cout << "\n Nodo -12- no encontrado.";
    cout << endl;

    return 0;
}

BinaryTree::BinaryTree(){ root = nullptr; }

Node* BinaryTree::getRoot(){ return root; }

Node* BinaryTree::createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void BinaryTree::insertNode(int data){
    if(root == nullptr) root = createNode(data);
    else{
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* aux = q.front();
            q.pop();
            if(aux->left != nullptr) q.push(aux->left);
            else{
                aux->left = createNode(data);
                return;
            }
            if(aux->right != nullptr) q.push(aux->right);
            else{
                aux->right = createNode(data);
                return;
            }
        }
    }
}

void BinaryTree::printPreOrder(Node* current){
    if (current == nullptr) return;
    cout << current->data << " - ";
    printPreOrder(current->left);
    printPreOrder(current->right);
}

void BinaryTree::printInOrder(Node* current){
    if (current == nullptr) return;
    printInOrder(current->left);
    cout << current->data << " - ";
    printInOrder(current->right);
}

void BinaryTree::printPostOrder(Node* current){
    if (current == nullptr) return;
    printPostOrder(current->left);
    printPostOrder(current->right);
    cout << current->data << " - ";
}

bool BinaryTree::depthSearch(Node* current, int data){
    if (current == nullptr) return false;
    else if (data == current->data) return true;
    else if (depthSearch(current->left, data)) return true;
    else return depthSearch(current->right, data);
}

bool BinaryTree::breadthSearch(int data){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* aux = q.front();
        q.pop();
        if(aux->data == data) return true;
        else{
            if(aux->left != nullptr) q.push(aux->left);
            if(aux->right != nullptr) q.push(aux->right);
        }
    }
    return false;
}
