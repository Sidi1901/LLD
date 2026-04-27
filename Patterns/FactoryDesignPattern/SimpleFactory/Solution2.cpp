#include <iostream>
#include <string>
using namespace std;

class Shape
{
public:
    virtual void draw() = 0; // Pure virtual function to be implemented by concrete shape types
};

class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a circle\n";
    }
};

class Square : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a square\n";
    }
};

class Triangle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a triangle\n";
    }
};

class ShapeFactory
{
public:
    // static means we can call this method without creating an instance of ShapeFactory. It belongs to the class, not to any object.
    static Shape *createShape(const string &type)
    {
        if (type == "circle")
        {
            return new Circle();
        }
        else if (type == "square")
        {
            return new Square();
        }
        else if (type == "triangle")
        {
            return new Triangle();
        }
        return nullptr;
    }
};

int main()
{
    Shape *s1 = ShapeFactory::createShape("circle");
    Shape *s2 = ShapeFactory::createShape("square");
    Shape *s3 = ShapeFactory::createShape("triangle");

    s1->draw();
    s2->draw();
    s3->draw();

    delete s1;
    delete s2;
    delete s3;
    return 0;
}
