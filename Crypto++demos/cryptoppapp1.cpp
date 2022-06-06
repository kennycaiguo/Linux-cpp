//Crypto++demo
#include<iostream>
using namespace std;
#include<aes.h>
using namespace CryptoPP;

int main()
{
   cout<<"AES Parameters: "<<endl;
   cout<<"Algorithm name :"<<AES::StaticAlgorithmName()<<endl;
   //Crypto++库在一般用字节数来表示长度
   cout<<"Block size :"<< AES::BLOCKSIZE * 8 <<endl;
   cout<<"Min Key length :"<< AES::MIN_KEYLENGTH * 8 <<endl;
   cout<<"Max Key length :"<< AES::MAX_KEYLENGTH * 8 <<endl;
   
   //加密解密功能由AESEncryption和AESDecryption来实现
   //加密过程
   AESEncryption aesEncryptor;
   unsigned char aesKey[AES::DEFAULT_KEYLENGTH];
   unsigned char inBlock[AES::BLOCKSIZE] ="123456789";
   unsigned char outBlock[AES::BLOCKSIZE];
   unsigned char xorBlock[AES::BLOCKSIZE];
   memset(xorBlock,0,AES::BLOCKSIZE);
   
   aesEncryptor.SetKey(aesKey,AES::DEFAULT_KEYLENGTH);//设定秘钥
   aesEncryptor.ProcessAndXorBlock(inBlock,xorBlock,outBlock);//加密处理
   //以16进制显示加密后的数据
  for(int i=0;i<16;i++)
   {
      cout<<inBlock[i]<<""; 
   }
   
    cout<<endl;
   for(int i=0;i<16;i++)
   {
      cout<<inBlock[i]<<"";
     cout<<hex<<(int)outBlock[i]<<" ";
	 
   }
   cout << endl;
   //解密
   AESDecryption aesDecryptor;
   unsigned char plainText[AES::BLOCKSIZE];
   aesDecryptor.SetKey(aesKey,AES::DEFAULT_KEYLENGTH);
   aesDecryptor.ProcessAndXorBlock(outBlock,xorBlock,plainText);
   cout<<"reasult:"<<endl;
   for(int i=0;i<16;i++)
   {
     cout<<plainText[i];
	 
   }
   cout << endl;
   
   
   return 0;
}

