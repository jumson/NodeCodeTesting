// http://www.arduinolab.net/aes-encryptiondecryption-using-arduino-uno/
// the link above should be usefull
// i'll be applying this to the esp8266
// also, my original code should move from String, start to use byte arrays, to use this library

/*------------------------------------------------------------------------------ 
Program:      aesEncDec 
 
Description:  Basic setup to test AES CBC encryption/decryption using different 
              key lengths.
 
Hardware:     Arduino Uno R3 
 
Software:     Developed using Arduino 1.8.2 IDE
 
Libraries:    
              - AES Encryption Library for Arduino and Raspberry Pi: 
                https://spaniakos.github.io/AES/index.html
 
References: 
              - Advanced Encryption Standard by Example: 
              http://www.adamberent.com/documents/AESbyExample.pdf
              - AES Class Reference: https://spaniakos.github.io/AES/classAES.html
 
Date:         July 9, 2017
 
Author:       G. Gainaru, http://www.arduinolab.net
              (based on AES library documentation and examples)
------------------------------------------------------------------------------*/
#include <AES.h>
#include "./printf.h"

AES aes ;

unsigned int keyLength [3] = {128, 192, 256}; // key length: 128b, 192b or 256b

byte *key = (unsigned char*)"01234567890123456789012345678901"; // encryption key
byte plain[] = "http://www.arduinolab.net/aes-encryptiondecryption-using-arduino-uno/"; // plaintext to encrypt

unsigned long long int myIv = 36753562; // CBC initialization vector; real iv = iv x2 ex: 01234567 = 0123456701234567

void setup ()
{
  Serial.begin (9600) ;
  printf_begin();
}

void loop () 
{
  for (int i=0; i < 3; i++)
  {
    Serial.print("- key length [b]: ");
    Serial.println(keyLength [i]);
    aesTest (keyLength[i]);
    delay(2000);
  }
}

void aesTest (int bits)
{
  aes.iv_inc();
  
  byte iv [N_BLOCK] ;
  int plainPaddedLength = sizeof(plain) + (N_BLOCK - ((sizeof(plain)-1) % 16)); // length of padded plaintext [B]
  byte cipher [plainPaddedLength]; // ciphertext (encrypted plaintext)
  byte check [plainPaddedLength]; // decrypted plaintext
  
  aes.set_IV(myIv);
  aes.get_IV(iv);

  Serial.print("- encryption time [us]: ");
  unsigned long ms = micros ();
  aes.do_aes_encrypt(plain,sizeof(plain),cipher,key,bits,iv);
  Serial.println(micros() - ms);

  aes.set_IV(myIv);
  aes.get_IV(iv);
  
  Serial.print("- decryption time [us]: ");
  ms = micros ();
  aes.do_aes_decrypt(cipher,aes.get_size(),check,key,bits,iv); 
  Serial.println(micros() - ms);
  
  Serial.print("- plain:   ");
  aes.printArray(plain,(bool)true); //print plain with no padding

  Serial.print("- cipher:  ");
  aes.printArray(cipher,(bool)false); //print cipher with padding

  Serial.print("- check:   ");
  aes.printArray(check,(bool)true); //print decrypted plain with no padding
  
  Serial.print("- iv:      ");
  aes.printArray(iv,16); //print iv
  printf("\n===================================================================================\n");
}
