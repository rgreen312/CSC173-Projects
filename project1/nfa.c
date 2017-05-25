/*
 * nfa.c
 *
 *  Created on: Jan 27, 2017
 *      Author: striest
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nfa.h"
#include "dfa.h"
#include "IntSet.h"

NFA* NFA_new(int nstates) {
	NFA* out = (NFA*) malloc(sizeof(NFA*));
		out->nstates = nstates;
		out->states = (NFA_State*) malloc(nstates * sizeof(NFA_State*));
		for (int i = 0; i < nstates; i++) {
			(out->states + i)->is_accepting = false;
			for (int j = 0; j < NFA_NSYMBOLS; j++) {
				(out->states + i)->transitions[j] = IntSet_new2(nstates);
				IntSet_add((out->states + i)->transitions[j], -1);
			}
		}
		out->current_states = IntSet_new();
		IntSet_add(out->current_states, 0);
		return out;
}
void NFA_free(NFA* nfa){
	for(int i = 0; i < NFA_get_size(nfa); i++){
	    for(int j = 0; j < NFA_NSYMBOLS; j++){
	      IntSet_free(nfa->states[i].transitions[j]);
		}
	}
}
int NFA_get_size(NFA* nfa){
	return sizeof(nfa);
}
IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return ((nfa->states) + statenum)->transitions[(int) symbol];
}
void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
	IntSet_add(((nfa->states) + src)->transitions[(int) symbol], dst);
}
void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
	while (*str != '\0') {
			NFA_add_transition(nfa, src, *str, dst);
			str++;
		}
}
void NFA_add_transition_all(NFA *nfa, int src, int dst) {
	for (int j = 0; j < NFA_NSYMBOLS; j++) {
			IntSet_add((nfa->states + src)->transitions[j], dst);
	}
}
IntSet *NFA_get_current_states(NFA *nfa) {
	return nfa->current_states;
}
void NFA_set_current_states(NFA *nfa, IntSet *states) {
	nfa->current_states = states;
}
void NFA_set_current_state(NFA *nfa, int state) {
	IntSet* temp = IntSet_new();
	IntSet_add(temp, 0);
	nfa->current_states = temp;
}
bool NFA_get_accepting(NFA *nfa, int statenum) {
	return (nfa->states + statenum)->is_accepting;
}
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
	(nfa->states + statenum)->is_accepting = value;
}
bool NFA_is_accepting(NFA *nfa){
	IntSetIterator* iter = IntSet_iterator(nfa->current_states);
	while(IntSetIterator_has_next(iter)) {
		if(NFA_get_accepting(nfa, IntSetIterator_next(iter))) {
			free(iter);
			return true;
		}
	}
	free(iter);
	return false;
}
bool NFA_execute(NFA *nfa, char *input) {
	while (*input != '\0') {
		IntSet* temp = IntSet_new();
		//make an iterator to go through the current states
		IntSetIterator* iter = IntSet_iterator(nfa->current_states);
		while (IntSetIterator_has_next(iter)) {
			//iterator for the transitions on each row of the table
			IntSetIterator* iter2 = IntSet_iterator(
					NFA_get_transitions(nfa, IntSetIterator_next(iter),*input));
			while (IntSetIterator_has_next(iter2)) {
				int entry = IntSetIterator_next(iter2);
				if (!(IntSet_contains(temp, entry)) && (entry >= 0) && (entry < nfa->nstates)) {
					IntSet_add(temp, entry);
				}
			}
			free(iter2);
		}
		free(iter);
		free(nfa->current_states);
		nfa->current_states = temp;
		input++;
		printf("Current States:");
		IntSet_print(nfa->current_states);

	}
	return NFA_is_accepting(nfa);
}
void NFA_reset(NFA* nfa) {
	IntSet* temp = IntSet_new();
	IntSet_add(temp, 0);
	free(nfa->current_states);
	nfa->current_states = temp;
}
DFA* DFA_construct(NFA* nfa) {
	int size = (int)pow(2, nfa->nstates);
	DFA* out = DFA_new(size);
	//IntSet* stateTable = (IntSet**)malloc(out->nstates * sizeof(IntSet_new2(out->nstates)));
	IntSet** stateTable = malloc(size*sizeof(IntSet*)); //this is an array of intsets to keep track of the set of states the node refers to. Links with the indexes of the dfa..
	//printf("%s\n", "test1");
	for(int i = 0; i < size; i++) {
		//printf("%d\n", i);
		stateTable[i] = IntSet_new2(1);
	}
	//printf("%s\n", "test");
	IntSet_add(stateTable[0], 0);
	for (int i = 0; i < (int)pow(2, nfa->nstates); i++) {
		printf("%d\n", i);
		if (IntSet_is_empty(stateTable[i])) {
			//printf("%d\n", i);
			break;
		}

		// run through all the transitions in all the previous states to get the new states
		// run though the alphabet first, then run though the states in the node.
		for (int j = 0; j < NFA_NSYMBOLS; j++) {
			IntSet* temp = IntSet_new();
			//loop through the states in the spot on the statetable
			IntSetIterator* iter1 = IntSet_iterator(stateTable[i]);
			while (IntSetIterator_has_next(iter1)) {
				//loop through the transitions at that character
				IntSetIterator* iter2 = IntSet_iterator(NFA_get_transitions(nfa, IntSetIterator_next(iter1),(char) j));
				while (IntSetIterator_has_next(iter2)) {
					int entry = IntSetIterator_next(iter2);
					if (!(IntSet_contains(temp, entry)) && (entry >= 0) && (entry < nfa->nstates)) {
						IntSet_add(temp, entry);
					}
				}
				//free(iter2);
			}
			//free(iter1);
			//printf("Temp: ");
			//IntSet_print(temp);
			//finds the corresponding DFA state for the set of NFA states
			//generated and creates the proper transition.
			for (int k = 0; k < (int)pow(2, nfa->nstates); k++) {
				if (IntSet_is_empty(stateTable[k])) {
					DFA_set_transition(out, i, (char) j, k);
					stateTable[k] = temp;
					break;
				}
				//printf("%c\n",(char)j);
				//printf("k = %i\n", i);
				//IntSet_print(stateTable[k]);
				//printf("\n");
				if (IntSet_equals(temp, stateTable[k])) {
					DFA_set_transition(out, i, (char) j, k);
					break;
				}
			}
		}
		
		// for(int i = 0; i < (int)pow(2, nfa->nstates); i++) {
		// 	IntSet_print(stateTable[i]);
		// }
	}

	//marks the states as accepting
	//printf("marking accepting\n");
	for (int i = 0; i < nfa->nstates; i++) {
		if ((nfa->states + i)->is_accepting) {
			for (int j = 0; j < (int)pow(2, nfa->nstates); j++) {
				if(IntSet_is_empty(stateTable[j])) {
					break;
				}
				if(IntSet_contains(stateTable[j], i)) {
					(out->states + j)->is_accepting = TRUE;
				}
			}
		}
	}
	printf("done\n");
	return out;
}