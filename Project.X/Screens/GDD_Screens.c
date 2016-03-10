
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
 * @author Devon Harker, Josh Haskins, Vincent Tennant
 * @version 2013-04-03
 *****************************************************************************/


/***************************************************
 *INCLUDE FILES
 ***************************************************/
#include "Graphics/Graphics.h"
#include "GDD_Screens.h"

/***************************************************
 * String literals used in the project
 ***************************************************/
const XCHAR Lockscreen_BTN_1text[ ] = "1";
const XCHAR Lockscreen_BTN_Dtext[ ] = "Delete";
const XCHAR Lockscreen_STE_4text[ ] = "Enter Password";
const XCHAR Lockscreen_BTN_2text[ ] = "2";
const XCHAR Lockscreen_BTN_3text[ ] = "3";
const XCHAR Lockscreen_BTN_4text[ ] = "4";
const XCHAR Lockscreen_BTN_5text[ ] = "5";
const XCHAR Lockscreen_BTN_6text[ ] = "6";
const XCHAR Lockscreen_BTN_7text[ ] = "7";
const XCHAR Lockscreen_BTN_8text[ ] = "8";
const XCHAR Lockscreen_BTN_9text[ ] = "9";
const XCHAR Lockscreen_BTN_Rtext[ ] = "Reset";
const XCHAR Lockscreen_BTN_13text[ ] = "Submit";

const XCHAR Home_BTN_Fireworkstext[ ] = "Fireworks";
const XCHAR Home_BTN_Temperaturetext[ ] = "Open Door";
const XCHAR Home_BTN_16text[ ] = "Button";
const XCHAR Home_BTN_Settingstext[ ] = "Settings";
const XCHAR Home_homeTexttext[ ] = "Light On";

const XCHAR Settings_BTN_chngpwtext[ ] = "Change Password";
const XCHAR Settings_BTN_addusertext[ ] = "Add User";
const XCHAR Settings_BTN_colourtext[ ] = "Change Colour Scheme";
const XCHAR Settings_BTN_nothingtext[ ] = "Do Nothing";

const XCHAR Password_BTN_pwc1text[ ] = "1";
const XCHAR Password_BTN_pwcDtext[ ] = "Delete";
const XCHAR Password_pwcTexttext[ ] = "Enter New Password";
const XCHAR Password_BTN_pwc2text[ ] = "2";
const XCHAR Password_BTN_pwc3text[ ] = "3";
const XCHAR Password_BTN_pwc4text[ ] = "4";
const XCHAR Password_BTN_pwc5text[ ] = "5";
const XCHAR Password_BTN_pwc6text[ ] = "6";
const XCHAR Password_BTN_pwc7text[ ] = "7";
const XCHAR Password_BTN_pwc8text[ ] = "8";
const XCHAR Password_BTN_pwc9text[ ] = "9";
const XCHAR Password_BTN_pwcRtext[ ] = "Reset";
const XCHAR Password_BTN_pwcStext[ ] = "Submit";
const XCHAR Police_txtPolicetext[ ] = "The Police are on their way";




/***************************************************
 * Scheme Declarations
 ***************************************************/
GOL_SCHEME* defscheme;


/***************************************************
 * Function and global Declarations
 ***************************************************/
void (*CreateFunctionArray[NUM_GDD_SCREENS])();
void (*CreatePrimitivesFunctionArray[NUM_GDD_SCREENS])();
WORD currentGDDDemoScreenIndex;
BYTE update = 0;
static BYTE updateGPL = 0;

WORD getScreenIndex() {
    return currentGDDDemoScreenIndex;
}

/***************************************************
 * Function       : GDDDemoCreateFirstScreen
 * Parameters     : none
 * Return         : none
 * Description    : Creates the first screen
 ***************************************************/
void GDDDemoCreateFirstScreen(void) {
    currentGDDDemoScreenIndex = 0;
    update = 1;
    (*CreateFunctionArray[currentGDDDemoScreenIndex])();
}

/***************************************************
 * Function      : GDDDemoNextScreen
 * Parameters    : none
 * Return        : none
 * Description   : Updates counter to show next screen
 ***************************************************/
