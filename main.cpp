/* 
 * Project: Resistor Library (Friend Function Refactor)
 * Author: Lenny Mubea
 * Description: Educational framework for EEE students to master C++ encapsulation.
 */



#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;


class Resistor {
private:
    string label;
    double resistance; // in Ohms
    double tolerance;  // e.g., 0.05 for 5%
    double freqency;      // in Hz (for future use, currently not utilized in calculations)

public:
    Resistor(string l, double r, double t) : label(l), resistance(r), tolerance(t) {}

    // Getter for the label for access in the main function
    string getL() const { return label; }

    // Declaration of the friend functions
    friend void toleranceRange(const Resistor& r, double& rMin, double& rMax);
    friend double calculatePower(double current, const Resistor& r);
    friend double acImpedance(const Resistor& r, double frequency);
    friend double voltageDrop(const Resistor& r, double current);
    friend double thermalDeratedMaxPower(const Resistor& r, double ratedPowerW, double ambientTempC);
    friend bool qcInspector(const Resistor& r,double measured );
};

int main() {
    Resistor r1("R1", 1000, 0.05); // 1k Ohm
    Resistor r2("R2", 2200, 0.10); // 2.2k Ohm



    double frequency = 50;
    double Z1 = acImpedance(r1, frequency); // Calculate impedance
    double Z2 = acImpedance(r2, frequency); // Calculate impedance

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;

    cout << "Impedance of " << r1.getL() << ": " << Z1 << " Ohms" <<" At "<< frequency << " Hz" << endl;
    cout << "Impedance of " << r2.getL() << ": " << Z2 << " Ohms" << " At "<< frequency << " Hz" << endl;

    double currentVal = 0.025; // Example: 25mA

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;

    // Using the friend function
    double v1 = voltageDrop(r1, currentVal);
    double v2 = voltageDrop(r2, currentVal);

    cout << "Voltage drop for " << r1.getL() << ": " << v1 << "V" << endl;
    cout << "Voltage drop for " << r2.getL() << ": " << v2 << "V" << endl;


    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;

     double minVal, maxVal;

    //Display range for resistor 1
    toleranceRange(r1, minVal, maxVal);
    cout << r1.getL() << " Range: " << minVal << " Ohms to " << maxVal << " Ohms" << endl;

    //Display range for resistor 2
    toleranceRange(r2, minVal, maxVal); 
    cout << r2.getL() << " Range: " << minVal << " Ohms to " << maxVal << " Ohms" << endl;


    // Power Test 1: high current — should trigger warning
    double p1 = calculatePower(0.06, r1);
    cout << "Power for " << r1.getL() << " is: " << p1 << "W" << endl;

    //Power Test 2: safe current — should not trigger warning
    double p2 = calculatePower(0.01, r2);
    cout << "Power for " << r2.getL() << " is: " << p2 << "W" << endl;

    cout << "Circuit initialized with " << r1.getL() << " and " << r2.getL() << endl;
   
double temp = 75.0;
double ratedPower = 0.25;
double maxPowerR1 = thermalDeratedMaxPower(r1, ratedPower, temp);
double maxPowerR2 = thermalDeratedMaxPower(r2, ratedPower, temp);
cout<< "At " << temp << "C, max derated power for " << r1.getL() << " is " << maxPowerR1 << "W" << endl;
cout<< "At " << temp << "C, max derated power for " << r2.getL() << " is " << maxPowerR2 << "W" << endl;

    // qc_inspector
double testMeasured = 1040.0; 
    cout << "\n--- QC Inspection ---" << endl;
    cout << "Testing " << r1.getL() << " with measured " << testMeasured << " Ohms..." << endl;
    
    qcInspector(r1, testMeasured);

    return 0;
}


 //Friend function definition
double acImpedance(const Resistor& r, double frequency) {
    const double omega = 2 * M_PI * frequency;
    const double C = 1e-12; // 1pF
    const double X_C = (frequency == 0) ? 0.0 : 1 / (omega * C);

    return sqrt(pow(r.resistance, 2) + pow(X_C, 2));
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

//Definition of friend function voltageDrop
double voltageDrop(const Resistor& r, double current) {
    return current * r.resistance;
}

//thermal derating function definition
double thermalDeratedMaxPower(const Resistor&, double ratedPowerW, double ambientTempC) {
    const double deratingStartC = 70.0;
    const double maxTempC = 155.0;

    if (ambientTempC <= deratingStartC) {
        return ratedPowerW;
    }
    if (ambientTempC >= maxTempC) {
        return 0.0;
    }

    return ratedPowerW * (1.0 - ((ambientTempC - deratingStartC) / (maxTempC - deratingStartC)));
}

//Definition of friend function QC inspector
bool qcInspector(const Resistor& r, double measured) {
    const double nominal = r.resistance;
    const double actualDeviation = abs(nominal - measured);
    const double deviationPercent = (nominal == 0.0) ? 100.0 : (actualDeviation / nominal) * 100.0;
    const double tolerancePercent = r.tolerance * 100.0;
    const bool withinSpec = deviationPercent <= tolerancePercent;

    cout << "Label: " << r.label
         << " | Result: " << (withinSpec ? "PASSED" : "FAILED")
         << " | Deviation: " << deviationPercent << "%" << endl;

    return withinSpec;
}
