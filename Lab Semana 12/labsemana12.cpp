#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

struct Vertex{
    string data;
};

class GraphControl{
    public:
        GraphControl(int max);
        void addVertex(string data);
        void addEdge(string src, string dest, int weight);
        int findIndexByVertex(string data);
        bool findPath(string src, string dest, vector<bool> visited, vector<string> path);
        void dijkstraPath(int limit, string src);
        void floydWarshallPath(int limit);
        void printMatrix();
    private:
        int max;
        vector<Vertex*> *verticesList;
        vector<vector<int>> *adjacencyMatrix;
        int minDistance(int limit, int dist[], bool sptSet[]);
        void printDijkstraSolution(int limit, string src, int dist[]);
        void printFloydWarshallSolution(int limit, int dist[9][9]);
};

int main(){
    GraphControl graph(10);

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");
    graph.addVertex("G");
    graph.addVertex("H");
    graph.addVertex("I");
    graph.addVertex("J");

    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 1);
    graph.addEdge("B", "D", 1);
    graph.addEdge("B", "E", 1);
    graph.addEdge("C", "F", 1);
    graph.addEdge("C", "G", 1);
    graph.addEdge("D", "E", 1);
    graph.addEdge("D", "F", 1);
    graph.addEdge("E", "F", 1);
    graph.addEdge("E", "H", 1);
    graph.addEdge("F", "G", 1);
    graph.addEdge("F", "H", 1);
    graph.addEdge("G", "I", 1);
    graph.addEdge("G", "J", 1);
    graph.addEdge("H", "J", 1);
    graph.addEdge("J", "I", 1);

    graph.printMatrix();

    vector<bool> visited(10, false);
    vector<string> path;
    graph.findPath("A", "F", visited, path);
    graph.findPath("G", "B", visited, path);
    graph.findPath("H", "J", visited, path);

    GraphControl graph2(9);

    graph2.addVertex("A");
    graph2.addVertex("B");
    graph2.addVertex("C");
    graph2.addVertex("D");
    graph2.addVertex("E");
    graph2.addVertex("F");
    graph2.addVertex("G");
    graph2.addVertex("H");
    graph2.addVertex("I");

    graph2.addEdge("A", "B", 4);
    graph2.addEdge("A", "H", 8);
    graph2.addEdge("B", "C", 8);
    graph2.addEdge("B", "H", 11);
    graph2.addEdge("C", "D", 7);
    graph2.addEdge("C", "F", 4);
    graph2.addEdge("C", "I", 2);
    graph2.addEdge("D", "E", 9);
    graph2.addEdge("D", "F", 14);
    graph2.addEdge("E", "F", 10);
    graph2.addEdge("F", "G", 2);
    graph2.addEdge("G", "H", 1);
    graph2.addEdge("G", "I", 6);
    graph2.addEdge("H", "I", 7);

    graph2.printMatrix();

    graph2.dijkstraPath(9, "C");
    graph2.dijkstraPath(9, "D");
    graph2.dijkstraPath(9, "I");

    graph2.floydWarshallPath(9);
    
    return 0;
}

GraphControl::GraphControl(int max){
    verticesList = new vector<Vertex*>;
    adjacencyMatrix = new vector<vector<int>>(max, vector<int>(max, 0));
}

void GraphControl::addVertex(string data){
    Vertex* newVertex = new Vertex();
    newVertex->data = data;
    verticesList->push_back(newVertex);
}

void GraphControl::addEdge(string src, string dest, int weight){
    int i = findIndexByVertex(src), j = findIndexByVertex(dest);
    vector<vector<int>> &matrix = *adjacencyMatrix;
    if(i != -1 && j != -1){
        matrix[i][j] = weight;
        matrix[j][i] = weight;
    }
}

int GraphControl::findIndexByVertex(string data){
    vector<Vertex*> &list = *verticesList;
    for(int i = 0; i < list.size(); i++)
        if(list[i]->data == data) return i;
    return -1;
}

bool GraphControl::findPath(string src, string dest, vector<bool> visited, vector<string> path){
    vector<Vertex*> &list = *verticesList;
    vector<vector<int>> &matrix = *adjacencyMatrix;
    visited[findIndexByVertex(src)] = true;
    path.push_back(src);
    if(src == dest){
        cout << "\n";
        for(int i = 0; i < path.size(); i++) cout << path[i];
        return true;
    }
    for(int i = 0; i < 10; i++)
        if (!visited[i] && matrix[findIndexByVertex(src)][i] == 1)
            if(findPath(list[i]->data, dest, visited, path)) return true;
    return false;
}

void GraphControl::dijkstraPath(int limit, string src){
    int dist[limit];
    bool sptSet[limit];
    vector<vector<int>> &matrix = *adjacencyMatrix;

    for(int i = 0; i < limit; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[findIndexByVertex(src)] = 0;

    for(int aux = 0; aux < limit - 1; aux++){
        int i = minDistance(limit, dist, sptSet);
        sptSet[i] = true;

        for(int j = 0; j < limit; j++)
            if(!sptSet[j] && matrix[i][j] && dist[i] != INT_MAX && dist[i] + matrix[i][j] < dist[j])
                dist[j] = dist[i] + matrix[i][j];
    }

    printDijkstraSolution(limit, src, dist);
}

int GraphControl::minDistance(int limit, int dist[], bool sptSet[]){
    int min = INT_MAX, min_index;
    for(int i = 0; i < limit; i++)
        if(sptSet[i] == false && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    return min_index;
}

void GraphControl::printDijkstraSolution(int limit, string src, int dist[]){
    vector<Vertex*> &list = *verticesList;
    cout << "\nDistancia desde " << src << " hasta:" << endl;
    for (int i = 0; i < limit; i++)
        cout << "  " << list[i]->data << " -> " << dist[i] << endl;
}

void GraphControl::floydWarshallPath(int limit){
    vector<vector<int>> &matrix = *adjacencyMatrix;
    int dist[9][9];
    int i, j, k;
    for (k = 0; k < limit; k++)
        for (i = 0; i < limit; i++)
            for (j = 0; j < limit; j++)
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j]) && (matrix[k][j] != 0 && matrix[i][k] != 0))
                    dist[i][j] = matrix[i][k] + matrix[k][j];
    
    cout << endl;
    printFloydWarshallSolution(limit, dist);
}

void GraphControl::printFloydWarshallSolution(int limit, int dist[9][9]){
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < limit; j++) {
            if (dist[i][j] == 0 || dist[i][j] > 100 || dist[i][j] < 0) cout << "INF  ";
            else{
                cout << dist[i][j];
                if(dist[i][j] >= 10) cout << "   ";
                else cout << "    ";
            }
        }
        cout << endl;
    }
}

void GraphControl::printMatrix(){
    vector<vector<int>> &matrix = *adjacencyMatrix;
    cout << "\n\nMatriz\n";
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] == 0) cout << "-  ";
            else{
                cout << matrix[i][j];
                if(matrix[i][j] >= 10) cout << " ";
                else cout << "  ";
            }
        }
        cout << "\n";
    }
}