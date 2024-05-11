#ifndef invert_h
#define invert_h

#define SUCCESS 0
#define FAILURE 1

/*Structure for link list*/
typedef struct node
{
    char data[10];
    struct node *link;
}Slist;

/*Structure for hashtable*/
typedef struct hashtable
{
    int index;
    struct main_node *link;
}hash_t;

/*Structure for main node*/
typedef struct main_node
{
    int file_count;
    char word[20];
    struct sub_node *sublink;
    struct main_node *mainlink;
}main_n;

/*Structure for sub node*/
typedef struct sub_node
{
    int word_count;
    char filename[20];
    struct sub_node *sublink;
}sub_n;


/*Validate the arguments*/
int Validate(Slist **head, int argc,char *argv[]);

/*Insert node at the last of the list */
int insert_last(Slist **head, char *fname);

/*Create a new node*/
Slist *create_node(char *fname);

/*Create a Database*/
int create_database(Slist **head, hash_t *HashTable);

/*Create a hash_table*/
int create_hash_table(hash_t *hash_table);

/*Create a main node*/
main_n *create_main_node(char *buf, char *data);

/*Create a sub node*/
sub_n *create_sub_node(char *fname);

/*Display a database*/
int display_database(hash_t *HashTable);

/*Search a database*/
int search_database(hash_t *HashTable, char *word);

/*Update a database*/
int update_database(hash_t *Hashtbale, char *file);

/*Save a database*/
int save_database(hash_t *HashTable, const char *file);

#endif
