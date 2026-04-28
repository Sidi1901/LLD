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
    virtual Shape *createShape() = 0; // Pure virtual function to be implemented by concrete factories
    void drawShape()
    {
        Shape *shape = createShape(); // Create a shape using the factory method
        shape->draw();                // Draw the shape
        delete shape;                 // Clean up memory
    }
};

class CircleFactory : public ShapeFactory
{
public:
    Shape *createShape() override
    {
        return new Circle();
    }
};

class SquareFactory : public ShapeFactory
{
public:
    Shape *createShape() override
    {
        return new Square();
    }
};

class TriangleFactory : public ShapeFactory
{
public:
    Shape *createShape() override
    {
        return new Triangle();
    }
};

int main()
{
    ShapeFactory *factory1 = new CircleFactory();
    Shape *s1 = factory1->createShape();
    s1->draw();

    ShapeFactory *factory2 = new SquareFactory();
    factory2->drawShape();

    ShapeFactory *factory3 = new TriangleFactory();
    factory3->drawShape();
}