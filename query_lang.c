/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   01-05-2017
* @Project: Mini Student Database
* @Filename: qury_lang.c
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/



#include "query_lang.h"

int start_query_processor()
{
	int no_of_records = 0;

	BST_GENERIC *main_root = NULL, *sum_main_root = NULL, **subwise_bst;

	int qurey_result = 0;

	char new_datafile[20];

	int choice = -1;

	STUDENT_DETAILS *existing_students;

	system("cls");

	printf("\t\t\t\t\t\t\tAvailable Options on Bench\n\n\t\t\t\t\t\t\t\t1. Fetch From Old DataBase\n\n\n\t\t\t\t\t\t\t\t2. Want To provide New Data\n\n");

	printf("\t\t\t\t\t\t\tWhat would You like to do?\n\n\t\t\t\t\t\t\t\t>");

	scanf("%d", &choice);

	if (choice == 1)
	{
		printf("\t\t\t\t\t\t\tFetching Data.....Please Wait.........\n\n");


		no_of_records = data_fetch(&existing_students);
		subwise_bst = (BST_GENERIC**)calloc(existing_students[0].no_of_subjects, sizeof(BST_GENERIC*));
		for (int i = 0; i<no_of_records; i++)
		{
			add_to_generic_tree(&main_root, existing_students[i], -2);
			add_to_generic_tree(&sum_main_root, existing_students[i], -1);
			for (int j = 0; j<existing_students[i].no_of_subjects; j++)
			{
				add_to_generic_tree(&subwise_bst[j], existing_students[i], j);
			}
		}
		/*
		printf("\t\t\tName Wise Tree is\n");
		inorder_traverse_generic(main_root,-2,&qurey_result);
		printf("\t\t\tNo of records found %d\n",qurey_result);

		qurey_result=0;
		printf("\t\t\tSum wise Tree\n");
		inorder_traverse_generic(sum_main_root,-1,&qurey_result);
		printf("\t\t\tNo of records found %d\n",qurey_result);

		for(int i=0;i<existing_students[0].no_of_subjects;i++)
		{
		qurey_result=0;
		printf("\t\t\tTree according to %s\n",existing_students[0].sub_names[i]);
		inorder_traverse_generic(subwise_bst[i],i,&qurey_result);
		}
		*/
		printf("\t\t\t\t\t\t\t\tData Fetched Successfully\n\n");

	}

	else
	{
		memset(new_datafile, '\0', 20);
		printf("\t\t\t\t\t\t\t\tEnter Filename as an input:\t");
		scanf("%s", new_datafile);
		FILE *new_data;
		int found_already = 0;
		new_data = fopen(new_datafile, "r");
		STUDENT_DETAILS *new_list;
		
		if (new_data == NULL)
		{
			printf("\t\t\t\t\t\t\t\t\t\t\tInvalid File Entered\n\n\n");
			exit(-1);
		}
		//validation get data as list contruct tress
		no_of_records=data_validation(new_data, &new_list);

		printf("\t\t\t\t\t\t\tFetching Data.....Please Wait.........\n\n");

		subwise_bst = (BST_GENERIC**)calloc(new_list[0].no_of_subjects, sizeof(BST_GENERIC*));
		for (int i = 0; i<no_of_records; i++)
		{
			found_already = 0;
			search_generic(main_root, new_list[i], 1, -2, &found_already);
			if (found_already == 0)
			{
				add_to_generic_tree(&main_root, new_list[i], -2);
				add_to_generic_tree(&sum_main_root, new_list[i], -1);
				for (int j = 0; j<new_list[i].no_of_subjects; j++)
				{
					add_to_generic_tree(&subwise_bst[j], new_list[i], j);
				}
			}
			else
			{
				printf("\t\t\t\t\t\t\t\t%s already present\n", new_list[i].name);
			}
		}

	}
	char *sub;
	int i, internal_choice = -1;
	double metric = 0;
	char *name;
	name = (char*)calloc(20, sizeof(char));
	sub = (char*)calloc(20, sizeof(char));
	system("cls");
	while (choice != 10)
	{
		printf("\t\t\t\t\t\t\t\tOptions Available on your Bench Are\n\n\t\t\t\t\t\t\t\t\t1.\tDISPLAY ALL\n\n\t\t\t\t\t\t\t\t\t2.\tDISPLAY AVG_WISE\n\n\t\t\t\t\t\t\t\t\t3.\tDISPLAY AVG WISE WITH SOME CONDITION\n\n\t\t\t\t\t\t\t\t\t4.\tDISPLAY SUBJECT WISE(YOU NEED TO ENTER SUBJECT)\n\n\t\t\t\t\t\t\t\t\t5.\tDISPLAY SUBJECT WISE + SOME CONDITION\n\n\t\t\t\t\t\t\t\t\t6.\tSEARCH FOR NAME\n\n\t\t\t\t\t\t\t\t\t7.\tADD NEW ENTITY\n\n\t\t\t\t\t\t\t\t\t8.\tEDIT ERROR RECORD ENTRY\n\n\t\t\t\t\t\t\t\t\t9.\tCHANGE OR DELETE RECORDS\n\n\t\t\t\t\t\t\t\t\t10.\tExit\n\n");
		printf("\t\t\t\t\t\t\t\tEnter Your Option\n\n\t\t\t\t\t\t\t\t\t>");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			qurey_result = 0;
			printf("\t\t\t\t\t\t\t\t\tThe records present are\n\n");
			display_all(main_root, -2, &qurey_result);
			printf("\t\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
			break;
		}
		case 2:
		{
			qurey_result = 0;
			printf("\n\t\t\t\t\t\t\t\t\tThe Leaderboard is\n\n");
			display_all(sum_main_root, -1, &qurey_result);
			printf("\t\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
			break;
		}
		case 3:
		{
			qurey_result = 0;
			{
				printf("\t\t\t\t\t\t\t\t\tOptions Avialable\n\n\t\t\t\t\t\t\t\t\t1.\tGreater than Or Equal To Avg\n\n\t\t\t\t\t\t\t\t\t2.\tLess Than Or Equal To Avg\n\n\t\t\t\t\t\t\t\t\t3.\tEqual to metric");
				printf("\n\n\t\t\t\t\t\t\t\t\tWhat Would you like to do?\n\n\t\t\t\t\t\t\t\t\t>");
				scanf("%d", &internal_choice);
				printf("\t\t\t\t\t\t\t\t\tEnter the metric :\t");
				scanf("%lf", &metric);
				switch (internal_choice)
				{
				case 1:
				{
					STUDENT_DETAILS *data;
					data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
					(*data).sum = (int)metric*(main_root->data.no_of_subjects);
					search_generic(sum_main_root, *data, 1, -1, &qurey_result);
					printf("\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
				}
				break;
				case 2:
				{
					STUDENT_DETAILS *data;
					data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
					(*data).sum = (int)metric*(main_root->data.no_of_subjects);
					search_generic(sum_main_root, *data, -1, -1, &qurey_result);
					printf("\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
				}
				break;
				case 3:
				{
					STUDENT_DETAILS *data;
					data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
					(*data).sum = (int)metric*(main_root->data.no_of_subjects);
					search_generic(sum_main_root, *data, 0, -1, &qurey_result);
					printf("\t\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
				}
				break;
				default:
					printf("\t\t\t\t\t\t\t\t\tInvalid Option\n");
					break;
				}
			}
			break;
		}
		case 4:
		{
			qurey_result = 0;
			printf("\t\t\t\t\t\t\t\t\tEnter the subject-name :\t");
			memset(sub, '\0', 20);
			scanf("\n%[^\n]*c", sub);
			/*Every Student recoed has the subject name so using root student record*/
			for (i = 0; i < main_root->data.no_of_subjects; i++)
			{
				if (strcmp(main_root->data.sub_names[i], sub) == 0)
				{
					break;
				}
			}
			if (i == main_root->data.no_of_subjects)
			{
				printf("\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Subject\n\n");
				break;
			}
			else
			{
				printf("\t\t\t\t\t\t\t\t\tLeaderboard Acoording to %s\n\n", sub);
				display_all(subwise_bst[i], i, &qurey_result);
				printf("\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
				break;
			}
		}
		case 5:
		{
			qurey_result = 0;
			printf("\t\t\t\t\t\t\t\t\tEnter the subject-name :\t");
			memset(sub, '\0', 20);
			scanf("\n%[^\n]*c", sub);
			/*Every Student recoed has the subject name so using root student record*/

			for (i = 0; i < main_root->data.no_of_subjects; i++)
			{
				if (strcmp(main_root->data.sub_names[i], sub) == 0)
				{
					break;
				}
			}
			if (i == main_root->data.no_of_subjects)
			{
				printf("\n\n\t\t\t\t\t\t\t\t\t\t\tInvalid Subject\n\n");
				break;
			}
			else
			{
				{
					printf("\t\t\t\t\t\t\t\t\tOptions Avialable\n\n\t\t\t\t\t\t\t\t\t1.\tGreater than Or Equal To Subject Score\n\n\t\t\t\t\t\t\t\t\t2.\tLess Than Or Equal To Subject Score\n\n\t\t\t\t\t\t\t\t\t3.\tEqual to metric");
					printf("\n\n\t\t\t\t\t\t\t\t\tWhat Would you like to do?\n\n\t\t\t\t\t\t\t\t\t>");
					scanf("%d", &internal_choice);
					printf("\t\t\t\t\t\t\t\t\tEnter the metric :\t");
					scanf("%lf", &metric);
					printf("\t\t\t\t\t\t\t\t\tLeaderboard Acoording to %s and Conditions\n\n", sub);

					switch (internal_choice)
					{
					case 1:
					{
						STUDENT_DETAILS *data;
						data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
						(*data).marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
						(*data).marks[i] = (int)metric;
						search_generic(subwise_bst[i], *data, 1, i, &qurey_result);
						printf("\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
					}
					break;

					case 2:
					{
						STUDENT_DETAILS *data;
						data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
						(*data).marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
						(*data).marks[i] = (int)metric;
						search_generic(subwise_bst[i], *data, -1, i, &qurey_result);
						printf("\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
					}

					break;

					case 3:
					{
						STUDENT_DETAILS *data;
						data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
						(*data).marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
						(*data).marks[i] = (int)metric;
						search_generic(subwise_bst[i], *data, 0, i, &qurey_result);
						printf("\t\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
					}

					break;

					default:
						printf("\t\t\t\t\t\t\t\t\tInvalid Option\n");
						break;

					}
				}
				break;
			}
		}
		case 6:
		{
			qurey_result = 0;
			printf("\t\t\t\t\t\t\t\tEnter Student Name :\t");
			scanf("\n%[^\n]*c", name);
			int j = 0;
			while (name[j])
			{
				name[j] = tolower(name[j]);
				j++;
			}
			STUDENT_DETAILS *data;
			data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
			strcpy((*data).name, name);
			search_generic(main_root, *data, 0, -2, &qurey_result);
			printf("\t\t\t\t\t\t\t\t\t\tFetched %d No of results\n\n", qurey_result);
			break;
		}
		case 7:
		{
			qurey_result = 0;
			printf("\t\t\t\t\t\t\t\tEnter Student Name :\t");
			scanf("\n%[^\n]*c", name);
			int i = 0;
			while (name[i])
			{
				name[i] = tolower(name[i]);
				i++;
			}
			STUDENT_DETAILS *data;
			data = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
			strcpy(data->name, name);
			(*data).marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
			search_generic(main_root, *data, 1, -2, &qurey_result);
			if (qurey_result > 0)
			{
				printf("\t\t\t\t\t\t\t\tStudent Name Already Exists\n\n");
			}
			else
			{
				no_of_records++;
				(*data).sub_names = (char**)calloc(main_root->data.no_of_subjects, sizeof(char*));

				for (int i = 0; i < main_root->data.no_of_subjects; i++)
				{
					(*data).sub_names[i] = (char*)calloc(20, sizeof(char));
					strcpy((*data).sub_names[i], main_root->data.sub_names[i]);
					printf("\t\t\t\t\t\t\t\tEnter %s Marks :\t", (*data).sub_names[i]);
					scanf("%d", &((*data).marks[i]));
					if ((*data).marks[i] >= 0 && (*data).marks[i] <= 100)
						(*data).sum += (*data).marks[i];
					else
					{
						printf("\t\t\t\t\t\t\t\t\tInvalid Marks\tRe-Enter\n\n");
						i--;
					}
				}

				(*data).no_of_subjects = main_root->data.no_of_subjects;
				add_to_generic_tree(&main_root, *data, -2);
				add_to_generic_tree(&sum_main_root, *data, -1);

				for (int j = 0; j < main_root->data.no_of_subjects; j++)
				{
					add_to_generic_tree(&subwise_bst[j], *data, j);
				}
				prepare_student_database(main_root, no_of_records);
			}
			break;
		}
		case 8:
		{
			FILE *error_file_p;
			STUDENT_DETAILS *new_student;
			new_student = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
			int present = 0;
			error_file_p = fopen(".error_file", "r");
			int no_of_errors = 0;
			char **name;
			int *check;
			name = (char**)calloc(100, sizeof(char*));
			check = (int*)calloc(100, sizeof(int));
			if (error_file_p != NULL)
			{
				char line[100] = { '\0' };
				int i = 0, j = 0;
				printf("\t\t\t\t\t\t\t\t\tErrors Found in these entries\n\n");
				for (int l = 0; l < 100; l++)
				{
					name[l] = (char*)calloc(20, sizeof(char));
				}
				while (fgets(line, 50, error_file_p))
				{
					if (i > 100)
					{
						name = (char**)realloc(name, i * 20);
						check = (int*)realloc(check, i * sizeof(int));
					}
					sscanf(line, "%[^\n]\n", name[i++]);
					no_of_errors++;
					printf("\t\t\t\t\t\t\t\t\t%d\t%s\n", i - 1, name[i - 1]);
				}
				while (1)
				{
					char input[20] = { '\0' };
					printf("\t\t\t\t\t\t\t\t\tEnter whose details you want to enter\t");
					scanf("\n%[^\n]", input);
					int r = 0;
					while (input[r])
					{
						input[r] = tolower(input[r]);
						r++;
					}
					for (j = 0; j < i; j++)
					{
						if (strcmp(name[j], input) == 0)
						{
							strcpy(new_student->name, name[j]);
							new_student->sub_names = (char**)calloc(main_root->data.no_of_subjects, sizeof(char*));
							new_student->marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
							new_student->no_of_subjects = main_root->data.no_of_subjects;

							for (int l = 0; l < main_root->data.no_of_subjects; l++)
							{
								new_student->sub_names[l] = (char*)calloc(20, sizeof(char*));
							}

							for (int k = 0; k < main_root->data.no_of_subjects; k++)
							{
								strcpy(new_student->sub_names[k], main_root->data.sub_names[k]);
								printf("\t\t\t\t\t\t\t\t\tEnter %s marks\t", new_student->sub_names[k]);
								scanf("%d", &(new_student->marks[k]));
								if (new_student->marks[k] < 0 || new_student->marks[k]>100)
								{
									printf("\t\t\t\t\t\t\t\t\tIvalid Marks Re-Enter\n");
									k--;
								}
								else
								{
									new_student->sum += new_student->marks[k];
								}
							}
							check[j] = 1;

							search_generic(main_root, *new_student, 1,-2, &present);
							if (present == 0)
							{
								add_to_generic_tree(&main_root, *new_student, -2);
								add_to_generic_tree(&sum_main_root, *new_student, -1);

								for (int p = 0; p < main_root->data.no_of_subjects; p++)
								{
									add_to_generic_tree(&subwise_bst[p], *new_student, p);
								}
								no_of_records++;
								prepare_student_database(main_root, no_of_records);
							}
							else
							{
								printf("\t\t\t\t\t\t\t\t\t\t\t%s Already Present Hence Removing from error list\n\n", new_student->name);
							}
							break;
						}
					}
					if (j == i)
					{
						printf("\t\t\t\t\t\t\t\t\t\t\tInvalid Name Entered\n\n");
					}
					else
					{
						break;
					}
				}
			}
			fclose(error_file_p);
			error_file_p = fopen(".error_file", "w");
			if(error_file_p!=NULL)
			{
				for (int m = 0; m < no_of_errors; m++)
				{
					if (check[m] != 1)
					{
						fseek(error_file_p, 0, SEEK_END);
						fprintf(error_file_p, "%s\n", name[m]);
					}
				}
				fclose(error_file_p);
			}
			break;
		}
		case 9:
		{
			STUDENT_DETAILS *del_student;
			STUDENT_DETAILS *altered_record;
			int present = 0;
			del_student = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
			altered_record = (STUDENT_DETAILS*)calloc(1, sizeof(STUDENT_DETAILS));
			printf("\t\t\t\t\t\t\t\tEnter Whose record you want to change/delete :\t");
			scanf("\n%[^\n]", del_student->name);
			int k = 0;
			while (del_student->name[k])
			{
				del_student->name[k] = tolower(del_student->name[k]);
				k++;
			}
			search_generic(main_root,*del_student, 1, -2, &present);
			if (present == 1)
			{
				//fetch data by delete changee it here add it to trees
				memset((*altered_record).name, '\0', 20);
				altered_record->marks = (int*)calloc(main_root->data.no_of_subjects, sizeof(int));
				altered_record->sub_names = (char**)calloc(main_root->data.no_of_subjects, sizeof(char*));
				
				for (int i = 0; i < main_root->data.no_of_subjects; i++)
				{
					altered_record->sub_names[i] = (char*)calloc(20, sizeof(char));
					strcpy(altered_record->sub_names[i], main_root->data.sub_names[i]);
				}

				int k = 0;
				STUDENT_DETAILS *new_records = (STUDENT_DETAILS*)calloc(no_of_records, sizeof(STUDENT_DETAILS));
				int end_point = 0;

				main_root = generic_delete_node(main_root, *del_student, &altered_record);
				get_data_from_tree(main_root, new_records, &end_point);
				int l = 0;
				//display_all(main_root, -2, &l);
				int alter_choice = -1;
				printf("\t\t\t\t\t\t\t\tEnter Choice\n\n\t\t\t\t\t\t\t\t1.\tAlter Name\n\n\t\t\t\t\t\t\t\t2.\tAlter Sub-marks\n\n");
				printf("\t\t\t\t\t\t\t\tEnter Choice\n\t\t\t\t\t\t\t\t\t>");
				scanf("%d", &alter_choice);

				switch (alter_choice)
				{
				case 1:
				{
					printf("\t\t\t\t\t\tEnter Name :\t");
					memset(altered_record->name, '\0', 20);
					scanf("\n%[^\n]", altered_record->name);
					int i = 0;
					while (altered_record->name[i])
					{
						altered_record->name[i] = tolower(altered_record->name[i]);
						i++;
					}
					add_to_generic_tree(&main_root, *altered_record, -2);

					//deallocate_tree(sum_main_root);
					sum_main_root = NULL;

					for (int i = 0; i < main_root->data.no_of_subjects; i++)
					{
						//deallocate_tree(subwise_bst[i]);
						subwise_bst[i] = NULL;
					}

					for (i = 0; i < end_point; i++)
					{
						add_to_generic_tree(&sum_main_root, new_records[i], -1);
						for (int j = 0; j < main_root->data.no_of_subjects; j++)
						{
							add_to_generic_tree(&subwise_bst[j], new_records[i], j);
						}
					}
					add_to_generic_tree(&sum_main_root, *altered_record, -1);
					for (int i = 0; i < main_root->data.no_of_subjects; i++)
					{
						add_to_generic_tree(&subwise_bst[i], *altered_record, i);
					}

					break;
				}
				case 2:
				{
					char sub[20] = { '\0' };
					printf("\t\t\t\t\t\tEnter subject you want to alter:\t");
					scanf("\n%[^\n]", sub);
					int i = 0;
					while(sub[i])
					{
						sub[i] = tolower(sub[i]);
						i++;
					}

					for (i = 0; i < main_root->data.no_of_subjects; i++)
					{
						if (strcmp(sub, altered_record->sub_names[i]) == 0)
						{
							break;
						}
					}

					if (i == main_root->data.no_of_subjects)
					{
						printf("\t\t\t\t\t\tInvalid Subject Enterd\n\n");
					}
					else
					{
						altered_record->sum -= altered_record->marks[i];
						while (1)
						{
							printf("\t\t\t\t\t\t\tEnter %s Marks\t", altered_record->sub_names[i]);
							scanf("%d", &altered_record->marks[i]);
							if (altered_record->marks[i] >= 0 && altered_record->marks[i] <= 100)
							{
								altered_record->sum += altered_record->marks[i];
								break;
							}
							else
							{
								printf("\t\t\t\t\t\t\tInvalid Marks Enterd\n\n");
							}
						}
						add_to_generic_tree(&main_root, *altered_record, -2);

						//deallocate_tree(sum_main_root);
						sum_main_root = NULL;

						for (int i = 0; i < main_root->data.no_of_subjects; i++)
						{
							//deallocate_tree(subwise_bst[i]);
							subwise_bst[i] = NULL;
						}

						for (i = 0; i < end_point; i++)
						{
							add_to_generic_tree(&sum_main_root, new_records[i], -1);
							for (int j = 0; j < main_root->data.no_of_subjects; j++)
							{
								add_to_generic_tree(&subwise_bst[j], new_records[i], j);
							}
						}
						add_to_generic_tree(&sum_main_root, *altered_record, -1);
						for (int i = 0; i < main_root->data.no_of_subjects; i++)
						{
							add_to_generic_tree(&subwise_bst[i], *altered_record, i);
						}
					}
					break;
				}
				default:
				{
					printf("\t\t\t\t\t\t\t\t\tInvalid Choice\n\n");
					break;
				}
				}
			}
			else
			{
				printf("\t\t\t\t\t\t\t\tData Not Present to Delete\n\n");
			}
			break;
		}
		case 10:
		{
			prepare_student_database(main_root, no_of_records);
			printf("\n\t\t\t\t\t\t\tClosing Query Menu.........\t\t\n\n");
			break;
		}
		default:
		{
			printf("\t\t\t\t\tInvalid Option\n\n");
			break;
		}
		}
	}
	return 0;
}

int display_all(BST_GENERIC *root, int decider, int *no_of_items)
{
	//send root and call inorder
	printf("\t\t\t\t\t\t\tThe Students Present Are\n");
	inorder_traverse_generic(root, decider, no_of_items);
	return 0;
}

int prepare_student_database(BST_GENERIC *root, int no_of_records)
{
	int record_counter,cur_pos_of_list=0;
	FILE *database_file_p;

	STUDENT_DETAILS *list_of_existing_students;
	list_of_existing_students = (STUDENT_DETAILS*)calloc(no_of_records, sizeof(STUDENT_DETAILS));
	database_file_p = fopen(".temp_student.dat", "w+");
	fprintf(database_file_p,"%d %d\n", no_of_records, root->data.no_of_subjects);
	for (int i = 0; i < root->data.no_of_subjects; i++)
	{
		fseek(database_file_p, 0, SEEK_END);
		if (i != (root->data.no_of_subjects - 1))
		{
			fprintf(database_file_p, "%s,", root->data.sub_names[i]);
		}
		else
		{
			fprintf(database_file_p, "%s", root->data.sub_names[i]);
		}
	}
	fprintf(database_file_p, "\n");
	/*for (int i = 0; i < no_of_records; i++)
	{
		list_of_existing_students[i].marks = (int*)calloc(root->data.no_of_subjects, sizeof(int));
	}*/
	fseek(database_file_p, 0, SEEK_END);
	if (database_file_p != NULL)
	{
		get_data_from_tree(root, list_of_existing_students, &cur_pos_of_list);
		if (cur_pos_of_list >= 0)
		{
			for (int i = 0; i < cur_pos_of_list; i++)
			{
				fseek(database_file_p, 0, SEEK_END);
				fprintf(database_file_p, "%s\n", list_of_existing_students[i].name);
				for (int j = 0; j < root->data.no_of_subjects; j++)
				{
					fseek(database_file_p, 0, SEEK_END);
					fprintf(database_file_p,"%d\t", list_of_existing_students[i].marks[j]);
				}
				fseek(database_file_p, 0, SEEK_END);
				fprintf(database_file_p, "\n");
			}
		}
		else
		{
			printf("\t\t\t\t\t\t\tError Fetching Data from tree");
		}
		fclose(database_file_p);
		
		remove(".student.dat");
		
		rename(".temp_student.dat", ".student.dat");
	}
	else
	{
		printf("\t\t\t\t\t\t\t\tUnable to Write to file\n\n");
	}

	return 1;
}

int data_fetch(STUDENT_DETAILS **existing_students)
{

	int result;

	char *database_file;

	//struct to stor each record and no of rec

	int no_of_records, no_of_subjects, record_counter = 0;

	char *line, *name, *marks_line, *marks_dummy, *sub_dummy, **sub_names;

	int i, j;

	int sub_no = 0;

	int record_type = 0;

	STUDENT_DETAILS *existing_students_list;

	database_file = (char*)calloc(10, sizeof(char));


	strcpy(database_file, ".student.dat");

	FILE *database_file_p;

	if ((database_file_p = fopen(database_file, "r")) != NULL)
	{

		//free(database_file);

		result = 1;
		//We dont expect a student name being more than 20 characters
		line = (char*)calloc(1000, sizeof(char));
		fgets(line, 1000, database_file_p);

		sscanf(line, "%d %d", &no_of_records, &no_of_subjects);

		existing_students_list = (STUDENT_DETAILS*)calloc(no_of_records, sizeof(STUDENT_DETAILS));

		/*printf("no_of_record %d no_subs %d\n",no_of_records,no_of_subjects);*/

		memset(line, '\0', 1000);

		fgets(line, 1000, database_file_p);
		sub_dummy = line;
		sub_names = (char**)calloc(no_of_subjects, sizeof(char*));

		for (int i = 0; i<no_of_subjects; i++)
		{
			sub_names[i] = (char*)calloc(20, sizeof(char));
			memset(sub_names[i], '\0', 20);
		}

		i = 0, j = 0;
		while (*sub_dummy != '\n')
		{
			if (*sub_dummy == ',')
			{
				if(i<no_of_subjects)
					sub_names[i][j] = '\0';
				i++, j = 0;
				sub_dummy++;
			}
			else
			{
				sub_names[i][j++] = tolower(*sub_dummy);
				sub_dummy++;
			}
		}

		for(int i=0;i<no_of_subjects;i++)
		{
		printf("%s\n",sub_names[i]);
		}
		memset(line, '\0', 1000);

		while (fgets(line, 1000, database_file_p))
		{
			record_type++;
			if (record_type % 2 == 1)
			{
				name = (char*)calloc(10, sizeof(char));
				memset(name, '\0', 10);
				sscanf(line, "%s\n", name);
				strcpy(existing_students_list[record_counter].name, name);
				existing_students_list[record_counter].sub_names = (char**)calloc(no_of_subjects, sizeof(char*));
				for (int i = 0; i<no_of_subjects; i++)
				{
					existing_students_list[record_counter].sub_names[i] = (char*)calloc(20, sizeof(char));
					memset(existing_students_list[record_counter].sub_names[i], '\0', 20);
					strcpy(existing_students_list[record_counter].sub_names[i], sub_names[i]);
				}
				//printf("\t%s\t",existing_students_list[record_counter].name);
				free(name);
			}
			else
			{
				sub_no = 0;
				marks_line = (char*)calloc(6 * no_of_subjects + 1, sizeof(char));
				existing_students_list[record_counter].no_of_subjects = no_of_subjects;
				sscanf(line, "%[^\n]", marks_line);
				marks_dummy = marks_line;
				existing_students_list[record_counter].marks = (int*)calloc(no_of_subjects, sizeof(int));
				while (*marks_dummy)
				{
					if (*marks_dummy >= '0' && *marks_dummy <= '9')
					{
						existing_students_list[record_counter].marks[sub_no++] = strtol(marks_dummy, &marks_dummy, 10);
						existing_students_list[record_counter].sum += existing_students_list[record_counter].marks[sub_no - 1];
					}
					else
					{
						marks_dummy++;
					}
				}
				/*
				for(int i=0;i<no_of_subjects;i++)
				{
				printf("%d\t",existing_students_list[record_counter].marks[i]);
				}
				*/
				printf("\n");
				record_counter++;
				free(marks_line);
			}
			memset(line, '\0', 20);
		}

		free(line);
		fclose(database_file_p);
	}

	else
	{
		free(database_file);
		perror("DataFetch::DataBase File Not Found");
		result = -1;
	}

	*existing_students = existing_students_list;

	result = record_counter;
	//Sending number of records sent
	return result;
}

int data_validation(FILE *new_data_file_p, STUDENT_DETAILS **new_list)
{
	if (new_data_file_p == NULL)
	{
		return -1;
	}

	else
	{

		char line[1000] = { '\0' };
		int no_of_subjects = -1;
		int no_of_records = 0;
		int line_type = 0;
		int no_of_error_records = 0;
		char name[20] = { '\0' };
		FILE *error_file_p;
		error_file_p = fopen(".error_file", "w");
		STUDENT_DETAILS *list_of_students;
		list_of_students = (STUDENT_DETAILS*)calloc(1000, sizeof(STUDENT_DETAILS));
		fgets(line, 1000, new_data_file_p);
		
		sscanf(line, "%d%[^\n]", &no_of_subjects);
		
		memset(line, '\0', 1000);
		fgets(line, 1000, new_data_file_p);
		char **sub_names,*sub_dummy;
		sub_names = (char**)calloc(no_of_subjects, sizeof(char*));
		sub_dummy = line;

		for (int i = 0; i<no_of_subjects; i++)
		{
			sub_names[i] = (char*)calloc(20, sizeof(char));
			memset(sub_names[i], '\0', 20);
		}

		int i = 0, j = 0;
		while (*sub_dummy != '\n')
		{
			if (*sub_dummy == ',')
			{
				if(i<no_of_subjects)
					sub_names[i][j] = '\0';
				i++, j = 0;
				sub_dummy++;
			}
			else
			{
				sub_names[i][j++] = tolower(*sub_dummy);
				sub_dummy++;
			}
		}

		while (fgets(line, 1000, new_data_file_p))
		{
			line_type++;
			if ((line[0] >= 'a' && line[0] <= 'z') || (line[0] >= 'A' && line[0] < 'Z'))
			{
				if (line_type % 2 == 0)
				{
					line_type--;
					no_of_error_records++;
					fseek(error_file_p, 0, SEEK_END);
					fprintf(error_file_p, "%s\n", name);
				}
				memset(name, '\0', 20);
				sscanf(line, "%[^\n]", name);
				int i = 0;
				while (name[i])
				{
					name[i] = tolower(name[i]);
					i++;
				}
			}
			else
			{
				if (line_type % 2 == 1)
				{
					line_type--;
					continue;
				}
				strcpy(list_of_students[no_of_records].name, name);
				if (no_of_records > 1000)
				{
					list_of_students = (STUDENT_DETAILS*)realloc(list_of_students, no_of_records * sizeof(STUDENT_DETAILS));
				}
				char*marks_dummy = line;
				int sub_no = 0;
				list_of_students[no_of_records].no_of_subjects = no_of_subjects;
				list_of_students[no_of_records].marks = (int*)calloc(list_of_students[no_of_records].no_of_subjects, sizeof(int));
				list_of_students[no_of_records].sub_names = (char**)calloc(list_of_students[no_of_records].no_of_subjects, sizeof(char*));
				for (int i = 0; i < list_of_students[no_of_records].no_of_subjects; i++)
				{
					list_of_students[no_of_records].sub_names[i] = (char*)calloc(20, sizeof(char));
					strcpy(list_of_students[no_of_records].sub_names[i], sub_names[i]);
				}
				while (*marks_dummy)
				{
					if ((*marks_dummy >= '0' && *marks_dummy <= '9') || (*marks_dummy == '-' || *marks_dummy == '+'))
					{
						if (*marks_dummy == '-')
						{
							marks_dummy++;
							list_of_students[no_of_records].marks[sub_no++] = (-1)*strtol(marks_dummy, &marks_dummy, 10);
						}
						else if (*marks_dummy == '+')
						{
							marks_dummy++;
							list_of_students[no_of_records].marks[sub_no++] = strtol(marks_dummy, &marks_dummy, 10);
						}
						else
						{
							list_of_students[no_of_records].marks[sub_no++] = strtol(marks_dummy, &marks_dummy, 10);
						}
						if (list_of_students[no_of_records].marks[sub_no - 1] > 100 || list_of_students[no_of_records].marks[sub_no - 1] < 0)
						{
							printf("\t\t\t\t\t\t\tData Provided at %s of %s Re_enter Data\t",list_of_students[no_of_records].sub_names[sub_no-1],list_of_students[no_of_records].name);
							scanf("%d", &list_of_students[no_of_records].marks[sub_no - 1]);
						}
						list_of_students[no_of_records].sum += list_of_students[no_of_records].marks[sub_no - 1];
					}
					else
					{
						marks_dummy++;
					}

				}
				no_of_records++;
			}
		}
		if (line_type % 2 == 1)
		{
			no_of_error_records++;
			fprintf(error_file_p, "%s\n", name);
		}
		printf("\t\t\t\t\t\t\t\t\t\tThere are %d error Records\n\n", no_of_error_records);
		fclose(error_file_p);
		system("pause");
		list_of_students = (STUDENT_DETAILS*)realloc(list_of_students, no_of_records * sizeof(STUDENT_DETAILS));
		*new_list = list_of_students;
		return no_of_records;
	}

}