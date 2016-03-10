/*****************************************************************************
 *
 * Software License Agreement
 *
 * Copyright © 2012 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED ÒAS ISÓ WITHOUT WARRANTY OF ANY
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

/*****************************************************************************
 * SECTION:  Includes
 *****************************************************************************/
#include <Graphics/Graphics.h>
#include "GDD_Screens.h"

#include <p32xxxx.h> // Include PIC32 specifics header file.
#include <plib.h> // Include the PIC32 Peripheral Library.

#define CLOSED              0
#define OPEN                1

#define OFF                 0
#define ON                  1

BYTE doorStatus = CLOSED;
BYTE lightStatus = ON;
BYTE customLightShow = OFF;
extern BYTE update;

int code = 0;
int count = 0;
int attempt = 0;
char star[] = "Enter Password";
const int pwLength = 5;
int currentPWIndex;
int passwords[] = {12345, 55555, 77777, 98765, 11111};
char usernames[5][7] = {
    {"Demo"},
    {"Josh"},
    {"Devon"},
    {"Vincent"},
    {"Guest"}
};

/**
 * Close the door.
 */
void closeDoor() {
    LATEbits.LATE8 = 1;
    LATDbits.LATD14 = 0;
    doorStatus = CLOSED;
}

/**
 * Open the door.
 */
void openDoor() {
    LATEbits.LATE8 = 1;
    LATDbits.LATD14 = 1;
    doorStatus = OPEN;
}

/**
 * Turn light on.
 */
void lightOn() {
    LATEbits.LATE8 = 0;
    LATDbits.LATD14 = 1;
    lightStatus = ON;
}

/**
 * Turn light off.
 */
void lightOff() {
    LATEbits.LATE8 = 0;
    LATDbits.LATD14 = 0;
    lightStatus = OFF;
}

/**
 * Resets all data related to password entry.
 */
void clearCode() {
    code = 0;
    count = 0;
    attempt = 0;
}

/**
 * Custom light show with the joystick.
 */
void customLights() {
    if (customLightShow) {
        lightOn();
        LATCbits.LATC1 = LATBbits.LATB0;
        LATCbits.LATC2 = LATBbits.LATB1;
        LATDbits.LATD3 = !LATBbits.LATB3;
        LATDbits.LATD2 = !LATBbits.LATB4;
        LATDbits.LATD1 = !LATBbits.LATB4;
    }
}

/**
 * Handles the scenario when user attempts to enter a password longer than 5 digits.
 */
void theMax() {
    if (getScreenIndex() == 0) {
        if (count > pwLength) {
            StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), "Max Length Reached");
            SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
            code = code / 10;
            count = count - 1;
        }

        setNumLights(count);

    } else if (getScreenIndex() == 3) {
        if (count > pwLength) {
            StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), "Max Length Reached");
            SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
            code = code / 10;
            count = count - 1;
        }

        setNumLights(count);
    }


}

/**
 * Uses the passed parameters to either turn on or off the lights.
 * @param a light 1
 * @param b light 2
 * @param c light 3
 * @param d light 4
 * @param e light 5
 */
void turnOnSpecficLights(BYTE a, BYTE b, BYTE c, BYTE d, BYTE e) {

    LATCbits.LATC1 = a;
    LATCbits.LATC2 = b;
    LATDbits.LATD3 = c;
    LATDbits.LATD2 = d;
    LATDbits.LATD1 = e;
}

/**
 * A light show using the lights.
 */
void fireworks() {

    // Josh's light show.
    turnOnSpecficLights(ON, ON, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, OFF, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, ON, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, ON, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, ON, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, OFF, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, ON, ON, ON);
    ourDelay(150000);


    //Devon's light show.
    turnOnSpecficLights(OFF, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, ON, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, ON, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, OFF, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, OFF, OFF, OFF);
    ourDelay(150000);
    
    turnOnSpecficLights(ON, OFF, OFF, OFF, OFF);
    ourDelay(150000);



    //end sequence
    turnOnSpecficLights(ON, ON, ON, ON, ON);
    ourDelay(150000);

    turnOnSpecficLights(OFF, ON, ON, ON, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, ON, OFF, OFF);
    ourDelay(150000);

    turnOnSpecficLights(OFF, OFF, OFF, OFF, OFF);
    ourDelay(150000);

}

/**
 * Delays the program for s specific amount of time.
 *
 * Also includes ASSEMBLY.
 *
 * @param delay amount of time for delay
 */
