/** *****************************************************************************
 *
 * @file    test_mem.c
 * @date    07-11-2012
 * @author  Maxime Philippe - non schneider
 * @brief   XLoader basic memory test
 *
 *******************************************************************************/


#include "common.h"
#include "test_mem.h"
//#define DEBUG_TEST_MEM

/* *****************************************************************************
 *
 * test memory
 *
 * Warning : for startAddr parameter, address can be absolute or relative
 * (it depends on driver used for read and write commands)
 *
 *******************************************************************************/
void pReadFunc(unsigned address, int nbByte, void *ptrToData)
{
	if     (nbByte == 8) *(unsigned long*) (ptrToData) = *(volatile unsigned long*) (address);
	else if(nbByte == 4) *(unsigned*)      (ptrToData) = *(volatile unsigned*)      (address);
	else if(nbByte == 2) *(unsigned short*)(ptrToData) = *(volatile unsigned short*)(address);
	else if(nbByte == 1) *(unsigned char*) (ptrToData) = *(volatile unsigned char*) (address);
}
void pWriteFunc(unsigned address, int nbByte, void *ptrToData)
{
	if     (nbByte == 8) *(volatile unsigned long*) (address) = *(unsigned long*) (ptrToData);
	else if(nbByte == 4) *(volatile unsigned*)      (address) = *(unsigned*)      (ptrToData);
	else if(nbByte == 2) *(volatile unsigned short*)(address) = *(unsigned short*)(ptrToData);
	else if(nbByte == 1) *(volatile unsigned char*) (address) = *(unsigned char*) (ptrToData);
}

int memoryTest (
		unsigned startAddr,				/**< memory start address used for test*/
		unsigned int  memNbBytes,       /**< size of the tested memory (number of bytes)*/
		unsigned char DataNbBit)        /**< data bus size in bits */
{
	int valRet = OK;
	unsigned char AddrNbBit;		/**< address bus size in bits */

	/* Test walking bus on data bus */

	if (memDataBusWalking (
			startAddr,		/**< memory location used for test*/
			DataNbBit)      /**< data bus size in bits */
	)
	{
#ifdef CONFIG_RAM_TEST_VERBOSE
		uartDebug_Puts("\nMemAddrBusWalking FAIL\r\n");
#endif
		valRet = ERROR;
	}
#ifdef DEBUG_TEST_MEM
	else
	{
		uartDebug_Puts("\nMemDataBusWalking OK\r\n");
	}
#endif

	/* Test walking bus on address bus */
	AddrNbBit = 0;
	while (memNbBytes >> (AddrNbBit + 1))
	{
		AddrNbBit++; /* Compute address bus size (number of bits) */
	}
	if (memAddrBusWalking(
			startAddr,		/**< memory location used for test*/
			AddrNbBit,      /**< address bus size in bits */
			1)              /**< access size in bytes */
	)
	{
		valRet = ERROR;
#ifdef CONFIG_RAM_TEST_VERBOSE
		uartDebug_Puts("\nMemAddrBusWalking FAIL\r\n");
#endif
	}
#ifdef DEBUG_TEST_MEM
	else
	{
		uartDebug_Puts("\nMemAddrBusWalking OK\r\n");
	}
#endif
#if 0
	/* Test memory cells */
	uartDebug_Puts("3\r\n");
	if (memAddrMarchX(
			startAddr,		/**< base address of tested memory*/
			memNbBytes)     /**< size of the tested memory (number of bytes)*/
	)
	{
		uartDebug_Puts("X\r\n");
		valRet = ERROR;
	}
	else
	{
		uartDebug_Puts("4\r\n");
	}
#endif
	return valRet;
}

/* *****************************************************************************
 *
 * @brief	Test data memory bus
 *
 * Write and read walking bits pattern to a single memory location :
 *  - first step  : walk a 1 bit among zeroes
 *  - second step : walk a 0 bit among ones
 *
 * @return  OK (0) or ERROR (1)
 *
 *******************************************************************************
 */
