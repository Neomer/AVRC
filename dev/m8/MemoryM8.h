#ifndef MEMORY
#define MEMORY

#define iPIN_DISP	0x00
#define iDDR_DISP	0x01
#define iPORT_DISP	0x02

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define iTWBR	(0x20)
#define iTWSR	(0x21)
#define iTWAR	(0x22)
#define iTWDR	(0x23)

/* ADC */
#define iADCW	(0x24)
#ifndef __ASSEMBLER__
#define iADC	(0x24)
#endif
#define iADCL	(0x24)
#define iADCH	(0x25)
#define iADCSR	(0x26)
#define iADCSRA	(0x26)  /* Changed in 2486H-AVR-09/02 */
#define iADMUX	(0x27)

/* analog comparator */
#define iACSR	(0x28)

/* USART */
#define iUBRRL	(0x29)
#define iUCSRB	(0x2A)
#define iUCSRA	(0x2B)
#define iUDR	(0x2C)

/* SPI */
#define iSPCR	(0x2D)
#define iSPSR	(0x2E)
#define iSPDR	(0x2F)

/* Port D */
#define iPIND	(0x30)
#define iDDRD	(0x31)
#define iPORTD	(0x32)

/* Port C */
#define iPINC	(0x33)
#define iDDRC	(0x34)
#define iPORTC	(0x35)

/* Port B */
#define iPINB	(0x36)
#define iDDRB	(0x37)
#define iPORTB	(0x38)

#define iPB		0x36
#define iPC		0x33
#define iPD		0x30

/* EEPROM Control Register */
#define iEECR	(0x3C)

/* EEPROM Data Register */
#define iEEDR	(0x3D)

/* EEPROM Address Register */
#define iEEAR	(0x3E)
#define iEEARL	(0x3E)
#define iEEARH	(0x3F)

#define iUCSRC	(0x40)
#define iUBRRH	(0x40)

#define iWDTCR	(0x41)
#define iASSR	(0x42)

/* Timer 2 */
#define iOCR2	(0x43)
#define iTCNT2	(0x44)
#define iTCCR2	(0x45)

/* Timer 1 */
#define iICR1	(0x46)
#define iICR1L	(0x46)
#define iICR1H	(0x47)
#define iOCR1B	(0x48)
#define iOCR1BL	(0x48)
#define iOCR1BH	(0x49)
#define iOCR1A	(0x4A)
#define iOCR1AL	(0x4A)
#define iOCR1AH	(0x4B)
#define iTCNT1	(0x4C)
#define iTCNT1L	(0x4C)
#define iTCNT1H	(0x4D)
#define iTCCR1B	(0x4E)
#define iTCCR1A	(0x4F)

#define iSFIOR	(0x50)

#define iOSCCAL	(0x51)

/* Timer 0 */
#define iTCNT0	(0x52)
#define iTCCR0	(0x53)

#define iMCUCSR	(0x54)
#define iMCUSR   (0x54)  /* Defined as an alias for MCUCSR. */

#define iMCUCR	(0x55)

#define iTWCR	(0x56)

#define iSPMCR	(0x57)

#define iTIFR	(0x58)
#define iTIMSK	(0x59)

#define iGIFR	(0x5A)
#define iGIMSK	(0x5B)
#define iGICR	(0x5B)

#endif // MEMORY

