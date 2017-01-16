#ifndef MEMORY
#define MEMORY

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define iTWBR	(0x00)
#define iTWSR	(0x01)
#define iTWAR	(0x02)
#define iTWDR	(0x03)

/* ADC */
#define iADCW	(0x04)
#ifndef __ASSEMBLER__
#define iADC	(0x04)
#endif
#define iADCL	(0x04)
#define iADCH	(0x05)
#define iADCSR	(0x06)
#define iADCSRA	(0x06)  /* Changed in 2486H-AVR-09/02 */
#define iADMUX	(0x07)

/* analog comparator */
#define iACSR	(0x08)

/* USART */
#define iUBRRL	(0x09)
#define iUCSRB	(0x0A)
#define iUCSRA	(0x0B)
#define iUDR	(0x0C)

/* SPI */
#define iSPCR	(0x0D)
#define iSPSR	(0x0E)
#define iSPDR	(0x0F)

/* Port D */
#define iPIND	(0x10)
#define iDDRD	(0x11)
#define iPORTD	(0x12)

/* Port C */
#define iPINC	(0x13)
#define iDDRC	(0x14)
#define iPORTC	(0x15)

/* Port B */
#define iPINB	(0x16)
#define iDDRB	(0x17)
#define iPORTB	(0x18)

/* EEPROM Control Register */
#define iEECR	(0x1C)

/* EEPROM Data Register */
#define iEEDR	(0x1D)

/* EEPROM Address Register */
#define iEEAR	(0x1E)
#define iEEARL	(0x1E)
#define iEEARH	(0x1F)

#define iUCSRC	(0x20)
#define iUBRRH	(0x20)

#define iWDTCR	(0x21)
#define iASSR	(0x22)

/* Timer 2 */
#define iOCR2	(0x23)
#define iTCNT2	(0x24)
#define iTCCR2	(0x25)

/* Timer 1 */
#define iICR1	(0x26)
#define iICR1L	(0x26)
#define iICR1H	(0x27)
#define iOCR1B	(0x28)
#define iOCR1BL	(0x28)
#define iOCR1BH	(0x29)
#define iOCR1A	(0x2A)
#define iOCR1AL	(0x2A)
#define iOCR1AH	(0x2B)
#define iTCNT1	(0x2C)
#define iTCNT1L	(0x2C)
#define iTCNT1H	(0x2D)
#define iTCCR1B	(0x2E)
#define iTCCR1A	(0x2F)

#define iSFIOR	(0x30)

#define iOSCCAL	(0x31)

/* Timer 0 */
#define iTCNT0	(0x32)
#define iTCCR0	(0x33)

#define iMCUCSR	(0x34)
#define iMCUSR   (0x34)  /* Defined as an alias for MCUCSR. */

#define iMCUCR	(0x35)

#define iTWCR	(0x36)

#define iSPMCR	(0x37)

#define iTIFR	(0x38)
#define iTIMSK	(0x39)

#define iGIFR	(0x3A)
#define iGIMSK	(0x3B)
#define iGICR	(0x3B)

#endif // MEMORY

