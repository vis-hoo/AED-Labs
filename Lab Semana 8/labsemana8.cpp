#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data);
void addNode(Node** root, Node* newNode);
void printTree(Node* root);
bool searchNode(Node* root, int data);
Node* findMinValue(Node* root);
Node* findMaxValue(Node* root);
void deleteNode(Node** root, int data);

int main(){
    Node* root = nullptr;
    addNode(&root, createNode(100));
    addNode(&root, createNode(8));
    addNode(&root, createNode(345));
    addNode(&root, createNode(12));
    addNode(&root, createNode(90));
    addNode(&root, createNode(7));
    addNode(&root, createNode(16));
    addNode(&root, createNode(5));
    printTree(root);

    if (searchNode(root, 12)) cout << "\n12 encontrado" << endl;
    else cout << "\n12 no encontrado" << endl;
    if (searchNode(root, 115)) cout << "115 encontrado" << endl;
    else cout << "115 no encontrado" << endl;
    if (searchNode(root, 345)) cout << "345 encontrado" << endl;
    else cout << "345 no encontrado" << endl;
    if (searchNode(root, 0)) cout << "0 encontrado" << endl;
    else cout << "0 no encontrado" << endl;

    cout << "\nValor minimo ingresado: " << findMinValue(root)->data << endl;
    cout << "Valor maximo ingresado: " << findMaxValue(root)->data << endl;

    deleteNode(&root, 100);
    deleteNode(&root, 16);
    deleteNode(&root, 400);
    deleteNode(&root, 90);
    cout << endl;
    printTree(root);
}

Node* createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void addNode(Node** root, Node* newNode){
    if (*root == nullptr) *root = newNode;
    else {
        Node* current = *root;
        if (newNode->data <= current->data) addNode(&current->left, newNode);
        else addNode(&current->right, newNode);
    }
}

void printTree(Node* root){
    if (root == nullptr) {
        cout << endl;
        return;
    }
    printTree(root->left);
    cout << root->data << " - ";
    printTree(root->right);
}

bool searchNode(Node* root, int data){
    if (root == nullptr) return false;
    else if (data == root->data) return true;
    else if (data <= root->data) return searchNode(root->left, data);
    else return searchNode(root->right, data);
}

Node* findMinValue(Node* root){
    if (root->left == nullptr) return root;
    else return findMinValue(root->left);
}

Node* findMaxValue(Node* root){
    if (root->right == nullptr) return root;
    else return findMaxValue(root->right);
}

void deleteNode(Node** root, int data){
    Node* current = *root;
    if (*root == nullptr) cout << "\nEl nodo " << data << " no existe.";
    else if (data == current->data){
        *root = current->left;
        addNode(root, current->right);
        cout << "\nEl nodo " << current->data << " ha sido eliminado.";
        current->left = nullptr;
        current->right = nullptr;
        free(current);
    }
    else if (data <= current->data) deleteNode(&current->left, data);
    else deleteNode(&current->right, data);
}