#ifndef EDITFUNCTION_H
#define EDITFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retrieve.h"

#define MAX_BOOKS 1000
#define FILE_NAME "fixedbooks.csv"


// function declarations
void noline(char *str);
int load_books(struct Book books[]);
void save_books(struct Book books[], int count);
void editbook();

#endif // this and #ifindef prevent incl header twice
