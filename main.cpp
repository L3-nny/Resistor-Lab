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

    // Getter for the label for access in the main function
    string getL() const { return label; }

   // Declaration of the friend function
    friend void toleranceRange(const Resistor& r, double& rMin, double& rMax);
};


// Definition of the friend function
void  toleranceRange(const Resistor& r, double& rMin, double& rMax) {
rMin = r.resistance * (1 - r.tolerance);
rMax = r.resistance * (1 + r.tolerance);
}

int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;

    double minVal, maxVal;
    toleranceRange(r1, minVal, maxVal);
    cout << r1.getL() << "Range: " << minVal << "Ohms to " << maxVal << "Ohms" << endl;

    toleranceRange(r2, minVal, maxVal); 
     cout << r2.getL() << "Range: " << minVal << "Ohms to " << maxVal << "Ohms" << endl;

    return 0;
}