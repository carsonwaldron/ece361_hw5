#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <math.h>
#include <time.h>
#include "float_rndm.h"
#include "iom361_r2.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters until newline or end of file
    }
}

void printTree(struct Data* root, int space) { // Function to print the tree

    if (root == NULL) //if no root do nothing
        return;

    space += 10; //spaces so tree easieer to read

    printTree(root->right, space); //prints the right side of the tree

    printf("\n");
    for (int i = 10; i < space; i++) //shows current nodes values (temp,hum,time)
        printf(" ");
    printf("%s (%.1f, %.1f)\n", root->date, root->temp, root->humidity);

    printTree(root->left, space); // now do the left side
}

// Populate the BST with random dates and data
struct Data* populateTree(struct Data* root, int numDates) {
    time_t now = time(NULL);//get current time
    struct tm randomDate = *localtime(&now); // convert current time to struct tm
    randomDate.tm_mon = 0;  // January 
    randomDate.tm_year = 2024-2024; // 2024 

    char formattedDate[11]; // Buffer for formatted date
    for (int i = 0; i < numDates; i++) {
        randomDate.tm_mday = rand() % 31 + 1; // random day in January 
        mktime(&randomDate); // Normalize the date

        // format  date as a string
        strftime(formattedDate, sizeof(formattedDate), "%m-%d-%Y", &randomDate);

        // generatse random temp and humidity same as other hw
        float temp = float_rand_in_range(20.0, 30.0);
        float humid = float_rand_in_range(30.0, 90.0);

         
        root = insert(root, formattedDate, temp, humid);// inserts the date, temp,humidty into BST node
    }
    return root;
}


void inOrderTraversal(struct Data* root) {
    if (root == NULL) //if theres no root exit
        return;
    inOrderTraversal(root->left); //left subtree first
    printf("timestamp: %s, Temp: %.1f, Humidity: %.1f\n", root->date, root->temp, root->humidity); //prints the current node data
    inOrderTraversal(root->right); //right subtree second
}

int main() {
    struct Data* root = NULL; // creates an empty BST
    int numNodes = 31; // number of nodes to generate (one for each day in January)
    root = populateTree(root, numNodes); // calls populate tree function to populate tree with data

    printTree(root, 0); // call function to print the whole tree

    char search_date[11]; // Buffer to store the date user is searching for
    while (1) { // infinite loop to repeat
        printf("enter the date to search for in this exact form -> (MM-DD-YYYY) (or press Enter to quit): ");
        
        if (fgets(search_date, sizeof(search_date), stdin) == NULL) {
            printf("Error reading input\n");
            break;
        }
        
        search_date[strcspn(search_date, "\n")] = '\0'; //remove newline character

        if (strlen(search_date) == 0) {//if no character input quit
            printf("done\n");
            break;
        }

        struct Data* result = search(root, search_date); // call search function
        if (result != NULL) {
            printf("the date you searched for has the following\n");
            printf("Timestamp: %s, Temp: %.2f, Humidity: %.2f\n\n", result->date, result->temp, result->humidity);
        } else {
            printf("Date not found.\n\n");
        }

        clearInputBuffer();
    }

    printf("in order traversal:\n");
    inOrderTraversal(root); // call in order traversal function

    return 0;
}
