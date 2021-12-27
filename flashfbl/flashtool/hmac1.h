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
* Filename:     $Source: HMACSHA1.h $
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
* Description:            
*
* Notes:        
*
******************************************************************************/

#ifndef _IPSEC_SHA1_H_
#define _IPSEC_SHA1_H_


void HMACSHA1
(
	uint8_t* k,		/* data of HMAC-K */
	uint8_t* d,		/* data to be Hash */
	uint8_t* out		/* digest output buffer */
);

#endif
/*****************************************************************************
 *                                    E O F                                                                     
 *****************************************************************************/