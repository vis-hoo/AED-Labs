#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

class LinkedList{
    public:
        LinkedList();
        void addNode(int data);
        Node* findNode(int data);
        void deleteNode(int data);
        void printList();
    private:
        Node* first;
};

LinkedList::LinkedList(){
    first = nullptr;
}

void LinkedList::addNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (first == nullptr) first = newNode;
    else{
        Node* current = first;
        while(current->next != nullptr) current = current->next;
        current->next = newNode;
    }
}

Node* LinkedList::findNode(int data){
    if (first == nullptr) cout << "\nLista vacia.\n";
    else{
        Node* current = first;
        while(current->next != nullptr && current->data != data) current = current->next;
        if (current->data == data){
            cout << "\nNodo " << data << " encontrado.";
            return current;
        }
        else cout << "\nElemento -" << data << "- no encontrado.";
    }
    return nullptr;
}

void LinkedList::deleteNode(int data){
    Node* toBeDeleted = findNode(data);
    if (toBeDeleted == first) free(toBeDeleted);
    else if (toBeDeleted != nullptr){
        Node* aux = first;
        while (aux->next != toBeDeleted) aux = aux->next;
        aux->next = toBeDeleted->next;
        toBeDeleted->next = nullptr;
        free(toBeDeleted);
        cout << "\nNodo " << data << " eliminado.";
    }
}

void LinkedList::printList(){
    if (first == nullptr) cout << "\nLista vacia.\n";
    else{
        Node* current = first;
        while(current != nullptr){
            cout << "\nNodo: " << current->data << ".";
            current = current->next;
        }
    }
}

int main(){
    LinkedList list;

    list.addNode(5);
    list.addNode(9);
    list.addNode(46);
    list.addNode(1111);
    list.addNode(3);
    list.addNode(8);
    list.printList();

    cout << endl;
    list.findNode(46);
    list.findNode(2);
    list.findNode(175);
    list.findNode(1111);

    cout << endl;
    list.deleteNode(9);
    list.deleteNode(1);
    list.deleteNode(1111);
    list.deleteNode(77);
    cout << endl;
    list.printList();
}