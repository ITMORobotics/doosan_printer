import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('127.0.0.1', 55555)
print('connecting to %s port %s' % server_address)
sock.connect(server_address)

try:

    # Send data
    # message = 'G28'
    message = 'G1 Z15.0 F3000 ;Move the platform down 15mm'
    sock.sendall(message.encode('utf-8'))

    # Look for the response
    response = sock.recv(4096)

    if not response:
        print("[-] Not Received")
        exit(1)

    print("[+] Received", repr(response.decode('utf-8')))

finally:
    print('close socket')
    sock.close()
