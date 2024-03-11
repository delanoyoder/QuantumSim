// qubit.h
#ifndef QUBIT_H  // Include guard
#define QUBIT_H

#include <complex>

using namespace std;

class Qubit {
public:
    Qubit(complex<double> alpha, complex<double> beta);  // Constructor
    complex<double> getAlpha() const;  // Getter for alpha
    complex<double> getBeta() const;  // Getter for beta
    void setAlpha(complex<double> newAlpha);
    void setBeta(complex<double> newBeta);
    void displayState() const;  // Display the Qubit's state

private:
    complex<double> alpha;  // Amplitude for state |0>
    complex<double> beta;   // Amplitude for state |1>
};

#endif  // QUBIT_H
