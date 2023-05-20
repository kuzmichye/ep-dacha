#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "other_headers.h"
#include "structures.h"

void read_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines("gardenassociant.db")))
        return;
    FILE *in = fopen(main_file, "r");
    FILE *in_tmp = fopen(tmp_file, "w");
    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        fprintf(in_tmp, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' opened!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void close_file(){
    if (remove(tmp_file) == 0)
        printf("The file is closed successfully.");
    else
        printf("The file is not closed.");
    getcharLock(2);
}

void save_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines(tmp_file)))
    {
        printf("Open File first!");
        return;
    }

    FILE *in = fopen(main_file, "w");
    FILE *in_tmp = fopen(tmp_file, "r");

    char str[100];
    for(int i=0; i<file_lines; i++)
    {
        fgets(str, sizeof(str), in_tmp);
        fprintf(in, "%s", str);
    }

    fclose(in);
    fclose(in_tmp);
    printf("File '%s' saved!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void add_note(){
    int file_lines = 0;
    snt_member*snt_array = get_temp_structure(&file_lines);
    int newID = snt_array[file_lines - 1].id + 1;
    free(snt_array);
    printf("New ID: %d\n", newID);
    int areaID = 0;
    printf("Area ID: ");
    scanf("%d", &areaID);
    int OwnerID = 0;
    printf("Owner ID: ");
    scanf("%d", &OwnerID);
    long new_phone_Number = 0;
    printf("Phone_Number: ");
    scanf("%ld", &new_phone_Number);
    int add_r = 0;
    printf("Address ID: ");
    scanf("%d", &add_r);
    FILE *tmp = fopen(tmp_file, "a");
    fprintf(tmp, "%d;%d;%d;%ld;%d;\n", newID, areaID, OwnerID, new_phone_Number, add_r);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void delete_note(){
    int file_lines = 0;
    snt_member* snt_array = get_temp_structure(&file_lines);
    file_print(snt_array, file_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_note_index(snt_array, file_lines, id_to_remove))==-1) return;
    FILE *tmp = fopen(tmp_file, "w");
    int i;
    for(i = 0; snt_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%d;%d;%ld;%d;\n",
                snt_array[i].id,
                snt_array[i].area_number,
                snt_array[i].owner,
                snt_array[i].phone_number,
                snt_array[i].address
                );
    for(i++;  i < file_lines; i++)
        fprintf(tmp, "%d;%d;%d;%ld;%d;\n",
                snt_array[i].id,
                snt_array[i].area_number,
                snt_array[i].owner,
                snt_array[i].phone_number,
                snt_array[i].address
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void edit_note(){
    int file_lines = 0;
    snt_member* snt_array = get_temp_structure(&file_lines);
    file_print(snt_array, file_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_note_index(snt_array, file_lines, id_to_edit))==-1)
        return;
    printf("\n\nEditing ID: %d\n", index);

    printf("New Area_number ID: ");
    scanf("%d", &snt_array[index].area_number);

    printf("New Owner ID: ");
    scanf("%d", &snt_array[index].owner);

    printf("New Phone number season: ");
    scanf("%ld", snt_array[index].phone_number);

    printf("New Price: ");
    scanf("%d", &snt_array[index].address);


    FILE *tmp = fopen(tmp_file, "w");
    for(int i=0; i<file_lines; i++){
    fprintf(tmp, "%d;%d;%d;%ld;%d;\n",
            snt_array[i].id,
            snt_array[i].area_number,
            snt_array[i].owner,
            snt_array[i].phone_number,
            snt_array[i].address
            );
    }
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void display_dictionary(const char* filename)
{
    print_dict(filename);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void edit_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dict* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_edit, 1))==-1) return;
    printf("\nEditing ID: %d\n", id_to_edit);
    printf("New value: ");
    char str[200]; char temp;
    scanf("%c",&temp); scanf("%[^\n]",str);
    strcpy(dict_array[index].value, str);
    FILE *in = fopen(filename, "w");
    for(int i=0; i<dict_lines; i++){
    fprintf(in, "%d;%s;\n",
            dict_array[i].id,
            dict_array[i].value
            );
    }
    fclose(in);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}



void add_note_dictionary(const char* filename){
    int file_lines = 0;
    dict* dictionary_ = read_dictionary_(filename, &file_lines);
    int newID = dictionary_[file_lines - 1].id + 1;
    free(dictionary_);

    printf("New ID: %d\n", newID);
    char value[150];
    printf("New value: ");
    scanf("%s", value);

    FILE *tmp = fopen(filename, "a");
    fprintf(tmp, "%d;%s;\n", newID, value);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void delete_element_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dict* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_remove, 1))==-1) return;
    FILE *tmp = fopen(filename, "w");
    int i;
    for(i = 0; dict_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    for(i++;  i < dict_lines; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void file_display(){
    int file_lines = 0;
    snt_member* snt_array = get_temp_structure(&file_lines);
    file_print(snt_array, file_lines);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void export_txt(){
    int file_lines = 0;
    snt_member* snt_array = get_temp_structure(&file_lines);
    FILE *out = fopen("out.txt", "w");
    int name_lines=-1, address_lines=-1;
    dict* name_array = read_dictionary_(name_file,&name_lines);
    dict* address_array = read_dictionary_(address_file, &address_lines);

    for(int i=0; i<file_lines; i++)
    {
        char tmp_name[100] = "*!?no_value\0";
        char tmp_address[100] = "*!?no_value\0";
        int name_ind = _get_dictionary_index(name_array, name_lines, snt_array[i].owner, 0);
        int address_ind = _get_dictionary_index(address_array, address_lines, snt_array[i].address, 0);
        if(name_ind != -1)
            strcpy(tmp_name, name_array[name_ind].value);
        if(address_ind != -1)
            strcpy(tmp_address, address_array[address_ind].value);
        fprintf(out,"%-2d\t%3d\t\t%10s\t%10ld\t\t%5s\n",
                    snt_array[i].id,
                    snt_array[i].area_number,
                    tmp_name,
                    snt_array[i].phone_number,
                    tmp_address);
    }
    fclose(out);
    printf("\nData exported to 'out.txt'\n");
    printf("Press ENTER to go back...\n");
    getcharLock(2);
}


void about(){
    printf("\nThe purpose of the app is to work with the database of SNT users.\n");
    printf("Program is made by Yegor Kuzmenko");
    printf("\nPress ENTER to go back...\n");
    getcharLock(2);
}
