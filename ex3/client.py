'''
client
'''
import sys
import socket
import threading,time
import des as ds
import des_1 as des_jm

#global variable
isNormar=True
other_usr=''
object_pub_key='' # 目标聊天对象的公钥


def gcd(a,b):
    return int(gcd(b,a%b) if b else a)

def LeastCommonMultipe(a,b,c):
    t=a*b/c
    return int(t)

def Mode(a,b,mode):
    sum=1
    a=a%mode
    while b>0:
        if b%2==1:
            sum=(sum*a)%mode
        b=b/2
        a=(a*a)%mode
    return int(sum)

def generate_keypair():
    p=17
    q=19
    n=p*q
    c=gcd(p-1,q-1)
    l=LeastCommonMultipe(p-1,q-1,c)
    # e
    for i in range(l-1, 1, -1):
        if gcd(i,l) == 1:
            e=i

    # e
    for i in range(2, l):
        if (e*i)%l==1:
            d=i
    return [n,e,d]

def publickey_pair():
    #print('123123123123')
    tmp=generate_keypair()
    return (tmp[0],tmp[1])

def privatekey_pair():
    tmp=generate_keypair()
    return (tmp[0],tmp[2])

# 客户端RSA加密
def rsa_eneryption(val):
    params=generate_keypair()
    #n e d
    mitxt=Mode(val,params[2],params[0])
    return str(mitxt)

# 客户端RSA解密
def rsa_jiemi(val,pub):
    params=pub.split('#')
    #n e d
    plaintxt=Mode(int(val),int(params[1]),int(params[0]))
    return chr(plaintxt)

# 明文加密
def get_mitxt(content):
    res=''
    for index in range(len(content)):
        res=res+' '+rsa_eneryption(ord(content[index]))
    res=res[1:]
    return res

# RSA解密
def get_plaintxt(content,pub):
    plaintxt=''
    mitxts=content.split(' ')
    print(len(mitxts))
    for mit in mitxts:
        print(mit)
        plaintxt=plaintxt+rsa_jiemi(mit,pub)
    return plaintxt


def recieve_msg(username,pubkey,prakey,s):
    global isNormar,other_usr
    print ('Please waiting other user login...')
    print(pubkey,'pubkey')
    print(prakey,'prakey')
    s.send(('login|%s|%s|%s' %(username,pubkey,prakey)).encode())
    while(isNormar):
        data= s.recv(1024).decode()#阻塞线程，接受消息
        msg=data.split('|')
        if msg[0]=='login':
            print ('%s user has already logged in, start to chat' % msg[1])
            other_usr=msg[1]
        elif msg[0] == 'pub':
            print('objective user public key is %s' % msg[1])
            tmp=msg[1].split('$')
            # RSA公钥，用于DES_KEY解密
            pubs=tmp[0]
            # DES_KEY
            des_key=tmp[1]
            # content
            content=tmp[2]
            # RSA解密DES_KEY
            des_key_plain=get_plaintxt(des_key,pubs)
            # 信息明文
            plain=des_jm.desdecode(content,des_key_plain)
            print(plain)
        else:
            messages=msg[0].split('$')
            plaintxt=get_plaintxt(messages[1],messages[0])
            print(plaintxt)
            #print(msg[0])

#程序入口'login|%s' %username
def main():
    global isNormar,other_usr,object_pub_key
    try:
        print ('Please input your name:')
        usrname=input()
        tp=publickey_pair()
        pubkey=str(tp[0])+'#'+str(tp[1])
        tp=privatekey_pair()
        prakey=str(tp[0])+'#'+str(tp[1])
        #print(pubkey[0],pubkey[1])
        print(pubkey,prakey)
        s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.connect(("127.0.0.1",9999))
        t=threading.Thread(target=recieve_msg,args=(usrname,pubkey,prakey,s))
        t.start()
    except:
        print ('connection exception')
        isNormar=False
    finally:
        pass
    while isNormar:
        msg=input()#接受用户输入
        if msg=="exit":
            isNormar=False
        else:
            if(other_usr!=''):
                # 输入DES密钥
                des_key=input('请输入DES密钥: ')
                msg=ds.desencode(msg,des_key)
                des_key=get_mitxt(des_key)
                # 将信息发送给谁
                other_usr=input('Who do you want to send the message?Input his name: ')
                s.send(("talk|%s|%s|%s" % (other_usr,des_key,msg)).encode()) #编码消息并发送
    #s.close()

if __name__=="__main__":
    main()
