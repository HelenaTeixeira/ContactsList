/*Helena Teixeira 93720 LEIC-T*/
/*ficheiro com as estruturas da lista duplamente ligada ordenada
bem como declaracoes das funcoes relacionadas com a estrutura*/
#ifndef CONTACTO
#define CONTACTO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name, *local,*dominio,*n_tel;
}Contacto;

typedef struct stru_node{
	struct stru_node *next,*previous;
	Contacto *contacto;
}node;

typedef struct{
	node *head, *last;
}list;

list *create_list();
node *create_node(char *input[]);
list * add_last(list *l,node *n);
void free_node(node *n);
void free_list(list *l);
void tratamento_lista_r(node *b,list *l);
#endif

