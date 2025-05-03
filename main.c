#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retrieve.h"
#include "save.h"
#include "editfunction.h"

// TO COMPILE: gcc mainoutlineprogram.c retrieve.c karo.c editfunction.c -o mainoutlineprogram --> add the .c functions that you are using as well
// run with ./mainoutlineprogram

void whensave (){
    int Option2;
    printf ("Indicate, if you want to edit an existing entry using 1 or create a new entry using 2:");
    scanf ("%d", &Option2);
    flush_newline();
    switch (Option2) {
        case 1:
        printf ("Editing an existing entry:\n");
        editbook();
        break;

        case 2:
        printf ("Creating a new entry, please fill out existing information:\n");
        newentry();
        break;

        default:
        printf ("This is an invalid option\n");
    }
}



int main (){
  
    int Option1;

    while (Option1 != 0) { // while loop as main menu so that after each of the options was chosen and "conducted" the user has the option to try another option

        printf ("Indicate, if you want to save a new entry using 1 or retrieve existing information using 2:\nIf you want to exit the program enter 0\n");
        scanf ("%d", &Option1);
        switch (Option1) {
            case 1:
            printf ("Saving a new entry\n");
            whensave();
            break;

            case 2:
            printf ("Retrieving existing information\n"); 
            retrieve();
            break;

            case 0: 
            printf("You are exiting this program now\n");
            return 0;


            default:
            printf ("This is an invalid option\n");
            break;
        }
    }

}







