/*Helena Teixeira 93720 LEIC-T*/
/*ficheiro com declaracoes de funcoes relacionadas com o objetivo
do enunciado, ou seja, toda a parte operacional dos comandos lidos
no main*/
#ifndef MAINOPPS
#define MAINOPPS

Contacto *fix(char *input[]);
void ler_input(char *token[4]);
void add_contacto(list *l,list_hash *hash_table[],list_hash *hash_table_email[]);
void represent(Contacto *a);
void listagem(list*l);
void procura(list_hash *hash_table[]);
void remove_contact(list *l,list_hash *hash_table[],list_hash *hash_table_email[]);
node_hash *change_email_in_l(node_hash *aux, char *input[]);
void change_email(list_hash *hash_table[] ,list_hash *hash_table_email[]);
void occ(list_hash *hash_table_email[]);

#endif