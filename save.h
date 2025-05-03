// save.h
#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>

char *title;           // I created pointers for dynamic memory allocation
char *author;           //This is important for the malloc function below
char *description;
char *genres;
char *url;
float avg_rating;  //I have chosen float here to enable ratings like 5.7 
int num_ratings;   // I have chosen int here because the number of ratings in a whole number (e.g. it has 560 ratings)
char confirm;

void flush_newline();
char *read_string(const char *prompt, size_t size);
void newentry();

#endif