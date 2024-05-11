#include "invert.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*function to validate whether the CLA are passed and */
int Validate(Slist **head, int argc, char *argv[])
{
    FILE *fp;
    for(int i=1; i<=(argc-1); i++)
    {
	/*check the file passed through the CLA is .txt extension file*/
	if(!strstr(argv[i],".txt"))
	{
	    puts("ERROR : Please pass the \".txt\" file\nLike : ./a.out file1.txt file2.txt ...");
	    return FAILURE;
	}
	else
	{
	    /*check file availability*/
	    if(fp = fopen(argv[i],"r"))
	    {
		fseek(fp,0,SEEK_END);
		/*check for the file size*/
		if(ftell(fp))
		{
		    /*add the filename to the single linked list*/
		    if(insert_last(head,argv[i]) != SUCCESS)
			continue;
		    else
			printf("%s is present and added to the list\n",argv[i]);
		}
		else
		{
		    printf("ERROR : \"%s\" file is empty\n",argv[i]);
		    continue;
		}
	    }
	    else
	    {
		printf("ERROR : \"%s\" file does'nt exist\n",argv[i]);
		continue;
	    }
	}
    }
}

/*insert the node in the list at last*/
int insert_last(Slist **head, char *fname)
{
    if(*head == NULL)
    {
	*head = create_node(fname);
	return SUCCESS;
    }
    Slist *temp = *head;
    while(temp != NULL)
    {
	/*check for the duplicate file and then add the file to the list*/
	if(strcmp(fname,temp->data))
	{
	    if(temp->link == NULL)
		break;
	    temp = temp->link;
	}
	else
	{
	    printf("ERROR : \"%s\" file is DUPLICATE FILE\n",fname);
	    return FAILURE;
	}
    }
    temp->link = create_node(fname);
    return SUCCESS;
}

/*Create node update the parts of node*/
Slist *create_node(char *fname)
{
    Slist *new = malloc(sizeof(Slist));
    strcpy(new->data,fname);
    new->link = NULL;
    return new;
}
