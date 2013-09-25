/** *****************************************************************************
 *
 * @file    test_mem.h
 * @date    07-11-2012
 * @author  Maxime Philippe
 * @brief   XLoader
 *
 *******************************************************************************
 */


#define OK    0
#define ERROR -1

#define DEBUG_MSG(...)
#define DEBUG_INFO(...)

#define TEST_DDR_WITH_ECC       1
#define TEST_DDR_WITHOUT_ECC    0

void pWriteFunc(unsigned address, int nbByte, void *ptrToData);
void pReadFunc(unsigned address, int nbByte, void *ptrToData);

int memDataBusWalking (
        unsigned  addrToTest,		    /**< memory location used for test*/
        unsigned char busNbBit)         /**< data bus size in bits */
;
int memAddrBusWalking (
		unsigned startAdrs,				/**< base address of tested memory*/
        unsigned char busNbBit,			/**< address bus size in bits */
        unsigned char accessNbByte)     /**< access size in bytes */
;
int memoryTest (
		unsigned startAddr,				/**< memory start address used for test*/
        unsigned int  memNbBytes,       /**< size of the tested memory (number of bytes)*/
        unsigned char DataNbBit)        /**< data bus size in bits */
;
int memAddrMarchX (
		unsigned startAdrs,		/**< base address of tested memory*/
        unsigned long size)     /**< size of the tested memory (number of bytes)*/
;