void GDDDemoNextScreen(void) {
    currentGDDDemoScreenIndex++;
    if (currentGDDDemoScreenIndex >= NUM_GDD_SCREENS) {
        currentGDDDemoScreenIndex = 0;
    }
    update = 1;
}

/***************************************************
 * Function      : GDDDemoGoToScreen
 * Parameters    : int screenIndex
 * Return        : none
 * Description   : Show the screen referred by the index
 ***************************************************/
void GDDDemoGoToScreen(int screenIndex) {
    currentGDDDemoScreenIndex = screenIndex;
    if (currentGDDDemoScreenIndex >= NUM_GDD_SCREENS) {
        currentGDDDemoScreenIndex = 0;
    }
    update = 1;
}

/***************************************************
 * Function       : GDDDemoGOLDrawCallback
 * Parameters     : none
 * Return         : none
 * Description    : Callback to do the actual drawing of widgets
 ***************************************************/
void GDDDemoGOLDrawCallback(void) {
    if (updateGPL) {
        (*CreatePrimitivesFunctionArray[currentGDDDemoScreenIndex])();
        updateGPL = 0;
    }

    if (update) {
        (*CreateFunctionArray[currentGDDDemoScreenIndex])();
        if (CreatePrimitivesFunctionArray[currentGDDDemoScreenIndex] != NULL) {
            updateGPL = 1;
        }
        update = 0;
    }
}

/***************************************************
 * Function       : CreateError
 * Parameters     : none
 * Return         : none
 * Description    : Creates a Error screen
 ***************************************************/
void CreateError(char* string) {
    // Blue Screen Error
    SetColor(119);
    ClearDevice();
    SetColor(-1);

    // Flash Error Message
    if (string == NULL) {
        OutTextXY(0, 0, "Runtime Error.");
    } else {
        OutTextXY(0, 0, string);
    }
}

/***************************************************
 * Function 	      :    CreateLockscreen
 * Parameters      :    none
 * Return          :    none
 * Description     :    Creates GOL widgets used in screen - Lockscreen
 ***************************************************/
