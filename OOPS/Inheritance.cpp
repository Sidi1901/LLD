#include <iostream>
#include <string>

// --------------------------------------------------------------------------------
// ── Example 1 : Inheritance ────────────────────────────────────────────
// --------------------------------------------------------------------------------

class Person {
public:
    Person(const std::string& name, int age)
        : name(name), age(age) {
        std::cout << "Person constructor: " << name << '\n';
    }

    virtual ~Person() {
        std::cout << "Person destructor: " << name << '\n';
    }

    virtual void display() const {
        std::cout << "Person: " << name << ", age " << age << '\n';
    }

protected:
    std::string name;
    int age;
};

class Employee : public Person {
public:
    Employee(const std::string& name, int age, const std::string& role, double salary)
        : Person(name, age), role(role), salary(salary) {
        std::cout << "Employee constructor: " << name << '\n';
    }

    ~Employee() override {
        std::cout << "Employee destructor: " << name << '\n';
    }

    void display() const override {
        std::cout << "Employee: " << name
                  << ", age " << age
                  << ", role " << role
                  << ", salary " << salary << '\n';
    }

private:
    std::string role;
    double salary;
};

int main() {
    std::cout << "-- Creating objects --\n";
    Person* person = new Person("Alice", 30);
    Person* employee = new Employee("Bob", 28, "Developer", 85000.0);

    std::cout << "\n-- Calling display() through base pointers --\n";
    person->display();
    employee->display();

    std::cout << "\n-- Cleaning up --\n";
    delete person;
    delete employee;
    return 0;
}
