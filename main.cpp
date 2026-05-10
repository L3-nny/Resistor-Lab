/* 
 * Project: Resistor Library (Friend Function Refactor)
 * Author: Lenny Mubea
 * Description: Educational framework for EEE students to master C++ encapsulation.
 */



#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;


class Resistor {
private:
    string label;
    double resistance; // in Ohms
    double tolerance;  // e.g., 0.05 for 5%
    double freqency;      // in Hz (for future use, currently not utilized)

public:
    Resistor(string l, double r, double t) : label(l), resistance(r), tolerance(t) {}

    // Getter for the label for access in the main function
    string getL() const { return label; }

    // Declaration of the friend functions
    friend void toleranceRange(const Resistor& r, double& rMin, double& rMax);
    friend double calculatePower(double current, const Resistor& r);
    friend double voltageDrop(const Resistor& r, double current);
    friend double thermalDeratedMaxPower(const Resistor& r, double ratedPowerW, double ambientTempC);
    friend double acImpedance(const Resistor& r, double freqHz);
    friend double calculateParallel(const Resistor& r1, const Resistor& r2);

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


double result = calculateParallel(r1, r2);

    // Ensuring NO output if any value was negative (result would be -1.0)
    if (result >= 0) {
        cout << fixed << setprecision(2);
        cout << "Equivalent Resistance: " << result << " Ohms" << endl;
    }else {
        cout << "Invalid resistor value detected." << endl;
    }

    return 0;
}


 //Friend function definition
double acImpedance(const Resistor& r, double frequency) {
    
  const double omega = 2 * M_PI * frequency; 
       
        double C = 1e-12; //12pF
        double X_C;

    // Prevent division by zero if capacitance is 0
    if (frequency > 0) {
       X_C = 1 / (omega * C); 
    } 
    if (frequency =0) {
    
     X_C = 0 ; // Capacitive reactance 
    }

    double Z = sqrt(pow(r.resistance, 2) + pow((X_C), 2)); 
    return Z;

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
    
//Definition of friend function calculateParallel
double calculateParallel(const Resistor& r1, const Resistor& r2) {
    if (r1.resistance < 0 || r2.resistance < 0) {
        return -1.0;
    }
    double req;
    if (r1.resistance + r2.resistance == 0) {
        req = 0;
    } else{
        req = (r1.resistance * r2.resistance) / (r1.resistance + r2.resistance);
    }
    return req;
}