void CreateLockscreen(void) {
    GOLFree();
    SetColor(RGBConvert(248, 252, 0));
    ClearDevice();


    if (defscheme != NULL) free(defscheme);
    defscheme = GOLCreateScheme();

    defscheme->Color0 = RGBConvert(32, 168, 224);
    defscheme->Color1 = RGBConvert(16, 132, 168);
    defscheme->TextColor0 = RGBConvert(24, 24, 24);
    defscheme->TextColor1 = RGBConvert(248, 252, 248);
    defscheme->EmbossDkColor = RGBConvert(248, 204, 0);
    defscheme->EmbossLtColor = RGBConvert(24, 116, 184);
    defscheme->TextColorDisabled = RGBConvert(128, 128, 128);
    defscheme->ColorDisabled = RGBConvert(208, 224, 240);
    defscheme->CommonBkColor = RGBConvert(208, 236, 240);
    defscheme->pFont = (void*) &Gentium_16;


    BUTTON *pBTN_1;
    pBTN_1 = BtnCreate(BTN_1, //name
            0, //left
            29, //top
            66, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_1text, //text
            defscheme //scheme
            );

    if (pBTN_1 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_D;
    pBTN_D = BtnCreate(BTN_D, //name
            199, //left
            30, //top
            319, //right
            100, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_Dtext, //text
            defscheme //scheme
            );

    if (pBTN_D == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    STATICTEXT *pSTE_4;
    pSTE_4 = StCreate(STE_4, //name
            0, //left
            0, //top
            319, //right
            30, //bottom
            ST_DRAW | ST_CENTER_ALIGN, //state
            (XCHAR*) Lockscreen_STE_4text, //text
            defscheme //scheme
            );

    if (pSTE_4 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_2;
    pBTN_2 = BtnCreate(BTN_2, //name
            66, //left
            29, //top
            132, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_2text, //text
            defscheme //scheme
            );

    if (pBTN_2 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_3;
    pBTN_3 = BtnCreate(BTN_3, //name
            132, //left
            29, //top
            198, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_3text, //text
            defscheme //scheme
            );

    if (pBTN_3 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_4;
    pBTN_4 = BtnCreate(BTN_4, //name
            0, //left
            99, //top
            66, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_4text, //text
            defscheme //scheme
            );

    if (pBTN_4 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_5;
    pBTN_5 = BtnCreate(BTN_5, //name
            66, //left
            99, //top
            132, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_5text, //text
            defscheme //scheme
            );

    if (pBTN_5 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_6;
    pBTN_6 = BtnCreate(BTN_6, //name
            132, //left
            99, //top
            198, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_6text, //text
            defscheme //scheme
            );

    if (pBTN_6 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_7;
    pBTN_7 = BtnCreate(BTN_7, //name
            0, //left
            169, //top
            66, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_7text, //text
            defscheme //scheme
            );

    if (pBTN_7 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_8;
    pBTN_8 = BtnCreate(BTN_8, //name
            66, //left
            169, //top
            132, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_8text, //text
            defscheme //scheme
            );

    if (pBTN_8 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_9;
    pBTN_9 = BtnCreate(BTN_9, //name
            132, //left
            169, //top
            198, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_9text, //text
            defscheme //scheme
            );

    if (pBTN_9 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_R;
    pBTN_R = BtnCreate(BTN_R, //name
            199, //left
            99, //top
            319, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_Rtext, //text
            defscheme //scheme
            );

    if (pBTN_R == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_13;
    pBTN_13 = BtnCreate(BTN_13, //name
            199, //left
            169, //top
            319, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Lockscreen_BTN_13text, //text
            defscheme //scheme
            );

    if (pBTN_13 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }


}

/***************************************************
 * Function 	      :    CreatePolice
 * Parameters      :    none
 * Return          :    none
 * Description     :    Creates GOL widgets used in screen - Police
 ***************************************************/
void CreatePolice(void) {
    GOLFree();
    SetColor(RGBConvert(248, 0, 0));
    ClearDevice();


    if (defscheme != NULL) free(defscheme);
    defscheme = GOLCreateScheme();

    defscheme->Color0 = RGBConvert(32, 168, 224);
    defscheme->Color1 = RGBConvert(16, 132, 168);
    defscheme->TextColor0 = RGBConvert(24, 24, 24);
    defscheme->TextColor1 = RGBConvert(248, 252, 248);
    defscheme->EmbossDkColor = RGBConvert(248, 204, 0);
    defscheme->EmbossLtColor = RGBConvert(24, 116, 184);
    defscheme->TextColorDisabled = RGBConvert(128, 128, 128);
    defscheme->ColorDisabled = RGBConvert(208, 224, 240);
    defscheme->CommonBkColor = RGBConvert(208, 236, 240);
    defscheme->pFont = (void*) &Gentium_16;


    STATICTEXT *ptxtPolice;
    ptxtPolice = StCreate(txtPolice, //name
            43, //left
            102, //top
            286, //right
            140, //bottom
            ST_DRAW | ST_CENTER_ALIGN, //state
            (XCHAR*) Police_txtPolicetext, //text
            defscheme //scheme
            );

    if (ptxtPolice == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }


}

/***************************************************
 * Function 	      :    CreateHome
 * Parameters      :    none
 * Return          :    none
 * Description     :    Creates GOL widgets used in screen - Home
 ***************************************************/
void CreateHome(void) {
    GOLFree();
    SetColor(RGBConvert(248, 0, 0));
    ClearDevice();


    if (defscheme != NULL) free(defscheme);
    defscheme = GOLCreateScheme();

    defscheme->Color0 = RGBConvert(32, 168, 224);
    defscheme->Color1 = RGBConvert(16, 132, 168);
    defscheme->TextColor0 = RGBConvert(24, 24, 24);
    defscheme->TextColor1 = RGBConvert(248, 252, 248);
    defscheme->EmbossDkColor = RGBConvert(248, 204, 0);
    defscheme->EmbossLtColor = RGBConvert(24, 116, 184);
    defscheme->TextColorDisabled = RGBConvert(128, 128, 128);
    defscheme->ColorDisabled = RGBConvert(208, 224, 240);
    defscheme->CommonBkColor = RGBConvert(208, 236, 240);
    defscheme->pFont = (void*) &Gentium_16;


    BUTTON *pBTN_Fireworks;
    pBTN_Fireworks = BtnCreate(BTN_Fireworks, //name
            0, //left
            120, //top
            159, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Home_BTN_Fireworkstext, //text
            defscheme //scheme
            );

    if (pBTN_Fireworks == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_Door;
    pBTN_Door = BtnCreate(BTN_Door, //name
            160, //left
            0, //top
            319, //right
            119, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Home_BTN_Temperaturetext, //text
            defscheme //scheme
            );

    if (pBTN_Door == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }



    BUTTON *pBTN_Settings;
    pBTN_Settings = BtnCreate(BTN_Settings, //name
            160, //left
            120, //top
            319, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            "Change PW", //text
            defscheme //scheme
            );

    if (pBTN_Settings == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *phomeText;
    phomeText = BtnCreate(homeText, //name
            0, //left
            0, //top
            159, //right
            119, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Home_homeTexttext, //text
            defscheme //scheme
            );

    if (phomeText == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }


}

/***************************************************
 * Function 	      :    CreateSettings
 * Parameters      :    none
 * Return          :    none
 * Description     :    Creates GOL widgets used in screen - Settings
 ***************************************************/
void CreateSettings(void) {
    GOLFree();
    SetColor(RGBConvert(0, 152, 248));
    ClearDevice();


    if (defscheme != NULL) free(defscheme);
    defscheme = GOLCreateScheme();

    defscheme->Color0 = RGBConvert(32, 168, 224);
    defscheme->Color1 = RGBConvert(16, 132, 168);
    defscheme->TextColor0 = RGBConvert(24, 24, 24);
    defscheme->TextColor1 = RGBConvert(248, 252, 248);
    defscheme->EmbossDkColor = RGBConvert(248, 204, 0);
    defscheme->EmbossLtColor = RGBConvert(24, 116, 184);
    defscheme->TextColorDisabled = RGBConvert(128, 128, 128);
    defscheme->ColorDisabled = RGBConvert(208, 224, 240);
    defscheme->CommonBkColor = RGBConvert(208, 236, 240);
    defscheme->pFont = (void*) &Gentium_16;


    BUTTON *pBTN_chngpw;
    pBTN_chngpw = BtnCreate(BTN_chngpw, //name
            0, //left
            0, //top
            319, //right
            59, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Settings_BTN_chngpwtext, //text
            defscheme //scheme
            );

    if (pBTN_chngpw == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_adduser;
    pBTN_adduser = BtnCreate(BTN_adduser, //name
            0, //left
            59, //top
            319, //right
            118, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Settings_BTN_addusertext, //text
            defscheme //scheme
            );

    if (pBTN_adduser == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_colour;
    pBTN_colour = BtnCreate(BTN_colour, //name
            0, //left
            118, //top
            319, //right
            177, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Settings_BTN_colourtext, //text
            defscheme //scheme
            );

    if (pBTN_colour == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_nothing;
    pBTN_nothing = BtnCreate(BTN_nothing, //name
            0, //left
            177, //top
            319, //right
            236, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Settings_BTN_nothingtext, //text
            defscheme //scheme
            );

    if (pBTN_nothing == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }


}

/***************************************************
 * Function 	      :    CreatePassword
 * Parameters      :    none
 * Return          :    none
 * Description     :    Creates GOL widgets used in screen - Password
 ***************************************************/
void CreatePassword(void) {
    GOLFree();
    SetColor(RGBConvert(248, 252, 0));
    ClearDevice();


    if (defscheme != NULL) free(defscheme);
    defscheme = GOLCreateScheme();

    defscheme->Color0 = RGBConvert(32, 168, 224);
    defscheme->Color1 = RGBConvert(16, 132, 168);
    defscheme->TextColor0 = RGBConvert(24, 24, 24);
    defscheme->TextColor1 = RGBConvert(248, 252, 248);
    defscheme->EmbossDkColor = RGBConvert(248, 204, 0);
    defscheme->EmbossLtColor = RGBConvert(24, 116, 184);
    defscheme->TextColorDisabled = RGBConvert(128, 128, 128);
    defscheme->ColorDisabled = RGBConvert(208, 224, 240);
    defscheme->CommonBkColor = RGBConvert(208, 236, 240);
    defscheme->pFont = (void*) &Gentium_16;


    BUTTON *pBTN_pwc1;
    pBTN_pwc1 = BtnCreate(BTN_pwc1, //name
            0, //left
            29, //top
            66, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc1text, //text
            defscheme //scheme
            );

    if (pBTN_pwc1 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwcD;
    pBTN_pwcD = BtnCreate(BTN_pwcD, //name
            199, //left
            30, //top
            319, //right
            100, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwcDtext, //text
            defscheme //scheme
            );

    if (pBTN_pwcD == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    STATICTEXT *ppwcText;
    ppwcText = StCreate(pwcText, //name
            0, //left
            0, //top
            319, //right
            30, //bottom
            ST_DRAW | ST_CENTER_ALIGN, //state
            (XCHAR*) Password_pwcTexttext, //text
            defscheme //scheme
            );

    if (ppwcText == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc2;
    pBTN_pwc2 = BtnCreate(BTN_pwc2, //name
            66, //left
            29, //top
            132, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc2text, //text
            defscheme //scheme
            );

    if (pBTN_pwc2 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc3;
    pBTN_pwc3 = BtnCreate(BTN_pwc3, //name
            132, //left
            29, //top
            198, //right
            99, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc3text, //text
            defscheme //scheme
            );

    if (pBTN_pwc3 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc4;
    pBTN_pwc4 = BtnCreate(BTN_pwc4, //name
            0, //left
            99, //top
            66, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc4text, //text
            defscheme //scheme
            );

    if (pBTN_pwc4 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc5;
    pBTN_pwc5 = BtnCreate(BTN_pwc5, //name
            66, //left
            99, //top
            132, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc5text, //text
            defscheme //scheme
            );

    if (pBTN_pwc5 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc6;
    pBTN_pwc6 = BtnCreate(BTN_pwc6, //name
            132, //left
            99, //top
            198, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc6text, //text
            defscheme //scheme
            );

    if (pBTN_pwc6 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc7;
    pBTN_pwc7 = BtnCreate(BTN_pwc7, //name
            0, //left
            169, //top
            66, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc7text, //text
            defscheme //scheme
            );

    if (pBTN_pwc7 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc8;
    pBTN_pwc8 = BtnCreate(BTN_pwc8, //name
            66, //left
            169, //top
            132, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc8text, //text
            defscheme //scheme
            );

    if (pBTN_pwc8 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwc9;
    pBTN_pwc9 = BtnCreate(BTN_pwc9, //name
            132, //left
            169, //top
            198, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwc9text, //text
            defscheme //scheme
            );

    if (pBTN_pwc9 == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwcR;
    pBTN_pwcR = BtnCreate(BTN_pwcR, //name
            199, //left
            99, //top
            319, //right
            169, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwcRtext, //text
            defscheme //scheme
            );

    if (pBTN_pwcR == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }

    BUTTON *pBTN_pwcS;
    pBTN_pwcS = BtnCreate(BTN_pwcS, //name
            199, //left
            169, //top
            319, //right
            239, //bottom
            0, //radius
            BTN_DRAW, //state
            NULL, //bitmap
            (XCHAR*) Password_BTN_pwcStext, //text
            defscheme //scheme
            );

    if (pBTN_pwcS == NULL) {
        CreateError(0);
        while (1); //Fatal Error, Check for memory leak or heap size
    }


}

/***************************************************
 * Function       : CreateFunctionArray
 * Parameters     : none
 * Return         : none
 * Description    : Creates a array of GOL function pointers
 ***************************************************/
void (*CreateFunctionArray[NUM_GDD_SCREENS])(void) =
{
    &CreateLockscreen,
    &CreateHome, //1
    &CreateSettings,
    &CreatePassword,
    &CreatePolice,

};



/***************************************************
 * Function       : CreatePrimitivesFunctionArray
 * Parameters     : none
 * Return         : none
 * Description    : Creates a array of GPL function pointers
 ***************************************************/
void (*CreatePrimitivesFunctionArray[NUM_GDD_SCREENS])(void) =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};


