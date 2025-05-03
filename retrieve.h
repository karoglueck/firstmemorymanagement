#ifndef RETRIEVE_H
#define RETRIEVE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_char_line 1000 //maximum number of lines (defined as preprocessor so that it can be changed easily)
#define max_columns 7 //maximum number of columns 
#define max_entries 100 //maximum number of entries
#define file_name "fixedbooks.csv"


//structure for book
struct Book {
    char title[100]; 
    char author[500];
    char description[2000];
    char genre[50];
    char avg_rating[5]; // defined as characters so strcpy can be used
    char num_rating[10];
    char URL[256];
};

// global definitions for those variables that are relevant across multiple functions
extern FILE* file1;
extern char column[max_columns][max_char_line]; //string that will store columns names 
extern int number_columns; //counts number of columns 
extern int book_count; //keeping track of the book counts --> important for the loop 
extern char option_title[100];
extern int option_category; 
extern int num_entries; 
extern char buffer[max_char_line]; // space to store line from file (assuming each line is at most 999 characters long)
extern int result;
extern struct Book library[100];

//function declarations
void print_column_names(char buffer[max_char_line], char column[][max_char_line], int *number_columns);
void fill_library(int *book_count);
int choose_category_find (int i);
void display_category(int i, int option2);
void display_result (int i);
void find_and_display ();
void retrieve();

#endif