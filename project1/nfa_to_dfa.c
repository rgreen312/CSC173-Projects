#include "IntSet.h"
#include "headers.h"
#include "nfa.h"
#include "dfa.h"

int exponent(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}

DFA* NFA_to_DFA(NFA* nfa) {
	int size = exponent(2, nfa->nstates);
	IntSet* newStates[size];

	DFA* dfa = DFA_new(size);
	newStates[0]=IntSet_new();
	IntSet_add(newStates[0], NFA_START_STATE);
	for (int j = 0; j < *nfa->nstates; j++) {
		for (int i = 0; i < NFA_SYMBOLS; i++) {

		}
	}
}