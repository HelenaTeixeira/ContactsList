/*Helena Teixeira 93720 LEIC-T*/

#include "headerfinal16.h"
#include "headerhash.h"
#include "tableopps.h"
#include "mainopps.h"

#define M 621
/*create_list_hash():cria uma lista do tipo list_hash
com a cabeca e o fim inicializados a NULL*/
list_hash *create_list_hash(){
	list_hash *l = malloc(sizeof(list_hash));
	l->head =NULL;
	l->last = NULL;
	return l;
}
/*create_list():cria uma lista do tipo list com a cabeca
e o fim inicializados a NULL*/
list *create_list(){
	list *l = malloc(sizeof(list));
	l->head =NULL;
	l->last = NULL;
	return l;
}
/*fix(input recebido):cria um contacto, ou seja, associa o
nome, a parte local do email, o dominio do email e o numero
de telefone*/
Contacto *fix(char *input[]){
	Contacto *aux= malloc(sizeof(Contacto));

	aux->name=malloc(sizeof(char)*(strlen(input[0])+1));
	strcpy(aux->name,input[0]);
	
	aux->local= malloc(sizeof(char)*(strlen(input[1])+1));
	strcpy(aux->local,input[1]);

	aux->dominio= malloc(sizeof(char)*(strlen(input[2])+1));
	strcpy(aux->dominio,input[2]);

	aux->n_tel=malloc(sizeof(char)*(strlen(input[3])+1));
	strcpy(aux->n_tel,input[3]);
	return aux;
}
/*create_node(input recebido):cria um node com o pointer
previous e o next a NULL bem como chama a funcao que cria
o contacto (fix) neste node*/
node *create_node(char *input[]){
	node *n = malloc(sizeof(node));
	n->previous = NULL;
	n->next = NULL;
	n->contacto = fix(input);
	return n;
}
/*create_node_hash(node):cria um node_hash com o pointer
previous e o next a NULL bem como aponta p para o node recebido*/
node_hash *create_node_hash(node *a){
	node_hash *n=malloc(sizeof(node_hash));
	n->previous=NULL;
	n->next=NULL;
	n->p= a;
	return n;
} 
/*add_last(list,node): adiciona o node recebido no fim da lista
list recebida*/
list * add_last(list *l,node *n){
	n->previous = l->last;
	if(!l->head) {
		l->head = n;
	}
	if(l->last)
		l->last->next = n;
	l->last = n;
	return l;
}
/*add_last_hash(list_hash,node_hash): adiciona o node_hash
recebido no fim da lista list_hash recebida*/
list_hash * add_last_hash(list_hash *l,node_hash *n){
	n->previous = l->last;
	if(!l->head) {
		l->head = n;
	}
	if(l->last)
		l->last->next = n;
	l->last = n;
	return l;
}
/*free_node(node):da free do node recebido*/
void free_node(node *n){
	free(n->contacto->name);
	free(n->contacto->local);
	free(n->contacto->dominio);
	free(n->contacto->n_tel);
	free(n->contacto);
	free(n);
}
/*free_list(list):da free da list recebida*/
void free_list(list *l){
	node *temp=l->head;
	while(temp){
		l->head = temp->next;
		free_node(temp);
		temp = l->head;
	}
	free(l);
}
/*free_node_hash(node_hash):da free do node_hash recebido*/
void free_node_hash(node_hash *n){
	free(n);
}
/*free_list_hash(list_hash):da free da list_hash recebida*/
void free_list_hash(list_hash *l){
	node_hash *temp=l->head;
	while(temp){
		l->head = temp->next;
		free_node_hash(temp);
		temp = l->head;
	}
	free(l);
}
/*hash_function(string):retorna o indice em que a string e
colocada na hash table(retirada do powerpoint da aula)*/
int hash_function(char *s){
	int indice=0;
	int a= 127;
	for(;*s != '\0';s++)
		indice = (a*indice + *s)%M;
	return indice;
}
/*inicializa_table(hash table dos nomes):coloca cada slot da
hash table a NULL*/
void inicializa_table(list_hash *hash_table[]){
	int x;
	for(x=0;x<M;x++){
		hash_table[x] = NULL;
	}
}
/*inicializa_table(hash table dos dominios):coloca cada slot da
hash table a NULL*/
void inicializa_table_email(list_hash *hash_table_email[]){
	int x;
	for(x=0;x<M;x++){
		hash_table_email[x] = NULL;
	}
}
/*free_table(hash table dos nomes):da free das list_hash 
que existirem nos slots da hash table recebida*/
void free_table(list_hash *hash_table[]){
	int x;
	for(x=0;x<M;x++){
		if(hash_table[x]!=NULL)
			free_list_hash(hash_table[x]);
	}
}
/*free_table_email(hash table dos dominios):da free das list_hash 
que existirem nos slots da hash table recebida*/
void free_table_email(list_hash *hash_table_email[]){
	int x;
	for(x=0;x<M;x++){
		if(hash_table_email[x]!=NULL)
			free_list_hash(hash_table_email[x]);
	}
}
/*ler_input(array de pointers):funcao que recebe o input e separa
o conteudo pelos' 'e '@' pondo os respetivos pointers no array recebido*/
void ler_input(char *token[4]){				
	int i;
	static char input[1600];
	fgets(input,1600, stdin);
	
	token[0]=strtok(input," @\n");
	for (i=1;i<4;i++){
		token[i]=strtok(NULL, " @\n");
	}
}
/*find_name(string,hashtable nomes):retorna o node hash
correspondente ao nome que estamos a procura na hash table
(se nao houver retorna NULL)*/
node_hash *find_name(char nome[],list_hash *hash_table[]){
	node_hash *temp;
	int indice=hash_function(nome);
	if((hash_table[indice])==NULL)
		return NULL;
	else{
		temp=hash_table[indice]->head;
		while(temp){
			if(strcmp(temp->p->contacto->name, nome)==0)
				return temp;
			temp= temp->next;
		}
	}
	return NULL;
}

