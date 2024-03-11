// quantum_gates.h
#ifndef QUANTUM_GATES_H
#define QUANTUM_GATES_H

#include <vector>
#include <complex>

using namespace std;

using ComplexMatrix = vector<vector<complex<double>>>;

// Identity
const ComplexMatrix IDENTITY = {
	{1, 0},
	{0, 1}
};

// Pauli-X Gate
const ComplexMatrix X = {
	{0, 1},
	{1, 0}
};

// Pauli-Y Gate
const ComplexMatrix Y = {
	{0, complex<double>(0, -1)},
	{complex<double>(0, 1), 0}
};

// Pauli-Z Gate
const ComplexMatrix Z = {
	{1, 0},
	{0, -1},
};

// Hadamard Gate
const ComplexMatrix H = {
	{1 / sqrt(2), 1 / sqrt(2)},
	{1 / sqrt(2), -1 / sqrt(2)}
};

// Controlled-NOT Gate
const ComplexMatrix CNOT = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1},
	{0, 0, 1, 0}
};

#endif // QUANTUM_GATES_H