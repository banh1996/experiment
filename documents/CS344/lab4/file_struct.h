// R. Jesse Chaney

#ifndef TRUE
# define TRUE 1
#endif // TRUE
#ifndef FALSE
# define FALSE 0
#endif // FALSE

#ifndef _FILE_STRUCT_H
# define _FILE_STRUCT_H

# define OPTIONS "hvi:o:"

# define ID_LEN 20
# define NAME_LEN 25
# define STREEN_LEN 50
# define CITY_LEN 40
# define ZIP_LEN 15
# define COUNTRY_LEN 15
# define EMAIL_LEN 50
# define PHONE_LEN 20

typedef struct file_struct_s {
    char fname[NAME_LEN];              // First name (given name)
    char mname[NAME_LEN];              // Middle name
    char lname[NAME_LEN];              // Last name (family name)
    char street[STREEN_LEN];           // Street address
    char city[CITY_LEN];               // City name
    char zip[ZIP_LEN];                 // The Postal code
    char country_code[COUNTRY_LEN];    // The country code for the address.

    char email[EMAIL_LEN];             // An email address
    char phone[PHONE_LEN];             // Phone number.

    char id[ID_LEN];                   // A "unique" id for each person in the file. It may
                                       // not actually be unique, but it is good enough for now.

} file_struct_t;

#endif // _FILE_STRUCT_H
