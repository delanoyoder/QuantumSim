// hadamard_gate.h
#ifndef HADAMARD_GATE_H
#define HADAMARD_GATE_H

#include "quantum_gate.h"

class HadamardGate : public QuantumGate {
public:
	void apply(Qubit& qubit) const override;
};

#endif // HADAMARD_GATE_H