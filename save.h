#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "karo.h"
#include "retrieve.h"

// TO COMPILE: gcc mainoutlineprogram.c retrieve.c karo.c editfunction.c -o mainoutlineprogram --> add the .c functions that you are using as well

void whensave (){
    int Option2;
    printf ("Indicate, if you want to edit an existing entry using 1 or create a new entry using 2:");
    scanf ("%d", &Option2);

    switch (Option2) {
        case 1:
        printf ("Editing an existing entry:\n");
       // editBook();
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
    printf ("Indicate, if you want to save a new entry using 1 or retrieve existing information using 2:");
    scanf ("%d", &Option1);
    switch (Option1) {
        case 1:
        printf ("Saving a new entry\n");
        whensave();
        break;

        case 2:
        printf ("Retrieving existing information\n"); 
        //retrieve();
        break;

        default:
        printf ("This is an invalid option\n");
    }


}