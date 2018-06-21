#_*_ coding:utf-8 _*_
#!/usr/bin/env python
#Filename:des.py

from desstruct import *
import re

__all__=['desencode']
class DES():
	def __init__(self):
		pass
	def code(self,from_code,key,code_len,key_len):
		output=""
		trun_len=0

		code_string=self._functionCharToA(from_code,code_len)
		code_key=self._functionCharToA(key,key_len)

		if code_len%16!=0:
			real_len=(code_len//16)*16+16
		else:
			real_len=code_len

		if key_len%16!=0:
			key_len=(key_len//16)*16+16
		key_len*=4

		trun_len=4*real_len
		for i in range(0,trun_len,64):
			run_code=code_string[i:i+64]
			l=i%key_len
			run_key=code_key[l:l+64]

			run_code= self._codefirstchange(run_code)
			run_key= self._keyfirstchange(run_key)

			for j in range(16):

				code_r=run_code[32:64]
				code_l=run_code[0:32]

				run_code=code_r

				code_r= self._functionE(code_r)

				key_l=run_key[0:28]
				key_r=run_key[28:56]
				key_l=key_l[d[j]:28]+key_l[0:d[j]]
				key_r=key_r[d[j]:28]+key_r[0:d[j]]
				run_key=key_l+key_r
				key_y= self._functionKeySecondChange(run_key)

				code_r= self._codeyihuo(code_r,key_y)

				code_r= self._functionS(code_r)

				code_r= self._functionP(code_r)

				code_r= self._codeyihuo(code_l,code_r)
				run_code+=code_r

			code_r=run_code[32:64]
			code_l=run_code[0:32]
			run_code=code_r+code_l

			output+=self._functionCodeChange(run_code)
		return output

	def _codeyihuo(self,code,key):
		code_len=len(key)
		return_list=''
		for i in range(code_len):
			if code[i]==key[i]:
				return_list+='0'
			else:
				return_list+='1'
		return return_list

	def _codefirstchange(self,code):
		changed_code=''
		for i in range(64):
			changed_code+=code[ip[i]-1]
		return changed_code

	def _keyfirstchange (self,key):
		changed_key=''
		for i in range(56):
			changed_key+=key[pc1[i]-1]
		return changed_key

	def _functionCodeChange(self, code):
		lens=len(code)//4
		return_list=''
		for i in range(lens):
			list=''
			for j in range(4):
				list+=code[ip_1[i*4+j]-1]
			return_list+="%x" %int(list,2)
		return return_list

	def _functionE(self,code):
		return_list=''
		for i in range(48):
			return_list+=code[e[i]-1]
		return return_list

	def _functionP(self,code):
		return_list=''
		for i in range(32):
			return_list+=code[p[i]-1]
		return return_list

	def _functionS(self, key):
		return_list=''
		for i in range(8):
			row=int( str(key[i*6])+str(key[i*6+5]),2)
			raw=int(str( key[i*6+1])+str(key[i*6+2])+str(key[i*6+3])+str(key[i*6+4]),2)
			return_list+=self._functionTos(s[i][row][raw],4)

		return return_list

	def _functionKeySecondChange(self,key):
		return_list=''
		for i in range(48):
			return_list+=key[pc2[i]-1]
		return return_list

	def _functionCharToA(self,code,lens):
		return_code=''
		lens=lens%16
		for key in code:
			code_ord=int(key,16)
			return_code+=self._functionTos(code_ord,4)
		if lens!=0:
			return_code+='0'*(16-lens)*4
		return return_code

	def _functionTos(self,o,lens):
		return_code=''
		for i in range(lens):
			return_code=str(o>>i &1)+return_code
		return return_code

def tohex(string):
	return_string=''
	for i in string:
		return_string+="%02x"%ord(i)
	return return_string

def tounicode(string):
	return_string=''
	string_len=len(string)
	for i in range(0,string_len,2):
		return_string+=chr(int(string[i:i+2],16))
	return return_string

def desencode(from_code,key):

	from_code=tohex(from_code)
	key=tohex(key)

	des=DES()
	key_len=len(key)
	string_len=len(from_code)

	if string_len<1 or key_len<1:
		print ('error input')
		return False
	key_code= des.code(from_code,key,string_len,key_len)
	return key_code

'''
if __name__  == '__main__':
	print("DES ")
	m=input("输入明文:")
	k=input("输入密钥:")
	print (desencode(m,k))
	k=input("按确定键退出")
'''