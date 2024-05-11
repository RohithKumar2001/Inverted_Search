#include "invert.h"
#include <stdio.h>
#include <string.h>

int save_database(hash_t *hashtable, const char *file) 
{
    //validate whether the file is .txt extension file
    if(strstr(file,".txt"))
    {
	//open the file in write mode
	FILE *fp = fopen(file, "w");

	//check if the file is successfully opened
	if (fp == NULL)
	{
	    printf("Error opening file: %s\n", file);
	    return FAILURE;
	}

	//loop through the hashtable
	for(int i = 0; i <= 26; i++) 					
	{
	    main_n *m_temp = hashtable[i].link;

	    //traverse through each main node
	    while(m_temp != NULL) 					
	    {
		//get the current sub node
		sub_n *s_temp = m_temp->sublink;

		//print main node parts to the file
		fprintf(fp, "#%d;", i);//index				
		fprintf(fp, "%s;", m_temp->word);//word			
		fprintf(fp, "%d", m_temp->file_count);//file count	

		//traverse through each sub_node
		while(s_temp != NULL)
		{
		    fprintf(fp, ";");
		    fprintf(fp, "%s;", s_temp->filename);//filename
		    fprintf(fp, "%d", s_temp->word_count);//word count

		    //move to the next sub node
		    s_temp = s_temp->sublink;
		}
		//end of sub_nodes for this main_node
		fprintf(fp, "#\n");				

		//move to next main node
		m_temp = m_temp->mainlink;
	    }
	}
	//close the file
	fclose(fp);										
    }
    else
    {
	printf("ERROR : \"%s\" file is not \".txt\" extension\n",file);
	return FAILURE;
    }

    printf("Database saved to file: %s\n", file);
    return SUCCESS;
}
