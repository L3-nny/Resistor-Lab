/* 
 * Project: Resistor Library (Friend Function Refactor)
 * Author: Lenny Mubea
 * Description: Educational framework for EEE students to master C++ encapsulation.
 */




#include <iostream>
#include <string>

using namespace std;

class Resistor {
private:
    string label;
    double resistance; // in Ohms
    double tolerance;  // e.g., 0.05 for 5%

public:
    Resistor(string l, double r, double t) : label(l), resistance(r), tolerance(t) {}

    // Getters - These make the current code "clunky"
    double getR() const { return resistance; }
    double getT() const { return tolerance; }
    string getL() const { return label; }

    friend double SeriesResistance(const Resistor& r1, const Resistor& r2) 
    }
};

SeriesResistance(const Resistor& r1, const Resistor& r2) {
    return r1.resistance + r2.resistance; // Accessing private members directly
}   

int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm

    double totalResistance = SeriesResistance(r1, r2);

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;
    cout << "Total Resistance in Series: " << totalResistance << " Ohms" << endl;
    return 0;
}
