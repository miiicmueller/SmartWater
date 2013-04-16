#ifndef T_MEASURES_STATEMENT_H
#define T_MEASURES_STATEMENT_H

#include <string>
#include <assert.h>

class tMeasuresStatement
{
private:
	int MonthlyConsumption[12];

	int CurrentMonthConsumption[31];

	int addressEEPROM;

	int nBytes;


private:
	void save();

public:
	void getMonthlyConsumption();

	void getCurrentMonthComsumption();

	void setMonthlyConsumption();

	void setCurrentMonthComsumption();

	void load();

};
#endif
