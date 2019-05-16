/*Helena Teixeira 93720 LEIC-T*/
/*ficheiro com as estruturas da lista duplamente ligada nas
hashtables bem como as declaracoes de funcoes relacionadas
com a estrutura*/
#ifndef HASHTABLE
#define HASHTABLE

typedef struct stru_node_hash{
	struct stru_node_hash *next,*previous;
	node *p;
}node_hash;

typedef struct{
	node_hash *head, *last;
}list_hash;


list_hash *create_list_hash();
node_hash *create_node_hash(node *a);
list_hash * add_last_hash(list_hash *l,node_hash *n);
void free_node_hash(node_hash *n);
void free_list_hash(list_hash *l);
void tratamento_lista_hash_r(node_hash *b,list_hash *l);
void remover_sem_dar_free(node_hash *b,list_hash *l);
#endif