/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
 /*
 * Modified by: William Wilson, Sam Triest, and Ryan Green.
 * Emails: wwils11@u.rochester.edu, striest@u.rochester.edu, rgreen@u.rochester.edu
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"
/**
 * Two AND gates connected to make a 3-input AND circuit.
 */

//Circuit for AND on 3 values
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

//Circuit for OR on 3 values
static Circuit* Circuits_Or3() {
    Value* in0 = new_Value(false);
    Value* in1 = new_Value(false);
    Value* in2 = new_Value(false);
    Gate* or0 = new_OrGate(in0, in1);
    Gate* or1 = new_OrGate(Gate_getOutput(or0), in2);

    Value** inputs = new_Value_array(3);
    inputs[0] = in0;
    inputs[1] = in1;
    inputs[2] = in2;

    Value** outputs = new_Value_array(1);
    outputs[0] = Gate_getOutput(or1);
    Gate** gates = new_Gate_array(2);
    gates[0] = or0;
    gates[1] = or1;
    return new_Circuit(3, inputs, 1, outputs, 2, gates);
}
//Circuit for oneBitAdder extra credit
static Circuit* Circuit_oneBitAdder() {
    Value* in0 = new_Value(false);
    Value* in1 = new_Value(false);
    Value* in2 = new_Value(false);

    Gate* and0 = new_AndGate(in0, in2);
    Gate* and1 = new_AndGate(in0, in1);
    Gate* and2 = new_AndGate(in1, in2);

    Gate* o1 = new_Or4Gate(Gate_getOutput(and0), Gate_getOutput(and1), Gate_getOutput(and2), new_Value(false));
    Value* cout = Gate_getOutput(o1);

    Gate* i1 = new_Inverter(Gate_getOutput(o1));

    Gate* a3 = new_And3Gate(in0, in1, in2);

    Gate* o3 = new_OrGate(Gate_getOutput(a3), Gate_getOutput(i1));

    //False is the identity for OR in this case
    Gate* o2 = new_Or4Gate(new_Value(false), in0, in1, in2);

    Gate* a4 = new_AndGate(Gate_getOutput(o2), Gate_getOutput(o3));

    Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** output = new_Value_array(2);
	output[0] = Gate_getOutput(o1);
	output[1] = Gate_getOutput(a4);
	Gate** gates = new_Gate_array(9);
	gates[0] = and0;
	gates[1] = and1;
	gates[2] = and2;
	gates[3] = a3;
	gates[4] = o2;
	gates[5] = o1;
	gates[6] = i1;
	gates[7] = o3;
	gates[8] = a4;
	Circuit *returnCircuit = new_Circuit(3, inputs, 2, output, 9, gates);
	return returnCircuit;
}

//Boolean to a string
static char* b2s(bool b) {
	return b ? "T" : "F";
}

//Circuits for the various parts
static Circuit* PartA() {
	Value* x = new_Value(false);
	Value* y = new_Value(false);
	Value* z = new_Value(false);
	Gate* inv = new_Inverter(y);
	Gate* and1 = new_AndGate(x, Gate_getOutput(inv));
	Gate* and2 = new_AndGate(y, z);
	Gate* or1 = new_OrGate(Gate_getOutput(and1), Gate_getOutput(and2));
	Value** inputs = new_Value_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	Value** output = new_Value_array(1);
	output[0] = Gate_getOutput(or1);
	Gate** gates = new_Gate_array(4);
	gates[0] = inv;
	gates[1] = and1;
	gates[2] = and2;
	gates[3] = or1;
	Circuit *returnCircuit = new_Circuit(3, inputs, 1, output, 4, gates);
	return returnCircuit;
}
static Circuit* PartB() {
	Value* x = new_Value(false);
	Value* y = new_Value(false);
	Value* z = new_Value(false);
	Gate* inv = new_Inverter(y);
	Gate* and1 = new_AndGate(x, Gate_getOutput(inv));
	Gate* inv2 = new_Inverter(Gate_getOutput(and1));
	Gate* and2 = new_AndGate(z, y);
	Gate* inv3 = new_Inverter(Gate_getOutput(and2));

	Gate* or1 = new_OrGate(Gate_getOutput(inv2), Gate_getOutput(inv3));
	Gate* inv4 = new_Inverter(Gate_getOutput(or1));
	Value** inputs = new_Value_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	Value** output = new_Value_array(1);
	output[0] = Gate_getOutput(inv4);
	Gate** gates = new_Gate_array(7);
	gates[0] = inv;
	gates[1] = and1;
	gates[2] = inv2;
	gates[3] = and2;
	gates[4] = inv3;
	gates[5] = or1;
	gates[6] = inv4;
	Circuit *returnCircuit = new_Circuit(3, inputs, 1, output, 7, gates);
	return returnCircuit;
}
static Circuit* PartC() {
	Value* x = new_Value(false);
	Value* y = new_Value(false);

	Gate* a = new_AndGate(x, y);
	Gate* b = new_Inverter(x);
	Gate* c = new_Inverter(y);
	Gate* d = new_AndGate(Gate_getOutput(c), Gate_getOutput(b));
	Gate* e = new_OrGate(Gate_getOutput(a), Gate_getOutput(d));
	Value** inputs = new_Value_array(2);
	Value** output = new_Value_array(1);
	inputs[0] = x;
	inputs[1] = y;
	output[0] = Gate_getOutput(e);
	Gate** gates = new_Gate_array(5);
	gates[0] = a;
	gates[1] = b;
	gates[2] = c;
	gates[3] = d;
	gates[4] = e;
	Circuit *returnCircuit = new_Circuit(2, inputs, 1, output, 5, gates);
	return returnCircuit;
}

