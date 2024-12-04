#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdio.h>

struct Data {
    char date[11]; // Date string in xx-xx-xxxx format
    float temp;
    float humidity;
    struct Data* left;
    struct Data* right;
};
//a few funtions
struct Data* insert(struct Data* node, const char* date, float temp, float humidity);
struct Data* search(struct Data* root, const char* date); 
#endif 

