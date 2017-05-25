#include <stdio.h>
#include <stdlib.h>
#include "IntSet.c"
#include "nfa.c"
#include "dfa.c"

int main()
{
	//printf("\nDFA 1:\n");
	/*char practice1[] = "ab";
    char practice2[] = "abab";
    char practice3[] = "abc";
    char practice4[] = "das";
	char practice5[] = "a";
	char practice6[] = "abababa5baba";
	char practiceB1[] = "10101";
	char practiceB2[] = "111111111";
	char practiceB3[] = "1000000001";
	char practiceB4[] = "110000100010001010";*/
	int finalstate = 0;
    //FIRST DFA
    /*DFA* dfa = DFA_new(3);
    DFA_set_accepting(dfa, 2, 1);
    DFA_set_transition(dfa, 0, 'a', 1);
    DFA_set_transition(dfa, 1, 'b', 2);
    DFA_print(dfa);
    finalstate = DFA_execute(dfa, practice1);
	printf("Pratice problems DFAa:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = DFA_execute(dfa, practice2);
    printf("practice2 = %d\n", finalstate);
    finalstate = DFA_execute(dfa, practice3);
    printf("practice3 = %d\n", finalstate);
    finalstate = DFA_execute(dfa, practice4);
    printf("practice4 = %d\n", finalstate);
	finalstate = DFA_execute(dfa, practice5);
    printf("practice5 = %d\n", finalstate);
	finalstate = DFA_execute(dfa, practice6);
    printf("practice6 = %d\n", finalstate);
	
	printf("\nDFA 2:\n");
	DFA* dfab = DFA_new(3);
	DFA_set_accepting(dfab, 2, 1);
	DFA_set_transition(dfab, 0, 'a', 1);
	DFA_set_transition(dfab, 1, 'b', 2);
	DFA_set_transition_all(dfab, 2, 2);
	DFA_print(dfab);
	finalstate = DFA_execute(dfab, practice1);
	printf("Pratice problems DFAb:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = DFA_execute(dfab, practice2);
    printf("practice2 = %d\n", finalstate);
    finalstate = DFA_execute(dfab, practice3);
    printf("practice3 = %d\n", finalstate);
    finalstate = DFA_execute(dfab, practice4);
    printf("practice4 = %d\n", finalstate);
	finalstate = DFA_execute(dfab, practice5);
    printf("practice5 = %d\n", finalstate);
	finalstate = DFA_execute(dfab, practice6);
    printf("practice6 = %d\n", finalstate);
	
	printf("\nDFA 3:\n");
	DFA* dfac = DFA_new(2);
	DFA_set_accepting(dfac, 0, 1);
	DFA_set_transition(dfac, 0, '1', 1);
	DFA_set_transition(dfac, 1, '1', 0);
	DFA_set_transition(dfac, 0, '0', 0);
	DFA_set_transition(dfac, 1, '0', 1);
	DFA_print(dfac);
	finalstate = DFA_execute(dfac, practiceB1);
	printf("Pratice problems DFAb:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = DFA_execute(dfac, practiceB2);
    printf("practice2 = %d\n", finalstate);
    finalstate = DFA_execute(dfac, practiceB3);
    printf("practice3 = %d\n", finalstate);
    finalstate = DFA_execute(dfac, practiceB4);
    printf("practice4 = %d\n", finalstate);

	printf("\nDFA 4:\n");
	DFA* dfad = DFA_new(4);
	DFA_set_accepting(dfad, 0, 1);
	DFA_set_transition(dfad, 0, '1', 1);
	DFA_set_transition(dfad, 0, '0', 3);
	DFA_set_transition(dfad, 1, '1', 0);
	DFA_set_transition(dfad, 1, '0', 2);
	DFA_set_transition(dfad, 2, '1', 3);
	DFA_set_transition(dfad, 2, '0', 1);
	DFA_set_transition(dfad, 3, '1', 2);
	DFA_set_transition(dfad, 3, '0', 0);

	
	DFA_print(dfad);
	finalstate = DFA_execute(dfad, practiceB1);
	printf("Pratice problems DFAb:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB2);
    printf("practice2 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB3);
    printf("practice3 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB4);
    printf("practice4 = %d\n", finalstate);


	printf("\nDFA 5:\n");
	DFA* dfad = DFA_new(4);
	DFA_set_accepting(dfad, 3, 1);
	DFA_set_transition(dfad, 0, '1', 1);
	DFA_set_transition(dfad, 0, '0', 0);
	DFA_set_transition(dfad, 1, '1', 2);
	DFA_set_transition(dfad, 1, '0', 0);
	DFA_set_transition(dfad, 2, '0', 3);
	DFA_set_transition(dfad, 2, '1', 2);
	DFA_set_transition(dfad, 3, '1', 2);
	DFA_set_transition(dfad, 3, '0', 3);

	
	DFA_print(dfad);
	finalstate = DFA_execute(dfad, practiceB1);
	printf("Pratice problems DFAb:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB2);
    printf("practice2 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB3);
    printf("practice3 = %d\n", finalstate);
    finalstate = DFA_execute(dfad, practiceB4);
    printf("practice4 = %d\n", finalstate);*/

	//INT SET TESTING
	/*IntSet *set = IntSet_new();

    printf("set contains 2? %d\n", IntSet_contains(set, 2));

    IntSet_add(set, 1);
    IntSet_add(set, 2);
    IntSet_add(set, 3);
    printf("set = ");
    IntSet_print(set);

    printf("set contains 2? %d\n", IntSet_contains(set, 2));

    IntSet_iterate(set, myfunc);

    IntSet *set2 = IntSet_new();
    IntSet_add(set2, 3);
    printf("set2 = ");
    IntSet_print(set2);
    printf("set contains_all set2? %d\n", IntSet_contains_all(set, set2));
    printf("set equals set2? %d\n", IntSet_equals(set, set2));
    IntSet_add(set2, 2);
    IntSet_add(set2, 1);
    printf("set2 = ");
    IntSet_print(set2);
    printf("set equals set2? %d\n", IntSet_equals(set, set2));

    IntSet_free(set);
    IntSet_free(set2);*/

	//NFA 1
	/*char practice1[] = "manmanman";
	char practice2[] = "man";
	char practice3[] = "jshdkajsdhakjsdman";
	char practice4[] = "sjhdbnasndjjbadkj111";
	NFA* nfa = NFA_new(4);
	NFA_set_accepting(nfa, 3, 1);
	NFA_add_transition(nfa, 0, 'm', 1);
	NFA_add_transition(nfa, 1, 'a', 2);
	NFA_add_transition(nfa, 2, 'n', 3);
	NFA_add_transition_all(nfa, 0, 0);
	finalstate = NFA_execute(nfa, practice1);
	printf("Pratice problems NFA1:\n");
    printf("practice1 = %d\n", finalstate);
    finalstate = NFA_execute(nfa, practice2);
    printf("practice2 = %d\n", finalstate);
    finalstate = NFA_execute(nfa, practice3);
    printf("practice3 = %d\n", finalstate);
    finalstate = NFA_execute(nfa, practice4);
    printf("practice4 = %d\n", finalstate);*/

	char practice5[] = "shington";
	char practice6[] = "wwashington";
	char practice7[] = "wasingtonn";
	
	NFA* nfa2 = NFA_new(20);
	NFA_add_transition_all(nfa2, 0, 0);
	//printf("hey1\n");
	//IntSet_print(NFA_get_transitions(nfa2, 0, 's'));
	NFA_add_transition_all(nfa2, 1, 1);
	NFA_add_transition_all(nfa2, 2, 2);
	NFA_add_transition_all(nfa2, 3, 3);
	NFA_add_transition_all(nfa2, 4, 4);
	NFA_add_transition_all(nfa2, 5, 5);
	NFA_add_transition_all(nfa2, 6, 6);
	//printf("hey2\n");
	//IntSet_print(NFA_get_transitions(nfa2, 0, 's'));
	NFA_add_transition_all(nfa2, 7, 7);
	//printf("hey3\n");
	//IntSet_print(NFA_get_transitions(nfa2, 0, 's'));
	NFA_add_transition_all(nfa2, 8, 8);
	NFA_add_transition_all(nfa2, 9, 9);
	NFA_add_transition_all(nfa2, 10, 10);
	NFA_add_transition_all(nfa2, 11, 11);
	NFA_add_transition_all(nfa2, 12, 12);
	NFA_add_transition_all(nfa2, 13, 13);
	NFA_add_transition_all(nfa2, 14, 14);
	NFA_add_transition_all(nfa2, 15, 15);
	NFA_add_transition_all(nfa2, 16, 16);
	NFA_add_transition_all(nfa2, 17, 17);
	NFA_add_transition_all(nfa2, 18, 18);
	NFA_add_transition_all(nfa2, 19, 19);
	NFA_set_accepting(nfa2, 2, 1);
	NFA_set_accepting(nfa2, 12, 1);
	NFA_set_accepting(nfa2, 4, 1);
	NFA_set_accepting(nfa2, 10, 1);
	NFA_set_accepting(nfa2, 8, 1);
	NFA_set_accepting(nfa2, 14, 1);
	NFA_set_accepting(nfa2, 16, 1);
	NFA_set_accepting(nfa2, 19, 1);
	NFA_add_transition(nfa2, 0, 'a', 1);
	NFA_add_transition(nfa2, 1, 'a', 2);
	NFA_add_transition(nfa2, 0, 's', 11);
	NFA_add_transition(nfa2, 11, 's', 12);
	NFA_add_transition(nfa2, 0, 'g', 3);
	NFA_add_transition(nfa2, 3, 'g', 4);
	NFA_add_transition(nfa2, 0, 'o', 9);
	NFA_add_transition(nfa2, 9, 'o', 10);
	NFA_add_transition(nfa2, 0, 'h', 5);
	NFA_add_transition(nfa2, 5, 'h', 6);
	NFA_add_transition(nfa2, 0, 'i', 7);
	NFA_add_transition(nfa2, 7, 'i', 8);
	NFA_add_transition(nfa2, 0, 't', 13);
	NFA_add_transition(nfa2, 13, 't', 14);
	NFA_add_transition(nfa2, 0, 'w', 15);
	NFA_add_transition(nfa2, 15, 'w', 16);
	NFA_add_transition(nfa2, 0, 'n', 17);
	NFA_add_transition(nfa2, 17, 'n', 18);
	NFA_add_transition(nfa2, 18, 'n', 19);


	 finalstate = NFA_execute(nfa2, practice5);
	printf("Pratice problems NFA1:\n");
    printf("practice5 = %d\n", finalstate);
    finalstate = NFA_execute(nfa2, practice6);
    printf("practice6 = %d\n", finalstate);
    finalstate = NFA_execute(nfa2, practice7);
    printf("practice7 = %d\n", finalstate);

	DFA* dfa = DFA_construct(nfa2);
	DFA_execute(dfa, "wwashington");



	/*
    NFA* nfa = NFA_new(4);
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'm', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition(nfa, 2, 'n', 3);
    NFA_set_accepting(nfa, 3, true);
    DFA* dfa = DFA_construct(nfa);
    //DFA_print(dfa);
    printf("\n%d\n", DFA_execute(dfa, "man"));
	*/
    return 0;
}