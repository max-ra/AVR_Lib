#include "avr/io.h"
#include "HC595.h"

//'''Beginn der C datei
//Lokale Variable Deklaration 
	static uint8_t HC595[HC595_Size - 1];
	static uint8_t HC595_Status;
	static uint8_t *HC595_DataPointer = HC595;		//Setzte Zeiger auf anfang des Daten speicher

//Programm code

void HC595_init (void) {
	//Setze Register status (Ein oder Ausgang) auf Ausgang
		HC595_DDR |= (1<<HC595_DDR_RCK) | (1<<HC595_DDR_SCK) | (1<<HC595_DDR_SER);
	
	//Setzte Status auf Abgeschlossene Initialisierung
		HC595_Status |= (1<<HC595_Status_init);

	//Lösche Daten aus Puffer raus
		HC595_reset();

	//Stoße Zyklus an um alle Speicher im IC zu löschen 
		HC595_update();
}

uint8_t HC595_cycle (void) {
if (HC595_Status & HC595_Status_Update) {					//Nur ausführen wenn ein Update angefordert wird
	//Invertierung für Aktive Low Ausgänge
		#if HC595_Output_AktivLow
			*HC595_DataPointer ^= 0xff;
		#endif

	for (int i=0;i<8;i++) {
		//Setze Daten Pin LOW
			HC595_Port &= ~(1<<HC595_Pin_SER);

		//Schau ob das Höchstwertige bit eine 1 hat
			if (*HC595_DataPointer & 0x80) {
				HC595_Port |= (1<<HC595_Pin_SER);
			}
							
		//Schiebe Takt raus Clock Signal
			HC595_Port |= (1<<HC595_Pin_SCK);
			HC595_Port &= ~(1<<HC595_Pin_SCK);
		
		//Setze Daten Pin LOW 
			HC595_Port &= ~(1<<HC595_Pin_SER);	
		
		//Pointer Zyklisch um 1 verschieben (Daten sind nach 8 Durchlaufen an der selben Position)
			*HC595_DataPointer = (*HC595_DataPointer >> 7) | (*HC595_DataPointer << 1);
	}

	//Invertierung für Aktive Low Ausgänge
		#if HC595_Output_AktivLow
			*HC595_DataPointer ^= 0xff;
		#endif

	//Schiebe Zeiger auf die Werte für den nächsten IC
		HC595_DataPointer++;

	if (HC595_DataPointer == (HC595 + HC595_Size)) {	//Alle Daten Wurden Seriell geschrieben
		//Setzte Pointer auf Anfangs wert
			HC595_DataPointer = HC595;

		//Setzte Status Update Zurück
			HC595_Status &= ~(1<<HC595_Status_Update);

		//Sende Impuls zum Laden der Register
			HC595_Port |= (1<<HC595_Pin_RCK);
			HC595_Port &= ~(1<<HC595_Pin_RCK);
	}
}
return HC595_Status;
}

void HC595_update (void) {
	if (!(HC595_Status & (1<<HC595_Status_Update)))
		HC595_Status |= (1<<HC595_Status_Update);
}

uint8_t HC595_getStatus (void) {
	//Zwischenspeichern des Fehlers
		uint8_t temp = HC595_Status;

	//Reset des Fehler (Passiert automatisch beim Aufrufen der Subroutine)
		HC595_Status &= ~(1<<HC595_Status_Error);
	
	//Echten Status Wert zurückgeben
		return temp;
}

//Bitmanipulation
	void HC595_setBit( unsigned char AusgangNr) {
		if (!(HC595_Status & (1<<HC595_Status_Update))) {
			AusgangNr--;								//Offset für die Ausgänge (Mit 1 wird auch ausgang 1 geschaltet)
			unsigned char Port = AusgangNr >> 3;
			unsigned char Bit = AusgangNr & 7;
			HC595[ Port ] |= (1 << ( Bit ) );
		}
	}

	void HC595_resetBit( unsigned char AusgangNr) {
	if (!(HC595_Status & (1<<HC595_Status_Update))) {
		AusgangNr--;								//Offset für die Ausgänge (Mit 1 wird auch ausgang 1 geschaltet)
		unsigned char Port = AusgangNr >> 3;
		unsigned char Bit = AusgangNr & 7;
		HC595[ Port ] &= ~(1 << ( Bit ) );
	}
	}

	void HC595_Byte (uint8_t Byte, uint8_t Port) {
		HC595[Port] = Byte;
	}

	void HC595_setByte( unsigned char Port) {
	if (!(HC595_Status & (1<<HC595_Status_Update)))
		HC595[ Port ] = 0x00;
	}

	void HC595_resetByte( unsigned char Port ) {
	if (!(HC595_Status & (1<<HC595_Status_Update)))
		HC595[ Port ] = 0x00;
	}

	void HC595_reset (void) {
		for (int z = 0; z < HC595_Size; z++)	{
			HC595[z] = 0x00;
		}
	}