#include "invert.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*function to search database*/
int search_database(hash_t *hashtable, char *word) 
{
    int index = toupper(word[0]) % 65;

    //validate whether the index is within valid range [0, 25]
    if(index < 0 || index > 25)	
	index = 26;

    main_n *m_temp = hashtable[index].link;

    //check if the main_node at the index is NULL
    if(m_temp == NULL) 			
    {
	printf("\nHashtable index is null\n");
	return FAILURE;
    }

    printf("%-12s %-12s %-12s %-12s %-12s\n","INDEX","WORD","FILECOUNT","FILENAME","WORDCOUNT");

    //traverse through main_nodes at this index
    while(m_temp)
    {
	//compare the string in the main_node with the target word
	if(strcmp(m_temp->word, word) == 0) 
	{
	    sub_n *s_temp = m_temp->sublink;

	    //print index, word, and file count of the main_node
	    printf("%-12d %-12s %-13d", hashtable[index].index, m_temp->word, m_temp->file_count);      

	    //update the sub_node pointer with the main_node sublink
	    s_temp = m_temp->sublink;     

	    //traverse through the subnodes
	    while (s_temp)  
	    {
		//print the filename and wordcount
		printf("%-12s %-13d", s_temp->filename, s_temp->word_count); 

		//update the sub_node pointer
		s_temp = s_temp->sublink;                                                   		
	    }
	    printf("\n");
	    return SUCCESS;
	}
	//update the main_node pointer
	m_temp = m_temp->mainlink;                                                      		
    }
    printf("\n");
    printf("ERROR : Word '%s' not found in the database.\n", word);
}
