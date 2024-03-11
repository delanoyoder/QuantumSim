// quantum_state.h
#ifndef QUANTUM_STATE_H
#define QUANTUM_STATE_H

#include <vector>
#include <complex>
#include <cmath>
#include "color_text.h"

using namespace std;

class QuantumState {
public:
    // Constructor for initializing a quantum state from a list of amplitudes
    explicit QuantumState(const vector<complex<double>>& initialState) {
        stateVector = initialState;
        numQubits = log2(initialState.size());
		displayInitializedState();
    }

	// Constructor that initializes the quantum state from a list of QuantumState objects
	QuantumState(const vector<QuantumState>& qubitStates) {
		if (!qubitStates.empty()) {
			// Initialize state vector with the state of the first QuantumState in the list
			stateVector = qubitStates[0].getStateVector();
			numQubits = static_cast<size_t>(log2(qubitStates[0].getStateVector().size()));

			// Compute the tensor product with the rest of the QuantumState objects
			for (size_t i = 1; i < qubitStates.size(); ++i) {
				stateVector = tensorProduct(stateVector, qubitStates[i].getStateVector());
				// Increase the total number of qubits by the number represented by the current QuantumState
				numQubits += static_cast<size_t>(log2(qubitStates[i].getStateVector().size()));
			}
		} else {
			// Default to a single qubit in the |0> state if no states are provided
			stateVector = {1.0, 0.0};
			numQubits = 1;
		}
		displayInitializedState();
	}

	void displayInitializedState() const {
		cout << BLUE << "Initialized QuantumState: |Ψ> = [";
		for (size_t i = 0; i < stateVector.size(); i++) {
			cout << stateVector[i] << " ";
		}
		cout << "]" << RESET << endl;
	}

	// Accessor for the number of qubits
	size_t getNumQubits() const {
		return numQubits;
	}

    // Accessor for the state vector, used in tensor products
    const vector<complex<double>>& getStateVector() const {
        return stateVector;
    }

    // Utility function to display the quantum state
    void displayState() const {
        for (size_t i = 0; i < stateVector.size(); ++i) {
			double probability = norm(stateVector[i]);
            cout << probability << "% : " << stateVector[i] << " |" << i << "> " << endl;
        }
        cout << endl;
    }

	bool isUnitary(const vector<vector<complex<double>>>& matrix) {
		// Assume matrix is 2x2 based on previous checks; otherwise, extend these concepts.
		vector<vector<complex<double>>> dagger(2, vector<complex<double>>(2));
		vector<vector<complex<double>>> productUUdagger(2, vector<complex<double>>(2, complex<double>(0, 0)));
		vector<vector<complex<double>>> productUdaggerU(2, vector<complex<double>>(2, complex<double>(0, 0)));

		// Compute the conjugate transpose (dagger)
		for (size_t i = 0; i < 2; ++i) {
			for (size_t j = 0; j < 2; ++j) {
				dagger[j][i] = conj(matrix[i][j]); // conjugate transpose
			}
		}

		// Compute U * U^dagger and U^dagger * U
		for (size_t i = 0; i < 2; ++i) {
			for (size_t j = 0; j < 2; ++j) {
				for (size_t k = 0; k < 2; ++k) {
					productUUdagger[i][j] += matrix[i][k] * dagger[k][j];
					productUdaggerU[i][j] += dagger[i][k] * matrix[k][j];
				}
			}
		}

		// Check if both products are identity matrices
		for (size_t i = 0; i < 2; ++i) {
			for (size_t j = 0; j < 2; ++j) {
				if (i == j) {
					if (abs(productUUdagger[i][j] - 1.0) > 1e-6 || abs(productUdaggerU[i][j] - 1.0) > 1e-6) // Not close to 1
						return false;
				} else {
					if (abs(productUUdagger[i][j]) > 1e-6 || abs(productUdaggerU[i][j]) > 1e-6) // Not close to 0
						return false;
				}
			}
		}

		return true; // Passed all checks, matrix is unitary
	}

