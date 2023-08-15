
#include "hashmap.h"






/*calculate the hash value of a given string using the djb2 hash algorithm*/
unsigned int hash(const char* str){
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % MAX_SIZE;
}

/*initialize all elements in the hashmap to empty strings*/
void initializeHashMap(HashMap* hm){
    int i;
    for (i=0; i<MAX_SIZE; i++) {
        strcpy(hm->table[i].key, "");   
        strcpy(hm->table[i].value, ""); 
    }
}




/*insert a new key-value pair into the hashmap*/
void insertElement(HashMap* hm, const char* key, const char* value){
    unsigned int index = hash(key);
    while (strcmp(hm->table[index].key, "") != 0){
        index = (index + 1) % MAX_SIZE; 
    }
    strcpy(hm->table[index].key, key);
    strcpy(hm->table[index].value, value);
}

/*get the value associated with a given key from the hashmap*/
const char* getValue(HashMap* hm, const char* key){
    unsigned int index = hash(key);
    while (strcmp(hm->table[index].key, key) != 0){
        index = (index + 1) % MAX_SIZE; 
        if (strcmp(hm->table[index].key, "") == 0){
            return NULL; 
        }
    }
    return hm->table[index].value;
}

/*free the memory used by the hashmap by resetting keys and values to empty strings*/
void freeHashMap(HashMap* hm){
    int i;
    for (i=0; i<MAX_SIZE; i++) {
        strcpy(hm->table[i].key, "");
        strcpy(hm->table[i].value, "");
    }
}

