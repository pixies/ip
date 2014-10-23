#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct   lista  {
  int info ; /* info pode ser de qualquer tipo */
  struct lista *prox; /* campo que armazena endereço do próximo elemento */
} Lista;


/* Funções para lista simplesmente encadeada */
Lista* lst_cria(){
    return   NULL ;
}

Lista* lst_insere(Lista* inicio,int i){
  Lista* novo = (Lista*) malloc(sizeof(Lista));
  novo->info  =  i ;
  novo->prox  = inicio ;
  return   novo  ;
}
int  lst_vazia(Lista* inicio){
  if (inicio == NULL)
  	return 1;
  else
	return 0;
}
Lista* lst_retira(Lista* inicio,int v){
    Lista* ant = NULL; /* guarda elementoanterior */
    Lista* p = inicio;/* ponteiro p/ percorrer a lista */
  while(p != NULL && p->info != v){
      ant  =  p ;
      p  =  p->prox ;
  }
/* verifica se achou o elemento */
  if (p == NULL)
     return inicio;

  if (ant == NULL)
     inicio = p->prox;
  else
     ant->prox = p->prox;
  free(p) ;
  return inicio ;
}

void    lst_libera(Lista* inicio){
  Lista* p  =  inicio ;
  while(p != NULL )  {
     Lista* t = p->prox;
     free(p); /* libera a memória apontada por “p”*/
     p = t;   /* faz  “p” apontar para o próximo */
  }
}
Lista*  lst_busca(Lista* inicio,int v){
  Lista   *p ;
  for (p = inicio; p != NULL; p = p->prox)  {
  	if (p->info == v)
         return p ;
  }
  return NULL;     /* não achou o elemento */
}

void  lst_imprime(Lista* inicio){
  Lista* p; /*variável auxiliar para percorrer a lista */
  int contador = 1;
  for(p = inicio; p != NULL; p = p->prox){
  	printf("|Endereco do no %d:%u|\n",contador,p);
  	printf("---------------------------------\n");
	printf ( "|info = %d| prox = %u|\n ",  p->info,p->prox) ;
	printf("---------------------------------\n\n\n");
	contador++;
	Sleep(2000);

  }
}



int main()
{

    Lista  * inicio ; /* declara uma lista não iniciada */
    inicio = lst_cria(); /*inicia lista vazia */
    inicio = lst_insere(inicio,23); /* insere o elemento 23 */
    inicio = lst_insere(inicio,45); /* insere o elemento 45 */
    inicio = lst_insere(inicio,56); /* insere o elemento 56 */
    inicio = lst_insere(inicio,78); /* insere o elemento 78 */
    lst_imprime(inicio);       /* imprime: 78 56 45 23 */
    getchar();

    printf("\nRetirando o elemento 78\n\n");
    getchar();
    inicio = lst_retira(inicio,78);
    lst_imprime(inicio);
    getchar();
    printf("\nRetirando o elemento 45\n\n");
    inicio = lst_retira(inicio,45);
    lst_imprime(inicio);
    lst_libera(inicio);

    return 0;
}
