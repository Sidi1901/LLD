#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------------
// ── Example 1 : Constructor Overloading ──────────────────────────────────────
//-------------------------------------------------------------------------------

// Use case: Constructors with optional context (dependency injection)
class Logger {
    string destination;
    ofstream fileStream;

public:
    Logger() : destination("console") {}

    Logger(string file) : destination(file) {
        fileStream.open(file, ios::app);
    }

    void log(const string& msg) {
        if (destination == "console") {
            cout << "[LOG] " << msg << "\n";
        } else {
            if (fileStream.is_open())
                fileStream << "[LOG] " << msg << "\n";
        }
    }

    ~Logger() {
        if (fileStream.is_open()) fileStream.close();
    }
};

//-------------------------------------------------------------------------------
// ── Example 2 : Avoid too many overloads  ──────────────────────────────────────
//-------------------------------------------------------------------------------

//Bad design
void process(int a)              { cout << "process(a=" << a << ")\n"; }
void process(int a, int b)       { cout << "process(a=" << a << ", b=" << b << ")\n"; }
void process(int a, int b, int c){ cout << "process(a=" << a << ", b=" << b << ", c=" << c << ")\n"; }
void process(string s)           { cout << "process(type=" << s << ")\n"; }

//Better design
struct ProcessRequest {
    int a;
    int b = 0;          // optional
    int c = 0;          // optional
    string type;        // optional
};

void process(ProcessRequest req) {
    cout << "process(a=" << req.a
         << ", b=" << req.b
         << ", c=" << req.c
         << ", type=" << (req.type.empty() ? "none" : req.type)
         << ")\n";
}



//-------------------------------------------------------------------------------
// ── main ──────────────────────────────────────────────────────────────────────
//-------------------------------------------------------------------------------

int main() {
    cout << "=== Example 1: Constructor Overloading ===\n";
    Logger consoleLogger;
    consoleLogger.log("Server started");

    Logger fileLogger("app.log");
    fileLogger.log("Writing to file");

    cout << "\n=== Example 2: Avoid too many overloads ===\n";
    cout << "-- Bad design --\n";
    process(1);
    process(1, 2);
    process(1, 2, 3);
    process(string("order"));

    cout << "-- Better design (parameter object) --\n";
    process({.a = 1});
    process({.a = 1, .b = 2});
    process({.a = 1, .b = 2, .c = 3});
    process({.a = 5, .type = "order"});


    return 0;
}
