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
  char duracao[6];
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

  printf("\nDados da música a ser inserida: ");
  printf("\nTítulo: ");
  fgets(NovaMusica->titulo, 49, stdin);
  printf("Artista: ");
  fgets(NovaMusica->artista, 49, stdin);
  printf("Duração: ");
  fgets(NovaMusica->duracao, 5, stdin);
  while((c = getchar()) != '\n' && c != EOF) {} //limpar o buffer

  InsereItemNaLista(*NovaMusica);
}

void BuscarMusicas()
{
  char tituloBuscado[50];
  int c;

  Musica *ElementoVarredura;

  printf("Digite o título da música a ser pesquisado: ");
  fgets(tituloBuscado, 49, stdin);

  ElementoVarredura = Head;

  while (ElementoVarredura != NULL)
  {
    if( strcmp(ElementoVarredura->titulo, tituloBuscado) == 0 ) {
    printf("\n####################################\n");
      printf("Título: %s", ElementoVarredura->titulo);
      printf("Artista: %s", ElementoVarredura->artista);
      printf("Duração: %s", ElementoVarredura->duracao);
    }
    ElementoVarredura = ElementoVarredura->prox;
  }
  printf("\n");

  getchar();
  return;
}

void ListarMusicas()
{
  
  Musica *ElementoVarredura = Head;

  while (ElementoVarredura != NULL)
  {
    printf("\n####################################\n");
    printf("Título: %s", ElementoVarredura->titulo);
    printf("Artista: %s", ElementoVarredura->artista);
    printf("Duração: %s", ElementoVarredura->duracao);
    ElementoVarredura = ElementoVarredura->prox;
  }
  printf("\n");
  getchar();
  return;
  
}


void IncializarAcervo() {

  struct Musica acervo[] = {
    {"Living on a Prayer\n", "Bon Jovi\n", "3:00", NULL},
    {"Amor e Fé\n", "Hungria Hip Hop\n", "5:22", NULL},
    {"Faroeste Caboclo\n", "Legiao Urbana\n", "9:07", NULL},
    {"Florentina\n", "Tiririca\n", "2:28", NULL},
    {"Boate Azul\n", "Joaquim e Manuel\n", "3:19", NULL},
    {"Stranded\n", "Gojira\n", "4:29", NULL},
    {"Pisces\n", "Jinjer\n", "5:05", NULL},
    {"Where Eagles Dare\n", "Iron Maiden\n", "6:13", NULL},
    {"Do Fundo da Grota\n", "Baitaca\n", "3:59", NULL},
    {"Pelados em Santos\n", "Mamonas Assassinas\n", "3:23", NULL},
  };

  unsigned int tamanhoAcervo = 10;
  for(int i = 0; i < tamanhoAcervo; i++) {
    InsereItemNaLista(acervo[i]);
  }
}

void InsereItemNaLista(struct Musica musica) {

  struct Musica* NovaMusica = (struct Musica *) malloc(sizeof(struct Musica));

  strcpy(NovaMusica->titulo, musica.titulo);
  strcpy(NovaMusica->artista, musica.artista);
  strcpy(NovaMusica->duracao, musica.duracao);
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
  printf("Volte sempre! :)\n\n");
  exit(0);
}
