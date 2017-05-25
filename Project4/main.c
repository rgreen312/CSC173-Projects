/*
Created by:
William Wilson
Sam Triest
Ryan Green

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

/***********************************************************/
//General Functions

// Taken from: https://github.com/fragglet/c-algorithms/blob/master/src/hash-string.c

//------------
//Hashing functions below
//------------
unsigned int string_hash(void *string) {
	/* This is the djb2 string hash function */

	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result;
}
int Hash(int id) {
	return abs(id % 1009);
}



/***********************************************************/
//-------------------------------------
//             CSG TABLE
//-------------------------------------
typedef struct CSG{
	char* Course;
	int StudentId;
	char* Grade;
	struct CSG* next;
} CSG;

CSG* CSG_new(char* course, int id, char* grade){
	CSG* out = (CSG*) malloc(sizeof(CSG));
	out->Course = course;
	out->StudentId = id;
	out->Grade = grade;
	out->next = NULL;
	return out;
}

void CSG_print(CSG* csg){
    if (csg == NULL) {
        printf("CSG printed is NULL\n");
        return;
    }
	printf("{%s, %d, %s}, ", csg->Course, csg->StudentId, csg->Grade);
	if(csg->next != NULL) {
		CSG_print(csg->next);
	}
}

typedef struct CSGTable{
	CSG* table[1009];
} CSGTable;

CSG* CSG_back_of_list(CSG* in){
	if(in->next == NULL){
		return in;
	} else {
		return CSG_back_of_list(in->next);
	}
}

CSG* CSG_list_search(int id, CSG* list, CSG* acc){
	if(list == NULL) {
		return acc;
	} else {
		if(list->StudentId == id){
			acc = CSG_new(list->Course, list->StudentId, list->Grade);
			acc->next = CSG_list_search(id, list->next, acc->next);
			return acc;
		} else {
			acc = CSG_list_search(id, list->next, acc);
			return acc;
		}
	}
}
CSG* CSG_lookup(int id, CSGTable* table){
	int hashval = Hash(id);
	CSG* out = CSG_list_search(id, table->table[hashval], NULL);
	return out;
}
void CSG_insert(CSG* in, CSGTable* table){
    if (CSG_lookup(in->StudentId, table) == NULL) {


		int hashval = Hash(in->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = in;
		} else {
			CSG_back_of_list(table->table[hashval])->next = in;
		}
	} else {
        if(strcmp(CSG_lookup(in->StudentId, table)->Course, in->Course)!=0){
            int hashval = Hash(in->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = in;
		} else {
			CSG_back_of_list(table->table[hashval])->next = in;
		}
        }
	}
}


void CSGTable_print(CSGTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CSG_print(table->table[i]);
			printf("\n");
		}
	}
}

