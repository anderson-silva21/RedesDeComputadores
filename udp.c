#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    // Criando o socket
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    // Buffer para armazenar a mensagem
    char buffer[256];

    // Estrutura para armazenar o endereço do cliente
    struct sockaddr_in client_address;
    int client_address_len = sizeof(client_address);

    while (1) {
        // Recebendo a mensagem
        int n = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &client_address, &client_address_len);
        if (n < 0) {
            perror("Erro ao receber a mensagem");
            exit(1);
        }

        printf("Mensagem recebida de %s:%d: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);

        // Enviando a mensagem de volta
        char *response = "Mensagem recebida com sucesso!";
        n = sendto(server_socket, response, strlen(response), 0, (struct sockaddr *) &client_address, sizeof(client_address));
        if (n < 0) {
            perror("Erro ao enviar a resposta");
            exit(1);
        }
    }

    // Fechando o socket
    close(server_socket);

    return 0;
}
