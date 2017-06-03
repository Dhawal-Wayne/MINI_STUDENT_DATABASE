/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   30-04-2017
* @Project: Mini Student Database
* @Filename: student_marks_system.c
* @Last modified by:   wayne
* @Last modified time: 01-05-2017
*/



#include "stdfx.h"

int main()
{
	int result, qury_result, reg_result;

	int choice;

	char *user_id, *password, *newuser_id, *newuser_pass;
	user_id = (char*)calloc(10, sizeof(char));
	password = (char*)calloc(10, sizeof(char));



	ADMIN_DETAILS login_details, user_register;

	while (1)
	{
		choice = -1;
		system("cls");
		printf("\n\n\n\t\t\t\t\t\t\t\t\tWelcome To My Mini Student DataBase\n\n\n");

		printf("\n\n\n\t\t\t\t\t\t\t\t\t    Enter Your Creditentials\n\n\n\n");

		printf("\tUserId: ");
		scanf("%s", user_id);

		printf("\tPassword: ");
		scanf("%s", password);

		strcpy(login_details.user_id, user_id);
		strcpy(login_details.password, password);

		if ((result = login(login_details))>0)
		{

			while (choice != 2)
			{
				printf("\n\n\t\t\t\t\t\t\t\tAvailable Options:\n\n");
				if (result == 5)
					printf("\t\t\t\t\t\t\t\t\t\t0:\tAdd Admin-User\n\n");
				printf("\t\t\t\t\t\t\t\t\t\t1:\tOpen Query\n\n");
				printf("\t\t\t\t\t\t\t\t\t\t2:\tExit\n\n");
				printf("\t\t\t\t\t\t\t\tYour Option :");
				scanf("%d", &choice);

				switch (choice)
				{
				case 1:
					if ((qury_result = start_query_processor()) == -1)
					{
						printf("Failed to start query\n");
					}
					break;

				case 2:
					printf("\n\n\n\t\t\t\t\t\t\t\t\t\tBye! Bye! %s\n\n\n", login_details.user_id);
					exit(0);
					break;

				case 0:
					if (result == 5)
					{
						while (1)
						{
							newuser_id = (char*)calloc(10, sizeof(char));
							newuser_pass = (char*)calloc(10, sizeof(char));
							printf("\tEnter New User ID :");
							scanf("%s", newuser_id);
							printf("\tEnter New User Password :");
							scanf("\n%s", newuser_pass);
							strcpy(user_register.user_id, newuser_id);
							strcpy(user_register.password, newuser_pass);

							if ((reg_result = register_user(user_register)) == 1)
							{
								printf("\t\tRegisterd User : %s", user_register.user_id);
								break;
							}
							else if (reg_result == 0)
							{
								printf("\t\t\t\tUserID Already Present\n");
							}
							else
							{
								printf("\t\t\t\tRegistration Failed\n");
								break;
							}

						}

						break;
					}
				default:
					printf("Invalid Option\n");
					break;
				}

			}
		}

		else if (result == 0)
		{
			printf("Main::Invalid password\n");
		}

		else
		{
			printf("Main::Invaid Creditentials\n");
		}

		//   sleep(2);

	}
	return 0;
}
