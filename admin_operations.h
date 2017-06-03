/**
* @Author: Dhawal_Wayne <wayne>
* @Date:   26-04-2017
* @Project: Mini Student Database
* @Filename: login.h
* @Last modified by:   wayne
* @Last modified time: 03-05-2017
*/

#ifndef ADMIN_OPERATIONS_H_
#define ADMIN_OPERATIONS_H_

#include "stdfx.h"

typedef struct ADMIN_DETAILS {
	char user_id[10];
	char password[10];
}ADMIN_DETAILS;

typedef struct ADMIN_LIST {
	int num_of_admins;
	ADMIN_DETAILS *admins_list;
}ADMIN_LIST;

/* can  implement root user for adding adminsor sudo users
extern char root_pass[10];
*/

extern int register_user(ADMIN_DETAILS new_user_details);


extern char * encrypt(char *password);

extern char * decrypt(char *password);


extern ADMIN_LIST fetch_admins(char *admin_filename);

extern int check_details(ADMIN_DETAILS admin_details);

extern int login(ADMIN_DETAILS admin_details);

#endif