	// Apply a single-qubit quantum gate to the state
	void applyGate(const vector<vector<complex<double>>>& gateMatrix, size_t targetQubit) {
		// Validate the gate matrix
		if (gateMatrix.size() != 2 || gateMatrix[0].size() != 2 || gateMatrix[1].size() != 2) {
			cerr << RED << "Invalid gate matrix size." << RESET << endl;
			return;
		}

		// Before applying the gate, check if it's unitary
		if (!isUnitary(gateMatrix)) {
			cerr << RED << "Gate matrix is not unitary." << RESET << endl;
			return; // Exit the function if the gate matrix is not unitary.
		}

		
		// Validate the target qubit index
		if (targetQubit >= numQubits) {
			cerr << RED << "Invalid target qubit index." << RESET << endl;
			return;
		}

		vector<complex<double>> newStateVector(stateVector.size(), complex<double>(0, 0));

		// Define the size of blocks and offsets based on the target qubit
		size_t block_size = pow(2, targetQubit);
		size_t num_blocks = pow(2, numQubits - targetQubit - 1);

		// Apply the gate to each block
		for (size_t block = 0; block < num_blocks; ++block) {
			for (size_t offset = 0; offset < block_size; ++offset) {
				size_t index0 = block * block_size * 2 + offset;
				size_t index1 = index0 + block_size;

				newStateVector[index0] = gateMatrix[0][0] * stateVector[index0] + gateMatrix[0][1] * stateVector[index1];
				newStateVector[index1] = gateMatrix[1][0] * stateVector[index0] + gateMatrix[1][1] * stateVector[index1];
			}
		}

		// Update the state vector
		stateVector = newStateVector;
	}


	// Apply a controlled quantum gate to the state
	void applyControlledGate(const vector<vector<complex<double>>>& gateMatrix, size_t controlQubit, size_t targetQubit) {
		// Validate the gate matrix
		if (gateMatrix.size() != 2 || gateMatrix[0].size() != 2 || gateMatrix[1].size() != 2) {
			cerr << RED << "Invalid gate matrix size." << RESET << endl;
			return;
		}

		// Before applying the gate, check if it's unitary
		if (!isUnitary(gateMatrix)) {
			cerr << RED << "Gate matrix is not unitary." << RESET << endl;
			return; // Exit the function if the gate matrix is not unitary.
		}

		// Validate the target qubit index
		if (targetQubit >= numQubits) {
			cerr << RED << "Invalid target qubit index." << RESET << endl;
			return;
		}

		vector<complex<double>> newStateVector(stateVector.size(), complex<double>(0, 0));

		// Define sizes and offsets based on control and target qubits
		size_t control_offset = pow(2, controlQubit);
		size_t target_offset = pow(2, targetQubit);
		size_t segment_size = pow(2, max(controlQubit, targetQubit) + 1); // size of each segment where control qubit could change
		size_t total_segments = stateVector.size() / segment_size;

		// Apply the gate in segments where the control qubit is 1
		for (size_t seg = 0; seg < total_segments; ++seg) {
			for (size_t offset = 0; offset < segment_size / 2; ++offset) {
				// Calculate indices within the segment
				size_t base_index = seg * segment_size + offset;
				size_t index_control_0 = base_index + (base_index / control_offset % 2 == 0 ? control_offset : 0);
				size_t index_control_1 = index_control_0 + (control_offset * (index_control_0 / control_offset % 2 == 0));

				if (index_control_1 / target_offset % 2 == 0) { // Apply gate only if control qubit is 1
					size_t index0 = index_control_1 + target_offset; // Index for target qubit |0>
					size_t index1 = index0 + target_offset; // Index for target qubit |1>

					newStateVector[index0] = gateMatrix[0][0] * stateVector[index0] + gateMatrix[0][1] * stateVector[index1];
					newStateVector[index1] = gateMatrix[1][0] * stateVector[index0] + gateMatrix[1][1] * stateVector[index1];
				} else {
					// If control qubit is 0, just copy the state vector
					newStateVector[index_control_0] = stateVector[index_control_0];
					newStateVector[index_control_1] = stateVector[index_control_1];
				}
			}
		}
	
		// Update the state vector
		stateVector = newStateVector;
	}

private:
    vector<complex<double>> stateVector;
    size_t numQubits;

    // Helper function to compute the tensor product of two state vectors
    static vector<complex<double>> tensorProduct(const vector<complex<double>>& v1, const vector<complex<double>>& v2) {
        vector<complex<double>> result(v1.size() * v2.size());
        for (size_t i = 0; i < v1.size(); ++i) {
            for (size_t j = 0; j < v2.size(); ++j) {
                result[i * v2.size() + j] = v1[i] * v2[j];
            }
        }
        return result;
    }
};

#endif  // QUANTUM_STATE_H
