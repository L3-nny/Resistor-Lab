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

    friend double calculatePower(double current, const Resistor& r);
};

double calculatePower(double current, const Resistor& r) {
    double power = (current * current) * r.resistance;

    if (power > 0.25) {
        cout << "WARNING: Power dissipation of " << power << "W exceeds the 0.25W limit for resistor " << r.label << "!" << endl;
    }

    return power;
}

int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm
    double p = calculatePower(0.06, r1); 

    cout << "Power for " << r1.getL() << " is: " << p << "W" << endl;

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;
    return 0;
}