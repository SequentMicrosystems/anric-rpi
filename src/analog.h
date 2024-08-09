#ifndef ANALOG_H
#define ANALOG_H

#include "cli.h"

extern const CliCmdType CMD_UIN_READ;
extern const CliCmdType CMD_UOUT_READ;
extern const CliCmdType CMD_UOUT_WRITE;

extern const CliCmdType CMD_UIN_CAL;
extern const CliCmdType CMD_UIN_CAL_RESET;

extern const CliCmdType CMD_UOUT_CAL;
extern const CliCmdType CMD_UOUT_CAL_RESET;

int val16Get(int dev, int baseAddr, int ch, float scale, float* val);
int val16Set(int dev, int baseAddr, int ch, float scale, float val);
int doUInRead(int argc, char *argv[]);
int doUOutRead(int argc, char *argv[]);
int doUOutWrite(int argc, char *argv[]);

int doUInCal(int argc, char *argv[]);
int doUInCalReset(int argc, char *argv[]);

int doUOutCal(int argc, char *argv[]);
int doUOutCalReset(int argc, char *argv[]);


#endif /* ANALOG_H */

// vi:fdm=marker
