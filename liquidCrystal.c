/* liquidCrystal.c
 * @description A basic library to write to an LCD Display (MPLAB X - C30)
 *
 * @author Andrew Siemer <andrew.siemer@eagles.oc.edu> [https://github.com/andrewsiemer]
 * @version 11.23.19
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "liquidCrystal.h"

/* LCDexample -
 *    a basic LCD test function (copy/paste body into main.c)
 */
void LCDexample() {
  /* Setup pins (only need to do once) */
  ADPCFGbits.PCFG9 = 1; //pin23Type = DIGITAL
  ADPCFGbits.PCFG8 = 1; //pin24Type = DIGITAL
  ADPCFGbits.PCFG7 = 1; //pin25Type = DIGITAL
  ADPCFGbits.PCFG6 = 1; //pin26Type = DIGITAL
  TRISFbits.TRISF6 = 0; //pin16Direction = OUTPUT
  TRISFbits.TRISF5 = 0; //pin21Direction = OUTPUT
  TRISFbits.TRISF4 = 0; //pin22Direction = OUTPUT
  TRISBbits.TRISB9 = 0; //pin23Direction = OUTPUT
  TRISBbits.TRISB8 = 0; //pin24Direction = OUTPUT
  TRISBbits.TRISB7 = 0; //pin25Direction = OUTPUT
  TRISBbits.TRISB6 = 0; //pin26Direction = OUTPUT
  
  /* Initialize LCD (only need to do once) */
  initializeLCD();

  /* Display 'hello world' */
  char const * TEXT = "hello world";
  writeToLCDXY(2, 3, TEXT); //write TEXT to display at (2,3)

  __delay32(3686000); //delay 2 seconds
  clearLCD(); //clear display

  /* Example write to all four lines */
  TEXT = "Row 1";
  writeToLCDXY(1, 0, TEXT);
  TEXT = "Row 2";
  writeToLCDXY(2, 0, TEXT);
  TEXT = "Row 3";
  writeToLCDXY(3, 0, TEXT);
  TEXT = "Row 4";
  writeToLCDXY(4, 0, TEXT);
}

/* 
 * Begin LCD library functions 
 */

/* Set Address for Rows & Columns */
void goToLCDXY(uint8_t const ROW, uint8_t const COLUMN) {
   uint8_t address;
   switch (ROW) {
      case 1: address = 0x00; break;
      case 2: address = 0x40; break;
      case 3: address = 0x10; break;
      case 4: address = 0x50; break;
      default: address = 0x00; break;
   }
   LCD_RS = 0;
   LCD_RW = 0;
   pulseCharLCD(0x80 | (address + COLUMN));
}

/* LCD Initialization */
void initializeLCD(void) {
   /* Wait a bit after power-up */
   __delay32(100000);
   LCD_RS = 0;

   /* Initialize LCD to 4-bit mode */
   pulseNibbleLCD(0x03);
   __delay32(10000);
   pulseNibbleLCD(0x03);
   __delay32(1000);
   pulseNibbleLCD(0x03);
   __delay32(1000);

   /* Function Set */
   pulseNibbleLCD(0x02); //set program mode
   __delay32(1000);
   pulseCharLCD(0x28); //set functions
   pulseCharLCD(0x04);
   pulseCharLCD(0x85);
   pulseCharLCD(0x06);
   pulseCharLCD(0x02);
   __delay32(500);

   /* Clear Display */
   pulseCharLCD(0x0C);
   pulseCharLCD(0x01);
   __delay32(1000);
   clearLCD();
}

/* Get character location to be displayed */
void pulseCharLCD(uint8_t const CHARACTER) {
   pulseNibbleLCD((CHARACTER & 0xF0) >> 4);
   pulseNibbleLCD(CHARACTER & 0x0F);
   __delay32(50);
}

/* Display character */
void pulseNibbleLCD(uint8_t const NIBBLE) {
   LCD_DB7 = (NIBBLE & 0x08) > 0;
   LCD_DB6 = (NIBBLE & 0x04) > 0;
   LCD_DB5 = (NIBBLE & 0x02) > 0;
   LCD_DB4 = (NIBBLE & 0x01) > 0;
   LCD_EN = 1;
   __delay32(50);
   LCD_EN = 0;
   __delay32(50);
}

/* Write string of characters to LCD */
void writeStringToLCD (char const * TEXT) {
   uint16_t loop = 0;
   LCD_RS = 1;
   LCD_RW = 0;

   for (loop = 0; TEXT[loop] != '\0'; loop++) {
     pulseCharLCD(TEXT[loop]);
   }
}

/* Write character to location on screen */
void writeToLCDXY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT) {
   goToLCDXY(ROW, COLUMN);
   writeStringToLCD(TEXT);
}

/* Fill screen with blank spaces */
void clearLCD (void) {
   char const * TEXT = "                ";
   writeToLCDXY(1, 0, TEXT);
   writeToLCDXY(2, 0, TEXT);
   writeToLCDXY(3, 0, TEXT);
   writeToLCDXY(4, 0, TEXT);
}