int memDataBusWalking (
		unsigned addrToTest,		/**< memory location used for test*/
		unsigned char busNbBit)		/**< data bus size in bits */
{

	int valRet = OK;
	unsigned char step;     /* 0 : walk a 1 among 0, 1 : walk a 0 among 1 */
	unsigned char index;    /* walking bit position */
	unsigned char nbBytes;  /* access size in bytes */
	unsigned int pattern;   /* reference value to write */
	unsigned int valTemp;   /* read value to compare */

	if (busNbBit > 32)
	{
		valRet = ERROR;
	}

	/* compute access size in bytes */
	nbBytes = busNbBit >> 3; /* divide by 8 */
	if (busNbBit & 0x7) /* remainder of the division */
	{
		nbBytes++;
	}

	/* test walking bit on data bus */
	for (step = 0; step < 2; step++) /* 0 : walk a 1 among 0, 1 : 0 among 1 */
	{
		for (index = 0; index < busNbBit; index++) /* walking bit position */
		{
			pattern = 0x1 << index; /* walk a 1 bit among zeroes */

			if (step) /* 1 : walk a 0 among ones */
			{
				pattern = ~pattern;
				pattern &= (0x1 << busNbBit) - 1; /* mask MSB (not used) */
			}

			/* Write test pattern */
			pWriteFunc( addrToTest,	/**< address to write */
						nbBytes,	/**< number of bytes to write */
						&pattern	/**< pointer to data to write */
						);

			/* Read back test pattern */
			pReadFunc (	addrToTest,	/**< address to read */
						nbBytes,	/**< number of bytes to read */
						&valTemp	/**< pointer to data to read */
						);

			/* Verify test pattern */
			valTemp &= (0x1 << busNbBit) - 1; /* mask MSB (not used) */
			if (valTemp != pattern) {
				valRet = ERROR;
#ifdef CONFIG_RAM_TEST_VERBOSE
				uartDebug_Puts("memDataBusWalking ERR @");
				uartDebug_Puthex((unsigned int)addrToTest);
				uartDebug_Puts(" ");
				uartDebug_Puthex((unsigned int)valTemp);
				uartDebug_Puts(" != ");
				uartDebug_Puthex((unsigned int)pattern);
				uartDebug_Puts("expected\r\n");
#endif
			}
			else
			{
#ifdef DEBUG_TEST_MEM
				uartDebug_Puts("memDataBusWalking SUCCESS @ addr=");
				uartDebug_Puthex((unsigned int)addrToTest);
				uartDebug_Puts("data=");
				uartDebug_Puthex((unsigned int)valTemp);
				uartDebug_Puts("\r\n");
#endif
			}
		}
	}

	return valRet;

}

/* *****************************************************************************
 *
 * @brief	Test address memory bus
 *
 * Write and read with walking bits pattern on address bus :
 *  - first step  : walk a 1 bit among zeroes
 *  - second step : walk a 0 bit among ones
 *
 * @return  OK (0) or ERROR (1)
 *
 *******************************************************************************
 */
