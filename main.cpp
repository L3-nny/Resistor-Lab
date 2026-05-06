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

friend double ThermalDerating(const Resistor& r, double tempC);
};

double ThermalDerating(const Resistor& r, double tempC){
    return r.resistance * (1. + 0.004 * (tempC - 25.0)); // linear derating model
}


int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;
   
double temp = 75.0;
double assumedR1 = ThermalDerating(r1, temp);
double assumedR2 = ThermalDerating(r2, temp);
cout<< "At " << temp << "C, " << r1.getL() << " is assumed to be " << assumedR1 << " Ohms" << endl;
cout<< "At " << temp << "C, " << r2.getL() << " is assumed to be " << assumedR2 << " Ohms" << endl;

    return 0;