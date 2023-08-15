

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1023

typedef struct {
    char key[50];
    char value[50];
} HashMapElement;


typedef struct {
    HashMapElement table[MAX_SIZE];
} HashMap;



unsigned int hash(const char* str);
void initializeHashMap(HashMap* hm);
void insertElement(HashMap* hm, const char* key, const char* value);
const char* getValue(HashMap* hm, const char* key);
void freeHashMap(HashMap* hm);



#endif