int memAddrBusWalking (
		unsigned startAdrs,				/**< base address of tested memory*/
		unsigned char busNbBit,			/**< address bus size in bits */
		unsigned char accessNbByte)		/**< access size in bytes */
{

	int valRet = OK;
	unsigned char addr_step;   /* 0 : walk a 1 among zeros, 1 : walk a 0 among ones */
	unsigned char data_step;   /* 0 : data = index, 1 : data = ~index */
	unsigned char index;       /* walking bit position */
	unsigned char data;        /* data to write */
	unsigned int pattern;      /* reference value to write */
	unsigned int valTemp;      /* read value to compare */

	if (busNbBit > 32)
	{
		valRet = ERROR;
	}

	/* test walking bit on addr bus */
	for (addr_step = 0; addr_step < 2; addr_step++) /* 0 : walk a 1 among 0, 1 : 0 among 1 */
	{
	    for (data_step = 0; data_step < 2; data_step++) /* 0 : data = index, 1 : data = ~index */
	    {
	        for (index = 0; index <= busNbBit; index++) /* walking bit position */
	        {
                if (index == busNbBit) {
                    pattern = 0; /* to cover limit */
                } else {
                    pattern = 0x1 << index; /* walk a 1 bit among zeroes */
                }

	            if (addr_step) /* 1 : walk a 0 among ones */
	            {
	                pattern = ~pattern;
	                pattern &= (0x1 << busNbBit) - 1; /* mask MSB (not used) */
	            }

                if (data_step) /* 1 : data = ~index */
                {
                    data = ~index;
                }
                else /* 0 : data = index */
                {
                    data = index;
                }

	            /* Write test pattern */
	            pWriteFunc( startAdrs + pattern,/**< address to write */
	                        accessNbByte,       /**< number of bytes to write */
	                        &data               /**< pointer to data to write */
	                        );
	        }
	        for (index = 0; index < busNbBit; index++) /* walking bit position */
	        {
	            pattern = 0x1 << index; /* walk a 1 bit among zeroes */

	            if (addr_step) /* 1 : walk a 0 among ones */
	            {
	                pattern = ~pattern;
	                pattern &= (0x1 << busNbBit) - 1; /* mask MSB (not used) */
	            }

                if (data_step) /* 1 : data = ~index */
                {
                    data = ~index;
                }
                else /* 0 : data = index */
                {
                    data = index;
                }

	            /* Read back test pattern */
	            pReadFunc ( startAdrs + pattern,/**< address to read */
	                        accessNbByte,       /**< number of bytes to read */
	                        &valTemp            /**< pointer to data to read */
	                        );

	            /* Verify test pattern */
	            valTemp &= ((0x1 << (accessNbByte * 8)) - 1); /* mask MSB (not used) */
	            if (valTemp != data) {
	            	valRet = ERROR;
#ifdef CONFIG_RAM_TEST_VERBOSE
					uartDebug_Puts("memAddrBusWalking ERR @");
					uartDebug_Puthex((unsigned int)(startAdrs + pattern));
					uartDebug_Puts(" ");
					uartDebug_Puthex((unsigned int)valTemp);
					uartDebug_Puts(" != ");
					uartDebug_Puthex((unsigned int)data);
					uartDebug_Puts("expected\r\n");
#endif
				}
	            else
	            {
#ifdef DEBUG_TEST_MEM
	            	uartDebug_Puts("memAddrBusWalking SUCCESS @ addr=");
	            	uartDebug_Puthex((unsigned int)(startAdrs + pattern));
	            	uartDebug_Puts("data=");
	            	uartDebug_Puthex((unsigned int)valTemp);
	            	uartDebug_Puts("\r\n");
#endif
	            }
	        }
	    }
	}

	return valRet;

}
#if  0
/* *****************************************************************************
 *
 * @brief	Test for address memory bus
 *
 * Use March X algorithm :
 *  - 1. All the memory is filled with zeros in the ascending order.
 *  - 2. In the ascending order, these zeros are read and ones are written
 *  - 3. In descending order, these ones are read and zeros are written
 *  - 4. In ascending order, the zeros are read.
 *
 * @return  OK (0) or ERROR (1)
 *
 *******************************************************************************
 */

int memAddrMarchX (
		unsigned startAdrs,		/**< base address of tested memory*/
		unsigned long size)		/**< size of the tested memory (number of bytes)*/
{
	int access_size = 8;
	int valRet = OK;
	const unsigned long pattern_0x00 = 0x00;
	const unsigned long pattern_0xff = ((1<<(access_size*8))-1);
	unsigned long pattern;
	unsigned long valTemp;
	unsigned currentAdrs;
	unsigned endAdrs;

	endAdrs = startAdrs + (size - access_size);

	/* 1. All the memory is filled with zeros in the ascending order */
	uartDebug_Puts("a\r\n");
	/* TODO: enable cache */
	pattern = pattern_0x00;

	for (currentAdrs = startAdrs; currentAdrs <= endAdrs; currentAdrs=currentAdrs+access_size)
	{
		/* Write test pattern */
		pWriteFunc( currentAdrs,	     /**< address to write */
				access_size,	     /**< number of bytes to write */
				(void *)&pattern	 /**< pointer to data to write */
		);
	}
	/* TODO: flush cache */
	/* TODO: disable cache */

	/* 2. In the ascending order, these zeros are read and ones are written */
	uartDebug_Puts("b\r\n");
	pattern = pattern_0xff;

	for (currentAdrs = startAdrs; currentAdrs <= endAdrs; currentAdrs=currentAdrs+access_size)
	{
		/* Read back test pattern */
		pReadFunc (	currentAdrs,     /**< address to read */
				access_size,         /**< number of bytes to write */
				(void *)&valTemp     /**< pointer to data to read */
		);

		/* Verify test pattern */
		if (valTemp != pattern_0x00)
		{
			uartDebug_Puts("er\r\n");
			valRet = ERROR;
		}

		/* Write test pattern */
		pWriteFunc( currentAdrs,     /**< address to write */
				access_size,	     /**< number of bytes to write */
				(void *)&pattern	 /**< pointer to data to write */
		);
	}

	/* 3. In descending order, these ones are read and zeros are written */
	uartDebug_Puts("c\r\n");
	pattern = pattern_0x00;
	for (currentAdrs = endAdrs;
			(currentAdrs >= startAdrs) && (currentAdrs <= endAdrs);
			currentAdrs=currentAdrs-access_size)
	{
		/* Read back test pattern */
		pReadFunc (	currentAdrs,     /**< address to read */
				access_size,         /**< number of bytes to write */
				(void *)&valTemp     /**< pointer to data to read */
		);

		/* Verify test pattern */
		if (valTemp != pattern_0xff)
		{
			uartDebug_Puts("er\r\n");
			valRet = ERROR;
			break;
		}

		/* Write test pattern */
		pWriteFunc( currentAdrs,     /**< address to write */
				access_size,	     /**< number of bytes to write */
				(void *)&pattern	 /**< pointer to data to write */
		);
	}
	/* 4. In ascending order, the zeros are read. */
	uartDebug_Puts("d\r\n");
	/* TODO: enable cache */
	for (currentAdrs = startAdrs; currentAdrs <= endAdrs; currentAdrs=currentAdrs+access_size)
	{
		/* Read back test pattern */
		pReadFunc (	currentAdrs,     /**< address to read */
				access_size,         /**< number of bytes to write */
				(void *)&valTemp     /**< pointer to data to read */
		);

		/* Verify test pattern */
		if (valTemp != pattern_0x00)
		{
			uartDebug_Puts("er\r\n");
			valRet = ERROR;
			break;
		}
	}
	/* TODO: flush cache */
	/* TODO: disable cache */

	return valRet;
}
#endif

