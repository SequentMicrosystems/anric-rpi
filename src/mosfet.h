#ifndef __MOSFET_H__
#define __MOSFET_H__
#include "cli.h"

extern const CliCmdType CMD_MOSFET_READ;
extern const CliCmdType CMD_MOSFET_WRITE;
extern const CliCmdType CMD_PWM_READ;
extern const CliCmdType CMD_PWM_WRITE;
extern const CliCmdType CMD_FREQ_WRITE;
extern const CliCmdType CMD_FREQ_READ;


int doMosfetRead(int argc, char *argv[]);
int doMosfetWrite(int argc, char *argv[]);
int doPwmRead(int argc, char *argv[]);
int doPwmWrite(int argc, char *argv[]);
int doFreqRead(int argc, char *argv[]);
int doFreqWrite(int argc, char *argv[]);

#endif
