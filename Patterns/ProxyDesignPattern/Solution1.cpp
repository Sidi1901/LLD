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


/* 
Here are the real reasons the pattern exists:

1. You don't own the real class
RealImage might come from a third-party library or a legacy codebase. You can't modify its constructor — it always loads eagerly. The proxy wraps it without touching it.

2. Single Responsibility
RealImage's job is to display an image, not to decide when to load it. Mixing lazy-loading logic into it couples two concerns. The proxy takes on that concern separately.

3. Access control / security proxy
The proxy can add permission checks, logging, or rate-limiting around the real object — none of which belong in RealImage itself.


void display() override {
    if (!userIsAuthorized()) throw runtime_error("Access denied");
    if (!realImage) realImage = new RealImage(filename);
    realImage->display();
}
4. Remote proxy
RealImage might live on a remote server. You can't put network call logic inside the real object — the proxy handles the transport layer transparently.

Bottom line: If you own the class and lazy loading is the only concern, your version is simpler and fine. The proxy pattern earns its complexity when you can't modify the real class, or when you need to layer multiple behaviors (auth + caching + logging) without polluting the real object.
*/
