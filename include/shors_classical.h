// shors_classical.h
#ifndef SHORS_CLASSICAL_H
#define SHORS_CLASSICAL_H

using namespace std;

// Function to find the Greatest Common Divisor (GCD) of two numbers
int gcd(int a, int b) {
    // Ensure that "a" and "b" are positive with assert
	assert(a > 0 && b > 0);

    // Loop until either one of the numbers becomes 0
    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }

    // When b becomes 0, a contains the GCD
    return a;
}

// Function to find all coprimes of a given number N
vector<int> findAllCoprimes(int N) {
    vector<int> coprimes;
    for (int i = 1; i < N; ++i) {
        if (gcd(i, N) == 1) { // Check if i is coprime with N
            coprimes.push_back(i);
        }
    }
    return coprimes;
}

void quantumModularExponentiation(QuantumState& reg1, QuantumState& reg2, int a, int N) {
    // Size of the first register, determines the superposition range
    size_t n = reg1.getNumQubits();
    
    // Apply modular exponentiation on each possible value of x represented in reg1
    for (size_t i = 0; i < n; ++i) {
        // Apply controlled multiplication based on the i-th qubit of reg1.
        // This is a simplification; actual implementation would involve
        // applying a series of quantum gates that effectively compute 
        // (a^2^i) mod N controlled by the i-th qubit of reg1.
		bool applyOperation = reg1.measureQubit(i); // Measure the i-th qubit of reg1
        int result = controlledModularExponentiation(a, 1 << i, N, applyOperation);
		reg2.applyModularMultiplication(result, N); // Apply the modular multiplication
    }
}

// Pseudocode for controlled modular exponentiation, not quantum, but illustrates the mathematical idea
int controlledModularExponentiation(int base, int exponent, int modulus, bool applyOperation) {
    if (applyOperation) {
        long long result = 1; // Use long long for larger calculations to avoid overflow
        base %= modulus; // Ensure base is within the modulus to start

        while (exponent > 0) {
            if (exponent % 2 == 1) { // If the exponent is odd
                result = (result * base) % modulus;
            }
            exponent >>= 1; // Equivalent to dividing exponent by 2
            base = (long long)base * base % modulus;
        }
        return result;
    } else {
        return 1; // Operation not applied, return identity for multiplication
    }
}

#endif // SHORS_CLASSICAL_H