/*insert_in_table(nome,node a inserir,hash_table dos emails):
coloca a lista com o node inserido nela no slot certo da table*/
void insert_in_table(char nome[],node *a,list_hash *hash_table[]){
	node_hash *b;
	list_hash *ldl;
	int indice=hash_function(nome);
	if(hash_table[indice]==NULL){
		ldl= create_list_hash();
		b= create_node_hash(a);
		add_last_hash(ldl,b);
		hash_table[indice]=ldl;
	}
	else{
		ldl= hash_table[indice];
		b= create_node_hash(a);
		add_last_hash(ldl,b);
	}
}
/*insert_in_table(nome,node a inserir,hash_table dos nomes):
coloca a lista com o node inserido nela no slot certo da table*/
void insert_in_table_email(char dominio[],node *a,list_hash *hash_table_email[]){
	node_hash *b;
	list_hash *ldl;
	int indice= hash_function(dominio);
	if(hash_table_email[indice]==NULL){
		ldl= create_list_hash();
		b=create_node_hash(a);
		add_last_hash(ldl,b);
		hash_table_email[indice]=ldl;
	}
	else{
		ldl=hash_table_email[indice];
		b=create_node_hash(a);
		add_last_hash(ldl,b);
	}
}
/*add_contacto(list,hashtable nomes, hash table email):chama as
funcoes q inserem um contacto na list recebida e coloca tambem um
node_hash relativo ao contacto nas duas hash tables recebidas*/
void add_contacto(list *l,list_hash *hash_table[],list_hash *hash_table_email[]){
	char *input[4];
	node *a;
	node_hash *b;
	ler_input(input);
	b=find_name(input[0],hash_table);
	if(b!=NULL){
		printf("Nome existente.\n");
	} else {
		a =create_node(input);
		l= add_last(l,a);
		insert_in_table(input[0],a,hash_table);
		insert_in_table_email(input[2],a,hash_table_email);
	}

}
void represent(Contacto *a){
	printf("%s %s@%s %s\n",a->name,a->local,a->dominio,a->n_tel);
}
/*listagem(list):representa todos os elementos da list recebida*/
void listagem(list*l){
	node *temp= l->head;
	while(temp){
		represent(temp->contacto);
		temp = temp->next;
	}
}

