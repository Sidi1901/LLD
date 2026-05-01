#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 📦 Problem Statement: Invoice Management System

// Design a system that manages invoices for an online store.

// ❌ SRP Violation — doing too many things in one class:
//      Storing invoice data
//      Calculating totals
//      Printing the invoice
//      Saving the invoice to a file

// ✅ SRP Fix — one class, one reason to change:
//      Invoice      → holds data and calculates total
//      InvoicePrinter  → handles display/printing
//      InvoiceStorage  → handles persistence

// ─────────────────────────────────────────────
// ❌ BAD: violates SRP — Invoice does everything
// ─────────────────────────────────────────────

class BadInvoice
{
    string customerName;
    vector<pair<string, double>> items; // {item, price}

public:
    BadInvoice(string name) : customerName(name) {}

    void addItem(string item, double price)
    {
        items.push_back({item, price});
    }

    double calculateTotal()
    {
        double total = 0;
        for (auto &i : items)
            total += i.second;
        return total;
    }

    // ❌ Responsibility 2: Printing — should NOT be here
    void printInvoice()
    {
        cout << "=== Invoice for " << customerName << " ===\n";
        for (auto &i : items)
            cout << "  " << i.first << ": $" << i.second << "\n";
        cout << "  Total: $" << calculateTotal() << "\n";
    }

    // ❌ Responsibility 3: Persistence — should NOT be here
    void saveToFile()
    {
        cout << "[File] Saving invoice for " << customerName << " to disk...\n";
        // Logic to save into file 
        //.....
        //....
    }
};

// ─────────────────────────────────────────────
// ✅ GOOD: each class has exactly one responsibility
// ─────────────────────────────────────────────

class Invoice
{
public:
    string customerName;
    vector<pair<string, double>> items;

    Invoice(string name) : customerName(name) {}

    void addItem(string item, double price)
    {
        items.push_back({item, price});
    }

    double calculateTotal() const
    {
        double total = 0;
        for (auto &i : items)
            total += i.second;
        return total;
    }
};

// Only reason to change: display format changes
class InvoicePrinter
{
public:
    void print(const Invoice &inv)
    {
        cout << "=== Invoice for " << inv.customerName << " ===\n";
        for (auto &i : inv.items)
            cout << "  " << i.first << ": $" << i.second << "\n";
        cout << "  Total: $" << inv.calculateTotal() << "\n";
    }
};

// Only reason to change: storage mechanism changes (DB, cloud, file)
class InvoiceStorage
{
public:
    void saveToFile(const Invoice &inv)
    {
        cout << "[File] Saving invoice for " << inv.customerName << " to disk...\n";
    }

    void saveToDatabase(const Invoice &inv)
    {
        cout << "[DB] Inserting invoice for " << inv.customerName << " into database...\n";
    }
};

int main()
{
    cout << "--- ❌ SRP Violation ---\n";
    BadInvoice bad("Alice");
    bad.addItem("Laptop", 999.99);
    bad.addItem("Mouse", 29.99);
    bad.printInvoice();
    bad.saveToFile();

    cout << "\n--- ✅ SRP Compliant ---\n";
    Invoice inv("Bob");
    inv.addItem("Keyboard", 79.99);
    inv.addItem("Monitor", 299.99);

    InvoicePrinter printer;
    printer.print(inv);

    InvoiceStorage storage;
    storage.saveToFile(inv);
    storage.saveToDatabase(inv);

    return 0;
}
