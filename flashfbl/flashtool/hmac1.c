/******************************************************************************
*
*       Copyright (C) 2010-2013 Wind Hill Technologies,
*                    All Rights Reserved
*
*       
*       
*
*       
*       
*
* Filename:     $Source: HMACSHA1.c $
* Author:       $Author: Chen Haizheng/Sun Jia $
* Locker:       $Locker:  $
* State:        $State: Exp $
* Revision:     $Revision: 1.1 $
*
* Functions:    
*
* History:      
*               
*
* Description:  HAMC-SHA1 algorithm          
*
* Notes:        
*
******************************************************************************/
/*
 *******************************************************************************
 *                                  Include files
 *******************************************************************************
*/
#include "HMACSHA1.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
*******************************************************************************
*                                   Global define
*******************************************************************************
*/

/******************* Defined By Brilliance Auto	*****************/				
/* HMAC input Seed length Bytes */
#define SEED_LENGTH		16
/* HMAC output Key length Bytes */
#define KEY_LENGTH		16
/* HMAC input K length Bytes	*/
#define K_LENGTH		8
#define CHUNK 1024 /* read 1024 bytes at a time */
#define BUFFER_SIZE 80
char buffer[BUFFER_SIZE];
uint8_t Key[KEY_LENGTH];
uint8_t Seed[SEED_LENGTH];
/*           HAMC-K				*/
uint8_t K_LV1[K_LENGTH] = {0x92, 0x0A, 0x22, 0x1F, 0x69, 0x38, 0xB4, 0xC7};
uint8_t K_LV2[K_LENGTH] = {0x92, 0x0A, 0x22, 0x1F, 0x59, 0x2D, 0xE4, 0x9E};
uint8_t K_LV3[K_LENGTH] = {0x92, 0x0A, 0x22, 0x1F, 0x74, 0x82, 0x8D, 0x34};
uint8_t K_LV4[K_LENGTH] = {0x92, 0x0A, 0x22, 0x1F, 0x9D, 0xA0, 0xC3, 0xB8};

/* Length of SHA1 Algorithm		*/
/* 20-Byte Don't change it     	*/
#define SHA_DIGESTSIZE	20

/* Block of SHA1 Algorithm		*/
/* 64-Byte Don't change it     	*/
#define SHA_BLOCKSIZE	64

#if defined(rol)
#undef rol
#endif

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

#define __LITTLE_ENDIAN 

#ifdef __LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00)|(rol(block->l[i],8)&0x00FF00FF))
#else
#define blk0(i) block->l[i]
#endif

#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15]^block->l[(i+2)&15]^block->l[i&15],1))

#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);
/*
*******************************************************************************
*                                    Types
*******************************************************************************
*/
typedef struct
{
	uint32_t state[5];			/* constant of SHA1 */
	uint32_t count[2];			/* counter */
	uint8_t  buffer[64];		/* 512-bit message blocks */
} SHA1_CTX;

/*
*******************************************************************************
*                                     Data
*******************************************************************************
*/

/*
*******************************************************************************
*                                  Lacal Data
*******************************************************************************
*/

/*
*******************************************************************************
*                                  Extern Data
*******************************************************************************
*/

/*
*******************************************************************************
*                                  Prototypes
*******************************************************************************
*/
static void* my_memcpy(	void *dest, const void *src, uint32_t count);
static void* my_memset(void *ptr,uint8_t c,uint32_t count); 
static uint8_t *my_strcpy(uint8_t *dst,const uint8_t *src);

void SHA1Transform(uint32_t state[5], uint8_t buffer[64]);
void SHA1Reset(SHA1_CTX *context);
void SHA1Input(SHA1_CTX *context, uint8_t* data, uint32_t len);
void SHA1Result(uint8_t digest[20], SHA1_CTX *context);
void SHA1Truncate(uint8_t* d1,	uint8_t* d2,uint32_t len);
/*
*******************************************************************************
*                               Functions/Classes
*******************************************************************************
*/
/**********************************************************************************************
 * my_memcpy
 **********************************************************************************************/
/*
 *
 * Satic function,use to copy data.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/
static void* my_memcpy
(	
	void *dest, 
	const void *src, 
	uint32_t count
)
{
	uint8_t *tmp = dest;
	const uint8_t *s = src;
	while (count--)
	{
		*(uint8_t *)dest = *(uint8_t *)src;
        dest = (uint8_t *)dest + 1;
        src = (uint8_t *)src + 1;
	}
	return dest;
}

/**********************************************************************************************
 * my_memset
 **********************************************************************************************/
/*
 *
 * Satic function,use to set memory.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/
static void* my_memset
(
	void *ptr,
	uint8_t c,
	uint32_t count
)  
{  
    void * tmp = ptr;  
    while(count--)  
    {  
        *(uint8_t *)ptr = (uint8_t)c;  
        ptr = (uint8_t *)ptr + 1;  
    }  
    return tmp;  
} 
/**********************************************************************************************
 * my_strcpy
 **********************************************************************************************/
