// x_gate.h
#ifndef X_GATE_H
#define X_GATE_H

#include "quantum_gate.h"

class XGate : public QuantumGate {
public:
	void apply(Qubit& qubit) const override;
};

#endif // X_GATE_H