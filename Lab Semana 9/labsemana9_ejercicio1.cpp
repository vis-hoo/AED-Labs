#include <iostream>
#include <vector>
using namespace std;

class Rectangle{
    public:
        Rectangle(int w, int h);
        int getArea();
        int getWidth();
        int getHeight();

    private:
        int width;
        int height;
};

Rectangle::Rectangle(int w, int h){
    width = w;
    height = h;
}

int Rectangle::getArea(){
    return width * height;
}

int Rectangle::getWidth(){
    return width;
}

int Rectangle::getHeight(){
    return height;
}