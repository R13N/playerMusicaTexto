#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int menu();
void InserirMusica();
void ListarMusicas();
void BuscarMusicas();
void Sair();
void IncializarAcervo();
void InsereItemNaLista(struct Musica musica);

struct Musica {
  char titulo[50];
  char artista[50];
  float duracao = 0;
  struct Musica *prox;
} *Head;

int main(int argc, char const *argv[])
{
  setlocale(LC_ALL, "Portuguese");

  int opcao;
  char resp;

  Head = NULL;


  IncializarAcervo();

  while(1)
  {
    opcao = menu();

    switch (opcao)
    {
    case 1: //LISTAR MÚSICAS
      ListarMusicas();
      break;
    case 2: //INSERIR MÚSICA
      InserirMusica();
      break;
    case 3:
      BuscarMusicas();
      break;
    case 4:
      Sair();
      break;
    default:
      printf("Opção inválida.");
      break;
    }
  
  }
  return 0;
}

int menu()
{
  int op, c;
  // system("clear");
  printf("************************\n\n");
  printf("Playslist de Músicas\n");
  printf("1 - Listar Músicas\n");
  printf("2 - Inserir Música\n");
  printf("3 - Procurar Música\n");
  printf("4 - Sair\n\n");
  printf("Digite uma opção: ");
  printf("\n\n");
  printf("************************\n");
  scanf("%d", &op);

  while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer
  system("clear");
  return op;
}

void InserirMusica()
{
  printf("Inserir Música.\n");
  int c;

  Musica *NovaMusica;
  NovaMusica = (struct Musica *)malloc(sizeof(struct Musica));
  Musica *ElementoVarredura;
  
  // you dont neeed to allocate memory for this since this is just a pointer
  // this is actually going to cause a "memory leak", since this will not be referenced
  // by any variable after this function returns, you will never be able to free() this memory
  // again. 
  // ElementoVarredura = (struct Musica *)malloc(sizeof(struct Musica));

  printf("\nDados da música a ser inserida: ");
  printf("\nTítulo: ");
  fgets(NovaMusica->titulo, 49, stdin);
  printf("Artista: ");
  fgets(NovaMusica->artista, 49, stdin);
  printf("Duração: ");
  scanf("%f", &NovaMusica->duracao);
  while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer


  // you can change this function to use the InsereItemNaLista() too if you want
  // instead of keeping this code duplicated here.
  if(Head == NULL)
  {
    Head = NovaMusica;
    Head->prox = NULL;
  }
  else
  {
    ElementoVarredura = Head;
    while (ElementoVarredura->prox != NULL)
      ElementoVarredura = ElementoVarredura->prox;

    ElementoVarredura->prox = NovaMusica;
    NovaMusica->prox = NULL;
  }
}

void BuscarMusicas()
{
  char tituloBuscado[50];
  int c;

  Musica *ElementoVarredura;

  printf("Digite o título da música a ser pesquisado: ");
  fgets(tituloBuscado, 49, stdin);
  // while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer

  ElementoVarredura = Head;

  while (ElementoVarredura != NULL)
  {
    
    // when comparing strings, the == actually compares the memory addresses that
    // the strings (pointers) are stored, not actually the content of the strings
    // you need to use a function like strcmp() that actually will de-reference each char of the string
    // and compare one by one
    // if(ElementoVarredura->titulo == tituloBuscado) {
    if( strcmp(ElementoVarredura->titulo, tituloBuscado) == 0 ) {
      printf("Título: %s \n", ElementoVarredura->titulo);
      printf("Artista: %s \n", ElementoVarredura->artista);
      printf("Duração: %2.2fmin \n", ElementoVarredura->duracao);
    }

    ElementoVarredura = ElementoVarredura->prox;

  }
  printf("\n");

  getchar();
  return;
}

void ListarMusicas()
{
  
  // starts pointing to the head of the list
  // since ElementoVarredura is a pointer, you don't need to allocate memory for this
  // it's just pointing to a memory address where the struct is stored, not actually storing the struct
  Musica *ElementoVarredura = Head;

  // while there's items in the list... 
  // note that if list is empty it won't even enter the while loop
  while (ElementoVarredura != NULL)
  {
    printf("\n####################################\n");
    printf("Título: %s", ElementoVarredura->titulo);
    printf("Artista: %s", ElementoVarredura->artista);
    printf("Duração: %2.2f", ElementoVarredura->duracao);
    ElementoVarredura = ElementoVarredura->prox;
  }
  printf("\n");
  getchar();
  return;
  
}


void IncializarAcervo() {

  // this is a local allocated array, meaning when this function returns, the memory allocated for
  // the acervo[] array is lost.
  struct Musica acervo[] = {
    { "Living on a Prayer\n", "Bon Jovi\n", 3.00, NULL},
    { "Vai Lacraia\n", "MC Serginho\n", 3.00, NULL},
    { "Faroeste Caboclo\n", "Legiao Urbana\n", 3.00, NULL},
    { "O Tikaco eh foda\n", "Bloco Tikaco\n", 3.00, NULL},
    { "Boate Azul\n", "Nao Lembro quem canta\n", 3.00, NULL}
  };
  // Dont forget to update the size here if you add more songs.
  // there are ways to calculate the size of the array automatically,
  // you can google it :)
  unsigned int tamanhoAcervo = 5;

  for(int i = 0; i < tamanhoAcervo; i++) {
    
    InsereItemNaLista(acervo[i]);

  }
  
}

void InsereItemNaLista(struct Musica musica) {

  // here we need to allocate memory because we're copying data from the local array "acervo",
  // into the linked list
  struct Musica* NovaMusica = (struct Musica *) malloc(sizeof(struct Musica));
  // note that NovaMusica->titulo = musica.titulo won't work, because you would be simply
  // making the NovaMusica pointer point to the string in the musica struct, which is locally defined
  // in the other function and would be lost after the function returns.
  // we need to use strcpy() which copies the string, char by char, onto the other string.
  strcpy(NovaMusica->titulo, musica.titulo);
  strcpy(NovaMusica->artista, musica.artista);
  NovaMusica->duracao = musica.duracao;
  NovaMusica->prox = NULL;

  if(Head == NULL)
  {
    Head = NovaMusica;
    Head->prox = NULL;
  }
  else
  {
    struct Musica* ElementoVarredura = Head;
    while (ElementoVarredura->prox != NULL)
      ElementoVarredura = ElementoVarredura->prox;

    ElementoVarredura->prox = NovaMusica;
    NovaMusica->prox = NULL;
  }

}


void Sair() {
  printf("Volte sempre! :)\n");
  exit(0);
}
