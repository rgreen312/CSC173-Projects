#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"

DFA *DFA_new(int nstates) {
	DFA *out = (DFA*)malloc(sizeof(DFA));
	out->nstates=nstates;
	(out->states) = (DFA_State*)malloc(nstates*sizeof(DFA_State));
	for (int i = 0; i < nstates; i++) {
		(out->states + i)->is_accepting = FALSE;
		for (int j=0; j<DFA_NSYMBOLS; j++) {
			((out->states)+i)->transitions[j] = -1;
		}
	}
	out->current_state = 0;
	return out;
}
void DFA_free(DFA *dfa) {
	free(dfa->states);
	free(dfa);
}
void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
	((dfa->states)+src)->transitions[(int)symbol] = dst;
}
void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) {
	while (*str != '\0') {
		DFA_set_transition(dfa, src, *str, dst);
		str++;
	}
}
void DFA_set_transition_all(DFA *dfa, int src, int dst) {
	for (int j=0; j<DFA_NSYMBOLS; j++) {
		((dfa->states)+src)->transitions[j] = dst;
	}
}
int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
	return ((dfa->states)+statenum)->transitions[(int)symbol];
}
int DFA_get_current_state(DFA *dfa) {
	return dfa->current_state;
}
void DFA_set_current_state(DFA *dfa, int statenum) {
	(dfa->current_state) = statenum;
}
int DFA_get_accepting(DFA *dfa, int statenum) {
	return ((dfa->states)+statenum)->is_accepting;
}
void DFA_set_accepting(DFA *dfa, int statenum, int value) {
	(((dfa->states)+statenum)->is_accepting)=value;
}
int DFA_is_accepting(DFA *dfa) {
	return ((dfa->states)+(dfa->current_state))->is_accepting;
}
int DFA_execute(DFA *dfa, char *input) {
	while (*input != '\0') {
		(dfa->current_state) = ((dfa->states) + (dfa->current_state))->transitions[(int)*input];
		if (dfa->current_state == -1) {
			return FALSE;
		}
		input++;
	}
	return DFA_is_accepting(dfa);
}
void DFA_print(DFA *dfa) {
	for (int i = 0; i<dfa->nstates; i++) {
		printf("%s %d: ", "State", i);
		for (int j = 0; j < DFA_NSYMBOLS; j++) {
			if (((dfa->states)+i)->transitions[j] != -1) {
				printf("%c:%d, ", (char)j, ((dfa->states)+i)->transitions[j]);
			}
		}
		printf("\n");
	}
}