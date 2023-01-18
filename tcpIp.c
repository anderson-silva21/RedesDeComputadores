#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    // Criando o socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Erro ao criar o socket");
        exit(1);
    }

    // Configurando o endereço
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9090);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind do endereço ao socket
    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Erro ao fazer o bind");
        exit(1);
    }

    // Escutando a conexão
    listen(server_socket, 5);

    // Aceitando a conexão
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0) {
        perror("Erro ao aceitar a conexão");
        exit(1);
    }

    // Recebendo a mensagem
    char buffer[256];
    int n = read(client_socket, buffer, sizeof(buffer));
    if (n < 0) {
        perror("Erro ao ler do socket");
        exit(1);
    }

    printf("Mensagem recebida: %s\n", buffer);

    // Enviando a mensagem de volta
    char *response = "Mensagem recebida com sucesso!";
    n = write(client_socket, response, strlen(response));
    if (n < 0) {
        perror("Erro ao escrever no socket");
        exit(1);
    }

    // Fechando o socket
    close(server_socket);
    close(client_socket);

    return 0;
}