/*procura(hash table):chama a funcao para procurar o nome e se
este existir representa o*/
void procura(list_hash *hash_table[]){
	char *input[4];
	node_hash *a;
	ler_input(input);
	a = find_name(input[0],hash_table);
	if(a){
		represent(a->p->contacto);
	}
	else
		printf("Nome inexistente.\n");
}
/*tratamento_lista_r(node,list):trata de fazer as alteracoes
necessarias aos pointers next e previous para remover o node*/
void tratamento_lista_r(node *b,list *l){
	if(b==l->head)
		l->head= b->next;
	if(b==l->last)
		l->last=b->previous;
	if(b->previous)
		b->previous->next=b->next;
	if(b->next)
		b->next->previous=b->previous;
	free_node(b);
}
/*tratamento_lista_hash_r(node,list):trata de fazer as alteracoes
necessarias aos pointers next e previous para remover o node_hash*/
void tratamento_lista_hash_r(node_hash *b,list_hash *l){
	if(b==l->head)
		l->head= b->next;
	if(b==l->last)
		l->last=b->previous;
	if(b->previous)
		b->previous->next=b->next;
	if(b->next)
		b->next->previous=b->previous;
	free_node_hash(b);
}
/*find_email(dominio,nome,hash_table_email):retorna o node_hash
correspondente ao dominio e nome que procuramos*/
node_hash *find_email(char dominio[],char nome[],list_hash *hash_table_email[]){
	node_hash *temp;
	int indice= hash_function(dominio);
	if(hash_table_email[indice]==NULL)
		return NULL;
	else{
		temp= hash_table_email[indice]->head;
		while(temp){
			if( strcmp(temp->p->contacto->name,nome)==0)
				return temp;
			temp=temp->next;
		}
	}
	return NULL;
}
/*remove_contact(list,hash_table nomes, hash_table_emails):
remove contacto da list bem como os node_hash das has tables
que apontam para esse node q vai ser removido*/
void remove_contact(list *l,list_hash *hash_table[],list_hash *hash_table_email[]){
	char *input[4];
	int l_n,l_e;
	node_hash *a;
	node_hash *b;
	ler_input(input);
	l_n = hash_function(input[0]);
	a= find_name(input[0],hash_table);
	if(a){
		l_e = hash_function(a->p->contacto->dominio);
		b=find_email(a->p->contacto->dominio,input[0],hash_table_email);
		tratamento_lista_hash_r(b,hash_table_email[l_e]);
		tratamento_lista_r(a->p,l);
		tratamento_lista_hash_r(a,hash_table[l_n]);
	}
	else
		printf("Nome inexistente.\n");

}
/*change_email(node_hash,input): altera o email na list pelo
recebido no input*/
node_hash *change_email_in_l(node_hash *aux, char *input[]){
	aux->p->contacto->local=realloc(aux->p->contacto->local,sizeof(char)*(strlen(input[1])+1));
	strcpy(aux->p->contacto->local,input[1]);
	aux->p->contacto->dominio=realloc(aux->p->contacto->dominio,sizeof(char)*(strlen(input[2])+1));
	strcpy(aux->p->contacto->dominio,input[2]);
	return aux;
}
/*remover_sem_dar_free(node_hash,list_hash):trata de fazer as alteracoes
necessarias aos pointers next e previous para inserir numa nova
lista o q vai ser retirado de outra*/
void remover_sem_dar_free(node_hash *b,list_hash *l){
	if(b==l->head)
		l->head= b->next;
	if(b==l->last)
		l->last=b->previous;
	if(b->previous)
		b->previous->next=b->next;
	if(b->next)
		b->next->previous=b->previous;
}
/*change_email(hash_table nomes, hash_table_email): muda o email
 e muda a posicao na hash_table_email quando alterado o dominio*/
void change_email(list_hash *hash_table[] ,list_hash *hash_table_email[]){
	int l_e;
	node_hash *aux,*temp,*a;
	char *input[4];
	ler_input(input);
	aux = find_name(input[0],hash_table);
	temp = aux;
	if(aux){
		a =find_email(temp->p->contacto->dominio,input[0],hash_table_email);
		l_e = hash_function(temp->p->contacto->dominio);
		remover_sem_dar_free(a,hash_table_email[l_e]);
		aux= change_email_in_l(aux,input);
		insert_in_table_email(input[2],a->p,hash_table_email);
		free_node_hash(a);
	}
	else{
		printf("Nome inexistente.\n");
	}
}
/*occ(hash_table_email):vai ao slot da hash table do dominio dado
e conta quantas vezes ocorre*/
void occ(list_hash *hash_table_email[]){
	char *input[4];
	int cnt=0;
	int indice;
	node_hash *temp;
	ler_input(input);
	indice = hash_function(input[0]);

	if(hash_table_email[indice]!=NULL){
		temp=hash_table_email[indice]->head;
		while(temp){
			if (strcmp(temp->p->contacto->dominio,input[0])==0)
				cnt++;
			temp= temp->next;
		}
	}
	printf("%s:%d\n",input[0],cnt);
}
