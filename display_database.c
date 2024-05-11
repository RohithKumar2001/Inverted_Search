#include "invert.h"
#include <stdio.h>

/*function to display database*/
int display_database(hash_t *hashtable)
{
    int i;
    main_n *m_temp;
    sub_n *s_temp;
    int flag = 0;

    printf("%-12s %-12s %-12s %-12s %-12s\n","INDEX","WORD","FILECOUNT","FILENAME","WORDCOUNT");

    //loop through the hashtable
    for(i = 0; i < 27; i++)	
    {
	//check if there's data at this index
	if(hashtable[i].link != NULL)
	{
	    m_temp = hashtable[i].link;

	    //traverse through main_nodes at this index
	    while(m_temp)		
	    {										
		//print index, word, and file count of the main_node
		printf("%-12d %-12s %-13d", i, m_temp->word, m_temp->file_count);	

		//update the sub_node pointer with the main_node sublink
		s_temp = m_temp->sublink;

		//traverse through the subnodes
		while(s_temp)	
		{
		    //print the filename and wordcount
		    printf("%-12s %-13d", s_temp->filename, s_temp->word_count);		

		    //update the sub_node pointer
		    s_temp = s_temp->sublink;							
		}
		printf("\n");

		//update the main_node pointer
		m_temp = m_temp->mainlink;	
	    }
	    printf("\n");
	}
    }
    return SUCCESS;
}
