#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_SIZE 80

/*

 Vahit Buğra YEŞİLKAYNAK
 150150019
 BIL105E Homework 3

 */

char *nullError;

/* This function asks and sets CCS and returns the size of CCS*/
int set_ccs(char **ccs){

    *ccs= (char *)malloc(MAX_STR_SIZE * sizeof(char)); // Allocating CCS

    printf("Enter CCS: ");

    getchar(); // Clearing the line for fgets
    fgets(*ccs, MAX_STR_SIZE, stdin); // Getting CCS

    int sizeOfStr; // size of CCS
    for(sizeOfStr = 0; *(*ccs + sizeOfStr) != '\n'; ++sizeOfStr){}
    ++sizeOfStr;
    // Now sizeOfStr is the size of CCS after removing newline character

    *(*ccs + sizeOfStr - 1) = '\0'; // Setting the place for \n to \0

    *ccs = (char *)realloc(*ccs, (sizeOfStr) * sizeof(char)); // re-allocation of CCS
    if (*ccs == '\0') {
        return -1;
    } // If realloc is unsuccesful return -1

    return sizeOfStr;
}

/* This function takes a substring from CCS*/
char *sub_string (char *ccs, int begin_index, int end_index){

    int sizeOfStr; // size of CCS
    for(sizeOfStr = 0; *(ccs + sizeOfStr) != '\0'; ++sizeOfStr){}
    ++sizeOfStr;    // This time the CCS I get as argument has no newline character
    // so I incremented sizeOfStr by one

    if ((end_index > sizeOfStr - 1) || (begin_index < 0)) {
        return NULL;
    } // If end_index and begin_index are beyond the limits of the CCS the function
    // returns NULL

    int size = end_index - begin_index + 1; // Size of the substring
    char *temp = (char *)malloc(size * sizeof(char)); // Allocation of the substring

    int count;
    for (count = begin_index; count <= end_index; ++count) {
        *(temp + count - begin_index) = *(ccs + count);
    } // The for loop sets characters in the given interval to temp
    *(temp + count - begin_index) = '\0'; // Then this sets the last character as '\0'
    return temp;
}

/* This function removes a string from CCS*/
char *remove_string(char **ccs, int begin_index, int end_index){

    int sizeOfStr; // size of CCS
    for(sizeOfStr = 0; *(*ccs + sizeOfStr) != '\0'; ++sizeOfStr){}
    ++sizeOfStr;    // This time the CCS I get as argument has no newline character
    // so I incremented sizeOfStr by one

    if ((end_index > sizeOfStr - 1) || (begin_index < 0)) {
        return NULL;
    }  // If end_index and begin_index are beyond the limits of the CCS the function
    // returns NULL

    int size1 = sizeOfStr - (end_index - begin_index + 1); // Size of CCS after removal
    int size2 = end_index - begin_index + 1; // Size of the removed string
    char *temp1 = (char *)malloc(size1 * sizeof(char)); // Allocating temp1
    char *temp2 = (char *)malloc(size2 * sizeof(char)); // Alloctating temp2

    int count;
    for (count = begin_index; count <= end_index; ++count) {
        *(temp2 + count - begin_index) = *(*ccs + count);
    } // Setting the characters in the interval to temp2 this will be the removed string

    for (count = 0; count < begin_index; ++count) {
        *(temp1 + count) = *(*ccs + count);
    }
    for (count = 0; count < sizeOfStr - 1 - end_index; ++count ) {
        *(temp1 + begin_index + count) = *(*ccs + end_index + count + 1);
    } // In this for loop the program is merging the two parts formed after the
    // removal of temp2. It is making it by setting characters one by one
    // to temp 1 after finishing first part it starts setting the second part

    for (count = 0; count < size1; ++count) {
        *(*ccs + count) = *(temp1 + count);
    } // This for loop sets temp1's characters to CCS's
    *(*ccs + count) = '\0'; // Setting the last character as '\0'

    *ccs = (char *)realloc(*ccs, size1 * sizeof(char)); // Re-allocation of CCS

    free(temp1); // Freeing temp1

    return temp2;
}

