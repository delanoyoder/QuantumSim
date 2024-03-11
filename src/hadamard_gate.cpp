// hadamard_gate.cpp
#include "hadamard_gate.h"
#include <complex>

using namespace std;

void HadamardGate::apply(Qubit& qubit) const {
	complex<double> alpha = qubit.getAlpha();
	complex<double> beta = qubit.getBeta();

	complex<double> newAlpha = (alpha + beta) / sqrt(2.0);
	complex<double> newBeta = (alpha - beta) / sqrt(2.0);

	qubit.setAlpha(newAlpha);
	qubit.setBeta(newBeta);
}