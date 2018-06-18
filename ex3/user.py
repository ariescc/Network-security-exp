'''
user datastructure
'''
import socket

class User:
    def __init__(self, skt, publickey='none', privatekey='none', username='none'):
        self.skt = skt
        self.publickey = publickey
        self.privatekey = privatekey
        self.username = username

    def send_msg(self, msg):
        self.skt.send(msg)

    def logout(self):
        self.skt.close()