/* This function inserts a string in CCS and returns the size of CCS*/
int insert_string(char **ccs, char *insert, int begin_index){

    char *copy; // This will be the copy of the CCS for some operations
    int sizeOfStr; // size of CCS
    for(sizeOfStr = 0; *(*ccs + sizeOfStr) != '\0'; ++sizeOfStr){}
    ++sizeOfStr;    // This time the CCS I get as argument has no newline character
    // so I incremented sizeOfStr by one
    int sizeOfIns; // size o insert
    for(sizeOfIns = 0; *(insert + sizeOfIns) != '\0'; ++sizeOfIns){}
    // insert has a newline character at the end of it so I will not increment

    if (begin_index > sizeOfStr - 1) {
        return -1;

    } // If begin index is beyond string limits return -1

    copy = (char *)malloc(sizeOfStr * sizeof(char));

    int count;
    for (count = 0; count < sizeOfStr; ++count) {
        *(copy + count) = *(*ccs + count);
    } // Copy CCS to copy

    *ccs = (char *)realloc(*ccs, (sizeOfStr + sizeOfIns - 1) * sizeof(char));
    // The sum of the sizes of two strings has 2 nulls in it so we decrement it by one

    if (*ccs == '\0') {
        return -1;
    } // If reallocation is unsuccesful return -1

    for (count = 0; count < sizeOfIns - 1; ++count) {
        *(*ccs + count + begin_index) = *(insert + count);
    } // Inserting insert to the BEGIN INDEX

    for (count = 0; count < sizeOfStr - begin_index; ++count) {
        *(*ccs + begin_index + sizeOfIns - 1 + count) = *(copy + count + begin_index);
    } // Adding the rest of the original CCS to CCS

    free(copy); // Freeing the memory space allocated for copy
    return sizeOfStr + sizeOfIns - 1;
}

/* This function finds and replaces a string*/
int replace_string(char **ccs, char *find, char *replace){

    int replacements = 0; // This will hold the number of replacements

    int sizeOfStr; // size of CCS
    for(sizeOfStr = 0; *(*ccs + sizeOfStr) != '\0'; ++sizeOfStr){}
    ++sizeOfStr;    // This time the CCS I get as argument has no newline character

    int sizeOfFind; // size of find
    for(sizeOfFind = 0; *(find + sizeOfFind) != '\0'; ++sizeOfFind){}
    // find has a newline character at the end of it so I will not increment

    int sizeOfRplc; // size of replace
    for(sizeOfRplc = 0; *(replace + sizeOfRplc) != '\0'; ++sizeOfRplc){}
    // replace has a newline character at the end of it so I will not increment



    int bigCount; int littleCount = 0; // bigCount counts CCS little counts find
    int startIndexs[MAX_STR_SIZE]; // An array to store beginning indexes of finds
    int match = 0; // This will be the boolean I will use to find strings
    // While characters keep matching this will be 1
    // for "one" found 'o' in CCS this = 1, 'n' still 1,
    // 'a' this = 0

    for (bigCount = 0; bigCount < sizeOfStr - 1; ++bigCount){ // I'm not interested in null char
        if (*(*ccs + bigCount) == *find){ // If the first char of the find is found in CCS
            match = 1;
        }

        if (match){ // If there is a match
            if (*(*ccs + bigCount) == *(find + littleCount)){ // Check if it still matches
                ++littleCount; // Increment to check next chars
            }
            else{ // If no longer matches set match to 0 and set little count to 0
                match = 0;
                littleCount = 0;
            }
        }

        if (littleCount == sizeOfFind - 1){ // If a match exist for all chars of find then
            ++replacements;                 // This means there is find in that CCS
            startIndexs[replacements - 1] = bigCount - sizeOfFind + 2;
            littleCount = 0; // Setting this to zero or it will skip one char
        } // Store the beginning indices of all finds' in CCS in an integer array
    }
    int i, j;
    for (i = 0; i < replacements; ++i) { // For all find indices
        remove_string(ccs, startIndexs[i], startIndexs[i] + sizeOfFind - 2);
        // This for loop removes finds from CCS
        for (j = i + 1; j < replacements; ++j) {
            startIndexs[j] -= sizeOfFind - 1;
        } // Then for every find removed, shifts the indices after it
    }

    for (i = 0; i < replacements; ++i) { // For all removed find indices
        insert_string(ccs, replace, startIndexs[i]);
        // Inserts replace to the indices
        for(j = i + 1; j < replacements; ++j){
            startIndexs[j] += sizeOfRplc - 1;
        } // Everytime it does shifts the indices
    }
    *ccs = (char *)realloc(*ccs, sizeof(char) * (sizeOfStr - 1 - (sizeOfFind - 1) * replacements + (sizeOfRplc - 1) * replacements + 1));
    // Calculating net char numbers without null then adding the null at the end
    return replacements; // Return the number of replacements
}

