/* 
 * Project: Resistor Library (Friend Function Refactor)
 * Author: Lenny Mubea
 * Description: Educational framework for EEE students to master C++ encapsulation.
 */




#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Resistor {
private:
    string label;
    double resistance; // in Ohms
    double tolerance;  // e.g., 0.05 for 5%
    double freqHz;      // in Hz (for future use, currently not utilized)

public:
    Resistor(string l, double r, double t) : label(l), resistance(r), tolerance(t){}    // Getters - These make the current code "clunky"
    string getL() const { return label; }

friend double acImpedance(const Resistor& r, double freqHz); // Friend function declaration
};

int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm

    double freqHz = 50;
    double Z1 = acImpedance(r1, freqHz); // Calculate impedance
    double Z2 = acImpedance(r2, freqHz); // Calculate impedance

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;

    cout << "Impedance of " << r1.getL() << ": " << Z1 << " Ohms" <<" At "<< freqHz << " Hz" << endl;
    cout << "Impedance of " << r2.getL() << ": " << Z2 << " Ohms" << " At "<< freqHz << " Hz" << endl;

    return 0;
}

 //Friend function definition
double acImpedance(const Resistor& r, double freqHz) {
  const double omega = 2 * M_PI * freqHz; 
        double X_C = 0 ; // Capacitive reactance
        double C = 1e-12; //12pF

    // Prevent division by zero if capacitance is 0
    if (freqHz > 0) {
         X_C = 1 / (omega * C); 
    } else {
        
    }

    double Z = sqrt(pow(r.resistance, 2) + pow(( X_C), 2)); 
    return Z;

}