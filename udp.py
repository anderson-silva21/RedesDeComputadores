import socket

# Cria um socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Liga o socket à porta onde o servidor deve escutar
server_address = ('localhost', 10000)
print('Iniciando o servidor na {} porta {}'.format(*server_address))
sock.bind(server_address)

while True:
    print('Aguardando dados')
    data, address = sock.recvfrom(4096)
    print('Recebido {} bytes de {}'.format(len(data), address))
    print('Dados: {}'.format(data))
    if data:
        sent = sock.sendto(data, address)
        print('Enviado {} bytes de volta para {}'.format(sent, address))
