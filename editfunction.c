#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editfunction.h"
#include "retrieve.h"


// function to remove extra lines
void noline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// FUNCTION to load books from csv filee
int load_books(struct Book books[]) {
    FILE *fp = fopen(FILE_NAME, "r"); //using pointer in read only mode
    if (!fp) {
        printf("Could not open file '%s'.\n", FILE_NAME);
        return 0;
    }

    char line[5000];
    int count = 0; //counter

    // skips header 
    fgets(line, sizeof(line), fp);

    // to read each line
    while (fgets(line, sizeof(line), fp) && count < MAX_BOOKS) { //loop until EOF or max books reached
        char *token; //stores each field we exctract

        token = strtok(line, ";"); //breaks at ; and returns the first token
        if (!token) continue; //nothing to read, so skip to next line
        strncpy(books[count].title, token, sizeof(books[count].title)); //copies the token to the book struct
        noline(books[count].title); //removes the newline character

        token = strtok(NULL, ";"); //gets the next token after the first one where we left off
        if (!token) continue;
        strncpy(books[count].author, token, sizeof(books[count].author));
        noline(books[count].author);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(books[count].description, token, sizeof(books[count].description));
        noline(books[count].description);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(books[count].genre, token, sizeof(books[count].genre));
        noline(books[count].genre);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(books[count].avg_rating, token, sizeof(books[count].avg_rating));
        noline(books[count].avg_rating);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(books[count].num_rating, token, sizeof(books[count].num_rating));
        noline(books[count].num_rating);

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(books[count].URL, token, sizeof(books[count].URL));
        noline(books[count].URL);

        count++;
    }

    fclose(fp); //closes the file pointer
    return count; //returns the number of books loaded
} // end of load function

// FUNCTION to save books back to CSV file..
void save_books(struct Book books[], int count) { // saves the books back to the file
    // opens the file in write mode, overwriting existing content
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) { //checks if the file was opened successfully
        printf("Error. Can't open that file for writing.\n"); 
        return;
    }

    // writes out the header
    fprintf(fp, "Book;Author;Description;Genre;Avg_Rating;Num_Ratings;URL\n"); // header for the csv file

    // writes each book entry
    for (int i = 0; i < count; i++) { //loop through the books array and write each book to the file
        // using %s for strings, %f for float, %d for int
        fprintf(fp, "%s;%s;%s;%s;%s;%s;%s\n",
                books[i].title, 
                books[i].author,
                books[i].description,
                books[i].genre,
                books[i].avg_rating,
                books[i].num_rating,
                books[i].URL);
    }

    fclose(fp); // closes the file pointer
}

// EDIT BOOK FUNCTION
void editbook() {
    
    struct Book books[MAX_BOOKS]; // array of Book structs to hold the book entries
    int total = load_books(books); // loads the books from the file into the array

    if (total == 0) {
        printf("No entries loaded.\n");
        return;
    }

    char search_title[100]; // buffer to hold the title of the book to be edited

    printf("Enter the exact title of the book to edit: ");
    fgets(search_title, sizeof(search_title), stdin); // read the title from user input
    noline(search_title); // remove the newline character

    int found = 0; // flag to check if the book was found
    for (int i = 0; i < total; i++) { // loop through the books array to find the book with the given title
        if (strcmp(books[i].title, search_title) == 0) { // compare the title with the search title
            // if they match, we found the book
            found = 1;
            char buffer[2048]; // buffer to hold user input for editing

            printf("\nEditing book: %s\n", books[i].title); // print the title of the book being edited
            printf("Press Enter to keep the current information.\n");

            printf("Author [%s]: ", books[i].author); // prompt for author
            fgets(buffer, sizeof(buffer), stdin); noline(buffer); // read input
            if (strlen(buffer) > 0) strncpy(books[i].author, buffer, sizeof(books[i].author)); //checks if enter was hit bc buffer is empty, if not copy the new input to the struct

            printf("Description [%s]: ", books[i].description);
            fgets(buffer, sizeof(buffer), stdin); noline(buffer);
            if (strlen(buffer) > 0) strncpy(books[i].description, buffer, sizeof(books[i].description));

            printf("Genre [%s]: ", books[i].genre);
            fgets(buffer, sizeof(buffer), stdin); noline(buffer);
            if (strlen(buffer) > 0) strncpy(books[i].genre, buffer, sizeof(books[i].genre));

            printf("Average Rating [%s]: ", books[i].avg_rating);
            fgets(buffer, sizeof(buffer), stdin); noline(buffer);
            if (strlen(buffer) > 0) strncpy(books[i].avg_rating, buffer, sizeof(books[i].avg_rating));

            printf("Number of Ratings [%s]: ", books[i].num_rating);
            fgets(buffer, sizeof(buffer), stdin); noline(buffer);
            if (strlen(buffer) > 0) strncpy(books[i].num_rating, buffer, sizeof(books[i].num_rating));

            printf("URL [%s]: ", books[i].URL);
            fgets(buffer, sizeof(buffer), stdin); noline(buffer);
            if (strlen(buffer) > 0) strncpy(books[i].URL, buffer, sizeof(books[i].URL));

            save_books(books, total);
            printf("\nBook entry updated!!\n");
            break;
        }
    }

    if (!found) { // if the book was not found, print an error message
        // this is the error message that is printed if the book was not found in the file
        printf("Error. Book title \"%s\" not found.\n", search_title);
    }
}

