#!/usr/bin/env python3

import json
import socket
import argparse

if __name__ == '__main__':

    parser = argparse.ArgumentParser(usage=__doc__)
    
    parser.add_argument('-a', '--host', help='IP address of socket', default='localhost')
    parser.add_argument('-p', '--port', help='Port of socket', type=int, default=10015)
    parser.add_argument('-x', '--xtce_file', help='XTCE file', default='./xtce.xml')

    args = parser.parse_args()

    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
    client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    client.bind(("", args.port))

    while True:
        data, addr = client.recvfrom(1024)
        print(data)