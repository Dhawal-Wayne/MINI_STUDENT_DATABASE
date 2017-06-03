/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   28-04-2017
* @Project: Mini Student Database
* @Filename: query_lang.h
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/



#ifndef QURY_LANG_H_
#define QURY_LANG_H_

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include "data_structure.h"

extern int display_all(BST_GENERIC *root, int decider, int *no_of_items);

extern int start_query_processor();

extern int prepare_student_database(BST_GENERIC *root, int no_of_subjects);

extern int data_fetch(STUDENT_DETAILS **existing_students_list);

extern int data_validation(FILE *new_data_file_p, STUDENT_DETAILS **new_list);

#endif
