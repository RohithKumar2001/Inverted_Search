#include "invert.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*function to create a hashtable*/
int create_hash_table(hash_t *hash_table)
{
    for(int i=0; i<27; i++)
    {
	hash_table[i].index = i;
	hash_table[i].link = NULL;
    }
}

/*function to create a database*/
int create_database(Slist **head, hash_t *HashTable)
{
    int index;
    Slist *temp = *head;
    /*traverse through the single linked list*/
    while(temp != NULL)
    {
	FILE *fp;
	char buf[50];

	/*fetch the filename ad open the file*/
	fp = fopen(temp->data,"r");

	/*validate the file is successfully opened*/
	if(!fp)
	{
	    printf("The %s file is not open",temp->data);
	    return FAILURE;
	}
	printf("Contents read from %s file:\n",temp->data);

	/*read the contents of the file and store it in array(buf)*/
	while(fscanf(fp,"%s",buf) != EOF)
	{
	    printf("%s\n",buf);

	    /*find the index*/
	    index = toupper(buf[0]) % 65;

	    /*check if the hashtable link of particular index is NULL*/
	    if(HashTable[index].link == NULL)
	    {
		/*create main node and sub node*/
		HashTable[index].link = create_main_node(buf,temp->data);
	    }
	    else
	    {
		main_n *m_temp = HashTable[index].link;
		sub_n *s_temp = m_temp->sublink;

		/*traverse main node and compare the word*/
		while(m_temp != NULL)
		{
		    if(m_temp->mainlink == NULL)
		    {
			/*check if the word is same*/
			if(strcmp(m_temp->word,buf))
			{
			    /*if word is not same create main node and sub node*/
			    m_temp->mainlink = create_main_node(buf,temp->data);
			    m_temp = m_temp->mainlink;
			}
			else
			{
			    /*traverse through the sub node*/
			    while(s_temp != NULL)
			    {
				if(s_temp->sublink == NULL)
				{
				    /*check if the filename is same*/
				    if(strcmp(s_temp->filename,temp->data))
				    {
					/*if the filename is not same create subnode and increement filecount*/
					s_temp->sublink = create_sub_node(temp->data);
					m_temp->file_count++;
				    }
				    else
					s_temp->word_count++;
				}
				s_temp = s_temp->sublink;
			    }
			}
		    }
		    m_temp = m_temp->mainlink;
		}
	    }
	}
	fclose(fp);
	temp = temp->link;
    }
}

/*function to create main node*/
main_n *create_main_node(char *buf, char *data)
{
    main_n *m_new = malloc(sizeof(main_n));
    m_new->file_count = 1;
    strcpy(m_new->word,buf);
    m_new->sublink = create_sub_node(data);
    m_new->mainlink = NULL;
    return m_new;
}

/*function to create sub node*/
sub_n *create_sub_node(char *fname)
{
    sub_n *s_new = malloc(sizeof(sub_n));
    s_new->word_count = 1;
    strcpy(s_new->filename,fname);
    s_new->sublink = NULL;
    return s_new;
}