void printTestMemFail(void) {
#ifdef CONFIG_RAM_TEST_VERBOSE
	uartDebug_Puts ("# Error : fail on memoryTest\r\n");
#endif
}

int test_ddr(int test_with_ecc)
{
#ifndef CONFIG_SPEAR_USBTTY
	if (test_with_ecc == TEST_DDR_WITHOUT_ECC)
	{
		/* ddr memory test */
		uartDebug_Puts("2\r\n");

#ifdef DEBUG_TEST_MEM
		uartDebug_Puts("\n mem: ");
		uartDebug_Putdec(get_expected_mem_size());
		uartDebug_Puts("\r\n");
#endif
		/* test ddr */
#ifdef CONFIG_SPEAR1380_REVC
		if (memoryTest(
				0x0,
				(unsigned int)get_expected_mem_size(),
				16) != 0)
		{
			printTestMemFail();
			hang();
		}
#endif
#ifdef CONFIG_SPEAR320_MDI
		//	uartDebug_Putdec((unsigned)get_expected_mem_size());
		//	uartDebug_Puts("\n");

		if (memoryTest(
				0x0,
				(unsigned int)get_expected_mem_size(),
				16) != 0)
		{
			printTestMemFail();
			hang();
		}

#endif
		uartDebug_Puts("3\r\n");
	} else {
#ifdef CONFIG_SPEAR1380_REVC
		int erreur = 0;
		/* Call ddr test function */
		if (memoryTest(
				0x0,
				(unsigned int)get_expected_mem_size(),
				16) != 0)
		{
			printTestMemFail();
	    	erreur++;
		}
	    /* check ECC in MPMC configuration registers */
	    if ((*( (volatile unsigned long *)(MPMC_CTRL_REG_26) ) >> MPMC_26_ECC_STS_SHIFT) & MPMC_26_ECC_STS_MSK)
	    {
	    	uartDebug_Puts ("# Error : double bit uncorrectable ECC event occurred on the read data\r\n");
	    	erreur++;
	    }
	    if ((*( (volatile unsigned long *)(MPMC_CTRL_REG_105) ) >> MPMC_105_ECC_STS_SHIFT) & MPMC_105_ECC_STS_MSK)
	    {
	    	uartDebug_Puts ("# Error : ECC event occurred\r\n");
	    	erreur++;
	    }

	    if (erreur == 0)
	    {
	    	uartDebug_Puts("a\r\n");
	    } else {
	    	hang();
	    }
#endif
#ifdef CONFIG_SPEAR320_MDI
//    	uartDebug_Puts ("# Error : ECC not available on MDI\r\n");
    	hang();
#endif
	}
#endif // CONFIG_SPEAR_USBTTY
	return 1;
}
