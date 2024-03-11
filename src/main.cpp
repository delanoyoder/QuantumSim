// main.cpp
#include "color_text.h"
#include "quantum_state.h"
#include "quantum_gates.h"
#include <vector>
#include <cmath>

using namespace std;

int main() {
    cout << endl;
    cout << YELLOW << "In this test qubits will always be reset to ";
    cout << "their initial state before applying the next gate." << RESET << endl;
    cout << endl;

    // Test a single qubit
    QuantumState qubit1({0.6, 0.8});
    qubit1.displayState();  // Display the initial quantum state

    // Apply the X Gate:
    // X|psi> = |0 1| |0.6| = [0.8 0.6]
    //          |1 0| |0.8|
    cout << "Applying X Gate: X|psi_0>" << endl;
    qubit1.applyGate(X, 0);  // Apply Gate
    qubit1.displayState();  // Display new state
    qubit1.applyGate(X, 0);  // Reset state

    // Apply the Y Gate:
    // Y|psi> = |0 -i| |0.6| = [-0.8i 0.6i]
    //          |i  0| |0.8|
    cout << "Applying Y Gate: Y|psi_0>" << endl;
    qubit1.applyGate(Y, 0);  // Apply Gate
    qubit1.displayState();  // Display new state
    qubit1.applyGate(Y, 0);  // Reset state

    // Apply the Z Gate:
    // Z|psi> = |1  0| |0.6| = [0.6 -0.8]
    //          |0 -1| |0.8|
    cout << "Applying Z Gate: Z|psi_0>" << endl;
    qubit1.applyGate(Z, 0);  // Apply Gate
    qubit1.displayState();  // Display new state
    qubit1.applyGate(Z, 0);  // Reset state

    // Apply the H Gate:
    // H|psi> = |1/sqrt(2)  1/sqrt(2)| |0.6| = [0.989949 -0.141421]
    //          |1/sqrt(2) -1/sqrt(2)| |0.8|
    cout << "Applying Hadamard Gate: H|psi_0>" << endl;
    qubit1.applyGate(H, 0);  // Apply Gate
    qubit1.displayState();  // Display new state
    qubit1.applyGate(H, 0);  // Reset state

    // Test two qubits
    QuantumState qubit2({-0.8, 0.6});  // |1> state

    // Combine them into a larger quantum state
    vector<QuantumState> qubits = {qubit1, qubit2};
    QuantumState combinedState(qubits);

    // Display the initial quantum state
    combinedState.displayState();

    // Apply and test Pauli-X gate on the first qubit
    cout << "Applying X Gate to qubit 0: X|psi_0>" << endl;
    combinedState.applyGate(X, 0);
    combinedState.displayState();
    combinedState.applyGate(X, 0);

    // Reset the combinedState for the next gate application if needed
    // Note: Resetting would typically involve reinitializing or providing a method to reset to a previous state.

    // Apply and test Pauli-Y gate on the second qubit
    cout << "Applying Y Gate to qubit 1: Y|psi_1>" << endl;
    combinedState.applyGate(Y, 1);
    combinedState.displayState();
    combinedState.applyGate(Y, 1);

    // Apply and test Pauli-Z gate on the first qubit
    cout << "Applying Z Gate to qubit 0: Z|psi_0>" << endl;
    combinedState.applyGate(Z, 0);
    combinedState.displayState();
    combinedState.applyGate(Z, 0);

    // Reset the combinedState for the next gate application if needed

    // Apply and test Hadamard gate on the first qubit
    cout << "Applying Hadamard gate to qubit 0: H|psi_0>" << endl;
    combinedState.applyGate(H, 0);
    combinedState.displayState();
    combinedState.applyGate(H, 0);

    // Test CNOT got on simple two qubit system
    // QuantumState qubit3({1, 0});  // |0> state
    QuantumState qubit3({1, 0});  // |0> state
    vector<QuantumState> qubits2 = {qubit3, qubit3};
    QuantumState combinedState2(qubits2);

    // Display the initial quantum state
    combinedState2.displayState();

    // Apply and test CNOT gate with first qubit being the control qubit
    // and the second qubit being the target qubit
    cout << "Applying CNOT Gate to qubits: CNOT(|psi_0> (x) |psi_1>)" << endl;
    combinedState.applyControlledGate(X, 0, 1);
    combinedState.displayState();
    combinedState.applyControlledGate(X, 0, 1);
    combinedState.displayState();

    return 0;
}
