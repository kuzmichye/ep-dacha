#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"


void getcharLock(int loops)
{
    for(int i = 0; i < loops; i++ )
        getchar();
}

void clearscreen()
{
    printf("\n");
    system("clear");
}

int filenlines(const char *filename)
{
    FILE *in = fopen(filename, "r");
    if(!in)
    {
        printf("Error... File '%s' not found!\nPress any key to continue...\n", filename);
        getcharLock(2); return 0;
    }
    int file_lines=0;
    char str[100];
    do
    {
        fgets(str, sizeof(str), in);
    }
    while(!feof(in) && ++file_lines);
    return file_lines;
}


snt_member* get_temp_structure(int* file_lines_){
    int file_lines = 0;
    if(!(file_lines=filenlines(tmp_file)))
        return 0;
    FILE *in = fopen(tmp_file, "r");
    snt_member* snt_array = (snt_member*)malloc(sizeof(snt_member) * file_lines);

    char str[100];
    for(int i=0; i<file_lines; i++)
    {
        fgets(str, sizeof(str), in);
        snt_array[i].id = atoi(strtok(str, ";"));
        snt_array[i].area_number = atoi(strtok(NULL, ";"));
        snt_array[i].owner = atoi(strtok(NULL, ";"));
        snt_array[i].phone_number = atol(strtok(NULL, ";"));
        snt_array[i].address = atoi(strtok(NULL, ";"));
    }
    fclose(in);
    *file_lines_ = file_lines;
    return snt_array;
}

dict* read_dictionary_(const char *filename, int *lines)
{
    int file_lines = 0;
    if(!(file_lines = filenlines(filename)))
        return 0;
    FILE *in = fopen(filename, "r");

    char str[100];
    dict* dictionary_array = (dict*)malloc(sizeof(dict) * file_lines);
    for(int i=0; i<file_lines; i++)
    {
        fgets(str, sizeof(str), in);
        dictionary_array[i].id = atoi(strtok(str, ";"));
        strcpy(dictionary_array[i].value, strtok(NULL, ";"));
    }
    *lines = file_lines;
    return dictionary_array;
}

int _get_dictionary_index(dict* dictionary_, int lines, int id, int mode){
    for(int i=0; i<lines; i++)
    {
        if(dictionary_[i].id == id) return i;
    }
    if(mode)
    {
        clearscreen();
        printf("Error... dictionary note id %d does not exist!\nPress ENTER to go back...", id);
        getcharLock(2);
    }
    return -1;
}

void file_print(snt_member* snt_array, int length)
{
    int name_lines=-1, address_lines=-1;
    dict* name_array = read_dictionary_(name_file, &name_lines);
    dict* address_array = read_dictionary_(address_file, &address_lines);

    printf("Id\t Area\t\tOwner\t\t\Phone_number\t\t\tAddress\n\n");
    for(int i=0; i<length; i++)
    {
        char tmp_name[100] = "*!?no_value\0";
        char tmp_address[100] = "*!?no_value\0";
        int name_ind = _get_dictionary_index(name_array, name_lines, snt_array[i].owner, 0);
        int address_ind = _get_dictionary_index(address_array, address_lines, snt_array[i].address, 0);
        if(name_ind != -1) strcpy(tmp_name, name_array[name_ind].value);
        if(address_ind != -1) strcpy(tmp_address, address_array[address_ind].value);
        printf("%-2d\t%3d\t\t%10s\t%10ld\t\t%5s\n",
               snt_array[i].id,
               snt_array[i].area_number,
               tmp_name,
               snt_array[i].phone_number,
               tmp_address);

    }
}

void print_dict(const char* filename)
{
    int dict_lines=-1;
    dict* dict_array = read_dictionary_(filename, &dict_lines);
    printf("Dictionary %s\n\n", filename);
    printf(" id  value\n\n");
    for(int i=0; i<dict_lines; i++){
        printf(" %-4d%s\n",
               dict_array[i].id,
               dict_array[i].value
               );
    }
}

int _get_note_index(snt_member* snt_array, int file_length, int id){
    for(int i=0; i<file_length; i++)
        if(snt_array[i].id == id) return i;
    clearscreen();
    printf("Error... Note id %d does not exist!\nPress ENTER to go back...", id);
    getcharLock(2);
    return -1;
}
