// A simple server in the internet domain using TCP
// The port number is passed as an argument

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MAX 2

typedef struct TipoItem {
  int valor;
  struct TipoItem *prox;
} TipoItem;

typedef struct {
  TipoItem *ultimo;
  int tamanho;
} TipoListaCircular;

typedef struct {
  int id;
  int value;
} TipoCliente;

typedef struct {
  TipoCliente data[MAX];
} cliente;

void error(const char *msg) {
  perror(msg);
  exit(1);
}

void inicializaLista(TipoListaCircular *lista) {
  lista->ultimo = NULL;
  lista->tamanho = 0;
}

void insereNoFinal(TipoListaCircular *lista, TipoItem novoItem) {
  TipoItem *novoNo;
  novoNo = malloc(sizeof(TipoItem));
  *novoNo = novoItem;
  if(lista->ultimo == NULL) {
    novoNo->prox = novoNo;
    lista->ultimo = novoNo;
  }
  else {
    novoNo->prox = lista->ultimo->prox;
    lista->ultimo->prox = novoNo;
    lista->ultimo=novoNo;
  }
  lista->tamanho++;
}

int removerListaCircular (TipoListaCircular *lista, int chave) {
  TipoItem *p1, *p2;
  p1 = lista->ultimo;
  p2 = p1->prox;
  if(lista->tamanho == 0)return -1;
  if(p1 != NULL) {
    do {
      p1=p1->prox;
      p2=p2->prox;
      if(p2->valor == chave) {
        if(lista->tamanho == 1) {
          lista->ultimo = NULL;
        }
        else if(p2 == lista->ultimo) {
          p1->prox = p2->prox;
          lista->ultimo = p1;
        }
        else {
          p1->prox = p2->prox;
        }
        lista->tamanho-=1;
        free(p2);
        return 1;
      }
    }
    while(p1!=lista->ultimo);
  }
  return -1;
}

void imprimeLista(TipoListaCircular *lista) {
  TipoItem *p =lista->ultimo;
  if(p != NULL) {
    do {
      p=p->prox;
      printf("%d ",p->valor);
    }
    while(p!=lista->ultimo);
    printf("\n");
  }
}

TipoListaCircular ativos;
int desliga = 0, on = 0;
int sockfd;

void inicializaCliente(cliente *sock) {
  int i;
  for(i = 0; i < MAX; i++) {
  sock->data[i].id = -1;
      sock->data[i].value = -1;
  }
}

void abreSocket(int *sockfd) {
  int optval = 1;
  *sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (*sockfd < 0)error("ERRO ao abrir socket");
  setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
}

void amarraSocket(int *sockfd, int portno) {
  struct sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(*sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERRO ao estabelecer ligação");
}

void *connection(void *sock_void_ptr) {
  char buffer[2048];
  int u_on = 1, n;
  char msg[200];
  struct timeval timeout;
  fd_set u_set;
  TipoCliente *newsock = (TipoCliente *)sock_void_ptr;
  TipoItem novo;
  socklen_t clilen;
  struct sockaddr_in cli_addr;
  sprintf(msg, "Bem-vindo ao servidor TCP/IP, o seu id e %d.\n\ Para sair digite 'quit' ou digite 'shutdown' para desconectar o servidor.\n\n\0",newsock->id);
  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsock->value = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
  if (newsock->value < 0)error("ERRO ao aceitar");
  n = write(newsock->value,msg,strlen(msg));
  if (n < 0) error("ERRO ao escrever no socket");
  printf("\nnova conexão %s porta:%hu\n",inet_ntoa(cli_addr.sin_addr),cli_addr.sin_port);
  novo.valor = newsock->id;
  insereNoFinal(&ativos, novo);
  printf("usuários on ");
  imprimeLista(&ativos);
  FD_ZERO(&u_set);
  FD_SET(newsock->value, &u_set);
  if( newsock->id == 1 ) { 
    do {
      timeout.tv_sec = 3600;
      timeout.tv_usec = 0;
      bzero(buffer,2048);
      n = select(FD_SETSIZE, &u_set, NULL, NULL, &timeout);
      if(n == -1)error("ERRO select");
      else if(n == 0) {
        printf("%d timed out\n",newsock->id);
        u_on = 0;
        break;
      }
      else {
        n = read(newsock->value,buffer,2048);
        if (n < 0) error("ERRO ao ler socket");
        if(strcmp("!!Alive!!\n",buffer) != 0) {
          if(strcmp("quit\r\n",buffer) == 0) {
            printf("id %d saiu\n",newsock->id);
            u_on = 0;
            break;
          }
          if(strcmp("shutdown\r\n",buffer) == 0) {
            desliga = 1;
            u_on = 0;
            break;
          }
        }
      }
    }
    while(u_on);
    on--;
    removerListaCircular(&ativos, newsock->id);
    newsock->id = -1;
    close(newsock->value);
    newsock->value = -1;
  }
  return NULL;
}

void envia(cliente *newsockfd) {
  char mensagem[7];
  int n, len;
  if( newsockfd->data[0].id != -1 && newsockfd->data[0].value != -1) {
    n = read(newsockfd->data[0].value,mensagem,7);
    if (n < 0) error("ERRO ao ler socket 0");
    len = strlen(mensagem);
    if( newsockfd->data[1].id != -1 && newsockfd->data[1].value != -1) {
      if(len < 7) {
        mensagem[len] = '\n';
        n = write(newsockfd->data[1].value,mensagem,len+1);
        if (n < 0) error("ERRO ao escrever no socket");
        printf("mensagem len: %d enviada.\n",len+1);
        printf("len: %d\n",len+1);
      }
    }
    on--;
    removerListaCircular(&ativos, newsockfd->data[0].id);
    newsockfd->data[0].id = -1;
    close(newsockfd->data[0].value);
    newsockfd->data[0].value = -1;
  }
}

int main(int argc, char *argv[]) {
  int portno, proximo = 0;
  pthread_t sock_thread, cmd_thread;
  cliente newsockfd;
  if (argc < 2) {
    fprintf(stderr,"ERRO, nenhuma porta fornecida\n");
    exit(1);
  }
  portno = atoi(argv[1]);
  inicializaLista(&ativos);
  inicializaCliente(&newsockfd);
  abreSocket(&sockfd);
  amarraSocket(&sockfd, portno);
  printf("Servidor TCP v11, MAX 2 usuários.\n");
  printf("para enviar uma mensagem digitar 'id' 'mensagem':\n");
  do {
    envia(&newsockfd);
    if (desliga == 1) break;
    if( proximo == MAX ) proximo = 0;
    if( newsockfd.data[1].id == -1 && newsockfd.data[1].value == -1 && on < MAX ) {
      printf("%d, 1\n",newsockfd.data[1].id);
      newsockfd.data[1].id = 1;
      if(pthread_create(&sock_thread, NULL, connection, &newsockfd.data[1]))
      error("Erro ao criar Thread");
      on++;
    }
    if( newsockfd.data[1].id > -1 && newsockfd.data[1].value > -1 && on < MAX ) {
      if( newsockfd.data[0].id == -1 && newsockfd.data[0].value == -1 && on < MAX ) {
        printf("%d, 0\n",newsockfd.data[0].id);
        newsockfd.data[0].id = 0;
        if(pthread_create(&sock_thread, NULL, connection, &newsockfd.data[0]))
        error("Erro ao criar Thread");
        on++;
      }
    }
  }
  while(1);
  close(sockfd);
  return 0;
}
