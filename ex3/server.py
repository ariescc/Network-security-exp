'''
server
'''
import sys
import socket
import threading,time
import user as User

#global variable
userlist=[]

def hand_user_con(usr):
    try:
        isNormar=True
        while isNormar:
            data=usr.skt.recv(1024).decode()
            time.sleep(1)
            msg=data.split('|')#分析消息
            #print('msg0', msg[0])
            if msg[0]=='login':
                print ('user [%s] login' % msg[1])
                usr.username=msg[1]
                usr.publickey=msg[2]
                notice_other_usr(usr)
            if msg[0]=='talk': # talk|user|des_key|msg
                print ('user[%s]to[%s]:%s' % (usr.username,msg[1],msg[2]))
                #send_msg(msg[1],msg[2])#发送消息给目标用户，参数1：目标用户，参数2：消息内容
                # 查找目标用户的pub_key
                pub=''
                for ur in userlist:
                    #print(ur.publickey,'bingo')
                    if ur.username == usr.username:
                        pub=ur.publickey
                        break
                # 将源发送用户的pub_key发送给目标用户
                pub='pub|'+pub
                for ur in userlist:
                    if ur.username == msg[1]:
                        pub=pub+'$'+msg[2]+'$'+msg[3]
                        send_msg(ur.username,pub)
            if msg[0]=='exit':
                print ('user [%s] exit' % msg[0])
                isNormar=False
                usr.close()
                userlist.remove(usr)
    except:
        isNormar=False

#通知其他用户以上的好友
def notice_other_usr(usr):
    if(len(userlist)>1):
        #print ('The two users')
        #userlist[0].skt.send(("login|%s" % userlist[1].username).encode())
        #userlist[1].skt.send(("login|%s" % userlist[0].username).encode())
        print('The number of users: ',len(userlist))
        for usr in userlist:
            usr.skt.send(('login|%s' % usr.username).encode())
    else:
        print ('The one users')

def send_msg(username,msg):
    for usr in userlist:
        if(usr.username==username):
            usr.skt.send(msg.encode())

#程序入口
def main():
    s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind(('0.0.0.0',9999))
    s.listen(5)
    print ('waiting for connection...')
    while True:
        sock,addr=s.accept()#等待用户连接
        print(sock, addr)
        user=User.User(sock)
        #print(user.username, '123')
        userlist.append(user)
        t=threading.Thread(target=hand_user_con,args=(user,));
        t.start()
    s.close()


if(__name__=="__main__"):
    main()
