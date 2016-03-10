
/*****************************************************************************
* Microchip Graphics Library
* Graphics Display Designer (GDD) Template
*****************************************************************************
 
* Dependencies:    See INCLUDES section below
* Processor:       PIC24F, PIC24H, dsPIC, PIC32
* Compiler:        MPLAB C30 V3.22, MPLAB C32 V1.05b
* Linker:          MPLAB LINK30, MPLAB LINK32
* Company:         Microchip Technology Incorporated
*
* Software License Agreement
*
* Copyright (c) 2010 Microchip Technology Inc.  All rights reserved.
* Microchip licenses to you the right to use, modify, copy and distribute
* Software only when embedded on a Microchip microcontroller or digital
* signal controller, which is integrated into your product or third party
* product (pursuant to the sublicense terms in the accompanying license
* agreement).  
*
* You should refer to the license agreement accompanying this Software
* for additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
* OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
* PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
* OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 
* BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
* DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
* INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
* COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
* CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
* OR OTHER SIMILAR COSTS.
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/


#ifndef    _GDD_SCREENS_H_
#define    _GDD_SCREENS_H_


/***************************************************
*FUNCTION DECLARATION
***************************************************/

void GDDDemoCreateFirstScreen(void);
void GDDDemoGOLDrawCallback(void);
void GDDDemoNextScreen(void);
void GDDDemoGoToScreen(int screenIndex);
void GDDDemoGOLMsgCallback(WORD objMsg, OBJ_HEADER *pObj, GOL_MSG *pMsg);


/***************************************************
*FONT DECLARATION
***************************************************/
extern const FONT_FLASH Gentium_16;


/***************************************************
*SCREEN DECLARATION
***************************************************/
void CreateLockscreen(void);
void CreateHome(void);
void CreateSettings(void);
void CreatePassword(void);
void CreatePolice(void);



/***************************************************
*UNIQUE WIDGET ID'S
***************************************************/
#define BTN_1 1
#define BTN_D 2
#define STE_4 3
#define BTN_2 4
#define BTN_3 5
#define BTN_4 6
#define BTN_5 7
#define BTN_6 8
#define BTN_7 9
#define BTN_8 10
#define BTN_9 11
#define BTN_R 12
#define BTN_13 13
#define BTN_Fireworks 14
#define BTN_Door 15
#define BTN_16 16
#define BTN_Settings 17
#define homeText 18
#define BTN_chngpw 19
#define BTN_adduser 20
#define BTN_colour 21
#define BTN_nothing 22
#define BTN_pwc1 23
#define BTN_pwcD 24
#define pwcText 25
#define BTN_pwc2 26
#define BTN_pwc3 27
#define BTN_pwc4 28
#define BTN_pwc5 29
#define BTN_pwc6 30
#define BTN_pwc7 31
#define BTN_pwc8 32
#define BTN_pwc9 33
#define BTN_pwcR 34
#define BTN_pwcS 35
#define txtPolice 36


#define	NUM_GDD_SCREENS 5
#endif
