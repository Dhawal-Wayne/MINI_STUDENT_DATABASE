/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   30-04-2017
* @Project: Mini Student Database
* @Filename: login.c
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/

#include "admin_operations.h"

/*
Since Number of Admins will be less
implementing them in an array structure
and using a linear seach algorithm
*/

ADMIN_LIST fetch_admins(char *admin_filename)
{
	FILE *admin_file;
	admin_file = fopen(admin_filename, "r");

	ADMIN_DETAILS *admin_list = NULL;
	char *record;
	char *user_id, *password;
	int initial_no_admins = 100;

	int i = 0;

	if (admin_file != NULL)
	{
		record = (char*)calloc(25, sizeof(char));
		password = (char*)calloc(10, sizeof(char));
		user_id = (char*)calloc(10, sizeof(char));
		admin_list = (ADMIN_DETAILS*)calloc(initial_no_admins, sizeof(ADMIN_DETAILS));
		while (fgets(record, 100, admin_file))
		{
			if (i >= 100)
			{
				admin_list = (ADMIN_DETAILS*)realloc(admin_list, ++initial_no_admins);
			}
			sscanf(record, "%s %s", user_id, password);

			strcpy(admin_list[i].password, password);
			strcpy(admin_list[i].user_id, user_id);

			i++;

			memset(record, '\0', 25);
			memset(password, '\0', 10);
			memset(user_id, '\0', 10);
		}

		fclose(admin_file);
	}
	else
	{
		printf("Admin File Missing\n");
	}

	return (ADMIN_LIST) { i, admin_list };
}


char* encrypt(char *password)
{
	char *encrypt_pass;
	encrypt_pass = (char*)calloc(10, sizeof(char));
	memset(encrypt_pass, '\0', 10);
	int key = '\012';

	int i = 0;

	if (password[i] == '\0')
	{
		perror("Got an empty password");
		return '\0';
	}

	while (password[i] != '\0')
	{
		encrypt_pass[i] = password[i] - key;
		i++;
	}

	return encrypt_pass;
}

char* decrypt(char *password)
{
	char *real_pass;
	real_pass = (char*)calloc(10, sizeof(char));
	memset(real_pass, '\0', 10);

	int key = '\012';

	int i = 0;

	if (password[i] == '\0')
	{
		perror("Got a empty password");
		return '\0';
	}

	while (password[i] != '\0')
	{
		real_pass[i] = password[i] + key;
		i++;
	}
	return real_pass;
}

int check_details(ADMIN_DETAILS admin_details)
{
	ADMIN_LIST admin_list;
	char admin_filename[] = ".adminfile.txt";
	admin_list = fetch_admins(admin_filename);

	int i = 0;

	while (i<admin_list.num_of_admins)
	{
		if (strcmp(admin_list.admins_list[i].user_id, admin_details.user_id) == 0)
		{
			if (strcmp(admin_details.password, decrypt(admin_list.admins_list[i].password)) == 0)
			{
				if (strcmp(admin_details.user_id, "root") == 0)
				{
					//5 is magic number (atleast of me) hence for root
					return 5;
				}
				//printf("Login Correct\n");
				return 1;
			}
			else
			{
				//printf("Password Incorrect\n");
				return 0;
			}
		}
		i++;
	}
	return -1;
}


int login(ADMIN_DETAILS admin_details)
{
	int  result;
	if ((result = check_details(admin_details)) == 5)
	{
		printf("\t\t\t\t\t\t\t\t\t\tRoot Logged In\n");
	}

	else if (result == 1)
	{
		printf("\t\t\t\t\t\t\t\t\t\t\tLogged In\n");
	}

	else if (result == 0)
	{
		printf("\t\t\t\t\t\t\t\t\t\t\tInvalid password\n");
	}
	else
	{
		printf("\t\t\t\t\t\t\t\t\t\t\tInvalid Creditentials\n");
	}

	return result;
}

int register_user(ADMIN_DETAILS new_user_details)
{
	int result;

	char admin_filename[] = ".adminfile.txt";

	FILE *admin_file;

	if ((result = check_details(new_user_details)) == -1)
	{
		if ((admin_file = fopen(admin_filename, "a")) != NULL)
		{
			fprintf(admin_file, "%s %s\n", new_user_details.user_id, encrypt(new_user_details.password));
			fclose(admin_file);
			return 1;
		}

		else
		{
			fclose(admin_file);
			return -1;
		}
	}

	else
	{
		return 0;
	}
}