/*
 *
 * Satic function,use to copy string.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/
static uint8_t *my_strcpy
(
	uint8_t *dst,
	const uint8_t *src
)  
{  
    uint8_t *ret = dst;  
    while((* dst++ = * src++) != '\0');  
    return ret;  
}

/**********************************************************************************************
 * SHA1Transform
 **********************************************************************************************/
/*
 *
 * This function use to calculate the SHA1 digest.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/	
void SHA1Transform
(
	uint32_t state[5],		/* constants used in SHA1 */
	uint8_t buffer[64]		/* data to be hashed */
)
{
	uint32_t a, b, c, d, e;
	typedef union {
		uint8_t c[64];
		uint32_t l[16];
	} CHAR64LONG16;

	CHAR64LONG16* block;

	static uint8_t workspace[64];
    block = (CHAR64LONG16*)workspace;
    my_memcpy(block, buffer, 64);

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    /* 80 steps used to calculate SHA1 digest */
    R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
    R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
    R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
    R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
    R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);
    R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
    R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
    R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
    R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
    R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);
    R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
    R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
    R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
    R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
    R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);
    R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
    R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
    R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
    R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
    R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);
    /* Return the SHA1 digest */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    a = b = c = d = e = 0;
}

/**********************************************************************************************
 * SHA1Reset
 **********************************************************************************************/
/*
 *
 * This function will initialize the context in preparation 
 * for computing a new SHA1 message digest.
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/	
void SHA1Reset
(
	SHA1_CTX* context	/* SHA1 structure need to reset */	
)
{
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
}
/**********************************************************************************************
 * SHA1Input
 **********************************************************************************************/
/*
 *
 * This function will process the message stored in the "data".
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/	
void SHA1Input
(	
	SHA1_CTX* context,		/* result returned from here */		
	uint8_t* data,	/* data to be processed */
	uint32_t len				/* data length  */
)
{
	uint32_t i, j;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j)
		context->count[1]++;
    context->count[1] += (len>>29);
    j = (j >> 3) & 63;
    if ((j + len) > 63) {
        my_memcpy(&context->buffer[j], data, (i = 64-j));
        SHA1Transform(context->state, context->buffer);
        for ( ; i + 63 < len; i += 64) {
            SHA1Transform(context->state, &data[i]);
        }
        j = 0;
    }
    else i = 0;
    my_memcpy(&context->buffer[j], &data[i], len - i);
}
/**********************************************************************************************
 * SHA1Input
 **********************************************************************************************/
