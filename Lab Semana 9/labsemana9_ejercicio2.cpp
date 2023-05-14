#include <iostream>
using namespace std;

class Point{
    public:
        Point(int xCoord, int yCoord);
        int getX();
        int getY();

    private:
        int x;
        int y;
};

Point::Point(int xCoord, int yCoord){
    x = xCoord;
    y = yCoord;
}

int Point::getX(){ return x; }

int Point::getY(){ return y; }

int main(){
    Point p1(3, 8);
    Point p2(6, 2);
    Point p3(5, 7);

    cout << "\nCoordenadas p1. X: " << p1.getX() << " - Y: " << p1.getY() << "." << endl;
    cout << "Coordenadas p2. X: " << p2.getX() << " - Y: " << p2.getY() << "." << endl;
    cout << "Coordenadas p3. X: " << p3.getX() << " - Y: " << p3.getY() << "." << endl;
}