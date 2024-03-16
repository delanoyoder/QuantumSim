// shors_algorithm.cpp
#include "quantum_state.h"
#include "quantum_gates.h"
#include "shors_classical.h"
#include <vector>
#include <complex>

using namespace std;

int main() {
    int N = 15; // The number to factorize
    vector<int> coprimes = findAllCoprimes(N); // Find all coprimes of N
    size_t comprimeIndex = 0; // Choose the first coprime as the base for the modular exponentiation
    int a = coprimes[comprimeIndex]; // Choose the first coprime as the base for the modular exponentiation

    // Assuming the number of qubits is n
    size_t n = 3; // For example, for 3 qubits

    // Initialize the quantum state with 2^n amplitudes all set to |000...0> (which is just |0>)
    vector<complex<double>> initialState(1 << n, 0); // 1 << n is 2^n
    initialState[0] = 1; // Set the state |000...0> amplitude to 1 (all other amplitudes are 0)

    // Create a quantum state object from this initial state
    QuantumState reg1(initialState);

    // Apply the Hadamard gate to each qubit to create a superposition
    for (size_t qubit = 0; qubit < n; ++qubit) {
        reg1.applyGate(H, qubit); // Applying Hadamard gate to each qubit
    }

    // Now reg1 is in a superposition state
    // You can display the state to confirm
    reg1.displayState();

    // Example for creating a second quantum register

    // Initialize the second quantum state with 2^n amplitudes, all set to |000...0> (which is just |0>)
    vector<complex<double>> secondInitialState(1 << n, 0); // 1 << n is 2^n
    secondInitialState[0] = 1; // Set the state |000...0> amplitude to 1 (all other amplitudes are 0)

    // Create the second quantum state object from this initial state
    QuantumState reg2(secondInitialState);

    // If needed, apply gates or perform operations on the second quantum register
    // For now, let's just display the initial state
    secondQState.displayState();

    return 0;
}
