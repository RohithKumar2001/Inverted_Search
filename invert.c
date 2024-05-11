#include "invert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*main function for invert search, collect the no. of arguments and arguments passed through the command line*/
int main(int argc, char *argv[])
{
    /*declare the hashtable,pointer and variables*/
    hash_t hash_table[27];
    int option,flag =0;
    Slist *head = NULL;
    /*check if the command line arguments are passed*/
    if(argc > 1)
    {
	Validate(&head,argc,argv);
	printf("Validation of CLA is Successful\n");
    }
    else
    {
	puts("ERROR : Please pass proper arguments\nLike : ./a.out file1.txt file2.txt ...");
	return FAILURE;
    }
    /*function call for creating hashtable*/
    create_hash_table(hash_table);
    /*super loop to perform operations*/
    while(1)
    {
	/*display the menu and read the option for operation*/
	puts("----------Menu----------\n1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database\n6. Exit");
	printf("Enter the option : ");
	scanf("%d",&option);
	char word[20];
	char file[20];
	char updt_file[20];
	switch(option)
	{
	    case 1:
		/*create database case, call the funtion to create a database*/
		if(create_database(&head,hash_table) == SUCCESS)
		{
		    flag = 1;
		    printf("INFO : Create database is Successful\n");
		}
		else
		    printf("ERROR : Creation of database is not possible\n");
		break;
	    case 2:
		/*display database case, call the function to display a database*/
		if(display_database(hash_table) == SUCCESS)
		    printf("INFO : Display database is Successful\n");
		else
		    printf("ERROR : Database cannot be displayed\n");
		break;
	    case 3:
		/*search database case, call the function to search a word in the database*/
		printf("Enter the Word to be searched : ");
		scanf("%s",word);
		if(search_database(hash_table,word) == SUCCESS)
		    printf("INFO : Search database is Successful\n");
		else
		    printf("ERROR : Search database is not possible\n");
		break;
	    case 4:
		/*update database case, check if database is not created and then call the function to update a database*/
		if(flag == 0)
		{
		    printf("Enter the File : ");
		    scanf("%s",updt_file);
		    if(update_database(hash_table, updt_file) == SUCCESS)
			printf("INFO : Update database is Successful\n");
		    else
		    	printf("ERROR : Update database is not possible\n");
		    break;
		}
		else
		{
		    printf("ERROR : Update database is not possible\nDatabase is already created\n");
		    break;
		}
	    case 5:
		/*save database case, call the function to save a database*/
		printf("Enter the filename : ");
		scanf("%s",file);
		if(save_database(hash_table,file) == SUCCESS)
		    printf("INFO : Save database is Successful\n");
		else
		    printf("ERROR : Save database is not possible\n");
		break;  
	    case 6:
		/*Exit case, terminate the program*/
		exit(0);
	    default :
		printf("ERROR : Please select proper option within 1 to 5 for operations and 6 to exit\n");
	}
    }
}
