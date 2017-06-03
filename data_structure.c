/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   02-05-2017
* @Project: Mini Student Database
* @Filename: data_structure.c
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/



#include "data_structure.h"


void add_to_generic_tree(BST_GENERIC **root, STUDENT_DETAILS data, int decider)
{
	BST_GENERIC *temp;
	if (decider == -2)
	{
		if (*root == NULL)
		{
			temp = (BST_GENERIC*)calloc(1, sizeof(BST_GENERIC));
			temp->left_stu = NULL;
			temp->right_stu = NULL;
			temp->data = data;
			*root = temp;
		}
		else if (strcmp((*root)->data.name, data.name) < 0)
		{
			add_to_generic_tree(&(*root)->right_stu, data, decider);
		}
		else
		{
			add_to_generic_tree(&(*root)->left_stu, data, decider);
		}
	}
	else if (decider == -1)
	{
		if (*root == NULL)
		{
			temp = (BST_GENERIC*)calloc(1, sizeof(BST_GENERIC));
			temp->left_stu = NULL;
			temp->right_stu = NULL;
			temp->data = data;
			*root = temp;
		}
		else if ((*root)->data.sum < data.sum)
		{
			add_to_generic_tree(&(*root)->right_stu, data, decider);
		}
		else
		{
			add_to_generic_tree(&(*root)->left_stu, data, decider);
		}
	}
	else
	{
		if (*root == NULL)
		{
			temp = (BST_GENERIC*)calloc(1, sizeof(BST_GENERIC));
			temp->left_stu = NULL;
			temp->right_stu = NULL;
			temp->data = data;
			*root = temp;
		}
		else if ((*root)->data.marks[decider]<data.marks[decider])
		{
			add_to_generic_tree(&(*root)->right_stu, data, decider);
		}
		else
		{
			add_to_generic_tree(&(*root)->left_stu, data, decider);
		}
	}
}

void inorder_traverse_generic(BST_GENERIC *root, int decider, int *no_of_items_found)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		inorder_traverse_generic(root->left_stu, decider, no_of_items_found);
		{
			*no_of_items_found += 1;
			if (decider == -2)
			{
				printf("\t\t\t\t\t\t\t\t%s\t", root->data.name);
				for (int i = 0; i<root->data.no_of_subjects; i++)
				{
					printf("(%s-->%d)\t", root->data.sub_names[i], root->data.marks[i]);
				}
				printf("\n");
			}
			else if (decider == -1)
			{
				printf("\t\t\t\t\t\t\t%s\t%d\t%f\n", root->data.name, root->data.sum, (float)(root->data.sum) / (root->data.no_of_subjects));
			}
			else
			{
				printf("\t\t\t\t\t\t\t%s\t(%s-->%d)\n", root->data.name, root->data.sub_names[decider], root->data.marks[decider]);
			}
		}
		inorder_traverse_generic(root->right_stu, decider, no_of_items_found);

	}
}

