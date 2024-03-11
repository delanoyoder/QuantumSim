// quantum_gate.h
#ifndef QUANTUM_GATE_H
#define QUANTUM_GATE_H

#include "qubit.h"

class QuantumGate {
public:
    virtual void apply(Qubit& qubit) const = 0;  // Pure virtual function
};

#endif // QUANTUM_GATE_H
