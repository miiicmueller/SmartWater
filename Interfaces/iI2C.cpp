#include <string>
#include <assert.h>

#include "iI2C.h"

//Initalisation des attributs UART_x statiques
iI2C* iI2C::USCI_B0 = NULL;
iI2C* iI2C::USCI_B1 = NULL;

iI2C::iI2C(iI2CSpeedEnum i2cSpeed, iI2CPortEnum i2cPort, iI2CModesEnum i2cMode,
		char i2cAddress) {

	//attribution du port I2C
	this->i2cPort = i2cPort;
	this->isEnabled = false;

	this->config(i2cSpeed, i2cMode, i2cAddress);

	//intialiser les adresse pointeur d'instance iUart pour les interruptions
	switch (this->i2cPort) {
	case kUSCI_B0:
		// On doit tester si le pointeur n'est pas utilisé
		// par un autre objet
		if (this->USCI_B0 == NULL) {
			USCI_B0 = this;

		} else {
			// Impossible de créer l'objet voulu
		}
		break;
	case kUSCI_B1:
		// On doit tester si le pointeur n'est pas utilisé
		// par un autre objet
		if (this->USCI_B1 == NULL) {
			USCI_B1 = this;
		} else {
			// Impossible de cr�eer l'objet voulu
		}
		break;
	default:
		;
	}
}

iI2C::~iI2C() {
	//Lib�ration de la pile d'interruption
	switch (this->i2cPort) {
	case kUSCI_B0:
		if (this->USCI_B0 == this) {
			USCI_B0 = NULL;
		}
		break;
	case kUSCI_B1:
		if (this->USCI_B1 == this) {
			USCI_B1 = NULL;
		}
		break;
	default:
		;
	}
}

void iI2C::config(iI2CSpeedEnum i2cSpeed, iI2CModesEnum i2cMode,
		char i2cAddress) {
	switch (this->i2cPort) {
	case kUSCI_B0:
		P3SEL |= 0x03;                            // Assign I2C pins to USCI_B1
		UCB0CTL1 |= UCSWRST;                      // I2C State Machine in Reset

		switch (i2cMode) {
		case kMaster:
			UCB0CTL0 |= UCMST + UCMODE_3 + UCSYNC; // I2C, Master, synchronous mode
			break;
		case kSlave:
			// To be completed
			break;
		}

		// Use of SMCLK 4MHz
		UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK

		switch (i2cSpeed) {
		case k100kHz:
			UCB0BR0 = 40;                           // fSCL = SMCLK/12 = ~100kHz
			UCB0BR1 = 0;
			break;
		case k400kHz:
			UCB0BR0 = 10;                           // fSCL = SMCLK/12 = ~100kHz
			UCB0BR1 = 0;
			break;
		}

		//Adress configuration
		UCB0I2COA = i2cAddress;
		break;

	case kUSCI_B1:
		P4SEL |= 0x06;                            // Assign I2C pins to USCI_B1

		UCB1CTL1 |= UCSWRST;                      // I2C State Machine in Reset

		switch (i2cMode) {
		case kMaster:
			UCB1CTL0 |= UCMST + UCMODE_3 + UCSYNC; // I2C, Master, synchronous mode
			break;
		case kSlave:
			// To be completed
			break;
		}

		// Use of SMCLK 4MHz
		UCB1CTL1 = UCSSEL_2 + UCSWRST + UCTR;            // Use SMCLK

		switch (i2cSpeed) {
		case k100kHz:
			UCB1BR0 = 40;                           // fSCL = SMCLK/12 = ~100kHz
			UCB1BR1 = 0;
			break;
		case k400kHz:
			UCB1BR0 = 10;                           // fSCL = SMCLK/12 = ~100kHz
			UCB1BR1 = 0;
			break;
		}

		//Adress configuration
		UCB1I2COA = i2cAddress;

		break;
	}
}

void iI2C::enable() {
	switch (this->i2cPort) {
	case kUSCI_B0:
		UCB0CTL1 &= ~(UCSWRST);
		break;
	case kUSCI_B1:
		UCB1CTL1 &= ~(UCSWRST);
		if (UCB1STAT & UCBBUSY)                   	// test if bus to be free
		{                                      // otherwise a manual Clock on is
											   // generated
			I2C_PORT_SEL_B1 &= ~SCL_PIN_B1;      // Select Port function for SCL
			I2C_PORT_OUT_B1 &= ~SCL_PIN_B1;               //
			I2C_PORT_DIR_B1 |= SCL_PIN_B1;                // drive SCL low
			I2C_PORT_SEL_B1 |= SDA_PIN_B1 + SCL_PIN_B1; // select module function for the
			// used I2C pins
		}
		break;
	default:
		;
	}
	this->isEnabled = true;
}

void iI2C::disable() {
	switch (this->i2cPort) {
	case kUSCI_B0:
		UCB0CTL1 |= (UCSWRST);
		break;
	case kUSCI_B1:
		UCB1CTL1 |= (UCSWRST);
		break;
	default:
		;
	}
	this->isEnabled = false;
}

bool iI2C::write(char aData) {
	//Ecrire la donnée
	UCB1TXBUF = aData;
}

char iI2C::read() {
	return UCB1RXBUF;
}

void iI2C::setSlaveAddr(char aSlaveAddr) {
	//Set Slave address
	UCB1I2CSA = aSlaveAddr;
	// Mode addr 7 bit
	UCB1CTL0 &= ~UCSLA10;
}

void iI2C::start() {

	UCB1CTL1 |= UCTXSTT;
}

bool iI2C::getStatusFlag(iI2CFlagEnum aFlag) {
	switch (aFlag) {
	case kTXIFG:
		return (bool) (UCB1IFG & UCTXIFG);
	case kSTT:
		return (bool) (UCB1CTL1 & UCTXSTT) ;
	case kNACK:
		return (bool) (UCB1IFG & UCNACKIFG) ;
	case kBUSY :
		return (bool) (UCB1STAT & UCBBUSY) ;
	case kSTP :
		return (bool) (UCB1CTL1 & UCTXSTP) ;
	case kRXIFG :
		return (bool) (UCB1IFG & UCRXIFG);
	default :
		return false;
	}
}

void iI2C::stop() {
	UCB1CTL1 |= UCTXSTP;
}

void iI2C::setWriteMode() {
	//Mode transmission
	UCB1CTL1 |= UCTR;
}

void iI2C::setReadMode() {
	UCB1CTL1 &= ~UCTR;
}

//------------------------------------------------------------------------------
// The USCIAB0_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count.
//------------------------------------------------------------------------------
#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void) {
	switch (__even_in_range(UCB1IV, 12)) {
	case 0:
		break;                           // Vector  0: No interrupts
	case 2:
		break;                           // Vector  2: ALIFG
	case 4:
		break;                           // Vector  4: NACKIFG
	case 6:
		break;                           // Vector  6: STTIFG
	case 8:
		break;                           // Vector  8: STPIFG
	case 10:
		break;                           // Vector 10: RXIFG
	case 12:                                  // Vector 12: TXIFG
		break;
	default:
		break;
	}
}
