#include <string>
#include <assert.h>

#include "iRTC.h"
#include "Interfaces/iCpu.h"

iRTC* iRTC::RTC_A = NULL;

/**
 * Constructeur de base
 * Active le mode RTC et initialise les alarmes à 0
 */
iRTC::iRTC()
    {
    //Configuration de la RTC_A en mode RTC
    RTCCTL01 |= RTCMODE;

    this->aDeltaMinuteAlarme = 0;
    this->aMinuteAlarme = 0;

    RTCAMIN = 0x00;
    RTCAHOUR = 0x00;

    RTCADOW = 0x00;
    RTCADAY = 0x01;
    RTCMON = 0x01;
    RTCYEAR = 0x01;

    iRTC::RTC_A = this;

    }

/**
 * Destructeur de base
 * Libère le pointeur static
 */
iRTC::~iRTC()
    {
    iRTC::RTC_A = NULL;
    }

/**
 * Activation du reveil du micro tout les xx minutes
 * aMin : minutes absolues pour l'alarme
 */
void iRTC::setAlarm(char aHour, char aMin)
    {

    RTCAHOUR = aHour + 0x80;
    RTCAMIN = aMin + 0x80;
    RTCADOW = 0x00;
    RTCADAY = 0x00;
    RTCCTL01 |= RTCAIE;
    }

/**
 * Permet de stopper les alarmes
 */
void iRTC::resetAlarm()
    {
    RTCCTL01 &= ~RTCAIE;
    RTCAHOUR = 0x00;
    RTCAMIN = 0x00;
    RTCADOW = 0x00;
    RTCADAY = 0x00;
    }

/**
 * Lecture de la date. Tout les nombres sont entiers
 * *aYear : Année sur 16bits
 * *aMonth: Mois de l'année sur 8bits
 * *aDay : Jour du mois sur 8bits
 * *aDayOfWeek : jour de la semaine sur 8bits
 */
void iRTC::readDate(int *aYear, char *aMonth, char *aDay, char *aDayOfWeek)
    {
    //Attente que l'heure soit valide env 1-2s pour être synchronisé
    // Il vaudrait mieux utiliser les interruptions
    while ((RTCCTL01 & RTCRDY))
	;
    while (!(RTCCTL01 & RTCRDY))
	;

    *aYear = RTCYEAR;
    *aMonth = RTCMON;
    *aDay = RTCDAY;
    *aDayOfWeek = RTCDOW;
    }

/**
 * Lecture de l'heure
 * Peut prendre une seconde ! On doit attendre le moment que l'heure soit valide...
 * *aHour : Heure sur 8bits
 * *aMin: Minutes sur 8bits
 * *aSecond : Secondes sur 8bits
 */
void iRTC::readTime(char *aHour, char *aMin, char *aSecond)
    {

//Attente que l'heure soit valide env 1-2s pour etre synchronise
// Il vaudrait mieux utiliser les interruptions
    while ((RTCCTL01 & RTCRDY))
	;
    while (!(RTCCTL01 & RTCRDY))
	;

    *aSecond = RTCSEC;
    *aMin = RTCMIN;
    *aHour = RTCHOUR;
    }

/**
 * Configuration de la date. Tout les nombres sont entiers
 * aYear : Annee sur 16bits
 * aMonth: Mois de l'annee sur 8bits
 * aDay : Jour du mois sur 8bits
 * aDayOfWeek : jour de la semaine sur 8bits
 */
void iRTC::setDate(int aYear, char aMonth, char aDay, char aDayOfWeek)
    {
    RTCYEAR = aYear;
    RTCMON = aMonth;
    RTCDAY = aDay;
    }

/**
 * Configuration de l'heure
 * Peut prendre une seconde ! On doit attendre le moment que l'heure soit valide...
 * aHour : Heure sur 8bits
 * aMinute: Minutes sur 8bits
 * aSecond : Secondes sur 8bits
 */
void iRTC::setHour(char aHour, char aMinute, char aSecond)
    {
    RTCSEC = aSecond;
    RTCMIN = aMinute;
    RTCHOUR = aHour;
    }

/**
 * Calibration de la RTC.
 * Principe : voir datasheet de la famille MSP430F55XX (UserGuide)
 *
 * Compensation en fonction de la température
 */
void iRTC::calibration(int aTemperature)
    {
    //TODO : possibilite d'implementation
    }

/**
 * Activation de la RTC (le clk)
 */
void iRTC::enableRTC()
    {
//Enable du Real Time Clock
    RTCCTL01 &= ~RTCHOLD;
    }

/**
 * Désactivation de la RTC (le clk)
 */
void iRTC::disableRTC()
    {
//Enable du Real Time Clock
    RTCCTL01 |= RTCHOLD;
    }

/**
 * Fonction appelé lors du réveil du microcontrolleur
 */
void iRTC::wakeUpInterrupt()
    {

    //Réveil du microcontrolleur
    iCpu::setPowerMode(kActiveMode);

    //Réamorcage de l'alarme
//	this->aMinuteAlarme += this->aDeltaMinuteAlarme;
//	RTCAMIN = this->aMinuteAlarme + 0x80;
    }

/**
 * @Deprecated
 * Inutile
 */
bool iRTC::write(UInt8 aData)
    {
    return false;
    }

/**
 * @Deprecated
 * Inutile
 */
UInt8 iRTC::read()
    {
    return 0;
    }

// RTC_A Interrupt handler
#pragma vector=RTC_VECTOR
__interrupt void RTC_A(void)
    {
    if ((RTCCTL01 & RTCAIFG)== RTCAIFG)
	{
	if (iRTC::RTC_A != NULL)
	    {
	    iRTC::RTC_A->wakeUpInterrupt();
	    RTCCTL01 &= ~RTCAIFG;

	    // Reveil du micro en phase endormi la plus basse
	    LPM3_EXIT;
	    }
	}

    }

