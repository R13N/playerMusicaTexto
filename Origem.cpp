#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int menu();
void InserirMusica();
void ListarMusicas();
void BuscarMusicas();

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
  ElementoVarredura = (struct Musica *)malloc(sizeof(struct Musica));

  printf("\nDados da música a ser inserida: ");
  printf("\nTítulo: ");
  fgets(NovaMusica->titulo, 49, stdin);
  printf("Artista: ");
  fgets(NovaMusica->artista, 49, stdin);
  printf("Duração: ");
  scanf("%f", &NovaMusica->duracao);
  while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer

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
  ElementoVarredura = (struct Musica *)malloc(sizeof(struct Musica));

  printf("Listar Músicas.\n");

  printf("Digite o título da música a ser pesquisado: ");
  fgets(tituloBuscado, 49, stdin);
  // while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer

  ElementoVarredura = Head;
  if(ElementoVarredura == NULL)
  {
    getchar();
    return;
  }
  while (ElementoVarredura != NULL)
  {
    if(ElementoVarredura->titulo == tituloBuscado)
    {
      printf("Título: %s \n", ElementoVarredura->titulo);
      printf("Artista: %s \n", ElementoVarredura->artista);
      printf("Duração: %2.2fmin \n", ElementoVarredura->duracao);
    }
    else
    {
      ElementoVarredura = ElementoVarredura->prox;
    }
  }
  printf("\n");

  getchar();
  return;
}

void ListarMusicas()
{
  
  Musica *ElementoVarredura;
  ElementoVarredura = (struct Musica *)malloc(sizeof(struct Musica));

  ElementoVarredura = Head;
  if(ElementoVarredura == NULL)
  {
    return;
  }
  while (ElementoVarredura != NULL)
  {
    printf("Título: %s", ElementoVarredura->titulo);
    printf("Artista: %s", ElementoVarredura->artista);
    printf("Duração: %2.2f", ElementoVarredura->duracao);
    ElementoVarredura = ElementoVarredura->prox;
  }
  printf("\n");

  getchar();
  return;
  
}
