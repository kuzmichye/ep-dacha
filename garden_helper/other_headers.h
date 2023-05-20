#ifndef OTHER_HEADERS_H
#define OTHER_HEADERS_H

#include "structures.h"

void getcharLock(int);
void clearscreen();

int filenlines(const char*);
snt_member* get_temp_structure(int*);
dict* read_dictionary_(const char*, int*);
void print_dict(const char*);
int _get_dictionary_index(dict*, int, int, int);
void file_print(snt_member*, int);
int _get_note_index(snt_member*, int, int );






#endif // OTHER_HEADERS_H