// Inverter circuit used for testing purposes
/*Circuit* inverterCircuit() {
    Value* in0 = new_Value(false);

    Gate* i0 = new_Inverter(in0);

    Value** inputs = new_Value_array(1);
	Value** output = new_Value_array(1);
	inputs[0] = in0;
	output[0] = Gate_getOutput(i0);
	Gate** gates = new_Gate_array(1);
	gates[0] = i0;

	Circuit *returnCircuit = new_Circuit(1, inputs, 1, output, 1, gates);
	return returnCircuit;
}*/


/*
    Used to test various numbers of inputs and outputs
*/
static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void test3In2Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	bool out1 = Circuit_getOutput(circuit, 1);
	printf("%s %s %s -> %s %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0), b2s(out1));
}

static void test1In1Out(Circuit* circuit, bool in0) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s -> %s\n", b2s(in0), b2s(out0));
}

static void test2in1out(Circuit* circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

/*
    Functions to test all inputs and outputs of the various circuits created
*/
static void testA(Circuit* parta) {
    printf("-------------\nx y z -> output\n-------------\n");
    test3In1Out(parta, 1, 1, 1);
    test3In1Out(parta, 1, 1, 0);
    test3In1Out(parta, 1, 0, 1);
    test3In1Out(parta, 1, 0, 0);
    test3In1Out(parta, 0, 1, 1);
    test3In1Out(parta, 0, 1, 0);
    test3In1Out(parta, 0, 0, 1);
    test3In1Out(parta, 0, 0, 0);
}

static void testB(Circuit* partb) {
    printf("-------------\nx y z -> output\n-------------\n");
    test3In1Out(partb, 1, 1, 1);
    test3In1Out(partb, 1, 1, 0);
    test3In1Out(partb, 1, 0, 1);
    test3In1Out(partb, 1, 0, 0);
    test3In1Out(partb, 0, 1, 1);
    test3In1Out(partb, 0, 1, 0);
    test3In1Out(partb, 0, 0, 1);
    test3In1Out(partb, 0, 0, 0);
}

static void testC(Circuit* partc) {
    printf("-------------\nx y -> output\n-------------\n");
    test2in1out(partc, 1, 1);
    test2in1out(partc, 1, 0);
    test2in1out(partc, 0, 1);
    test2in1out(partc, 0, 0);
}

static void testOneBit(Circuit* onebitadder) {
    printf("-------------\nx y z -> cout d\n-------------\n");
    test3In2Out(onebitadder, 1, 1, 1);
    test3In2Out(onebitadder, 1, 1, 0);
    test3In2Out(onebitadder, 1, 0, 1);
    test3In2Out(onebitadder, 1, 0, 0);
    test3In2Out(onebitadder, 0, 1, 1);
    test3In2Out(onebitadder, 0, 1, 0);
    test3In2Out(onebitadder, 0, 0, 1);
    test3In2Out(onebitadder, 0, 0, 0);
}


/*
    Main function
*/
int main(int argc, char **argv) {
    //Original test case, no longer necessary.
	/*Circuit* c = Circuits_and3();
	printf("Some input(s) false: should be false\n");
	test3In1Out(c, true, true, false);
	printf("All inputs true: should be true\n");
	test3In1Out(c, true, true, true);*/

    //Create the first three circuits
	Circuit* parta = PartA();
	Circuit* partb = PartB();
	Circuit* partc = PartC();

    //Test the circuits below on all possible inputs
	printf("Test Part 'A':\n");
    testA(parta);

    // Inverter Test - Not Necessary
    //Circuit* inv = inverterCircuit();
    //printf("Test Part INVERTER:\n");
    //test1In1Out(inv, 0);
    //test1In1Out(inv, 1);

    printf("\nTest Part 'B':\n");
    testB(partb);

    printf("\nTest Part 'C':\n");
    testC(partc);

    //Extra credit part, testing the One Bit Adder
	printf("\nTest the One Bit Adder Circuit:\n");
    Circuit* onebitadder = Circuit_oneBitAdder();
    testOneBit(onebitadder);
}
