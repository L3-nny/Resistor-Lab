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

  Task-5-Thermal-Derating
friend double ThermalDerating(const Resistor& r, double tempC);
       // Declaration of the friend function
    friend void toleranceRange(const Resistor& r, double& rMin, double& rMax);

     friend double calculatePower(double current, const Resistor& r);
 main
};

double ThermalDerating(const Resistor& r, double tempC){
    return r.resistance * (1. + 0.004 * (tempC - 25.0)); // linear derating model
}


int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm

     double minVal, maxVal;

    //Display range for resistor 1
    toleranceRange(r1, minVal, maxVal);
    cout << r1.getL() << "Range: " << minVal << "Ohms to " << maxVal << "Ohms" << endl;

    //Display range for resistor 2
    toleranceRange(r2, minVal, maxVal); 
     cout << r2.getL() << "Range: " << minVal << "Ohms to " << maxVal << "Ohms" << endl;


    // Power Test 1: high current — should trigger warning
    double p1 = calculatePower(0.06, r1);
    cout << "Power for " << r1.getL() << " is: " << p1 << "W" << endl;

    //Power Test 2: safe current — should not trigger warning
    double p2 = calculatePower(0.01, r2);
    cout << "Power for " << r2.getL() << " is: " << p2 << "W" << endl;

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;
 Task-5-Thermal-Derating
   
double temp = 75.0;
double assumedR1 = ThermalDerating(r1, temp);
double assumedR2 = ThermalDerating(r2, temp);
cout<< "At " << temp << "C, " << r1.getL() << " is assumed to be " << assumedR1 << " Ohms" << endl;
cout<< "At " << temp << "C, " << r2.getL() << " is assumed to be " << assumedR2 << " Ohms" << endl;
  
 main

    return 0;
}

    //Definition of friend fuction toleranceRange
void  toleranceRange(const Resistor& r, double& rMin, double& rMax) {
rMin = r.resistance * (1 - r.tolerance);
rMax = r.resistance * (1 + r.tolerance);
}

//Definition of friend fuction calculatePower
double calculatePower(double current, const Resistor& r) {
    double power = (current * current) * r.resistance;

    if (power > 0.25) {
        cout << "WARNING: Power dissipation of " << power << "W exceeds the 0.25W limit for resistor " << r.label << "!" << endl;
    }

    return power;
}
