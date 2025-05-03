#include <stdio.h>
#include <stdlib.h>  // for malloc, exit, free
#include <string.h>  // for strcspn
#include "save.h"

char *title;           // I created pointers for dynamic memory allocation
char *author;           //This is important for the malloc function below
char *description;
char *genres;
char *url;
float avg_rating;  //I have chosen float here to enable ratings like 5.7 
int num_ratings;   // I have chosen int here because the number of ratings in a whole number (e.g. it has 560 ratings)
char confirm;

// Flush INPUT buffer after scanf (delete things like the last character /n created when hitting enter)
//used after scnaf
void flush_newline() {
    while (getchar() != '\n');
}

// Reads a line of input with dynamic memory --> dynamically manages the string input
char *read_string(const char *prompt, size_t size) { //function to read a string from the user
    char *input = malloc(size); //allocates in the HEAP --> inout stays in the meory after function call ended ON RUNTIME!!
    if (input == NULL) {        //input is a local --> does not stay in the HEAP, but the rest will until free()
        fprintf(stderr, "Oh no! Memory allocation has failed:// %s\n", prompt);
        exit(1);
    }

    printf("%s", prompt);     //prompt the user for input          
    fgets(input, size, stdin);      //safely read until the newline character or the end of the file
    input[strcspn(input, "\n")] = '\0';  //removes the last character of a string \0 FOR fgets!

    return input;
}


void newentry() {
    do {
        // Read all inputs dynamically calling the read_string function
        title = read_string("Enter a Title please!: ", 100); 

        author = read_string("Now the Author: ", 100);

        description = read_string("Enter a short Description you know the general plot: ", 200);

        genres = read_string("Enter a specific Genre: ", 50);

        //Float and integers we read "not dynamically" with scanf
        printf("Enter the Average Rating for the book: ");
        scanf("%f", &avg_rating);
        flush_newline();

        printf("Enter the Number of Ratings (to see how well reviewed it actually is:)) ");
        scanf("%f", &num_ratings);
        flush_newline();

        url = read_string("Share a URL for downloading: ", 256);

        // Display before saving
        printf("\nDO NOT forget to CHECK your entries before Submitting:)\n");
        printf("\nYou entered:\n");
        printf("Title       : %s\n", title);
        printf("Author      : %s\n", author);
        printf("Description : %s\n", description);
        printf("Genre       : %s\n", genres);
        printf("Avg Rating  : %f\n", avg_rating);
        printf("Num Ratings : %d\n", num_ratings);
        printf("URL         : %s\n", url);


        //ask again to be sure if the user wants to save
        printf("\nAre you ABSOLUTELY sure you want to save this entry? (y/n): ");
        scanf(" %c", &confirm);
        flush_newline(); //clears buffer

        //If loop that stated to append to file when user chose yes
        if (confirm == 'y' || confirm == 'Y') {
            FILE *file = fopen("fixedbooks.csv", "a"); // append mode
            if (file == NULL) {
                perror("Failed to open file"); //the file was not found or able to nbe opened
                return;
            }

            //also here, for the av rating i have out %.2f to round to 2 decimals because it looks nicer in the output file:)
            fprintf(file, "%s;%s;\"%s\";%s;%.2f;%d;%s\n", //The description is put in double quotes to avoid a space or "," or "." to break the desciption (since the entries are seperated by ";")
                    title, author, description, genres, avg_rating, num_ratings, url);
            fclose(file);
            printf("Entry saved successfully!\n\n");
        } else {
            printf("Let's re-enter the information.\n\n"); //this is in case the user chose not to save


            // Free previously allocated strings before starting over
            free(title);
            free(author);
            free(description);
            free(genres);
            free(url);
        }

    } while (confirm != 'y' && confirm != 'Y'); //belongs to the do at thew top (do-while loop)

    // Frees these after saving to file was successful
    // When user inputs YES to save --> we free after the loop
    //When user input NO to save --> we free right away and restart
    free(title);
    free(author);
    free(description);
    free(genres);
    free(url);
}

