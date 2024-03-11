// qubit.cpp
#include "qubit.h"
#include <iostream>
#include <complex>

using namespace std;

// Constructor
Qubit::Qubit(complex<double> alpha, complex<double> beta) {
    double norm = sqrt(std::norm(alpha) + std::norm(beta));  // Calculate the normalization factor
    this->alpha = alpha / norm;  // Normalize the alpha amplitude
    this->beta = beta / norm;  // Normalize the beta amplitude
}

complex<double> Qubit::getAlpha() const {
    return alpha;  // Return the alpha amplitude
}

complex<double> Qubit::getBeta() const {
    return beta;  // Return the beta amplitude
}

void Qubit::setAlpha(complex<double> newAlpha) {
    this->alpha = newAlpha;
}

void Qubit::setBeta(complex<double> newBeta) {
    this->beta = newBeta;
}

// Display the Qubit's state
void Qubit::displayState() const {
    cout << "Qubit's State: " << alpha << "|0> + " << beta << "|1>" << endl;
}
