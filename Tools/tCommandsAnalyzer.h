/*
 * tCommandsAnalyzer.h
 *
 *  Created on: 30 août 2013
 *      Author: cyrille.savy
 */

#ifndef TCOMMANDSANALYZER_H_
#define TCOMMANDSANALYZER_H_

#include "tToolsCluster.h"

#define sizeMaxMode		3
#define sizeMaxMdp		21
#define sizeMaxCommand		21
#define sizeMaxParameter	21

typedef enum
    {
    kCommandNoCommand,
    kCommandDisconnect,
    kCommandConnect,
    kCommandError,
    kCommandMah,
    kCommandDispo,
    kCommandMode,
    kCommandOffset,
    kCommandAlarm,
    kCommandLimits,
    kCommandEtat,
    kCommandPassu,
    kCommandPassa,
    kCommandSimulate,
    kCommandReset,
    kCommandMonthlyconsumption,
    kCommandDailyconsumption,
    kCommandDysfunction,
    kCommandUnitName,
    kCommandPin,
    kCommandOwn
    } tCommandsEnum;

typedef enum
    {
    kEmpty,
    kPending,
    kModeOk,
    kPassWordOk,
    kCommandOk,
    kParametersOk,
    kComplete
    } tCommandsAnalyzerStateEnum;

typedef enum
    {
    kUser1,
    kUser2,
    kAdmin,
    kAdmin1,
    kAdmin2
    } tCommandsModeTypeEnum;

typedef enum
    {
    kDataUser1 = 1,
    kDataUser2 = 2
    } tCommandsUserNbEnum;

typedef struct
    {
    char theMode[sizeMaxMode];
    char theMdp[sizeMaxMdp];
    char theCommand[sizeMaxCommand];
    char theParameters[12][sizeMaxParameter];
    } tCommandBrut;

typedef struct
    {
    tCommandsEnum aCommandEnum;
    tCommandsModeTypeEnum aModeTypeEnum;
    tCommandsUserNbEnum aUserNb;
    UInt8 parametersNumber;
    } tCommandResult;

class tCommandsAnalyzer
    {
public:
    tCommandBrut aCommandBrut;
    tCommandResult aCommandResult;
    tCommandsAnalyzerStateEnum aStateEnum;

    tCommandsAnalyzer();

    void tCommandsAnalysis(char* aMessage, tToolsCluster* theTools);

    virtual ~tCommandsAnalyzer();

private:
    int maxSizesCommands[4];

    void tCommandsParser(char* aMessage);

    void tModeAnalyzer();

    void tPasswordAnalyzer(tToolsCluster* theTools);

    void tCommandAnalyzer();

    void tParametersAnalyzer();
    };

#endif /* TCOMMANDSANALYZER_H_ */