void ourDelay(int delay) {
    while (delay >= 0) {
        --delay;
        int i;
        for (i = 0; i < 10; ++i)
            asm("NOP");
    }
}

void GDDDemoGOLMsgCallback(WORD objMsg, OBJ_HEADER *pObj, GOL_MSG *pMsg) {


    /**************************************************************************
     Lockscreen
     **************************************************************************/

    //reset button
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_R))) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = 0;
        count = 0;
    }

    //delete button
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_D))) {

        if (count != 0) {
            code = code / 10;
            count = count - 1;
        }

        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
    }

    //submit button
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_13))) {
        BYTE pwMatch = 0;
        int i = 0;
        for (i = 0; i < sizeof (passwords); i++) {
            if (code == passwords[i] && code != 0) {
                pwMatch = 1;
                currentPWIndex = i;
                break;
            }
        }

        //for when password is correct
        if (pwMatch) {
            StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), (XCHAR*) "Access Granted");
            SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);

            clearCode();
            lightOff();
            GDDDemoGoToScreen(1);

        }//for when password is wrong
        else {

            code = 0;
            count = 0;
            attempt++;
            lightOn();

            //when too many attempts are made, police are called
            if (attempt >= 3) {
                //call police screen
                GDDDemoGoToScreen(4);

            } else {
                StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), (XCHAR*) "Wrong Password");
                SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
            }
        }

        setNumLights(count);
    }

    /****************
     Keypad (Numbers)
     ****************/
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_1)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 1;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_2)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 2;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_3)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 3;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_4)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 4;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_5)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 5;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_6)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 6;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_7)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 7;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_8)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 8;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_9)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((STE_4))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((STE_4))))), ST_DRAW);
        code = (code * 10) + 9;
        ++count;
    }

    /**************************************************************************
     Home Screen
     **************************************************************************/

    //light
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((homeText))) {
        if (lightStatus == OFF) {
            lightOn();
            BtnSetText(((BUTTON*) (GOLFindObject(homeText))), (XCHAR*) "Light Off");
            SetState(((BUTTON*) (GOLFindObject(homeText))), BTN_DRAW);
        } else {
            lightOff();
            BtnSetText(((BUTTON*) (GOLFindObject(homeText))), (XCHAR*) "Light On");
            SetState(((BUTTON*) (GOLFindObject(homeText))), BTN_DRAW);
        }
    }

    //change password
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_Settings))) {
        GDDDemoGoToScreen(3);
    }

    //fireworks
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_Fireworks))) {
        fireworks();
    }

    //door
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_Door)) {

        //opens the door
        if (doorStatus == CLOSED) {
            openDoor();
            BtnSetText(((BUTTON*) (GOLFindObject(BTN_Door))), (XCHAR*) "Close Door");
            SetState(((BUTTON*) (GOLFindObject(BTN_Door))), BTN_DRAW);
        } else {
            //close the door
            closeDoor();
            BtnSetText(((BUTTON*) (GOLFindObject(BTN_Door))), (XCHAR*) "Open Door");
            SetState(((BUTTON*) (GOLFindObject(BTN_Door))), BTN_DRAW);
        }
    }


    /**************************************************************************
     Settings Screen
     **************************************************************************/

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_chngpw)) {
        GDDDemoGoToScreen(3);
    }

    /**************************************************************************
     Change Password
     **************************************************************************/

    //password change reset
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_pwcR))) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = 0;
        count = 0;
    }

    //password change delete
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_pwcD))) {

        if (count != 0) {
            code = code / 10;
            count = count - 1;
        }

        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);

    }

    //password change submit
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == ((BTN_pwcS))) {

        if (code / 10000 == 0) {
            StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), (XCHAR*) "Must be 5 Characters");
            SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        } else {

            passwords[currentPWIndex] = code;
            code = 0;
            count = 0;
            GDDDemoGoToScreen(1);
        }

        setNumLights(count);
    }

    /****************
     Keypad (Numbers)
     ****************/
    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc1)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 1;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc2)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 2;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc3)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 3;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc4)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 4;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc5)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 5;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc6)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 6;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc7)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 7;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc8)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 8;
        ++count;
    }

    if (objMsg == BTN_MSG_RELEASED && pObj->ID == (BTN_pwc9)) {
        StSetText(((STATICTEXT*) (GOLFindObject(((pwcText))))), star);
        SetState(((STATICTEXT*) (GOLFindObject(((pwcText))))), ST_DRAW);
        code = (code * 10) + 9;
        ++count;
    }

    /**************************************************************************
     Universal/Always running
     **************************************************************************/
    theMax();
    customLights();
}
