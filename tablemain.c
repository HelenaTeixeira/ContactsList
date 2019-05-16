/*Helena Teixeira 93720 LEIC-T*/
#include "headerfinal16.h"
#include "headerhash.h"
#include "tableopps.h"
#include "mainopps.h"

#define M 621
int main(){
	int r=1;
	char c;
	list_hash *hash_table[M];
	list_hash *hash_table_email[M];
	list *l= create_list();
	inicializa_table(hash_table);
	inicializa_table_email(hash_table_email);
	while(r){
		switch(c= getchar()){
			case 'a':
				getchar();
				add_contacto(l,hash_table,hash_table_email);
				break;
			case 'l':
				getchar();
				listagem(l);
				break;
			case 'p':
				getchar();
				procura(hash_table);
				break;
			case 'r':
				getchar();
				remove_contact(l,hash_table,hash_table_email);
				break;
			case 'e':
				getchar();
				change_email(hash_table,hash_table_email);
				break;
			case 'c':
				getchar();
				occ(hash_table_email);
				break;
			case 'x':
				r=0;
				break;
			default:
				break;
		}
	}
	free_table_email(hash_table_email);
	free_table(hash_table);
	free_list(l);
	return 0;
}