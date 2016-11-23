/*
 * HC595.h
 *
 * Created: 23.11.2016 15:15:06
 *  Author: maxi
 */ 


#ifndef HC595_H_
#define HC595_H_

//#####Definitions Bereich####
//Settings
#define HC595_Output_AktivLow  1			//w   Wenn 1 werden die Ausg�nge als AktiveLOW betrachtet (Invertieren des Signales)
#define HC595_Size		2					//W   Anzahl aneinander geh�ngter Bausteine

#define HC595_Port		PORTA				//W   PORT am Mikrocontroller �ber den der Software SPI erfolgen soll
#define HC595_Pin_SER	PA1					//W   Serial Data (Daten-Leitung)
#define HC595_Pin_SCK	PA2					//W   Serial Clock (Takt-Leitung)
#define HC595_Pin_RCK	PA0					//W   Strobe Pin (�bernimmt Werte aus RAM und Schreibe nach Ausg�nge)

#define HC595_DDR		DDRA				//
#define HC595_DDR_SER 	PA1					//
#define HC595_DDR_SCK 	PA2					//
#define HC595_DDR_RCK 	PA0					//

//Program spezifisch
#define HC595_Bytes HC595_Size * 8			//--- Anzahl der Externen Ausg�nge

//Definitions
extern void HC595_init (void);				//Init Baugruppe
extern uint8_t HC595_cycle (void);			//Wird Zyklisch vom Haupt programm Aufgerufen (Multitasking Unterst�tzung) Gibt den Status der Baugruppe Zur�ck
extern void HC595_update (void);			//Startet Ausgabe (wichtige vorherige Funktion muss zyklisch aufgerufen werden)
extern uint8_t HC595_getStatus (void);		//fragt das Status byte ab

extern void HC595_setBit (uint8_t number);			//Setzt das angegebene Ausgangs bit auf 1 (Gez�hlt wird ab )
extern void HC595_resetBit (uint8_t number);		//Setzt das angegebene Ausgangs bit auf 0 (Gez�hlt wird ab )
extern void HC595_Byte (uint8_t Byte, uint8_t Port);//Kopiert das Byte in den angegebenen Port
extern void HC595_setByte (uint8_t nummer);			//Setzt das angegebene Ausgangs byte (controller nummer x) auf 1 (Gez�hlt wird ab 1)
extern void HC595_resetByte (uint8_t nummer);		//Setzt das angegebene Ausgangs byte (controller nummer x) auf 0 (Gez�hlt wird ab 1)
extern void HC595_reset (void);						//Setzt alle Ausg�nge auf 0

//Status Definitions
#define HC595_Status_init 0					//HC595 Initialisiert
#define HC595_Status_Error 1				//HC595 Fehler
#define HC595_Status_Update 7				//HC595 Start Update (Wird Zur�ckgesetzt wenn Update Fertig)




#endif /* HC595_H_ */