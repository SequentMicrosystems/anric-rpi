#include "analog.h"
#include "board.h"
#include "calib.h"
#include "cli.h"
#include "comm.h"
#include "help.h"
#include "relay.h"
#include "mosfet.h"


const CliCmdType *gCmdArray[] = {
	&CMD_HELP,
	&CMD_VERSION,
	&CMD_BOARD,
	&CMD_CAL_STATUS,
	&CMD_UIN_READ,
	&CMD_UIN_CAL,
	&CMD_UOUT_READ,
	&CMD_UOUT_WRITE,
	&CMD_UOUT_CAL,
	&CMD_RELAY_READ,
	&CMD_RELAY_WRITE,
	&CMD_MOSFET_READ,
	&CMD_MOSFET_WRITE,
	&CMD_PWM_READ,
	&CMD_PWM_WRITE,
	&CMD_FREQ_READ,
	&CMD_FREQ_WRITE,
	0
};
