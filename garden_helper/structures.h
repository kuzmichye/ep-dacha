#ifndef STRUCTS_H
#define STRUCTS_H

#define main_file "gardenassociant.db"
#define tmp_file "gardenassociant_tmp.db"
#define name_file "name.db"
#define address_file "address.db"


typedef struct {
    int id;
    int area_number;
    int owner;
    long phone_number;
    int address;
} snt_member;

typedef struct {
    int id;
    char value[50];
} dict;

#endif // STRUCTS_H
