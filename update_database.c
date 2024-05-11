#include "invert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*function to update the database with data from file*/
int update_database(hash_t *hashtable, char *file) 
{
    char array[100];
    int index;

    //open the file and read the contents
    FILE *fptr = fopen(file, "r");

    //validate whether the file is successfully opened
    if (fptr == NULL) 
    {
	printf("File not found\n");
	return FAILURE;
    }

    //read string upto delimeter from the file
    while (fscanf(fptr, "%s", array) != EOF) 
    {
	//check if the starting character is '#' or not
	if (array[0] != '#') 
	    return FAILURE;

	//find the index
	index = atoi(strtok(&array[1], ";"));

	//allocate memory for a new main node
	main_n *m_new = malloc(sizeof(main_n));

	//validate whether the memory is successfully allocated
	if (m_new == NULL)
	    return FAILURE;
	m_new->mainlink = NULL;

	//copy the word and file count from the array to main node
	strcpy(m_new->word, strtok(NULL, ";"));
	m_new->file_count = atoi(strtok(NULL, ";"));

	//allocate memory for new sub node
	sub_n *s_new, *s_prev;
	s_new = malloc(sizeof(sub_n));

	//validate whether the memory is successfully allocated
	if (s_new == NULL)
	    return FAILURE;
	s_new->sublink = NULL;

	//copy the filename and word count from array to subu node
	strcpy(s_new->filename, strtok(NULL, ";"));
	s_new->word_count = atoi(strtok(NULL, ";"));

	m_new->sublink = s_new;
	s_prev = s_new;

	//loop to process subnodes
	for (int i=1; i<(m_new->file_count); i++) 
	{
	    sub_n *s_new = malloc(sizeof(sub_n));
	    if (s_new == NULL)
		return FAILURE;

	    s_new->sublink = NULL;

	    //copy the filename and word count from array to subu node
	    if (i == (m_new->file_count) - 1) 
	    {
		strcpy(s_new->filename, (strtok(NULL, ";")));
		s_new->word_count = atoi(strtok(NULL, "#"));

		s_prev->sublink = s_new;
		s_prev = s_new;
	    } 
	    else
	    {
		strcpy(s_new->filename, (strtok(NULL, ";")));
		s_new->word_count = atoi(strtok(NULL, ";"));

		s_prev->sublink = s_new;
		s_prev = s_new;
	    }
	}

	//insert the new main node to hashtable like insert last functionality
	if (hashtable[index].link == NULL)
	    hashtable[index].link = m_new;
	else 
	{
	    main_n *temp = hashtable[index].link;
	    while (temp->mainlink) 
		temp = temp->mainlink;
	    temp->mainlink = m_new;
	}
    }

    //close the file
    fclose(fptr);

    return SUCCESS;
}