CSGTable* CSGTable_new(){
	CSGTable* out = (CSGTable*) malloc(sizeof(CSGTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

void CSG_delete_h(int id, char* course, CSG* list) {
	if(list->next == NULL){
		return;
	} else if(list->next->StudentId == id && strcmp((list->next)->Course, course)== 0){
		list->next = list->next->next;
		CSG_delete_h(id, course, list->next);
		return;
	} else {
		CSG_delete_h(id, course, list->next);
	}
}

void CSG_delete(int id, char* course, CSGTable* table) {
	int hashval = Hash(id);
	if((table->table[hashval])->StudentId == id && strcmp((table->table[hashval])->Course, course)== 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CSG_delete_h(id, course, table->table[hashval]);
	}
}
CSGTable* CSG_Selection(CSGTable* table, char* attribute, char* search) {
        CSGTable* newTable = CSGTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CSG_insert(CSG_new(table->table[i]->Course, table->table[i]->StudentId, table->table[i]->Grade), newTable);
                                }
                                CSG* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CSG_insert(CSG_new(element->Course, element->StudentId, element->Grade), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "student")==0) {
                int sid = atoi(search);
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (sid==table->table[i]->StudentId) {
                                        CSG_insert(CSG_new(table->table[i]->Course, table->table[i]->StudentId, table->table[i]->Grade), newTable);
                                }
                                CSG* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (sid==element->StudentId) {
                                                CSG_insert(CSG_new(element->Course, element->StudentId, element->Grade), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END CSG TABLE------------------------


/***********************************************************/
//-------------------------------------
//             SNAP TABLE
//-------------------------------------
typedef struct SNAP {
	int StudentId;
	char* Name;
	char* Address;
	int Phone;
	struct SNAP* next;
}SNAP;

void SNAP_print(SNAP* snap){
    if (snap == NULL) {
        printf("SNAP printed is NULL\n");
        return;
    }
	printf("{%d, %s, %s, %d}, ", snap->StudentId, snap->Name, snap->Address, snap->Phone);
	if(snap->next != NULL) {
		SNAP_print(snap->next);
	}
}

SNAP* SNAP_new(int id, char* name, char* address, int phone) {
	SNAP* out = (SNAP*) malloc(sizeof(SNAP));
	out->StudentId = id;
	out->Name = name;
	out->Address = address;
	out->Phone = phone;
	out->next = NULL;
	return out;
}

typedef struct SNAPTable{
	SNAP* table[1009];
} SNAPTable;

SNAPTable* SNAPTable_new(){
	SNAPTable* out = (SNAPTable*) (malloc(sizeof(SNAPTable)));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

SNAP* SNAP_list_search(int id, SNAP* list, SNAP* acc){
	if(list == NULL) {
		return acc;
	} else {
		if(list->StudentId == id){
			acc = SNAP_new(list->StudentId, list->Name, list->Address, list->Phone);
			acc->next = SNAP_list_search(id, list->next, acc->next);
			return acc;
		} else {
			acc = SNAP_list_search(id, list->next, acc);
			return acc;
		}
	}
}

SNAP* SNAP_lookup(int id, SNAPTable* table) {
	int hashval = Hash(id);
	SNAP* out = SNAP_list_search(id, table->table[hashval], NULL);
	return out;
}


SNAP* SNAP_back_of_list(SNAP* in){
	if(in->next == NULL){
		return in;
	} else {
		return SNAP_back_of_list(in->next);
	}
}

void SNAP_insert(SNAP* in, SNAPTable* table){
	if(SNAP_lookup(in->StudentId, table) == NULL){
		int hashval = Hash(in->StudentId);
		if(table->table[hashval] == NULL){
			table->table[hashval] = in;
		} else {
			SNAP_back_of_list(table->table[hashval])->next = in;
		}
	}
}

void SNAP_delete_h(int id, SNAP* list) {
	if(list->next == NULL){
		return;
	} else if(list->next->StudentId == id){
		list->next = list->next->next;
		SNAP_delete_h(id, list->next);
		return;
	} else {
		SNAP_delete_h(id, list->next);
	}
}

void SNAP_delete(int id, SNAPTable* table) {
	int hashval = Hash(id);
	if((table->table[hashval])->StudentId == id){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		SNAP_delete_h(id, table->table[hashval]);
	}
}

void SNAPTable_print(SNAPTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
            printf("%d: ", i);
            SNAP_print(table->table[i]);
            printf("\n");
		}
	}
}

SNAPTable* SNAP_Selection(SNAPTable* table, char* attribute, char* search) {
        SNAPTable* newTable = SNAPTable_new();
        if (strcmp(attribute, "name")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Name, search) == 0) {
                                        SNAP_insert(SNAP_new(table->table[i]->StudentId, table->table[i]->Name, table->table[i]->Address, table->table[i]->Phone), newTable);
                                }
                                SNAP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Name, search) == 0) {
                                                SNAP_insert(SNAP_new(element->StudentId, element->Name, element->Address, element->Phone), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "student")==0) {
                int sid = atoi(search);
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (sid==table->table[i]->StudentId) {
                                        SNAP_insert(SNAP_new(table->table[i]->StudentId, table->table[i]->Name, table->table[i]->Address, table->table[i]->Phone), newTable);
                                }
                                SNAP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (sid==element->StudentId) {
                                                SNAP_insert(SNAP_new(element->StudentId, element->Name, element->Address, element->Phone), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END SNAP TABLE------------------------


/***********************************************************/
//-------------------------------------
//             CP TABLE
//-------------------------------------
typedef struct CP {
	char* Course;
	char* Prerequisite;
	struct CP* next;
} CP;

typedef struct CPTable{
	CP* table[1009];
} CPTable;

CP* CP_new(char* course, char* prerequisite) {
	CP* out = (CP*) malloc(sizeof(CP));
	out->Course = course;
	out->Prerequisite = prerequisite;
	out->next = NULL;
	return out;
}
void CP_print(CP* cp){
    if (cp == NULL) {
        printf("CP printed is NULL\n");
        return;
    }
	printf("{%s, %s}, ", cp->Course, cp->Prerequisite);
	if(cp->next != NULL) {
		CP_print(cp->next);
	}
}
CP* CP_back_of_list(CP* in){
	if(in->next == NULL){
		return in;
	} else {
		return CP_back_of_list(in->next);
	}
}
void CP_insert(CP* in, CPTable* table){
	int hashval = Hash(string_hash(in->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		CP_back_of_list(table->table[hashval])->next = in;
	}
}
CP* CP_list_search(char* course, CP* list, CP* acc){
	if(list == NULL) {
		return acc;
	} else {
		if(strcmp(list->Course, course)==0) {
			acc = CP_new(list->Course, list->Prerequisite);
			acc->next = CP_list_search(course, list->next, acc->next);
			return acc;
		} else {
			acc = CP_list_search(course, list->next, acc);
			return acc;
		}
	}
}
CP* CP_lookup(char* course, CPTable* table){
	int hashval = Hash(string_hash(course));
	CP* out = CP_list_search(course, table->table[hashval], NULL);
	return out;
}
void CPTable_print(CPTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CP_print(table->table[i]);
			printf("\n");
		}
	}
}
CPTable* CPTable_new(){
	CPTable* out = (CPTable*) malloc(sizeof(CPTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

void CP_delete_h(char* course, CP* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CP_delete_h(course, list->next);
		return;
	} else {
		CP_delete_h(course, list->next);
	}
}

void CP_delete(char* course, CPTable* table) {
	int hashval = Hash(string_hash(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CP_delete_h(course, table->table[hashval]);
	}
}

CPTable* CP_Selection(CPTable* table, char* attribute, char* search) {
        CPTable* newTable = CPTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CP_insert(CP_new(table->table[i]->Course, table->table[i]->Prerequisite), newTable);
                                }
                                CP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CP_insert(CP_new(element->Course, element->Prerequisite), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "prerequisite")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Prerequisite, search) == 0) {
                                        CP_insert(CP_new(table->table[i]->Course, table->table[i]->Prerequisite), newTable);
                                }
                                CP* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Prerequisite, search) == 0) {
                                                CP_insert(CP_new(element->Course, element->Prerequisite), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END CP TABLE------------------------


/***********************************************************/
//-------------------------------------
//             CDH TABLE
//-------------------------------------
typedef struct CDH {
	char* Course;
	char* Day;
	char* Hour;
	struct CDH* next;
} CDH;
typedef struct CDHTable{
	CDH* table[1009];
} CDHTable;

CDH* CDH_new(char* course, char* day, char* hour) {
	CDH* out = (CDH*) malloc(sizeof(CDH));
	out->Course = course;
	out->Day = day;
	out->Hour = hour;
	out->next = NULL;
	return out;
}
void CDH_print(CDH* cdh){
    if (cdh == NULL) {
        printf("CDH printed is NULL\n");
        return;
    }
	printf("{%s, %s, %s}, ", cdh->Course, cdh->Day, cdh->Hour);
	if(cdh->next != NULL) {
		CDH_print(cdh->next);
	}
}
CDH* CDH_back_of_list(CDH* in){
	if(in->next == NULL){
		return in;
	} else {
		return CDH_back_of_list(in->next);
	}
}
void CDH_insert(CDH* in, CDHTable* table){
	int hashval = Hash(string_hash(in->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		CDH_back_of_list(table->table[hashval])->next = in;
	}
}
CDH* CDH_list_search(char* course, CDH* list, CDH* acc){
	if(list == NULL) {
		return acc;
	} else {
		if(strcmp(list->Course, course)==0) {
			acc = CDH_new(list->Course, list->Day, list->Hour);
			acc->next = CDH_list_search(course, list->next, acc->next);
			return acc;
		} else {
			acc = CDH_list_search(course, list->next, acc);
			return acc;
		}
	}
}
CDH* CDH_lookup(char* course, CDHTable* table){
	int hashval = Hash(string_hash(course));
	CDH* out = CDH_list_search(course, table->table[hashval], NULL);
	return out;
}
void CDHTable_print(CDHTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CDH_print(table->table[i]);
			printf("\n");
		}
	}
}
CDHTable* CDHTable_new(){
	CDHTable* out = (CDHTable*) malloc(sizeof(CDHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

void CDH_delete_h(char* course, CDH* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CDH_delete_h(course, list->next);
		return;
	} else {
		CDH_delete_h(course, list->next);
	}
}
void CDH_delete(char* course, CDHTable* table) {
	int hashval = Hash(string_hash(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CDH_delete_h(course, table->table[hashval]);
	}
}

CDHTable* CDH_Selection(CDHTable* table, char* attribute, char* search) {
        CDHTable* newTable = CDHTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "day")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Day, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Day, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "hour")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Hour, search) == 0) {
                                        CDH_insert(CDH_new(table->table[i]->Course, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Hour, search) == 0) {
                                                CDH_insert(CDH_new(element->Course, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END CDH TABLE------------------------



/***********************************************************/
//-------------------------------------
//             CR TABLE
//-------------------------------------
typedef struct CR {
	char* Course;
	char* Room;
	struct CR* next;
} CR;

typedef struct CRTable{
	CR* table[1009];
} CRTable;

CR* CR_new(char* course, char* room) {
	CR* out = (CR*) malloc(sizeof(CR));
	out->Course = course;
	out->Room = room;
	out->next = NULL;
	return out;
}
void CR_print(CR* cr){
    if (cr == NULL) {
        printf("CR printed is NULL\n");
        return;
    }
	printf("{%s, %s}, ", cr->Course, cr->Room);
	if(cr->next != NULL) {
		CR_print(cr->next);
	}
}
CR* CR_back_of_list(CR* in){
	if(in->next == NULL){
		return in;
	} else {
		return CR_back_of_list(in->next);
	}
}
void CR_insert(CR* in, CRTable* table){
	int hashval = Hash(string_hash(in->Course));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		CR_back_of_list(table->table[hashval])->next = in;
	}
}
CR* CR_list_search(char* course, CR* list, CR* acc){
	if(list == NULL) {
		return acc;
	} else {
		if(strcmp(list->Course, course)==0) {
			acc = CR_new(list->Course, list->Room);
			acc->next = CR_list_search(course, list->next, acc->next);
			return acc;
		} else {
			acc = CR_list_search(course, list->next, acc);
			return acc;
		}
	}
}
CR* CR_lookup(char* course, CRTable* table){
	int hashval = Hash(string_hash(course));
	CR* out = CR_list_search(course, table->table[hashval], NULL);
	return out;
}
void CRTable_print(CRTable* table){
	for(int i = 0; i< 1009; i++){
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CR_print(table->table[i]);
			printf("\n");
		}
	}
}
CRTable* CRTable_new(){
	CRTable* out = (CRTable*) malloc(sizeof(CRTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}

void CR_delete_h(char* course, CR* list) {
	if(list->next == NULL){
		return;
	} else if(strcmp(list->next->Course, course) == 0){
		list->next = list->next->next;
		CR_delete_h(course, list->next);
		return;
	} else {
		CR_delete_h(course, list->next);
	}
}
void CR_delete(char* course, CRTable* table) {
	int hashval = Hash(string_hash(course));
	if(strcmp(table->table[hashval]->Course, course) == 0){
		table->table[hashval] = (table->table[hashval])->next;
	} else {
		CR_delete_h(course, table->table[hashval]);
	}
}

CRTable* CR_Selection(CRTable* table, char* attribute, char* search) {
        CRTable* newTable = CRTable_new();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CR_insert(CR_new(table->table[i]->Course, table->table[i]->Room), newTable);
                                }
                                CR* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CR_insert(CR_new(element->Course, element->Room), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "room")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Room, search) == 0) {
                                        CR_insert(CR_new(table->table[i]->Course, table->table[i]->Room), newTable);
                                }
                                CR* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Room, search) == 0) {
                                                CR_insert(CR_new(element->Course, element->Room), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END CR TABLE------------------------


/***********************************************************/
//-------------------------------------
//        DATABASE FUNCTIONS
//-------------------------------------
typedef struct Database {
    CSGTable *CSG;
    SNAPTable *SNAP;
    CPTable *CP;
    CDHTable *CDH;
    CRTable *CR;
}Database;

Database* Database_New() {
	Database *db = (Database *)malloc(sizeof(Database));
	db->CSG = CSGTable_new();
	db->SNAP = SNAPTable_new();
	db->CP = CPTable_new();
	db->CDH = CDHTable_new();
	db->CR = CRTable_new();
	return db;
}

void Database_print(Database* db) {
    printf("Printing database:\n");
    printf("SNAP Table:\n");
    SNAPTable_print(db->SNAP);
    printf("CP Table:\n");
    CPTable_print(db->CP);
    printf("CR Table:\n");
    CRTable_print(db->CR);
    printf("CSG Table:\n");
    CSGTable_print(db->CSG);
    printf("CDH Table:\n");
    CDHTable_print(db->CDH);
    printf("\nDone printing database.");
}


//----------------------------------------------
// DATABASE TO FILE AND READ FROM FILE BELOW
//----------------------------------------------
void database_toFile(Database* database, char* fileName) {
    FILE *f = fopen(fileName, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    const char *text = "Database:";

    fprintf(f, "%s\n", text);


    fprintf(f, "CDH:\n");
    for (int i=0; i<1009; i++) {
        if (database->CDH->table[i] != NULL) {
            CDH* temp = database->CDH->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n%s\n", temp->Course, temp->Day, temp->Hour);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CP:\n");
    for (int i=0; i<1009; i++) {
        if (database->CP->table[i] != NULL) {
            CP* temp = database->CP->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n", temp->Course, temp->Prerequisite);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CR:\n");
    for (int i=0; i<1009; i++) {
        if (database->CR->table[i] != NULL) {
            CR* temp = database->CR->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%s\n", temp->Course, temp->Room);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "CSG:\n");
    for (int i=0; i<1009; i++) {
        if (database->CSG->table[i] != NULL) {
            CSG* temp = database->CSG->table[i];
            while (temp != NULL) {
                fprintf(f, "%s\n%d\n%s\n", temp->Course, temp->StudentId, temp->Grade);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "SNAP:\n");
    for (int i=0; i<1009; i++) {
        if (database->SNAP->table[i] != NULL) {
            SNAP* temp = database->SNAP->table[i];
            while (temp != NULL) {
                fprintf(f, "%d\n%s\n%s\n%d\n", temp->StudentId, temp->Name, temp->Address, temp->Phone);
                temp = temp->next;
            }
        }
    }
    fprintf(f, "End DB\n");
    fclose(f);
}

Database* Database_from_file(char* fileName) {
    Database* db = Database_New();
    FILE *fp;
    char buff[255];
    int typeReading = 0; //0 is nothing, 1 is CDH, 2 is CP, 3 is CR, 4 is CSG, 5 is SNAP
    fp = fopen(fileName, "r");
    while (strcmp(buff, "End DB\n") != 0) {
        char* course = (char*)malloc(sizeof(char)*255);
        char* day = (char*)malloc(sizeof(char)*255);
        char* time = (char*)malloc(sizeof(char)*255);
        char* phone = (char*)malloc(sizeof(char)*255);
        char* prereq = (char*)malloc(sizeof(char)*255);
        char* room = (char*)malloc(sizeof(char)*255);
        char* address = (char*)malloc(sizeof(char)*255);
        char* studentID = (char*)malloc(sizeof(char)*255);
        char* grade = (char*)malloc(sizeof(char)*255);
        char* name = (char*)malloc(sizeof(char)*255);
        int phoneNum = (int)malloc(sizeof(int));
        int idNumber = (int)malloc(sizeof(int));
        fgets(buff, 255, (FILE*)fp);

        if (strcmp(buff, "End DB\n") == 0) {
            break;
        }

        if (strcmp(buff, "CDH:\n")==0) {
            typeReading = 1;
        } else if (strcmp(buff, "CP:\n")==0) {
            typeReading = 2;
        } else if (strcmp(buff, "CR:\n")==0) {
            typeReading = 3;
        } else if (strcmp(buff, "CSG:\n")==0) {
            typeReading = 4;
        } else if (strcmp(buff, "SNAP:\n")==0) {
            typeReading = 5;
        } else {
            //HERE IF DATA BEING INSERTED
            if (typeReading == 1) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(day, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(time, buff);

                //printf("%s-%s-%s\n", course, day, time);

                CDH* newCDH = CDH_new(course, day, time);

                CDH_insert(newCDH, db->CDH);

            } else if (typeReading ==2) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(prereq, buff);

                //printf("%s-%s\n", course, prereq);

                CP* newCP = CP_new(course, prereq);
                CP_insert(newCP, db->CP);

            } else if (typeReading ==3) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(room, buff);

                //printf("%s-%s\n", course, room);

                CR* newCR = CR_new(course, room);
                CR_insert(newCR, db->CR);
            } else if (typeReading ==4) {
                buff[strlen(buff)-1]= '\0';
                strcpy(course, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(studentID, buff);
                idNumber = atoi(studentID);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(grade, buff);

                //printf("%s-%d-%s\n", course, idNumber, grade);

                CSG* newCSG = CSG_new(course, idNumber, grade);

                CSG_insert(newCSG, db->CSG);
            } else if (typeReading == 5) {
                //snap
                //Database_print(db);
                buff[strlen(buff)-1]= '\0';
                strcpy(studentID, buff);
                idNumber = atoi(studentID);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(name, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(address, buff);

                fgets(buff, 255, (FILE*)fp);
                buff[strlen(buff)-1]= '\0';
                strcpy(phone, buff);
                phoneNum = atoi(phone);

                //printf("%d-%s-%s-%d\n", idNumber, name, address, phoneNum);

                SNAP* newSNAP = SNAP_new(idNumber, name, address, phoneNum);

                SNAP_insert(newSNAP, db->SNAP);
            }


        }
    }
    fclose(fp);
    return db;
}
//----------------------------------------------
// DATABASE TO FILE AND READ FROM FILE ABOVE
//----------------------------------------------


/***********************************************************/
/***************CRDH join of CR and CDH*********************/
//-------------------------------------
//            CRDH TABLE
//-------------------------------------
typedef struct CRDH{
	char* Course;
	char* Room;
	char* Day;
	char* Hour;
	struct CRDH* next;
}CRDH;

CRDH* CRDH_new(char* course, char* room, char* day, char* hour){
	CRDH* out = (CRDH*) malloc(sizeof(CRDH));
	out->Course = course;
	out->Room = room;
	out->Day = day;
	out->Hour = hour;
	out->next = NULL;
	return out;
}

void CRDH_print(CRDH* crdh) {
	printf("{%s, %s, %s, %s}, ", crdh->Course, crdh->Room, crdh->Day, crdh->Hour);
	if (crdh->next != NULL) {
		CRDH_print(crdh->next);
	}
}
typedef struct CRDHTable{
	CRDH* table[1009];
}CRDHTable;

void CRDH_join_h(CR* cr_list, CDH* cdh_list, CRDHTable* table);
CRDH* CRDH_back_of_list(CRDH* in);

//CRDH table can only be created from a natural join of CR and CDH, so the new function reflects that
CRDHTable* CRDHTable_new(CRTable* cr_table, CDHTable* cdh_table){
	CRDHTable* out = (CRDHTable*) malloc(sizeof(CRDHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	for(int i = 0; i < 1009; i++){
		for(int j = 0; j < 1009; j++){
			CRDH_join_h(cr_table->table[i], cdh_table->table[j], out);
		}
	}
	return out;
}
CRDHTable* CRDHTable_new2(){
	CRDHTable* out = (CRDHTable*) malloc(sizeof(CRDHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}


void CRDH_insert(CRDH* in, CRDHTable* table){
	int hashval = Hash(string_hash(in->Room));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		CRDH_back_of_list(table->table[hashval])->next = in;
	}
}

CRDH* CRDH_back_of_list(CRDH* in){
	if(in->next == NULL){
		return in;
	} else {
		return CRDH_back_of_list(in->next);
	}
}

void CRDH_join_h(CR* cr_list, CDH* cdh_list, CRDHTable* table){
	while(cr_list != NULL){
		while(cdh_list!= NULL){
			if(strcmp(cr_list->Course, cdh_list->Course) == 0){
				CRDH_insert(CRDH_new(cr_list->Course, cr_list->Room, cdh_list->Day, cdh_list->Hour), table);
			}
			cdh_list = cdh_list->next;
		}
		cr_list = cr_list->next;
	}
}

void CRDHTable_print(CRDHTable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			CRDH_print(table->table[i]);
			printf("\n");
		}
	}
}

CRDHTable* CRDH_Selection(CRDHTable* table, char* attribute, char* search) {
        CRDHTable* newTable = CRDHTable_new2();
        if (strcmp(attribute, "course")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Course, search) == 0) {
                                        CRDH_insert(CRDH_new(table->table[i]->Course, table->table[i]->Room, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CRDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Course, search) == 0) {
                                                CRDH_insert(CRDH_new(element->Course, element->Room, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        else if (strcmp(attribute, "room")==0) {
                for (int i = 0; i < 1009; i++){
                        if (table->table[i] != NULL) {
                                if (strcmp(table->table[i]->Room, search) == 0) {
                                        CRDH_insert(CRDH_new(table->table[i]->Course, table->table[i]->Room, table->table[i]->Day, table->table[i]->Hour), newTable);
                                }
                                CRDH* element = table->table[i];
                                while (element != NULL) {
                                        if (element->next == NULL)
                                                break;
                                        element=element->next;
                                        if (strcmp(element->Room, search) == 0) {
                                                CRDH_insert(CRDH_new(element->Course, element->Room, element->Day, element->Hour), newTable);
                                        }
                                }
                        }
                }
        }
        return newTable;
}
//-----------------------END CRDH TABLE------------------------


/**********************Projection***************************/

//-------------------------------------
//            DH TABLE
//-------------------------------------
typedef struct DH{
	char* Day;
	char* Hour;
	struct DH* next;
} DH;

DH* DH_new(char* day, char* hour){
	DH* out = (DH*) malloc(sizeof(DH));
	out->Day = day;
	out->Hour = hour;
	out->next = NULL;
	return out;
}

void DH_print(DH* dh) {
	printf("{%s, %s}, ", dh->Day, dh->Hour);
	if (dh->next != NULL) {
		DH_print(dh->next);
	}
}

typedef struct DHTable{
	DH* table[1009];
}DHTable;

DHTable* DHTable_new(){
	DHTable* out = (DHTable*) malloc(sizeof(DHTable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}
DH* DH_back_of_list(DH* in){
	if(in->next == NULL){
		return in;
	} else {
		return DH_back_of_list(in->next);
	}
}

void DH_insert(DH* in, DHTable* table){
	int hashval = Hash(string_hash(in->Day));
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		DH_back_of_list(table->table[hashval])->next = in;
	}
}

DHTable* projection_dh(CRDHTable* table, char* column1, char* column2) {
    DHTable* dhtable = DHTable_new();
    for (int i=0; i < 1009; i++) {
        if ((strcmp(column1, "Day")==0 && strcmp(column2, "Hour")==0) || (strcmp(column1, "Hour")==0 && strcmp(column2, "Day")==0)) {
            if (table->table[i] != NULL) {
                //CRDH_print(table->table[i]);
                DH_insert(DH_new(table->table[i]->Day, table->table[i]->Hour), dhtable);

                CRDH* elem = table->table[i];
                //CRDH_print(elem);
                while (elem != NULL) {
                    if (elem->next == NULL)
                            break;
                    elem=elem->next;
                    //CRDH_print(elem);
                    DH_insert(DH_new(elem->Day, elem->Hour), dhtable);
                }
            }
        }
    }
    return dhtable;
}

void DHTable_print(DHTable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL) {
			printf("%d: ", i);
			DH_print(table->table[i]);
			printf("\n");
		}
	}
}
//-----------------------------END DH TABLE----------------------------

//----------------------------------------------------------------------
//-------------------------------------
//            S TABLE
//-------------------------------------
typedef struct S{
	int StudentID;
	struct S* next;
} S;

S* S_new(int studentid){
	S* out = (S*) malloc(sizeof(S));
	out->StudentID = studentid;
	return out;
}

void S_print(S* s) {
	if (s->StudentID < 500000) {
		printf("{%d}, ", s->StudentID);
		if (s->next != NULL) {
			S_print(s->next);
		}
	}
}
typedef struct STable{
	S* table[1009];
}STable;

STable* STable_new(){
	STable* out = (STable*) malloc(sizeof(STable));
	for(int i = 0; i < 1009; i++){
		out->table[i] = NULL;
	}
	return out;
}
S* S_back_of_list(S* in){
	if(in->next == NULL){
		return in;
	} else {
		return S_back_of_list(in->next);
	}
}

void S_insert(S* in, STable* table){
	int hashval = Hash(in->StudentID);
	if(table->table[hashval] == NULL){
		table->table[hashval] = in;
	} else {
		S_back_of_list(table->table[hashval])->next = in;
	}
}

STable* projection_s(CSGTable* table, char* column) {
    STable* stable = STable_new();
    for (int i=0; i < 1009; i++) {
        if (strcmp(column, "StudentId")==0) {
            if (table->table[i] != NULL) {
                //CRDH_print(table->table[i]);
                S_insert(S_new(table->table[i]->StudentId), stable);

                CSG* elem = table->table[i];
                //CRDH_print(elem);
                while (elem != NULL) {
                    if (elem->next == NULL)
                            break;
                    elem=elem->next;
                    //CRDH_print(elem);

                    S_insert(S_new(elem->StudentId), stable);
                }
            }
        }
    }
    return stable;
}

void STable_print(STable* table) {
	for (int i = 0; i < 1009; i++) {
		if (table->table[i] != NULL && table->table[i]->StudentID > 0) {
			printf("%d: ", i);
			S_print(table->table[i]);
			printf("\n");
		}
	}
}
//-----------------------END S TABLE------------------------


/***********************************************************/
//-------------------------------------
//            QUERIES
//-------------------------------------
//Must put student name in single quotes in the query e.g. 'C. Brown'
char* GradeInCourse(char str[], Database* db) {
	//“What grade did StudentName get in Course-Name?”
	char student[50] = "";
	char course[50] = "";
	static char grade[50] = "";
	char *A[] = {"What", "grade", "did", "*", "get", "in", "*"};
	int i = 0;
	int studentid = -1;
	int size = sizeof(A)/sizeof(char *);
	char * pch;
	pch = strtok (str," ?");
	while (pch != NULL) {
		//char *pch2 = pch+1;
		//printf("%s\n", pch);
		//printf ("%s\n",pch);
		//printf("%s\n", A[i]);
		//printf("hey\n");
		if (i > size) {
			printf("fail\n");
			break;
		}
		if (strcmp(A[i], "*")!=0) {
			if (strcmp(A[i], pch)==0){}
			else {return "failed";}
		}
		else {
			if (strcmp(student, "")==0) {
				char temp[50];
				strncpy(temp, pch, strlen(pch));
				if (temp[strlen(pch)-1]=='\'') {
					temp[strlen(pch)-1]='\0';
					strcpy(student, pch);
				}
				else {
					while (temp[strlen(pch)-1]!='\'') {
						//printf("%s\n", pch);
						//printf("%s\n", student);
						if (strcmp(student, "")==0) {
							 char *pch2 = pch+1;
							 strcat(student, pch2);
						}
						else
							strcat(student, pch);
						strcat(student, " ");
						pch = strtok (NULL, " ");
						strncpy(temp, pch, strlen(pch));
						if (pch == NULL)
							return "failed";
					}
					temp[strlen(pch)-1]='\0';
					strcat(student, temp);
				}
			}
			else if (strcmp(course, "")==0) {
				strcpy(course,pch);
			}
			else
				return "failed";
			//printf("%s\n", pch);
		}
		pch = strtok (NULL, " ?");
		//if (pch == NULL)
			//return "failed";
		i++;
	}
	if (strcmp(course, "")!=0) {
		SNAPTable* snapsearch = SNAP_Selection(db->SNAP, "name", student);
		for(int i = 0; i < 1009; i++) {
			if (snapsearch->table[i] != NULL) {
				studentid = snapsearch->table[i]->StudentId;
			}
		}
		if (studentid == -1)
			return "No results found";
		char id[6];
		sprintf(id, "%d", studentid);;
		CSGTable* csgsearch = CSG_Selection(db->CSG, "student", id);
		csgsearch = CSG_Selection(csgsearch, "course", course);
		if (csgsearch->table[Hash(studentid)] == NULL)
			return "No results found";
		strcpy(grade, csgsearch->table[Hash(studentid)]->Grade);
	}
	else
		return "failed";
  return grade;
}
char* LocationAtTime(char str[], Database* db) {
	//“Where is StudentName at Hour on Day?”
	char student[50] = "";
	char hour[50] = "";
	char day[50] = "";
	char course[50] = "";
	static char location[50] = "";
	char *A[] = {"Where", "is", "*", "at", "*", "on", "*"};
	int i = 0;
	int studentid = -1;
	int size = sizeof(A)/sizeof(char *);
	char * pch;
	pch = strtok (str," ?");
	while (pch != NULL) {
		if (i > size) {
			printf("fail\n");
			break;
		}
		if (strcmp(A[i], "*")!=0) {
			if (strcmp(A[i], pch)==0){}
			else {printf("broke"); break;}
		}
		else {
			if (strcmp(student, "")==0) {
				char temp[50];
				strncpy(temp, pch, strlen(pch));
				if (temp[strlen(pch)-1]=='\'') {
					temp[strlen(pch)-1]='\0';
					strcpy(student, pch);
				}
				else {
					while (temp[strlen(pch)-1]!='\'') {
						//printf("%s\n", pch);
						//printf("%s\n", student);
						if (strcmp(student, "")==0) {
							 char *pch2 = pch+1;
							 strcat(student, pch2);
						}
						else
							strcat(student, pch);
						strcat(student, " ");
						pch = strtok (NULL, " ");
						strncpy(temp, pch, strlen(pch));
						if (pch == NULL)
							return "failed";
					}
					temp[strlen(pch)-1]='\0';
					strcat(student, temp);
				}
			}
			else if (strcmp(hour, "")==0) {
				strcpy(hour,pch);
			}
			else if (strcmp(day, "")==0) {
				strcpy(day, pch);
			}
			else
				return "failed";
			//printf("%s\n", pch);
		}
		pch = strtok (NULL, " ?");
		//if (pch == NULL)
			//return "failed";
		i++;
	}
	// printf("\nStudent: %s\n", student);
	// printf("\nHour: %s\n", hour);
	// printf("\nDay: %s\n", day);

	if (strcmp(day, "")!=0) {
		SNAPTable* snapsearch = SNAP_Selection(db->SNAP, "name", student);
		for(int i = 0; i < 1009; i++) {
			if (snapsearch->table[i] != NULL) {
				studentid = snapsearch->table[i]->StudentId;
			}
		}
		if (studentid == -1)
			return "No results found";
		char id[6];
		sprintf(id, "%d", studentid);;
		CSGTable* csgsearch = CSG_Selection(db->CSG, "student", id);
		CDHTable* cdhsearch = CDH_Selection(db->CDH, "hour", hour);
		cdhsearch = CDH_Selection(cdhsearch, "day", day);
		for (int j = 0; j< 1009; j++) {
			if (csgsearch->table[j]!=NULL) {
				CSG* csg2 = csgsearch->table[j];
				while (csg2 != NULL) {
					CDHTable* cdhsearch2 = CDH_Selection(cdhsearch, "course", csg2->Course);
					for (int k = 0; k < 1009; k++) {
						if (cdhsearch2->table[k] != NULL) {
							CDH* cdh2 = cdhsearch2->table[k];
							while (cdh2 != NULL) {
								if (strcmp(cdh2->Day, day)==0 &&
									strcmp(cdh2->Hour, hour)==0) {
									strcpy(course, cdh2->Course);
									break;
								}
								cdh2 = cdh2->next;
							}
						}
					}
					csg2 = csg2->next;
				}
			}
		}
		if (strcmp(course,"")==0) {
			return "No results found";
		}
		else {
			CRTable* crsearch = CR_Selection(db->CR, "course", course);
			for (int i = 0; i < 1009; i++) {
				if (crsearch->table[i] != NULL) {
					strcpy(location, crsearch->table[i]->Room);
				}
			}
		}

	}
	else
		return "failed";

  return location;
}
/***********************************************************/

int main(){

    printf("---------------------------\n          Part1\n---------------------------\n");
    //Database gotten
    Database* db = Database_New();
    printf("Database created.\n\n");

    //Get tables
    SNAPTable* snaptable = db->SNAP;
    CRTable* crtable = db->CR;
    CDHTable* cdhtable = db->CDH;
    CSGTable* csgtable = db->CSG;
    CPTable* cptable = db->CP;
    printf("Got Tables.\n\n");

    //Print database
    Database_print(db);


    printf("Inserting Data...\n");
    //Insert values into tables
    //CSG
    CSG_insert(CSG_new("CS101", 12345, "A"), csgtable);
    CSG_insert(CSG_new("CS101", 67890, "B"), csgtable);
    CSG_insert(CSG_new("EE200", 12345, "C"), csgtable);
    CSG_insert(CSG_new("EE200", 22222, "B+"), csgtable);
    CSG_insert(CSG_new("CS101", 33333, "A-"), csgtable);
    CSG_insert(CSG_new("PH100", 67890, "C+"), csgtable);

    //SNAP
    SNAP_insert(SNAP_new(12345, "C. Brown", "12 Apple St.", 5551234), snaptable);
    SNAP_insert(SNAP_new(67890, "L. Van Pelt", "134 Pear Ave.", 5555678), snaptable);
    SNAP_insert(SNAP_new(22222, "P. Patty", "56 Grape Blvd.", 5559999), snaptable);

    //CP
    CP_insert(CP_new("CS101", "CS100"), cptable);
    CP_insert(CP_new("EE200", "EE005"), cptable);
    CP_insert(CP_new("EE200", "CS100"), cptable);
    CP_insert(CP_new("CS120", "CS101"), cptable);
    CP_insert(CP_new("CS121", "CS120"), cptable);
    CP_insert(CP_new("CS205", "CS101"), cptable);
    CP_insert(CP_new("CS206", "CS121"), cptable);
    CP_insert(CP_new("CS206", "CS205"), cptable);

    //CDH
    CDH_insert(CDH_new("CS101", "M", "9AM"), cdhtable);
    CDH_insert(CDH_new("CS101", "W", "9AM"), cdhtable);
    CDH_insert(CDH_new("CS101", "F", "9AM"), cdhtable);
    CDH_insert(CDH_new("EE200", "Tu", "10AM"), cdhtable);
    CDH_insert(CDH_new("EE200", "W", "1PM"), cdhtable);
    CDH_insert(CDH_new("EE200", "Th", "10AM"), cdhtable);

    //CR
    CR_insert(CR_new("CS101", "Turing Aud."), crtable);
    CR_insert(CR_new("EE200", "25 Ohm Hall"), crtable);
    CR_insert(CR_new("PH100", "Newton Lab."), crtable);
    printf("Inserted Data.\n");

    //Print database after insert
    printf("\n\n-----Print database after inserting data:-----\n\n");
    Database_print(db);

    //--------------
    //Lookup data //
    //--------------
    printf("\n\n\n-----Lookup various data in the table:-----\n");

    //SNAP lookup
    printf("\nSNAP lookup:\n");
    SNAP_print(SNAP_lookup(67890, snaptable)); //lookup 67890
    printf("\n");
    SNAP_print(SNAP_lookup(1, snaptable)); //lookup 1 (not in table)

    //CP lookup
    printf("\nCP lookup:\n");
    CP_print(CP_lookup("EE200", cptable));
    printf("\n");
    CP_print(CP_lookup("CS120", cptable));
    printf("\n");
    CP_print(CP_lookup("EE200", cptable));
    printf("\n");
    CP_print(CP_lookup("CS206", cptable));
    printf("\n");
    CP_print(CP_lookup("CS888", cptable)); //not in table

    //CDH lookup
    printf("\nCDH lookup:\n");
    CDH_print(CDH_lookup("EE200", cdhtable));
    printf("\n");
    CDH_print(CDH_lookup("EE500", cdhtable)); //not in table


    //SENDING TO FILE AND LOADING FROM FILE
    printf("-----Sending to File and Loading from File-----");
    printf("\n\nSending database to file...\n");
    database_toFile(db, "newFile.txt");
    printf("Sent database to file.\n");

    printf("\nMaking new database from file...\n");
    Database* db2 = Database_from_file("newFile.txt");
    printf("Made database from file.\n");

    printf("\n--New database from file printed:--\n\n");
    Database_print(db2);


    //Delete a value from each table and print database again
    printf("\n\n-----Delete a value from each table:-----\n");
    CSG_delete(12345, "CS101", csgtable);
    SNAP_delete(12345, snaptable);
    CDH_delete("EE200", cdhtable);
    CR_delete("CS101", crtable);
    CP_delete("EE200", cptable);
    printf("Deleted a value from each table.\n");
    printf("\n--Print Database after deleting a value from each relation:--\n");

    /*printf("\nRe-inserting some of the data for other tests after...\n");
    CR_insert(CR_new("CS101", "Turing Aud."), crtable);
    SNAP_insert(SNAP_new(12345, "C. Brown", "12 Apple St.", 5551234), snaptable);
    CSG_insert(CSG_new("CS101", 12345, "A"), csgtable);
    CDH_insert(CDH_new("EE200", "Tu", "10AM"), cdhtable);
    CP_insert(CP_new("EE200", "EE005"), cptable);*/

    Database_print(db);
    //--------
    // PART 2
    //--------
    printf("\n\n---------------------------\n          Part2\n---------------------------\n");
    printf("(These query's are run on a seperate database (one made from file) that did not have values deleted)\n");

    printf("\n-----Running the Query 'What grade did C. Brown get in CS101?' as a string input-----\n");
    printf("Result:\n");
    char query1[] = "What grade did \'C. Brown\' get in CS101?";
    printf("%s\n", GradeInCourse(query1, db2));
    printf("\n-----Running the Query 'Where is C. Brown at 9AM on M?' as a string input-----\n");
    printf("Result:\n");
    char query2[] = "Where is \'C. Brown\' at 9AM on M?";
    printf("%s\n", LocationAtTime(query2, db2));

    //------
    //PART 3
    //------
    printf("\n\n---------------------------\n          Part3\n---------------------------\n");
    printf("\n\n-----Selection Testing:-----\n\n");
    printf("Selecting course 'CS101' in CSG table...\n");
    CSGTable_print(CSG_Selection(db2->CSG, "course", "CS101"));

    printf("\nSelecting StudentID '67890' in CSG table...\n");
    CSGTable_print(CSG_Selection(db2->CSG, "student", "67890"));

    printf("\nSelecting name 'P. Patty' from SNAP table...\n");
    SNAPTable_print(SNAP_Selection(db2->SNAP, "name", "P. Patty"));

    printf("\nSelecting course 'EE200' from CP table...\n");
    CPTable_print(CP_Selection(db2->CP, "course", "EE200"));

    printf("\nSelecting prerequisite 'CS101' from CP table...\n");
    CPTable_print(CP_Selection(db2->CP, "prerequisite", "CS101"));

    printf("\nSelecting course 'CS101' from CDH table...\n");
    CDHTable_print(CDH_Selection(db2->CDH, "course", "CS101"));

    printf("\nSelecting day 'M' from CDH table...\n");
    CDHTable_print(CDH_Selection(db2->CDH, "day", "M"));

    printf("\nSelecting hour '1PM' from CDH table...\n");
    CDHTable_print(CDH_Selection(db2->CDH, "hour", "1PM"));

    printf("\nSelecting course 'EE200' from CR table...\n");
    CRTable_print(CR_Selection(db2->CR, "course", "EE200"));

    printf("\nSelecting room 'Newton Lab.' from CR table...\n");
    CRTable_print(CR_Selection(db2->CR, "room", "Newton Lab."));



    //JOIN
    printf("\n\n-----Joining two tables-----\n(in this case, CDH and CR)\n\n");
    CRTable* crJoin = CRTable_new();
	CDHTable* cdhJoin = CDHTable_new();

	CR_insert(CR_new("CS101", "Turing Aud."), crJoin);
	CR_insert(CR_new("EE200", "Ohm Hall"), crJoin);
	CR_insert(CR_new("PH100", "Newton Lab."), crJoin);

	CDH_insert((CDH_new("CS101", "M", "9AM")), cdhJoin);
	CDH_insert((CDH_new("CS101", "W", "9AM")), cdhJoin);
	CDH_insert((CDH_new("CS101", "F", "9AM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "Tu", "10AM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "W", "1PM")), cdhJoin);
	CDH_insert((CDH_new("EE200", "Th", "10AM")), cdhJoin);


	CRDHTable* crdh = CRDHTable_new(crJoin, cdhJoin);
    printf("Result:\n");
	CRDHTable_print(crdh);

	//PROJECTION
	printf("\n-----Testing Projection-----\n(in this case on a CRDH table on columns Day and Hour)\n\n");

    printf("Result:\n");
	DHTable* dhtable = projection_dh(crdh, "Day", "Hour");
	DHTable_print(dhtable);

	//Examples from textbook
	printf("\n-----Many required examples from textbook have already been done, here are the rest-----\n\n");
	printf("\nExample from Fig. 8.13 in textbook:\n");
	printf("(Taking the Projection of studentID from Selection of CS101)\n\n");

	printf("1st step, Selecting course 'CS101' in CSG table...\n\n");
	CSGTable* newTable = CSG_Selection(db2->CSG, "course", "CS101");
    CSGTable_print(newTable);

    printf("\n2nd step, Projecting StudentID exclusively from the table made in 1st step:\n");
    STable* stable = projection_s(newTable, "StudentId");
    STable_print(stable);

    printf("\n\nExample from Fig. 8.15 in textbook:\n");
    printf("(Joining CR and CDH, Selecting Room, and Projecting Day,Hour)\n\n");

    printf("1st step, Already constructed CRDH earlier as test, so using that table:\n");
    CRDHTable_print(crdh);

    printf("\n2nd step, Selecting room='Turing Aud.' from joined relations.\n");
    CRDHTable* crdhSelected = CRDH_Selection(crdh, "room", "Turing Aud.");
    CRDHTable_print(crdhSelected);

    printf("\n3rd step, Projecting 'Day,Hour' from the table generated in 2nd step:\n");
    DHTable_print(projection_dh(crdhSelected, "Day", "Hour"));
}

