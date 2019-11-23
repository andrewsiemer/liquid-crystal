/* liquidCrystal.h
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
#include <stdint.h>
#include <p30f3013.h>

#ifndef LIQUIDCRYSTAL_H
#define	LIQUIDCRYSTAL_H

/* LCD Pins */
#define LCD_RS LATFbits.LATF6 //Pin 16
#define LCD_RW LATFbits.LATF5 //Pin 21
#define LCD_EN LATFbits.LATF4 //Pin 22
#define LCD_DB4 LATBbits.LATB9 //Pin 23
#define LCD_DB5 LATBbits.LATB8 //Pin 24
#define LCD_DB6 LATBbits.LATB7 //Pin 25
#define LCD_DB7 LATBbits.LATB6 //Pin 26

/* Example Function */
void LCDexample();

/* LCD functions */
void goToLCDXY(uint8_t const ROW, uint8_t const COLUMN);
void initializeLCD(void);
void pulseCharLCD(uint8_t const CHARACTER);
void pulseNibbleLCD(uint8_t const NIBBLE);
void writeStringToLCD (char const * TEXT);
void writeToLCDXY (uint8_t const ROW, uint8_t const COLUMN, char const * TEXT);
void clearLCD(void);

#endif	/* LIQUIDCRYSTAL_H */

