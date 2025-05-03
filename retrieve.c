

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retrieve.h"
#define max_char_line 1000 //maximum number of lines (defined as preprocessor so that it can be changed easily)
#define max_columns 7 //maximum number of columns 
#define max_entries 100 //maximum number of entries
#define file_name "fixedbooks.csv"



//global definitions for those variables that are relevant across multiple functions
FILE* file1;
char column[max_columns][max_char_line]; //string that will store columns names 
int number_columns = 0; //counts number of columns 
int book_count = 0; //keeping track of the book counts --> important for the loop 
char option_title[100];
int option_category; 
int num_entries; 
char buffer[max_char_line]; // space to store line from file (assuming each line is at most 999 characters long)
int result;
struct Book library[max_entries];

// entering retrieving option
void first_option () { //????

    
}


//main function from my retrieve function 
void retrieve() {
        //informing user over state of the program and providing them with the opportunity to exit this part of the program
        printf("Thank you for choosing the retreaving existing information option, you can now retrieve information from the available file.\nIn case you do want to exit this program, please enter 0, if you want to continue, please enter any other number: \n");
        int option0; 
        scanf("%d", &option0); 
        if (option0 == 0){
            printf("You are exiting this program now\n");
            exit(0); // leaving option
        }

        else 
        printf("Thank you for choosing to continue! \n");
        

    // 1. Open file and print columns 
    
        //Open File
        file1 = fopen(file_name, "r"); //opening existing csv sheet
    
    
        //checking if the File was opened successfully
        if (file1 == NULL) {
            printf("The existing file could not be opened");
            exit(0);
        }
        else {
            printf("The file was now successfully opened\n\n");
        }
        //read first line (column headers) and check if text exists in file
    
        char *result = fgets(buffer, sizeof(buffer), file1); //read line from file1
        if (result == NULL) { //checking if text is present in file 
            printf("There appears to be no content in this file, you will now exit the program\n");
            fclose(file1);
            exit(0);
        }
       
        buffer[strcspn(buffer, "\r\n")] = '\0'; //remove new line if present --> strcspn returns number of elements in buffer that are not \r (moves curser to beginning of line) or \n --> this way the at this index the element can be replaced by \n which ends the string
        
        print_column_names(buffer, column, &number_columns); 
    
    // 2. Organize the data into suitable structures for streamlined retrieval --> the data is copied into the array "library" holding the structure of the data table
    
        fill_library(&book_count);
    
    // 3. Prompt the user to specify the field and criteria for the desired entry retrieval.
    // 4. Search for matching entries based on specified criteria. For instance, you can list restaurants whose names start with "Ab" or those that offer a particular style of cuisine.
        
        int menu;
        while (menu != 0) {
        printf("Please indicate if you want to choose a category to search by (entering 1) or return to the main menu (enter 0)\n");
            scanf("%d", &menu);

            switch(menu) {
                case 0: printf("You are returning to the main menu\n");
                        return;

                case 1:
                        printf("Now that you have seen the categories please specify a category that you want to search by using the following numbers: \nIf you want to exit please enter 7\n");
                        for(int i = 0; i < number_columns; i++) { // for loop to print the column headers and more efficiently
                        printf("%d: %s\n", i, column[i]);
                }
                        scanf("%d", &option_category); // scan number of category option
                        while (getchar() != '\n'); //cleans buffer
    
                        printf("Now please enter the keyword you want to search by (you can also only enter the first letters): \n");
                        fgets(option_title, sizeof(option_title), stdin); // reading user input but using fgets instead of scanf so that spaces can be read as well
                        option_title[strcspn(option_title, "\r\n")] = '\0'; // remove newline
    
                        // 5. Display pertinent information for the retrieved entries, with the option to show only partial details. Users should have the ability to view comprehensive information for individual entries while retaining the option to return to the previous overview.
    
                        find_and_display(); 
                break;

                default: printf("Invalid option\n");
                break;
            }
        }
     }        

           


        
    
    



//function to print the columns
void print_column_names(char buffer[max_char_line], char column[][max_char_line], int *number_columns) {

    //checking if text is present in lie

    char *token = strtok(buffer, ";");

    //while loop to print the header columns
    printf("The column headers are: \n");
    while (token && *number_columns < max_columns) { //while a token is there and the number of columns does not reach the maximum
        strcpy(column[*number_columns], token);  // copies token (name of cell) into columns array 
        printf("%s\n", column[*number_columns]); 
        (*number_columns)++; //increases the index of the column (so that in the end the number of columns can be seen)
        token = strtok(NULL, ";"); //breaks down string from where it left off --> necessary so that the loop does not begin again from the beginning all the time 
    }
}

