/*****************************************************************************
 * This is the brains for the PIC18 chip. It's not very smart.
 *
 * @author Devon Harker, Josh Haskins, Vincent Tennant
 * @version 2013-04-03
 *****************************************************************************/

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <p18f23k22.h>

/////////////////////////////////////////////////////////////////////////////
//                            CONFIG SETTINGS
/////////////////////////////////////////////////////////////////////////////

#pragma config FOSC = INTIO67       //Internal Oscillator
#pragma config PLLCFG = ON          //oscillator multiplied by 4
#pragma config PRICLKEN = ON        //Primary clock enabled
#pragma config PBADEN = OFF         //PORTB<5:0> pins are configured as digital I/O on Reset
#pragma config CCP3MX = PORTC6      //P3A/CCP3 input/output is mulitplexed with RC6
#pragma config T3CMX = PORTC0       //T3CKI is on RC0
#pragma config P2BMX = PORTC0       //P2B is on RC0
#pragma config MCLRE = INTMCLR      //RE3 input pin enabled; MCLR disabled
#pragma config DEBUG = OFF          //Debug disabled
#pragma config XINST = OFF          //Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config WDTEN = OFF          //WDT is controlled by SWDTEN bit of the WDTCON register
#pragma config FCMEN = OFF          //Disable Fail Safe Clock Monitor
#pragma config IESO = OFF           //Disable Internal External Switchover
#pragma config PWRTEN = ON          //Enable Power-Up Timer
#pragma config BOREN =  NOSLP       //Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
#pragma config BORV = 285           //Set brown-out voltage to 2.85v
#pragma config LVP = OFF            //Low-Voltage ICSP disabled
#pragma config CP0 = OFF            //Block 0 (00200-0007FFh) not code-protected
#pragma config CP1 = OFF            //Block 1 (000800-000FFFh) not code-protected
#pragma config CPB = OFF            //Boot Block (000000-0001FFh) not code-protected
#pragma config CPD = OFF            //Data EEPROM not code-protected
#pragma config WRT0 = OFF           //Block 0 (00200-0007FFh) not write-protected
#pragma config WRT1 = OFF           //Block 1 (000800-000FFFh) not write-protected
#pragma config WRTC = OFF           //Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTB = OFF           //Boot Block (000000-0001FFh) not write-protecte
#pragma config WRTD = OFF           //Data EEPROM not write-protected
#pragma config EBTR0 = OFF          //Block 0 (00200-0007FFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF          //Block 1 (000800-000FFFh) not protected from table reads executed in other blocks
#pragma config EBTRB = OFF          //Boot Block (000000-0001FFh) not protected from table reads executed in other blocks

/////////////////////////////////////////////////////////////////////////////
//                            CONSTANTS
/////////////////////////////////////////////////////////////////////////////

#define _XTAL_FREQ          64000000
#define TRUE                1
#define FALSE               0

#define PowerLED            LATBbits.LATB5
#define PowerLEDTris        TRISBbits.TRISB5

#define AlertLight          LATCbits.LATC3
#define AlertLightTris      TRISCbits.TRISC3
#define DoorMotor           LATCbits.LATC2
#define DoorMotorTris       TRISCbits.TRISC2

#define PWMTris             TRISBbits.RB1
#define PWMPin              LATBbits.LATB1

#define Control0            PORTAbits.RA0
#define Control1            PORTAbits.RA1
#define ControlTris0        TRISAbits.TRISA0
#define ControlTris1        TRISAbits.TRISA1
#define ControlAnsel0       ANSELAbits.ANSA0
#define ControlAnsel1       ANSELAbits.ANSA1

#define RX2                 LATBbits.LATB7
#define RX2Tris             TRISBbits.TRISB7

#define TX2                 LATBbits.LATB6
#define TX2Tris             TRISBbits.TRISB6

#define SetOn(x)            (x) = 1
#define SetOff(x)           (x) = 0
#define SetAsOutput(x)      (x) = 0
#define SetAsInput(x)       (x) = 1
#define SetAsDigital(x)     (x) = 0

int doorState;
#define CLOSED              0
#define OPEN                1

/////////////////////////////////////////////////////////////////////////////
//                            ROUTINES
/////////////////////////////////////////////////////////////////////////////

/**
 * Initializes inputs and outputs.
 */
void initialize() {
    //Sets Internal Oscillator to 16Mhz
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;

    //Uses 4x Multiplier to achieve 64Mhz
    OSCTUNEbits.PLLEN = 1; //Enables PLL

    //Configure Power LED
    SetAsOutput(PowerLEDTris);

    //Configure Alert Light
    SetAsOutput(AlertLightTris);
    SetOff(AlertLight);

    //Configure Door Motor
    SetAsOutput(DoorMotorTris);
    SetOff(DoorMotor);

    //Configure Input from Control
    SetAsInput(ControlTris0);
    SetAsInput(ControlTris1);
    SetAsDigital(ControlAnsel0);
    SetAsDigital(ControlAnsel1);
    SetOff(Control0);
    SetOff(Control1);

    //Set up PMWm Module
    SetAsOutput(PWMTris);
    SetOff(PWMPin);
    doorState = CLOSED;
}

/**
 * Boot sequence for the boot up light.
 */
void boot() {

    int i, j;

    for (i = 0; i < 3; i++) {
        SetOn(PowerLED);

        //80ms delay
        for (j = 0; j < 8; j++)
            __delay_ms(10);

        SetOff(PowerLED);

        //80ms delay
        for (j = 0; j < 8; j++)
            __delay_ms(10);
    }
}

/**
 * Controls the motor.
 */
void motor() {
    int j;
    //we go up to 1.2ms
    SetOn(PWMPin);
    __delay_us(1200);

    if (doorState == CLOSED) {

        //we go up to 20ms
        SetOff(PWMPin);
        __delay_us(800); //.8ms
        for (j = 0; j < 18; j++) //18ms
            __delay_ms(1);
    } else {
        //we go up to 2ms
        __delay_us(800);

        SetOff(PWMPin);
        //we go up to 20ms
        for (j = 0; j < 18; j++)//18ms
            __delay_ms(1);
    }
}

/////////////////////////////////////////////////////////////////////////////
//                            MAIN
/////////////////////////////////////////////////////////////////////////////

int main(void) {

    initialize();
    boot();
    char OldControlInput = 0;
    char NewControlInput = 0;

    while (TRUE) {

        motor(); //PMW loop

        NewControlInput = Control0 + 2 * Control1;

        if (OldControlInput != NewControlInput) {

            if (NewControlInput == 0) {
                SetOff(AlertLight);
            } else if (NewControlInput == 1) {
                SetOn(AlertLight);
            } else if (NewControlInput == 2) {
                SetOff(DoorMotor);
                doorState = CLOSED;
            } else if (NewControlInput == 3) {
                SetOn(DoorMotor);
                doorState = OPEN;
            }

            OldControlInput = NewControlInput;
        }
    }

    return (EXIT_SUCCESS);
}
