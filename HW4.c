#include <stdio.h>
#include <stdlib.h>

/*

 Vahit Buğra YEŞİLKAYNAK
 150150019
 BIL105E Homework 4

 */

typedef struct {
    int personId;
    double height;
    double weight;
    double BMI;
}Person; // Creating struct Person

int Erk(int base, int power){ // Does not represent my current state of mind :)
    int i, adam;
    adam = base;
    if (power == 0) {
        return 1;
    }
    for (i = 1; i < power; ++i) {
        adam = adam * base;
    }
    return adam;
} // My pow function for powers of 0 and bigger

int StringToInt(char *cs){
    int size = 0;
    int number = 0;
    int i;
    for (; *(cs + size) != '\0';){++size;}
    for (i = 0; i < size; ++i) {number += (*(cs + i) - '0') * Erk(10, size - (i + 1));}
    return number;
} // My function which converts String to Int

double Good(double bad){
    return (bad < 0 ? (bad * -1) : bad);
} // My absolute value function for doubles

int main (int argc, char *argv[]){
    FILE *filePtr; // Declaring file pointer

    char *theFile = (char *)malloc(15 * sizeof(char)); // Defining the String to read lines

    char *prop1 = (char *)malloc(5 * sizeof(char)); // *****
    char *prop2 = (char *)malloc(4 * sizeof(char)); // Defining the Strings to hold Person values temporarily
    char *prop3 = (char *)malloc(4 * sizeof(char)); // *****

    int N, M, threshold; // Declaring N, M and threshold

    N = StringToInt(argv[1]); // Converting N to int
    M = StringToInt(argv[2]); // Converting M to int
    threshold = StringToInt(argv[3]); // Converting threshold to int

    Person *people; // Declaring Person array people
    people = (Person *)malloc(N * sizeof(Person));

    filePtr = fopen("height_weight.txt", "r"); // Opening data file to read
    fseek(filePtr, 32, SEEK_CUR); // Pass the first line which has headers, change this to 33 if OSX

    int i, j, which, length; // which is for knowing which Person value it is reading
                             // length is for defining chars

    for (i = 0; i < N; ++i){
        fgets(theFile, 15, filePtr); // Read a line from the txt
        which = 0; // which value is it reading? id, height or weight
        length = 0; // length of the value id height or weight

        /*This for loop reads chars then by looking for special chars
         it declares id, height and weight values as strings*/

        for (j = 0; j < 15; ++j) {

            if (which == 0) {
                *(prop1 + length) = *(theFile + j);
                *(prop1 + length + 1) = '\0';// For every char it declares also
                                            // Sets the next char to null
                ++length;
                if (*(theFile + j + 1) == '\t') {
                    length = 0;
                    ++j; // If the character is tab it passes it
                    which = 1;
                }
            }

            else if (which == 1) {
                *(prop2 + length) = *(theFile + j);
                *(prop2 + length + 1) = '\0';// For every char it declares also
                                            // Sets the next char to null
                ++length;
                if (*(theFile + j + 1) == '\t') {
                    length = 0;
                    ++j; // If the character is tab it passes it
                    which = 2;
                }
            }

            else if (which == 2){
                *(prop3 + length) = *(theFile + j);
                *(prop3 + length + 1) = '\0'; // For every char it declares also
                                            // Sets the next char to null
                ++length;
                if ((int)*(theFile + j + 1) == 13 || *(theFile + j + 1) == '\n') { // At the end of the line there
                                                    // was a char with ASCII value 13 or \n they work different on OSX and itu ssh
                    break;
                }
            }
        } // End of for to read chars

        people[i].personId = StringToInt(prop1); // Declare person ID
        people[i].height = (int)StringToInt(prop2); // Declare height
        people[i].weight = (int)StringToInt(prop3); // Declare weight
        people[i].BMI = people[i].weight / ((people[i].height / 100) * (people[i].height / 100));
        // Calculate BMI

    } // End of for to read lines
    free(prop1); free(prop2); free(prop3);

    for (i = 0; i < N; ++i) { // Sort by |BMI- threshold| with insetion sort
        for (j = 0; j < i; ++j) {
            if (Good(people[j].BMI - threshold) < Good(people[i].BMI - threshold)) {
                Person person;
                person = people[i];
                people[i] = people[j];
                people[j] = person;
            }
        }
    }

    fclose(filePtr); // Close data file


    // Print output file
    filePtr = fopen("Output.txt", "w");
    fprintf(filePtr, "Person_id\tHeight(cm)\tWeight(kg)\tBMI\t\t|BMI - Threshold|\n");
    for (i = 0; i < M; ++i) {
        fprintf(filePtr, "%d\t\t%d\t\t%d\t\t%.2lf\t\t%.2lf\n", people[i].personId, (int)people[i].height, (int)people[i].weight, people[i].BMI, Good(people[i].BMI - threshold));
    }
    fclose(filePtr);

    return 0;
}
