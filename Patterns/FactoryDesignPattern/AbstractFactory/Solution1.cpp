#include <iostream>
#include <string>
using namespace std;

class Button
{
public:
    virtual void click() = 0;  // Pure virtual function to be implemented by concrete buttons
    virtual void render() = 0; // Pure virtual function to be implemented by concrete buttons
};

class CheckBox
{
public:
    virtual void toggle() = 0; // Pure virtual function to be implemented by concrete checkboxes
    virtual void render() = 0; // Pure virtual function to be implemented by concrete checkboxes
};

class MacButton : public Button
{
public:
    void click() override
    {
        cout << "Mac Button clicked\n";
    }
    void render() override
    {
        cout << "Rendering Mac Button\n";
    }
};

class MacCheckBox : public CheckBox
{
public:
    void toggle() override
    {
        cout << "Mac CheckBox toggled\n";
    }
    void render() override
    {
        cout << "Rendering Mac CheckBox\n";
    }
};

class WindowsButton : public Button
{
public:
    void click() override
    {
        cout << "Windows Button clicked\n";
    }
    void render() override
    {
        cout << "Rendering Windows Button\n";
    }
};

class WindowsCheckBox : public CheckBox
{
public:
    void toggle() override
    {
        cout << "Windows CheckBox toggled\n";
    }
    void render() override
    {
        cout << "Rendering Windows CheckBox\n";
    }
};

// The Abstract Factory interface declares methods for creating each type of product.
class GUIFactory
{
public:
    virtual Button *createButton() = 0;     // Pure virtual function to create a Button
    virtual CheckBox *createCheckBox() = 0; // Pure virtual function to create a CheckBox
};

class MacFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new MacButton();
    }
    CheckBox *createCheckBox() override
    {
        return new MacCheckBox();
    }
};

class WindowsFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new WindowsButton();
    }
    CheckBox *createCheckBox() override
    {
        return new WindowsCheckBox();
    }
};

int main()
{
    GUIFactory *f1 = new MacFactory();
    Button *b1 = f1->createButton();
    CheckBox *c1 = f1->createCheckBox();
    b1->render();
    c1->render();

    GUIFactory *f2 = new WindowsFactory();
    Button *b2 = f2->createButton();
    CheckBox *c2 = f2->createCheckBox();
    b2->render();
    c2->render();

    delete b1;
    delete c1;
    delete f1;
    delete b2;
    delete c2;
    delete f2;
}