void search_generic(BST_GENERIC *root, STUDENT_DETAILS data, int condition, int decider, int *no_of_items_found)
{
	/*
	condition --->{ == >= or <= };
	decider   --->{name,sum,marks_subwide}
	*/
	int choice = 1;
	if (root != NULL)
	{
		if (decider == -2)
		{
			if (condition == 0)
			{

				if (strcmp(data.name, root->data.name) == 0)
				{
					while (choice>0)
					{
						printf("\t\t\t\t\t\t\t\t\t\tAvailable Options\n\n\t\t\t\t\t\t\t\t\t\t1.\tDiplay Avg\n\n\t\t\t\t\t\t\t\t\t\t2.\tDisplay All Sub Marks\n\n\t\t\t\t\t\t\t\t\t\t3.\tDisplay Particular Subject\n\n");
						printf("\t\t\t\t\t\t\t\t\t\t\tYour Choice:\t");
						scanf("%d", &choice);
						switch (choice)
						{
						case 1:
						{

							printf("\t\t\t\t\t\t\t\t\t\t%s Avg is \t%f\n\n", root->data.name, (float)root->data.sum / root->data.no_of_subjects);
							choice = -1;
							break;
						}
						case 2:
						{
							printf("\t\t\t\t\t\t\t\t\t\t%s", root->data.name);
							for (int i = 0; i < root->data.no_of_subjects; i++)
							{
								printf("(%s-->%d)\t", root->data.sub_names[i], root->data.marks[i]);
							}
							printf("\n\n");
							choice = -1;
							break;
						}
						case 3:
						{
							char *sub = (char*)calloc(20, sizeof(char));
							printf("\t\t\t\t\t\t\t\t\t\t\tEnter Subject\t:");
							scanf("\n%[^\n]", sub);
							int i = -1;
							for (i = 0; i < root->data.no_of_subjects; i++)
							{
								if (strcmp(sub, root->data.sub_names[i]) == 0)
								{
									break;
								}
							}
							if (i == root->data.no_of_subjects)
							{
								printf("\t\t\t\t\t\t\t\t\t\t\tInvalid Subject\n\n");
							}
							else
							{
								printf("\t\t\t\t\t\t\t\t\t%s\t\t(%s-->%d)\n\n", root->data.name, root->data.sub_names[i], root->data.marks[i]);
							}
							choice = -1;
							break;
						}
						default:
						{
							printf("\t\t\t\t\t\t\t\t\t\t\tInvaild Choice\t\t\tRe-Enter\n\n");
						}
						}
					}

					*no_of_items_found += 1;
				}
				else if (strcmp(data.name, root->data.name) > 0)
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
			else if (condition == 1)
			{
				if (strcmp(data.name, root->data.name) == 0)
				{
					*no_of_items_found += 1;
				}
				else if (strcmp(data.name, root->data.name) > 0)
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
		}
		else if (decider == -1)
		{
			if (condition == 0)
			{
				if (data.sum == root->data.sum)
				{
					*no_of_items_found += 1;
					printf("\n\t\t\t\t\t\t\t\t\t%s\t%d\t%f\n", root->data.name, root->data.sum,(float)(root->data.sum)/(root->data.no_of_subjects));
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}

				else if (data.sum > root->data.sum)
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
			else if (condition == -1)
			{
				if (root->data.sum <= data.sum)
				{
					printf("\t\t\t\t\t\t\t\t\t%s\t%d\t%f\n", root->data.name, root->data.sum, (float)(root->data.sum) / (root->data.no_of_subjects));
					*no_of_items_found += 1;
					inorder_traverse_generic(root->left_stu, decider, no_of_items_found);
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
			else
			{
				if (root->data.sum < data.sum)
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}

				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
					*no_of_items_found += 1;
					printf("\t\t\t\t\t\t\t\t\t%s\t%d\t%f\n", root->data.name, root->data.sum, (float)(root->data.sum) / (root->data.no_of_subjects));
					inorder_traverse_generic(root->right_stu, decider, no_of_items_found);
				}
			}

		}
		else
		{
			if (condition == 0)
			{
				if (data.marks[decider] == root->data.marks[decider])
				{
					*no_of_items_found += 1;
					printf("\t\t\t\t\t\t\t%s\t(%s-->%d)\n", root->data.name, root->data.sub_names[decider],root->data.marks[decider]);
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}

				else if (data.marks[decider] > root->data.marks[decider])
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
			else if (condition == -1)
			{
				if (root->data.marks[decider] <= data.marks[decider])
				{
					inorder_traverse_generic(root->left_stu, decider, no_of_items_found);
					*no_of_items_found += 1;
					printf("\t\t\t\t\t\t\t%s\t(%s-->%d)\n", root->data.name, root->data.sub_names[decider], root->data.marks[decider]);
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}
				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
				}
			}
			else
			{
				if (root->data.marks[decider] < data.marks[decider])
				{
					search_generic(root->right_stu, data, condition, decider, no_of_items_found);
				}

				else
				{
					search_generic(root->left_stu, data, condition, decider, no_of_items_found);
					*no_of_items_found += 1;
					printf("\t\t\t\t\t\t\t%s\t(%s-->%d)\n", root->data.name, root->data.sub_names[decider], root->data.marks[decider]);
					inorder_traverse_generic(root->right_stu, decider, no_of_items_found);
				}
			}
		}
	}

	else
	{
		return;
	}
}

void get_data_from_tree(BST_GENERIC *root, STUDENT_DETAILS *list_of_students, int *cur_pos_in_list)
{
	if (root == NULL)
	{
		return ;
	}
	else
	{
		get_data_from_tree(root->left_stu, list_of_students, cur_pos_in_list);
		{
			strcpy((list_of_students[*cur_pos_in_list]).name, root->data.name);
			list_of_students[*cur_pos_in_list].no_of_subjects = root->data.no_of_subjects;
			list_of_students[*cur_pos_in_list].sum = root->data.sum;
			list_of_students[*cur_pos_in_list].sub_names = (char**)calloc(root->data.no_of_subjects, sizeof(char*));
			list_of_students[*cur_pos_in_list].marks = (int*)calloc(root->data.no_of_subjects, sizeof(int));
			for (int i = 0; i < root->data.no_of_subjects; i++)
			{
				list_of_students[*cur_pos_in_list].sub_names[i] = (char*)calloc(20, sizeof(char));
				strcpy(list_of_students[*cur_pos_in_list].sub_names[i], root->data.sub_names[i]);
				(list_of_students[*cur_pos_in_list]).marks[i] = root->data.marks[i];
			}
			*cur_pos_in_list = *cur_pos_in_list + 1;
		}
		get_data_from_tree(root->right_stu, list_of_students, cur_pos_in_list);
	}
}


BST_GENERIC* inorder_successor(BST_GENERIC *root)
{
	BST_GENERIC *current = root;
	while (current->left_stu != NULL)
	{
		current = (current)->left_stu;
	}
	return current;
}

BST_GENERIC * generic_delete_node(BST_GENERIC *root, STUDENT_DETAILS data, STUDENT_DETAILS **deleted)
{
	if (root == NULL)
	{
		return;
	}
	{
		if (strcmp(data.name, root->data.name) < 0)
		{
			root->left_stu = generic_delete_node(root->left_stu, data, deleted); 
		}
		else if (strcmp(data.name, root->data.name) > 0)
		{
			root->right_stu = generic_delete_node(root->right_stu, data, deleted);
		}
		else
		{
			if ((*deleted)->name[0] == '\0')
			{
				(*deleted)->no_of_subjects = root->data.no_of_subjects;
				(*deleted)->sum = root->data.sum;
				strcpy((*deleted)->name, root->data.name);
				for (int i = 0; i < root->data.no_of_subjects; i++)
				{
					strcpy((*deleted)->sub_names[i], root->data.sub_names[i]);
					(*deleted)->marks[i] = root->data.marks[i];
				}
			}

			if (root->left_stu == NULL)
			{
				BST_GENERIC* temp = root->right_stu;
				//free(root);
				return temp;
			}
			else if (root->right_stu == NULL)
			{
				BST_GENERIC *temp = root->left_stu;
				//free(root);
				return temp;
			}

			BST_GENERIC *temp = inorder_successor(root->right_stu);
			{
				strcpy(root->data.name, temp->data.name);
				root->data.no_of_subjects = temp->data.no_of_subjects;
				root->data.sum = temp->data.sum;
				for (int i = 0; root->data.no_of_subjects; i++)
				{
					strcpy(root->data.sub_names[i], temp->data.sub_names[i]);
					root->data.marks[i] = temp->data.marks[i];
				}
			}
			root->right_stu = generic_delete_node(root->right_stu, temp->data, deleted);
		}
		return root;
	}
}