/*
 *
 * Pad the message to 512 bits, and calaulate the SHA1 digest.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/	
void SHA1Result
(
	uint8_t digest[20],	/* SHA1 digest  */		
	SHA1_CTX* context			/* message need to pad and calculate  */
)
{
	uint32_t i, j;
	uint8_t finalcount[8];
	/* Pad the message */
    for (i = 0; i < 8; i++) {
        finalcount[i] = (uint8_t)((context->count[(i >= 4 ? 0 : 1)]
         >> ((3-(i & 3)) * 8) ) & 255); 
    }
    SHA1Input(context, (uint8_t *)"\200", 1);
    while ((context->count[0] & 504) != 448) {
        SHA1Input(context, (uint8_t *)"\0", 1);
    }
    SHA1Input(context, finalcount, 8);
    for (i = 0; i < 20; i++) {
        digest[i] = (uint8_t)
         ((context->state[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
    }
    /* Wipe variables */
    i = j = 0;
    my_memset(context->buffer, 0x00, 64);
    my_memset(context->state, 0x00, 20);
    my_memset(context->count, 0x00, 8);
    my_memset(&finalcount, 0x00, 8);  
	/* Calculate the SHA1 digest */
    SHA1Transform(context->state, context->buffer);
}
/**********************************************************************************************
 * SHA1Truncate
 **********************************************************************************************/
/*
 *
 * This function use to truncate the digest to the length needed.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/	
void SHA1Truncate
(
	uint8_t* d1,		/* data to be truncated */
	uint8_t* d2,		/* truncated data */
	uint32_t len		/* length in bytes to keep */
)
{
	uint32_t i ;
	for (i = 0 ; i < len ; i++) 
		d2[i] = d1[i];
}
/**********************************************************************************************
 * HMACSHA1
 **********************************************************************************************/
/*
 *
 * Calculte the HMAC-SHA1 digest.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/
void HMACSHA1
(
	uint8_t* k,		/* data of HMAC-K */
	uint8_t* d,		/* data to be Hash */
	uint8_t* out		/* digest output buffer */
)
{
	SHA1_CTX ictx, octx ;
	uint8_t isha[SHA_DIGESTSIZE], osha[SHA_DIGESTSIZE] ;
	uint8_t buf[SHA_BLOCKSIZE] ;
	uint32_t i ;

	/*************** Perform inner SHA1 ******************/
	SHA1Reset(&ictx) ;
	
	for (i = 0 ; i < K_LENGTH ; ++i)				/* Pad k with ipad */
		buf[i] =  k[i] ^ 0x36 ;
	for (i = K_LENGTH ; i < SHA_BLOCKSIZE ; ++i) 
		buf[i] = 0x36 ;

	SHA1Input(&ictx, buf, SHA_BLOCKSIZE) ;			/* start with inner pad */
	SHA1Input(&ictx, d, SEED_LENGTH) ;				/* then text of datagram */
	SHA1Result(isha, &ictx) ;						/* finish up 1st pass */
	/*************** Perform outer SHA1 ******************/
	SHA1Reset(&octx) ;								/* innt context for 1st pass*/

	for (i = 0 ; i < K_LENGTH ; ++i)				/* Pad K with opad */
		buf[i] =  k[i] ^ 0x5C ;
	for (i = K_LENGTH ; i < SHA_BLOCKSIZE ; ++i) 
		buf[i] = 0x5C ;

	SHA1Input(&octx, buf, SHA_BLOCKSIZE) ;			/* start with outer pad */
	SHA1Input(&octx, isha, SHA_DIGESTSIZE) ;		/* then results of 1st hash */
	SHA1Result(osha, &octx) ;						/* finish up 2nd pass */

	/*************** Truncate the results ****************/
	SHA1Truncate(osha, out, KEY_LENGTH) ;
}
 void read_seed_from_file(const char* filename)
 {
	char buf[CHUNK];
	FILE *file;
	size_t nread;

	file = fopen(filename, "r");
	if (file) {
		while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
			fwrite(buf, 1, nread, stdout);
		if (ferror(file)) {
			/* deal with error */
		}
		fclose(file);
	}
	strncpy(buffer,buf,BUFFER_SIZE - 1);
 }
/**********************************************************************************************
 * main
 **********************************************************************************************/
/*
 *
 * For test.
 * 
 *
 * \author     Chen Haizheng/Sun Jia
 *
 * \return     
 *
 * \note       
 *
 * \history
 *
 **********************************************************************************************/
 char* substr(const char* src, int m, int n)
{
    // get length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char* dest = (char*)malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
} 

uint8_t hexstring2array(char* hexstring, uint8_t arr[], uint8_t length)
{
	char * pch;
	int cnt = 0;
	pch = strtok (hexstring," ");
	arr[0] = (uint8_t)strtol(pch, NULL, 16);
	cnt = 1;
	while (pch != NULL)
	{
		pch = strtok (NULL, " ");
		arr[cnt] = (uint8_t)strtol(pch, NULL, 16);
		cnt++;
	}

	if((cnt > length) && ((arr[cnt-1]) != 0))
	{
		return 0;
	}
	return 1;	
}

void clear_buff(char* buffer)
{
	int i = 0;
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		buffer[i] = 0;
	}
}

#if 0
uint32_t main()
{

	uint8_t i = 0;
	uint8_t cnt = 0;
	uint8_t hexValue;
	
	#if 0
	int count = 0;
	char* seedStr = buffer;
    for (i = 0; i < 16; i++) {
        
        char* dest = substr(seedStr, i + count, i + 2 + count);
        sscanf(dest, "%x", &hexValue);
		
        Seed[i] = hexValue;
        count += 1;
    }
	#endif
	printf("Reading data from txt file...\n\r");
	printf("Seed:\n\r");
	read_seed_from_file("seed.txt");

	printf("\n\r");
	if(!hexstring2array(buffer,Seed,SEED_LENGTH))
	{
		printf("Invalid Seed. Please fill the valid seed with 16 Bytes\n\r");
		printf("Example: 0x12 0x5D 0xFD 0x18 0x04 0x47 0x8C 0x49 0xCC 0xE7 0x77 0xC6 0x7F 0xFD 0x11 0x7F\n\r");
	}
	HMACSHA1(K_LV1,Seed,Key);
	printf("Key 1\n");
	for(i = 0; i < 16; i++)
	printf("0x%x ",Key[i]);
	printf("\n");

	HMACSHA1(K_LV2,Seed,Key);
	printf("Key 2\n");
		for(i = 0; i<16;i++)
	printf("0x%x ",Key[i]);
	printf("\n");

	HMACSHA1(K_LV3,Seed,Key);
	printf("Key 3\n");
		for(i = 0; i<16;i++)
	printf("0x%x ",Key[i]);
	printf("\n");

	HMACSHA1(K_LV4,Seed,Key);
	printf("Key 4\n");
	for(i = 0; i<16;i++)
	printf("0x%x ",Key[i]);
	
	return 0;
}
#endif
/*****************************************************************************
 *                                    E O F                                                                     
 *****************************************************************************/