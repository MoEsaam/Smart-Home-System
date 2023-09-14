#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TWI_interface.h"
#include "RTC_interface.h"

void RTC_voidInitialization(void)
{
	/* INITIALIZE TWI MODULE AS A MASTER */
    TWI_voidMasterInitialization();

    /* TRANSMIT START COMMUNICATION */
    TWI_SendStartCondition();

    /* CONNECT TO RTC MODULE BY SENDING IT'S ID THE BUS */
    TWI_SendSlaveAddressWithWrite(RTC_WriteMode);        // Connect to DS1307 by sending its ID on I2c Bus
    TWI_MasterWriteDataByte(RTC_ControlRegAddress);// Select the Ds1307 ControlRegister to configure Ds1307

    TWI_MasterWriteDataByte(0x00);                        // Write 0x00 to Control register to disable SQW-Out

	TWI_SendStopCondition();                             // Stop I2C communication after initializing DS1307
}
void RTC_SetDateTime(E_RTC *rtc)
{
	TWI_SendStartCondition();                          // Start I2C communication

    TWI_SendSlaveAddressWithWrite(RTC_WriteMode);      // connect to DS1307 by sending its ID on I2c Bus
    TWI_MasterWriteDataByte(RTC_SecondRegAddress); // Request sec RAM address at 00H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Second/10)<<4) + (rtc->RTC_u8Second%10));                    // Write sec from RAM address 00H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Minute/10)<<4) + (rtc->RTC_u8Minute%10));                    // Write min from RAM address 01H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Hour/10)<<4) + (rtc->RTC_u8Hour%10));              // Write hour from RAM address 02H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Weekday/10)<<4) + (rtc->RTC_u8Weekday%10));                // Write weekDay on RAM address 03H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Date/10)<<4) + (rtc->RTC_u8Date%10)) ;                   // Write date on RAM address 04H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Month/10)<<4) + (rtc->RTC_u8Month%10));                    // Write month on RAM address 05H
    TWI_MasterWriteDataByte(((rtc->RTC_u8Year/10)<<4) + (rtc->RTC_u8Year%10));             // Write year on RAM address 06h

    TWI_SendStopCondition();                              // Stop I2C communication after Setting the Date
}
void RTC_GetDateTime(E_RTC *rtc)
{
	TWI_SendStartCondition();                            // Start I2C communication

	TWI_SendSlaveAddressWithWrite(RTC_WriteMode);        // connect to DS1307 by sending its ID on I2c Bus
	TWI_MasterWriteDataByte(RTC_SecondRegAddress); // Request Sec RAM address at 00H

	TWI_SendStopCondition();                                // Stop I2C communication after selecting Sec Register

	TWI_SendStartCondition();                            // Start I2C communication
	TWI_SendSlaveAddressWithRead(RTC_WriteMode);            // connect to DS1307(Read mode) by sending its ID

    rtc->RTC_u8Second = TWI_MasterReadDataByte_ACK();// read second and return Positive ACK
    rtc->RTC_u8Minute = TWI_MasterReadDataByte_ACK();                 // read minute and return Positive ACK
    rtc->RTC_u8Hour= TWI_MasterReadDataByte_ACK();               // read hour and return Negative/No ACK
    rtc->RTC_u8Weekday = TWI_MasterReadDataByte_ACK();           // read weekDay and return Positive ACK
    rtc->RTC_u8Date= TWI_MasterReadDataByte_ACK();              // read Date and return Positive ACK
    rtc->RTC_u8Month=TWI_MasterReadDataByte_ACK();            // read Month and return Positive ACK
    rtc->RTC_u8Year =TWI_MasterReadDataByte_NACK();             // read Year and return Negative/No ACK
    TWI_SendStopCondition();         // Stop I2C communication after reading the Date
    rtc->RTC_u8Second=((rtc->RTC_u8Second& 0xF0) >> 4)*10 + (rtc->RTC_u8Second& 0x0F);
    rtc->RTC_u8Minute=((rtc->RTC_u8Minute& 0xF0) >> 4)*10 + (rtc->RTC_u8Minute& 0x0F);
    rtc->RTC_u8Hour=((rtc->RTC_u8Hour& 0xF0) >> 4)*10 + (rtc->RTC_u8Hour& 0x0F);
    rtc->RTC_u8Weekday=((rtc->RTC_u8Weekday& 0xF0) >> 4)*10 + (rtc->RTC_u8Weekday& 0x0F);
    rtc->RTC_u8Date=((rtc->RTC_u8Date& 0xF0) >> 4)*10 + (rtc->RTC_u8Date& 0x0F);
    rtc->RTC_u8Month=((rtc->RTC_u8Month& 0xF0) >> 4)*10 + (rtc->RTC_u8Month& 0x0F);
    rtc->RTC_u8Year=((rtc->RTC_u8Year& 0xF0) >> 4)*10 + (rtc->RTC_u8Year& 0x0F);

}
