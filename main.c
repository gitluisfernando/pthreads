#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fila.h"

// Cria uma estrutura para as músicas
typedef struct
{
  char *nome;
  char *autor;
  char *duracao;
  char *genero;
} musicas;

/* O Mutex permite bloqueios para preservar seções críticas ou obter acesso exclusivo 
 * (Escrita e Leitura) a recursos
 * O Cond_t define as condições das variáveis para Produto x Consumo */
pthread_mutex_t mutexFila;
pthread_cond_t condicaoFila;

//Instacia a fila
Fila fila;

//Cria um vetor com as canções e suas respectivas informações
musicas faixas[] = {
    {"The Number of the Beast", "Iron Maiden", "04:49", "Heavy Metal"},
    {"One", "Metallica", "07:27", "Thrash Metal"},
    {"A Day in Life", "The Beatles", "05:37", "Classic Rock"},
    {"Time", "Pink Floyd", "06:53", "Psychedelic/Progressive Rock"},
    {"Negro Drama", "Racionais MC's", "06:51", "Rap"},
    {"Construção", "Chico Buarque", "06:23", "MPB"},
    {"Walk", "Foo Fighters", "04:15", "Rock"},
    {"What's Going On", "Marvin Gaye", "03:52", "Soul Music"},
    {"Blowin' in the Wind", "Bob Dylan", "02:48", "Folk Rock"},
    {"O Mundo é um Moinho", "Cartola", "03:55", "Samba"},
    {"Bohemian Rhapsody", "Queen", "05:55", "Classic Rock"},
    {"Smells Like Teen Spirit", "Nirvana", "05:01", "Grunge"},
    {"Poison Heart", "Ramones", "04:04", "Punk Rock"}};

//Exibe as músicas no terminal
void imprimirMusicas(musicas *musica)
{
  printf("Nome: %s\n"
         "Autor: %s\n"
         "Duração: %s\n"
         "Gênero: %s\n-♪-♪-♪-♪-♪-♪-♪-♪-♪-♪-♪-\n\n",
         musica->nome,
         musica->autor,
         musica->duracao,
         musica->genero);
}

//Inicializa o Mutex e a Variável de Condição
void Inicializar()
{
  pthread_mutex_init(&mutexFila, NULL);
  pthread_cond_init(&condicaoFila, NULL);
}

void *Fornecedor()
{

  while (1)
  {
    musicas *musica = &faixas[rand() % 20];

    /* Bloqueia a mutexFila para garantir que a adição de dados à fila ocorra sem problemas
   * Envia novos dados para a fila
   * Sinaliza à condicaoFila que novos dados estão disponíveis na fila
   * Ao terminar, desbloqueia o mutexFila */

    pthread_mutex_lock(&mutexFila);
    enviaParaFila(&fila, &musica);
    pthread_cond_signal(&condicaoFila);
    pthread_mutex_unlock(&mutexFila);

    sleep(2);
  }

  return NULL;
}

void *Consumidor()
{
  //Executa o loop do Consumidor
  while (1)
  {
    //Bloqueia a mutexFila
    pthread_mutex_lock(&mutexFila);

    //Enquanto a fila estiver vazia aguarda a condicaoFila ser sinalizada e desbloqueia e bloqueia o mutexFila
    while (!tamanhoFila(&fila))
    {
      pthread_cond_wait(&condicaoFila, &mutexFila);
    }

    musicas *musica;
    tirarFila(&fila, &musica);

    //Desbloqueia o mutexFila
    pthread_mutex_unlock(&mutexFila);

    //Imprime as músicas no terminal
    imprimirMusicas(musica);
  }

  return NULL;
}

int main(int argc, char *argv[])
{

  Inicializar();
  iniciaFila(&fila, sizeof(musicas));

  pthread_t fornecedor;
  pthread_create(&fornecedor, NULL, Fornecedor, NULL);

  pthread_t consumidores[3];

  for (int i = 0; i < 3; ++i)
  {
    pthread_create(&consumidores[i], NULL, Consumidor, NULL);
  }

  //Aguarda todos os threads do provedor juntando-se a eles
  for (int i = 0; i < 3; i++)
  {
    pthread_join(consumidores[i], NULL);
  }

  pthread_join(fornecedor, NULL);

  return EXIT_SUCCESS;
}