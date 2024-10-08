#include <stdio.h>
#include <stdlib.h>

#include "comm.h"
#include "data.h"
#include "relay.h"

const CliCmdType CMD_RELAY_READ = {
	"relrd",
        2,
        &doRelayRead,
        "  relrd            Read relay state\n",
        "  Usage 1:         "PROGRAM_NAME" <id> relrd <channel[1.."STR(RELAY_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" <id> relrd\n",
        "  Example:         "PROGRAM_NAME" 0 relrd 2  Get the state of relay #2 on board #0\n"
};
int doRelayRead(int argc, char *argv[]) {
        if(!(argc == 3 || argc == 4)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 3) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_RELAYS, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= RELAY_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 4) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_RELAYS, buf, 1)) {
			printf("Fail to write!\n");
			return ERROR;
		}
		int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= RELAY_CH_NO)) {
			printf("Led number out of range");
                        return ARG_RANGE_ERROR;
                }
		if(buf[0] & (1 << (rel - 1))) {
			printf("1\n"); /* rel ON */
		} else {
			printf("0\n");
		}
        }
        return OK;
} 

const CliCmdType CMD_RELAY_WRITE = {
	"relwr",
        2,
        &doRelayWrite,
        "  relwr            Change relay state\n",
        "  Usage 1:         "PROGRAM_NAME" <id> relwr <channel[1.."STR(RELAY_CH_NO)"]> <state(0/1)>\n"
        "  Usage 2:         "PROGRAM_NAME" <id> relwr <mask[0.."STR(MASK(RELAY_CH_NO))"]>\n",
        "  Example:         "PROGRAM_NAME" 0 relwr 2 1  Set the state of relay #2 to ON\n"
		            "channel #2 on board #1 to enable\n"
};
int doRelayWrite(int argc, char *argv[]) {
        if(!(argc == 4 || argc == 5)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 4) {
                int state = 0;
                state = atoi(argv[3]);
                if(!(0 <= state && state <= (1 << RELAY_CH_NO) - 1)) {
                        return ARG_RANGE_ERROR;
                }
                uint8_t buf[1];
                buf[0] = 0xff & state;
                if(OK != i2cMem8Write(dev, I2C_MEM_RELAYS, buf, 1)) {
                        printf("Fail to write!\n");
                        return ERROR;
                }
        }
        else if(argc == 5) {
                int state = 0;
                int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= RELAY_CH_NO)) {
			printf("Relay number out of range");
                        return ARG_RANGE_ERROR;
                }
                state = atoi(argv[4]);
                uint8_t buf[1];
                buf[0] = 0xff & rel;
                if(state > 0) {
                        if(OK != i2cMem8Write(dev, I2C_MEM_RELAY_SET, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
                else {
                        if(OK != i2cMem8Write(dev, I2C_MEM_RELAY_CLR, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
        }
        return OK;
} 