//function to store the data in a structure array 
void fill_library(int *book_count) { //parameter passed by reference so that it changes globally as well

    char rows_content[max_char_line]; //variable to store the content of each row
    
    while ((fgets(rows_content, sizeof(rows_content), file1) != NULL) && *book_count < max_entries) { //loop that iterates while, there is text within the row 
        
        rows_content[strcspn(rows_content, "\r\n")] = '\0';  // removes newline
        char *token = strtok(rows_content, ";"); //local variable is created that stores the tokens of the row after it has been tokenized
        
        strcpy((library)[*book_count].title, token); //the first token is copied into the title element of the array of the structure of the row indexed
        token = strtok(NULL, ";"); //after first token has been copied in, the next token is split, but form where the string was last split, so that the author of the book will be stored

        strcpy((library)[*book_count].author, token);
        token = strtok(NULL, ";");

        strcpy((library)[*book_count].description, token);
        token = strtok(NULL, ";");

        strcpy((library)[*book_count].genre, token);
        token = strtok(NULL, ";");

        strcpy(library[*book_count].avg_rating, token);
        token = strtok(NULL, ";");

        strcpy(library[*book_count].num_rating, token);
        token = strtok(NULL, ";");

        strcpy((library)[*book_count].URL, token);

        (*book_count)++;
    }

    printf("The data is stored in the array\n\n"); //confirming success of storing the data
}

// searches for matches that the user looks for
int choose_category_find (int i) {
    
    switch (option_category) {
        case 0: result = strncmp(option_title, library[i].title, strlen(option_title)) == 0; // setting it equal to 0 since strncmp returns 0 when it found a match
        break;

        case 1: result = strncmp(option_title, library[i].author, strlen(option_title)) == 0;
        break;

        case 2: result = strncmp(option_title, library[i].description, strlen(option_title)) == 0;
        break;

        case 3: result = strncmp(option_title, library[i].genre, strlen(option_title)) == 0;
        break;

        case 4: result = strncmp(option_title, library[i].avg_rating, strlen(option_title)) == 0;
        break; 

        case 5: result = strncmp(option_title, library[i].num_rating, strlen(option_title)) == 0;
        break; 

        case 6: result = strncmp(option_title, library[i].URL, strlen(option_title)) == 0;
        break;

        default: printf("Invalid option\n");
    }
    return result;
}


// displays category user specified
void display_category(int i, int option2) {
    switch (option2) {
        case 0: printf("Title: %s\n", library[i].title);
        break; 

        case 1: printf("Author: %s\n", library[i].author);
        break; 

        case 2:printf("Description: %s\n", library[i].description);
        break; 

        case 3: printf("Genre: %s\n", library[i].genre);
        break; 

        case 4: printf("Average Rating: %s\n", library[i].avg_rating);
        break; 

        case 5: printf("Number Rating: %s\n", library[i].num_rating);
        break; 
        
        case 6: printf("URL: %s\n", library[i].URL);
        break; 

        default: printf("You don't want to view any category in detail ://\n"); 
        break;

        return;
    }
}


// displays entire row of what user looks for
void display_result (int i) {
    
    int option2; 

    printf("Match found in entry %d:\n\n", i);  
    printf("Title: %s\n", library[i].title);
    printf("Author: %s\n", library[i].author);
    printf("Description: %s\n", library[i].description);
    printf("Genre: %s\n", library[i].genre);
    printf("Average Rating: %s\n", library[i].avg_rating);
    printf("Number Rating: %s\n", library[i].num_rating);
    printf("URL: %s\n\n", library[i].URL);
    
    int a = 1;
    while(a>0) { //infinite loop to keep asking the user if they want to see more categories until they enter 7 or there are no more books left
        a++;

    printf("If you want to see only one category please indicate which one, if you do not want to see a specific category just enter any other number: \n");
        
        for(int i = 0; i < number_columns; i++) { // for loop to print the column headers and more efficiently
            printf("%d: %s\n", i, column[i]);
        }
        printf("If you want to see the next book with that matches this key search please enter 7 (The program will return to the menu automatically if there are no books left)\n");
        
        scanf("%d", &option2); // reads user input for which category to display
        while (getchar() != '\n'); 

        if(option2 == 7) {
            return;
        }
        
        else if (option2 < 7 && option2 >= 0) {
            display_category(i, option2); // displays single categories using the switch case
        }
        else {
            printf("This is an invalid option\n");
        }
    }
}


// finds and displays the entries the user looks for
void find_and_display () {
    printf("You are looking for '%s' in the category '%d'\n", option_title, option_category); //showing user what they entered
    
    for (int i = 0; i < book_count; i++){ // for loop to iterate through all the book entries 

        if (choose_category_find (i)) {// finds the entry in the category chosen in the bookcount from the for loop
        display_result (i); // displays full result 

        }

    }
}


