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
#define HC595_Output_AktivLow  1			//w   Wenn 1 werden die Ausgänge als AktiveLOW betrachtet (Invertieren des Signales)
#define HC595_Size		2					//W   Anzahl aneinander gehängter Bausteine

#define HC595_Port		PORTA				//W   PORT am Mikrocontroller über den der Software SPI erfolgen soll
#define HC595_Pin_SER	PA1					//W   Serial Data (Daten-Leitung)
#define HC595_Pin_SCK	PA2					//W   Serial Clock (Takt-Leitung)
#define HC595_Pin_RCK	PA0					//W   Strobe Pin (Übernimmt Werte aus RAM und Schreibe nach Ausgänge)

#define HC595_DDR		DDRA				//
#define HC595_DDR_SER 	PA1					//
#define HC595_DDR_SCK 	PA2					//
#define HC595_DDR_RCK 	PA0					//

//Program spezifisch
#define HC595_Bytes HC595_Size * 8			//--- Anzahl der Externen Ausgänge

//Definitions
extern void HC595_init (void);				//Init Baugruppe
extern uint8_t HC595_cycle (void);			//Wird Zyklisch vom Haupt programm Aufgerufen (Multitasking Unterstützung) Gibt den Status der Baugruppe Zurück
extern void HC595_update (void);			//Startet Ausgabe (wichtige vorherige Funktion muss zyklisch aufgerufen werden)
extern uint8_t HC595_getStatus (void);		//fragt das Status byte ab

extern void HC595_setBit (uint8_t number);			//Setzt das angegebene Ausgangs bit auf 1 (Gezählt wird ab )
extern void HC595_resetBit (uint8_t number);		//Setzt das angegebene Ausgangs bit auf 0 (Gezählt wird ab )
extern void HC595_Byte (uint8_t Byte, uint8_t Port);//Kopiert das Byte in den angegebenen Port
extern void HC595_setByte (uint8_t nummer);			//Setzt das angegebene Ausgangs byte (controller nummer x) auf 1 (Gezählt wird ab 1)
extern void HC595_resetByte (uint8_t nummer);		//Setzt das angegebene Ausgangs byte (controller nummer x) auf 0 (Gezählt wird ab 1)
extern void HC595_reset (void);						//Setzt alle Ausgänge auf 0

//Status Definitions
#define HC595_Status_init 0					//HC595 Initialisiert
#define HC595_Status_Error 1				//HC595 Fehler
#define HC595_Status_Update 7				//HC595 Start Update (Wird Zurückgesetzt wenn Update Fertig)




#endif /* HC595_H_ */