#include <string>
#include <assert.h>
#include "Interfaces/iRTC.h"

#include "mRTC.h"

mRTC::mRTC()
    {
    this->iRtc = new iRTC();
    }

mRTC::~mRTC()
    {

    }

/**
 * Ouverture du module
 * Active la RTC
 */
void mRTC::mOpen()
    {
    this->iRtc->enableRTC();
    }

/**
 * Fermeture du module
 * Desactive la RTC + reset les alarme
 */
void mRTC::mClose()
    {
    this->iRtc->disableRTC();
    this->iRtc->resetAlarm();
    }

void mRTC::mSetup()
    {
//Noting to do
    }

/**
 * Lecture de la date. Tout les nombres sont entiers
 * *aYear : Année sur 16bits
 * *aMonth: Mois de l'année sur 8bits
 * *aDay : Jour du mois sur 8bits
 * *aDayOfWeek : jour de la semaine sur 8bits
 */
void mRTC::readDate(int *aYear, char *aMonth, char *aDay, char *aDayOfWeek)
    {
    this->iRtc->readDate(aYear, aMonth, aDay, aDayOfWeek);
    }

/**
 * Lecture de l'heure
 * Peut prendre une seconde ! On doit attendre le moment que l'heure soit valide...
 * *aHour : Heure sur 8bits
 * *aMin: Minutes sur 8bits
 * *aSecond : Secondes sur 8bits
 */
void mRTC::readTime(char *aHour, char *aMinute, char *aSecond)
    {
    this->iRtc->readTime(aHour, aMinute, aSecond);
    }

/**
 * Configuration de la date. Tout les nombres sont entiers
 * aYear : Année sur 16bits
 * aMonth: Mois de l'année sur 8bits
 * aDay : Jour du mois sur 8bits
 * aDayOfWeek : jour de la semaine sur 8bits
 */
void mRTC::setDate(int aYear, char aMonth, char aDay, char aDayOfWeek)
    {
    this->iRtc->setDate(aYear, aMonth, aDay, aDayOfWeek);
    }

/**
 * Configuration de l'heure
 * Peut prendre une seconde ! On doit attendre le moment que l'heure soit valide...
 * aHour : Heure sur 8bits
 * aMinute: Minutes sur 8bits
 * aSecond : Secondes sur 8bits
 */
void mRTC::setHour(char aHour, char aMinute, char aSecond)
    {
    this->iRtc->setHour(aHour, aMinute, aSecond);
    }

/**
 * Activation du reveil du micro tout les xx minutes
 * aMin : heure (min) de l'alarme
 */
void mRTC::setAlarm(char aHour,char aMinute) {
	this->iRtc->setAlarm(aHour,aMinute);
}

/**
 * Calibration de la RTC.
 * Principe : voir datasheet de la famille MSP430F55XX (UserGuide)
 *
 * Compensation en fonction de la température
 */
void mRTC::calibration(int aTemperature)
    {
    this->iRtc->calibration(aTemperature);
    }