/* This function runs the user menu*/
int user_menu(void){
    nullError = "You have to set Current Character Sequence (CCS) before doing any operations!\n";
    int selection = -1; // While selection is -1 the selections will be shown and
    // a selection will be waited from the user
    char *cs; // Defining CCS

    while (selection != 0) { // Unless user sets selection to 0 this function will run

        if (selection == -1) { // Showing selections and waiting for an input
            printf("\n0: Exit the program\n1: Set Current Character Sequence\n2: Get Substring\n");
            printf("3: Remove Substring\n4: Insert\n5: Replace\n\nEnter Your Choice: ");
            scanf("%d", &selection); // Print Main menu then ask for a selection
            printf("\n");
        }

        if(selection == 1){
            set_ccs(&cs); // The function gets and sets CCS
            selection = -1; // After setting program will return to main menu
        }

        if (selection == 2) {
            if (cs == '\0') {
                printf("%s", nullError);
                selection = 1;
            } // If CCS is null give an error and get/set CCS

            else {
                printf("Enter the BEGIN INDEX and END INDEX numbers: ");
                int begin_i, end_i;
                scanf("%d%d", &begin_i, &end_i); // User enters begining index and
                // ending index

                printf("\n");

                char *sub = sub_string(cs, begin_i, end_i); // Substring function

                if (sub == NULL) {
                    printf("Your operation wasn't successful.\n");
                } // The function returns NULL if the operation isn't successful

                printf("CCS: %s\nSubstring(%d, %d): \"%s\"\n", cs, begin_i, end_i, sub);
                // Print CCS and the substring
                free(sub); // Free the memory space allocated for substring
                selection = -1; // After giving substring it return to main menu
            }
        }

        if (selection == 3) {
            if (cs == '\0') {
                printf("%s", nullError);
                selection = 1;
            } // If CCS is null give an error and get/set CCS

            else{
                printf("Enter the BEGIN INDEX and END INDEX numbers: ");
                int begin_i, end_i;
                scanf("%d%d", &begin_i, &end_i); // User enters begining index and
                // ending index

                printf("\n");

                char *removed = remove_string(&cs, begin_i, end_i); // Remove function

                if (removed == NULL) {
                    printf("Your operation wasn't successful.\n");
                } // The function returns NULL if the operation isn't successful

                printf("CCS: %s\nRemoved String(%d, %d): \"%s\"\n", cs, begin_i, end_i,removed);
                // Print new CCS and the removed string
                free(removed); // Free the memory space allocated for the removed string
                selection = -1; // After removing return to the main menu
            }
        }

        if (selection == 4) {
            if (cs == '\0') {
                printf("%s", nullError);
                selection = 1;
            } // If CCS is null give an error and get/set CCS

            else{
                char *insert = (char *)malloc(MAX_STR_SIZE * sizeof(char));
                // Allocation of insert
                printf("Enter a new string for insertion:\n");
                getchar(); // Clearing the line for fgets
                fgets(insert, MAX_STR_SIZE, stdin); // Get insert with newline character
                int begin_index;
                printf("Enter the BEGIN INDEX number where the new string ");
                printf("begins: ");
                scanf("%d", &begin_index); // Get begin_index
                int success = insert_string(&cs, insert, begin_index); // Insertion function

                if (success == -1) {
                    printf("Your operation wasn't successful.\n");
                } // The function returns -1 if the operation isn't successful

                free(insert); // Freeing the memory space allocated for insert
                printf("CCS: %s\n", cs);
                selection = -1; // After insertion return to the main menu
            }
        }

        if (selection == 5) {
            if (cs == '\0') {
                printf("%s", nullError);
                selection = 1;
            } // If CCS is null give an error and get/set CCS

            else{
                char *find = (char *)malloc(MAX_STR_SIZE * sizeof(char));
                char *replace = (char*)malloc(MAX_STR_SIZE * sizeof(char));
                printf("Find what:\n");
                getchar(); // Clearing the line for fgets
                fgets(find, MAX_STR_SIZE, stdin); // Takes the string to be replaced
                printf("Replace with:\n");
                fgets(replace, MAX_STR_SIZE, stdin); // Takes the string to be replaced with
                int replacement = replace_string(&cs, find, replace); // Number of replacements
                free(find); free(replace); // Free the allocated space for find, replace
                printf("There were %d replacement.\nCCS: \"%s\"\n", replacement, cs);
                selection = -1; // After replacement return to the main menu
            }
        }
    } // End of while
    printf("Goodbye!\n");
    return 0;
} // End of function

int main(void){
    user_menu(); // Calls the main menu function
}