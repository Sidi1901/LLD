// PROBLEM: Without Strategy Pattern
//
// A navigation app supports multiple route modes: driving, walking, cycling.
// All logic lives inside Navigator, so adding a new mode means editing and
// recompiling this class — violating Open/Closed Principle. Behaviour cannot
// be swapped at runtime, and testing each mode requires instantiating the
// whole Navigator.

#include <iostream>
#include <string>

const std::string DRIVING = "DRIVING";
const std::string WALKING = "WALKING";
const std::string CYCLING = "CYCLING";

class Navigator
{
    std::string mode;

public:
    // Why use : mode(m) instead of { mode = m; } inside the body?

    // The initializer list constructs mode directly with m. The body-assignment version would first default-construct mode (empty string),
    // then assign m to it — two operations instead of one. For std::string it's a minor difference, but for types with no default constructor
    // it becomes mandatory.
    Navigator(const std::string &m) : mode(m) {}

    void buildRoute(const std::string &from, const std::string &to)
    {
        // Every new transport type forces us to touch this method.
        if (mode == DRIVING)
        {
            std::cout << "[Driving]  fastest road route from "
                      << from << " to " << to << "\n";
        }
        else if (mode == WALKING)
        {
            std::cout << "[Walking]  shortest footpath from "
                      << from << " to " << to << "\n";
        }
        else if (mode == CYCLING)
        {
            std::cout << "[Cycling]  bike-friendly route from "
                      << from << " to " << to << "\n";
        }
        // Adding BOAT, SUBWAY, etc. keeps bloating this if-else chain.
    }

    // Cannot switch strategy at runtime — mode is fixed at construction.
};

int main()
{
    Navigator nav(DRIVING);
    nav.buildRoute("Home", "Office");

    Navigator nav2(WALKING);
    nav2.buildRoute("Hotel", "Museum");

    return 0;
}
