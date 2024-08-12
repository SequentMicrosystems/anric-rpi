#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "comm.h"
#include "data.h"
#include "mosfet.h"
#include "analog.h"

bool badPwmCh(int ch)
{
	if (! (MIN_CH_NO <= ch && ch <= MOSFET_CH_NO))
	{
		printf("Mosfet channel out of range![%d..%d]\n", MIN_CH_NO, MOSFET_CH_NO);
		return true;
	}
	return false;
}

const CliCmdType CMD_MOSFET_READ =
{
	"mosrd",
	2,
	&doMosfetRead,
	"  mosrd            Read mosay state\n",
	"  Usage 1:         "PROGRAM_NAME" <id> mosrd <channel[1.."STR(MOSFET_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> mosrd\n",
	"  Example:         "PROGRAM_NAME" 0 mosrd 2  Get the state of mosay #2 on board #0\n"
};
int doMosfetRead(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 3)
	{
		uint8_t buf[2];
		uint16_t mosVal = 0;
		if (OK != i2cMem8Read(dev, I2C_MEM_MOS_DIG_REG1, buf, 2))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		memcpy(&mosVal, buf, 2);
		for (int mos = 1; mos <= MOSFET_CH_NO; ++mos)
		{
			if (mosVal & (1 << (mos - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 4)
	{
		uint8_t buf[2];
		uint16_t mosVal = 0;
		if (OK != i2cMem8Read(dev, I2C_MEM_MOS_DIG_REG1, buf, 2))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
		memcpy(&mosVal, buf, 2);
		int mos = atoi(argv[3]);
		if (! (1 <= mos && mos <= MOSFET_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERROR;
		}
		if (mosVal & (1 << (mos - 1)))
		{
			printf("1\n"); /* mos ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_MOSFET_WRITE =
{
	"moswr",
	2,
	&doMosfetWrite,
	"  moswr            Change mosfet state\n",
	"  Usage 1:         "PROGRAM_NAME" <id> moswr <channel[1.."STR(MOSFET_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> moswr <mask[0.."STR(MASK(MOSFET_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" 0 moswr 2 1  Set the state of mosay #2 to ON\n"
	"channel #2 on board #1 to enable\n"
};
int doMosfetWrite(int argc, char *argv[])
{
	if (! (argc == 4 || argc == 5))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 4)
	{
		int state = 0;
		state = atoi(argv[3]);
		if (! (0 <= state && state <= (1 << MOSFET_CH_NO) - 1))
		{
			return ARG_RANGE_ERROR;
		}
		uint8_t buf[2];
		uint16_t mosVal = 0;
		mosVal = 0xfff & state;
		memcpy(buf, &mosVal, 2);
		if (OK != i2cMem8Write(dev, I2C_MEM_MOS_DIG_REG1, buf, 2))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else if (argc == 5)
	{
		int state = 0;
		int mos = atoi(argv[3]);
		if (! (1 <= mos && mos <= MOSFET_CH_NO))
		{
			printf("Mosfet number out of range");
			return ARG_RANGE_ERROR;
		}
		state = atoi(argv[4]);
		uint8_t buf[2];
		uint16_t mosVal = 0;
		if (OK != i2cMem8Read(dev, I2C_MEM_MOS_DIG_REG1, buf, 2))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		memcpy(&mosVal, buf, 2);

		if (state > 0)
		{
			mosVal |= 1 << (mos - 1);

		}
		else
		{
			mosVal &= ~ (1 << (mos - 1));
		}
		memcpy(buf, &mosVal, 2);
		if (OK != i2cMem8Write(dev, I2C_MEM_MOS_DIG_REG1, buf, 2))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	return OK ;
}

const CliCmdType CMD_PWM_READ =
{/*{{{*/
	"pwmrd",
	2,
	&doPwmRead,
	"  pwmrd            Read Mosfet pwm value(%)\n",
	"  Usage:           "PROGRAM_NAME" <id> pwmrd <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 pwmrd 2 #Read pwm output on mosfet channel #2 on board #0\n",
};
int doPwmRead(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if (dev < 0)
	{
		return ERROR ;
	}
	int ch = atoi(argv[3]);
	if (badPwmCh(ch))
	{
		return ARG_RANGE_ERROR;
	}
	float val = 0;
	if (OK != val16Get(dev, I2C_MEM_PWM1, ch, 10, &val))
	{
		return ERROR ;
	}
	printf("%0.1f\n", val);
	return OK ;
}/*}}}*/
const CliCmdType CMD_PWM_WRITE =
{/*{{{*/
	"pwmwr",
	2,
	&doPwmWrite,
	"  pwmwr            Write Mosfet output pwm fill factor value(%)\n",
	"  Usage:           "PROGRAM_NAME" <id> pwmwr <channel> <value(%)>\n",
	"  Example:         "PROGRAM_NAME" 0 pwmwr 2 25 #Write 25% mosfet pwm channel #2 on board #0\n",
};
int doPwmWrite(int argc, char *argv[])
{
	if (argc != 5)
	{
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if (dev < 0)
	{
		return ERROR ;
	}
	int ch = atoi(argv[3]);
	if (badPwmCh(ch))
	{
		return ARG_RANGE_ERROR;
	}
	float val = atof(argv[4]);
	if (! (0 <= val && val <= 100))
	{
		printf("Invalid PWM, must be 0..100\n");
		return ARG_RANGE_ERROR;
	}
	if (OK != val16Set(dev, I2C_MEM_PWM1, ch, 10, val))
	{
		return ERROR ;
	}
	return OK ;
}/*}}}*/

const CliCmdType CMD_FREQ_READ =
{/*{{{*/
	"frd",
	2,
	&doFreqRead,
	"  frd              Read Mosfet pwm frequency(Hz)\n",
	"  Usage:           "PROGRAM_NAME" <id> frd \n",
	"  Example:         "PROGRAM_NAME" 0 frd #Read pwm output frequency on board #0\n",
};
int doFreqRead(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if (dev < 0)
	{
		return ERROR ;
	}

	uint8_t buf[2];
	uint16_t freqVal = 0;
	if (OK != i2cMem8Read(dev, I2C_PWM_FREQ, buf, 2))
	{
		printf("Fail to read!\n");
		return ERROR ;
	}
	memcpy(&freqVal, buf, 2);
	printf("%d\n", (int)freqVal);
	return OK ;
}/*}}}*/


const CliCmdType CMD_FREQ_WRITE =
{/*{{{*/
	"fwr",
	2,
	&doFreqWrite,
	"  fwr              Write Mosfet output pwm frequency(Hz)\n",
	"  Usage:           "PROGRAM_NAME" <id> fwr <value(Hz)>\n",
	"  Example:         "PROGRAM_NAME" 0 pwmwr 25 #Set pwm frequency to 25Hz on board #0\n",
};
int doFreqWrite(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if (dev < 0)
	{
		return ERROR ;
	}

	int val = atoi(argv[3]);
	if (! (TIM_PWM_MIN_FREQ <= val && val <= TIM_PWM_MAX_FREQ))
	{
		printf("Invalid frequency, must be %d..%d Hz\n", (int)TIM_PWM_MIN_FREQ, (int)TIM_PWM_MAX_FREQ);
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[2];
	uint16_t freqVal = 0;
	freqVal = (uint16_t)val;
	memcpy(buf, &freqVal, 2);
	if (OK != i2cMem8Write(dev, I2C_PWM_FREQ, buf, 2))
	{
		printf("Fail to write!\n");
		return ERROR ;
	}
	return OK ;
}/*}}}*/

