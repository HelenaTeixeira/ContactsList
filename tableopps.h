/*Helena Teixeira 93720 LEIC-T*/
/*ficheiro com as declaracoes das funcoes relacionadas com
as hashtables*/
#ifndef TABLEOPPS
#define TABLEOPPS

#define M 621

int hash_function(char *s);
void inicializa_table(list_hash *hash_table[]);
void inicializa_table_email(list_hash *hash_table_email[]);
void free_table(list_hash *hash_table[]);
void free_table_email(list_hash *hash_table_email[]);
node_hash *find_name(char nome[],list_hash *hash_table[]);
void insert_in_table(char nome[],node *a,list_hash *hash_table[]);
void insert_in_table_email(char dominio[],node *a,list_hash *hash_table_email[]);
node_hash *find_email(char dominio[],char nome[],list_hash *hash_table_email[]);

#endif