import socket

# Cria um socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Liga o socket à porta onde o servidor deve escutar
server_address = ('localhost', 10000)
print('Iniciando o servidor na {} porta {}'.format(*server_address))
sock.bind(server_address)

# Escutar conexões de entrada
sock.listen(1)

while True:
    # Aguarda uma conexão
    print('Aguardando uma conexão')
    connection, client_address = sock.accept()
    try:
        print('Conexão de', client_address)

        # Recebe dados em pacotes de até 1024 bytes
        data = connection.recv(1024)
        print('Dados recebidos: {!r}'.format(data))

        # Envia dados de volta para o cliente
        connection.sendall(data)
    finally:
        # Fecha a conexão
        connection.close()
