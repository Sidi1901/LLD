#include <iostream>
#include <string>
using namespace std;

// Virtual Proxy — defer expensive object creation until it is actually needed.
// Example: an image viewer that only loads the file from disk on first display.

class Image
{
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

class RealImage : public Image
{
    string filename;

    void loadFromDisk()
    {
        cout << "Loading image from disk: " << filename << "\n"; // expensive operation
    }

public:
    RealImage(const string &file) : filename(file)
    {
        loadFromDisk(); // load immediately when constructed
    }

    void display() override
    {
        cout << "Displaying image: " << filename << "\n";
    }
};

class ProxyImage : public Image
{
    string filename;
    RealImage *realImage = nullptr; // not created until first use

public:
    ProxyImage(const string &file) : filename(file) {}

    void display() override
    {
        if (!realImage)
            realImage = new RealImage(filename); // lazy initialization
        realImage->display();
    }

    ~ProxyImage()
    {
        delete realImage;
    }
};

int main()
{
    Image *img = new ProxyImage("photo.jpg");

    cout << "Image object created — no disk load yet.\n";

    img->display(); // disk load happens here, on first call
    img->display(); // uses already-loaded RealImage — no second load

    delete img;
    return 0;
}
