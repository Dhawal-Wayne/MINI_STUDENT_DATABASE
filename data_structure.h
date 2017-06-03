/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   02-05-2017
* @Project: Mini Student Database
* @Filename: data_structure.h
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/

#ifndef DATA_STRUCTURE_H_
#define DATA_STRUCTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

typedef struct STUDENT_DETAILS
{
	char name[20];
	int no_of_subjects;
	int *marks;
	char **sub_names;
	int sum;
}STUDENT_DETAILS;

typedef struct BST_GENERIC {
	STUDENT_DETAILS data;
	struct BST_GENERIC *left_stu;
	struct BST_GENERIC *right_stu;
}BST_GENERIC;

/*
condition --> {==(0) , <=(-1) ,>=(-2)}
decider   --> {name,sum,subwise}
*/

extern void inorder_traverse_generic(BST_GENERIC *root, int decider, int *no_of_items_found);

/*
find node copy all its details delete it and alter copied copy add it to main tree
later change all trees according by a inorder traversal
*/

extern void get_data_from_tree(BST_GENERIC *root, STUDENT_DETAILS *list_of_students,int *cur_pos_in_list);

extern void search_generic(BST_GENERIC *root, STUDENT_DETAILS data, int condition, int decider, int *no_of_items_found);

extern void add_to_generic_tree(BST_GENERIC **root, STUDENT_DETAILS data, int tree_num);

extern BST_GENERIC* inorder_successor(BST_GENERIC *root);

extern BST_GENERIC* generic_delete_node(BST_GENERIC *root, STUDENT_DETAILS data,STUDENT_DETAILS **deleted);

#endif
