#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class MatrixControl{
    public:
        MatrixControl(int vertices);
        void addEdge(int src, int dest);
        void printMatrix();
        bool hasEdge(int src, int dest);
        bool findPath(int src, int dest, vector<bool> visited, vector<int> path);
        void removeEdge(int src, int dest);
        void deleteVertex(int vertex);
    private:
        int max;
        vector<vector<int>> *graphMatrix;
};

void intToChar(int i);

int main(){
    MatrixControl matrix(8);
    matrix.addEdge(0, 1);
    matrix.addEdge(0, 2);
    matrix.addEdge(1, 3);
    matrix.addEdge(1, 4);
    matrix.addEdge(1, 5);
    matrix.addEdge(2, 3);
    matrix.addEdge(2, 5);
    matrix.addEdge(2, 6);
    matrix.addEdge(3, 4);
    matrix.addEdge(4, 5);
    matrix.addEdge(4, 7);
    matrix.addEdge(5, 6);
    matrix.addEdge(5, 7);
    matrix.addEdge(6, 7);

    matrix.printMatrix();

    matrix.hasEdge(5, 1);
    matrix.hasEdge(2, 4);
    matrix.hasEdge(0, 3);
    matrix.hasEdge(7, 4);
    matrix.hasEdge(3, 5);
    matrix.hasEdge(6, 2);
    cout << endl;

    vector<bool> visited(8, false);
    vector<int> path;
    matrix.findPath(0, 7, visited, path);
    matrix.findPath(3, 5, visited, path);
    matrix.findPath(4, 2, visited, path);
    matrix.findPath(2, 4, visited, path);

    //El vértice A solo puede ser alcanzado desde sí mismo.
    //Existe un ciclo entre B - E - D.
    matrix.removeEdge(1, 0);
    matrix.removeEdge(1, 3);
    matrix.removeEdge(2, 0);
    matrix.removeEdge(2, 3);
    matrix.removeEdge(2, 6);
    matrix.removeEdge(3, 4);
    matrix.removeEdge(4, 1);
    matrix.removeEdge(4, 5);
    matrix.removeEdge(5, 1);
    matrix.removeEdge(5, 2);
    matrix.removeEdge(5, 6);
    matrix.removeEdge(6, 7);
    matrix.removeEdge(7, 4);
    matrix.removeEdge(7, 5);
    matrix.printMatrix();

    matrix.deleteVertex(7);
    matrix.deleteVertex(0);
    matrix.removeEdge(0, 4);
    matrix.removeEdge(2, 1);
    matrix.removeEdge(4, 3);
    matrix.printMatrix();

    return 0;
}

MatrixControl::MatrixControl(int vertices){
    max = vertices;
    graphMatrix = new vector<vector<int>>(vertices, vector<int>(vertices, 0));
}

void MatrixControl::addEdge(int src, int dest){
    vector<vector<int>> &m = *graphMatrix;
    m[src][dest] = 1;
    m[dest][src] = 1;
}

void MatrixControl::printMatrix(){
    vector<vector<int>> &m = *graphMatrix;
    cout << "\n\nMatriz\n";
    int i = 0;
    for(const auto& row : m){
        for(int value : row){
            if(value == 0) cout << "- ";
            else cout << "1 ";
        }
        cout << "\n";
        i++;
    }
}

bool MatrixControl::hasEdge(int src, int dest){
    vector<vector<int>> &m = *graphMatrix;
    if(m[src][dest] == 1){
        cout << "\n";
        intToChar(src);
        cout << "y ";
        intToChar(dest);
        cout << "si son adyacentes.";
        return true;
    }
    else{
        cout << "\n";
        intToChar(src);
        cout << "y ";
        intToChar(dest);
        cout << "no son adyacentes.";
        return false;
    }
}

bool MatrixControl::findPath(int src, int dest, vector<bool> visited, vector<int> path){
    vector<vector<int>> &m = *graphMatrix;
    visited[src] = true;
    path.push_back(src);
    if(src == dest){
        cout << "\n";
        for(int i : path) intToChar(i);
        return true;
    }
    for(int i = 0; i < max; i++){
        if (!visited[i] && m[src][i] == 1){
            if(findPath(i, dest, visited, path)) return true;
        }
    }
    return false;
}

void MatrixControl::removeEdge(int src, int dest){
    vector<vector<int>> &m = *graphMatrix;
    m[src][dest] = 0;
}

void MatrixControl::deleteVertex(int vertex){
    vector<vector<int>> &m = *graphMatrix;
    for(int i = 0; i < max; i++) m[i].erase(m[i].begin() + vertex);
    m.erase(m.begin() + vertex);
}

void intToChar(int i){
    if (i == 0) cout << "A ";
    else if (i == 1) cout << "B ";
    else if (i == 2) cout << "C ";
    else if (i == 3) cout << "D ";
    else if (i == 4) cout << "E ";
    else if (i == 5) cout << "F ";
    else if (i == 6) cout << "G ";
    else if (i == 7) cout << "H ";
    else if (i == 8) cout << "I ";
}