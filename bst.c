#include "bst.h"
#include <string.h>

// Insert a new node into the BST funtion
//funtion gets called during populating the tree where the values generated 
//are passed to this funtion whihc then assigns to the node
struct Data* insert(struct Data* node, const char* date, float temp, float humidity) {
    if (node == NULL) { //if there is a node 
        struct Data* newNode = (struct Data*)malloc(sizeof(struct Data)); //make a new node using malloc
        strcpy(newNode->date, date);  // Copy the date string inputed to funtion to node date
        newNode->temp = temp;//set the temp passed to funtion to node temp
        newNode->humidity = humidity; //set humidity passed from the funtion to nodes humidity
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (strcmp(date, node->date) < 0) { // Compare strings 
        node->left = insert(node->left, date, temp, humidity);
    } else if (strcmp(date, node->date) > 0) {
        node->right = insert(node->right, date, temp, humidity);
    }

    return node;
}

// Search for a node in the BST by date.
//recursivly search tree by comparing seached date to date at each node
struct Data* search(struct Data* root, const char* date) {
    if (root == NULL || strcmp(root->date, date) == 0) // if no node do nothing
        return root;
    if (strcmp(date, root->date) < 0) // compare search date to root. if  smaller search left tree cus smaller numbers stored in left side
        return search(root->left, date); //if search date is larger search right subtree
    return search(root->right, date);
}
