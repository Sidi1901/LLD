#include <iostream>
#include <string>
using namespace std;

// 🖨️ Problem Statement: Multi-function Office Machine

// Design a system that models office machines (Printer, Scanner, Fax).

// ❌ ISP Violation — one fat interface forces all classes to implement methods they don't need:
//      A simple Printer is forced to implement scan() and fax() even though it can't do either
//      These empty/throwing overrides are a sign the interface is too broad

// ✅ ISP Fix — split the fat interface into small, focused interfaces:
//      Each class only implements the interfaces that match its actual capabilities

// ─────────────────────────────────────────────
// ❌ BAD: one fat interface — classes forced to implement methods they don't support
// ─────────────────────────────────────────────

class BadMachine
{
public:
    virtual void print(const string &doc) = 0;
    virtual void scan(const string &doc) = 0;
    virtual void fax(const string &doc) = 0;
    virtual ~BadMachine() {}
};

class BadPrinter : public BadMachine
{
public:
    void print(const string &doc) override
    {
        cout << "[Printer] Printing: " << doc << "\n";
    }

    void scan(const string &doc) override
    {
        // ❌ forced to implement — but this machine cannot scan
        throw runtime_error("Printer cannot scan!");
    }

    void fax(const string &doc) override
    {
        // ❌ forced to implement — but this machine cannot fax
        throw runtime_error("Printer cannot fax!");
    }
};

class BadAllInOne : public BadMachine
{
public:
    void print(const string &doc) override { cout << "[AllInOne] Printing: " << doc << "\n"; }
    void scan(const string &doc) override  { cout << "[AllInOne] Scanning: " << doc << "\n"; }
    void fax(const string &doc) override   { cout << "[AllInOne] Faxing:   " << doc << "\n"; }
};

// ─────────────────────────────────────────────
// ✅ GOOD: small focused interfaces — each class implements only what it supports
// ─────────────────────────────────────────────

class IPrinter
{
public:
    virtual void print(const string &doc) = 0;
    virtual ~IPrinter() {}
};

class IScanner
{
public:
    virtual void scan(const string &doc) = 0;
    virtual ~IScanner() {}
};

class IFax
{
public:
    virtual void fax(const string &doc) = 0;
    virtual ~IFax() {}
};

// ✅ SimplePrinter only implements what it can actually do
class SimplePrinter : public IPrinter
{
public:
    void print(const string &doc) override
    {
        cout << "[SimplePrinter] Printing: " << doc << "\n";
    }
};

// ✅ Scanner only implements what it can actually do
class SimpleScanner : public IScanner
{
public:
    void scan(const string &doc) override
    {
        cout << "[SimpleScanner] Scanning: " << doc << "\n";
    }
};

// ✅ AllInOne implements all three — because it genuinely supports all of them
class AllInOne : public IPrinter, public IScanner, public IFax
{
public:
    void print(const string &doc) override { cout << "[AllInOne] Printing: " << doc << "\n"; }
    void scan(const string &doc) override  { cout << "[AllInOne] Scanning: " << doc << "\n"; }
    void fax(const string &doc) override   { cout << "[AllInOne] Faxing:   " << doc << "\n"; }
};

int main()
{
    cout << "--- ❌ ISP Violation ---\n";
    BadAllInOne badAll;
    badAll.print("Report.pdf");
    badAll.scan("Report.pdf");

    BadPrinter badPrinter;
    badPrinter.print("Invoice.pdf");
    try
    {
        badPrinter.scan("Invoice.pdf"); // ❌ blows up — forced interface it can't honour
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    cout << "\n--- ✅ ISP Compliant ---\n";
    SimplePrinter printer;
    printer.print("Invoice.pdf"); // ✅ only does what it can

    SimpleScanner scanner;
    scanner.scan("Contract.pdf"); // ✅ only does what it can

    AllInOne allInOne;
    allInOne.print("Manual.pdf");
    allInOne.scan("Manual.pdf");
    allInOne.fax("Manual.pdf");

    return 0;
}
