/*
 * eeprom_common.c
 *
 *  Created on: Aug. 8, 2021
 *      Author: giacomo892
 */
#include <string.h>
#include "eeprom_common.h"
#include "eeprom.h"

eeprom_t settings;

bool loadParameters()
{

    read_flash_bin(&settings, EEPROM_START_ADD, sizeof(settings));

    //check crc field
    //if crc fails reset the parameters and load safe defaults and prevent arming
    //update firmware name and version

    //if (crc fail) restoreDefaultParameters();
}

bool saveParameters() //it's a bool, so better to check the returned value
{

    //update crc

    save_flash_nolib(&settings, sizeof(settings), EEPROM_START_ADD);
}

bool restoreDefaultParameters()
{
    //first boot / crc fail...
    memset(&settings, 0, sizeof(settings));

    settings.common.version = 1;
    settings.hardware.complementary_pwm = 1;
    settings.hardware.timing_advance_compact = 2;
    settings.hardware.pwm_frequency_multiplier_compact = 24;
    settings.hardware.startup_power_compact = 150;
    settings.hardware.motor_kv_compact = 55;            //motor_kv_compact*40 + 20
    settings.hardware.servo_low_value_compact = 175;    //750 + servo_low_value_compact*2
    settings.hardware.servo_high_value_compact = 75;    //1750 + servo_high_value_compact*2
    settings.hardware.servo_neutral_base_compact = 126; //1374 + servo_neutral_base_compact
    settings.hardware.servo_deadband = 100;
    settings.hardware.low_voltage_cut_off_threshold_compact = 80; //250+low_voltage_cut_off_threshold_compact

    //other settings are ok to be zero or they are defaulted (constrained in other parts of the code

    //update crc and then save to eeprom
}

uint16_t calculate_crc16(eeprom_t *buff)
{ //you don't want to calculate the CRC on the CRC field itself FIX IT

    uint8_16_u CRC_16;
    uint8_t length = sizeof(buff);
    CRC_16.word = 0;

    for (int i = 0; i < length; i++)
    { //use while...

        uint8_t xb = ((uint8_t *)buff)[i]; //IS THIS CORRECT?

        for (uint8_t j = 0; j < 8; j++)
        {
            if (((xb & 0x01) ^ (CRC_16.word & 0x0001)) != 0)
            {
                CRC_16.word = CRC_16.word >> 1;
                CRC_16.word = CRC_16.word ^ 0xA001;
            }
            else
            {
                CRC_16.word = CRC_16.word >> 1;
            }
            xb = xb >> 1;
        }
    }

    uint16_t crc16 = (CRC_16.bytes[1] << 8) | CRC_16.bytes[0];

    return crc16;
}

/*
bool check_crc16(eeprom_t* buff, uint16_t crc16){

    if(calculate_crc16(&buff) == crc16){
        return true;
    }
    else
    {
        return false;
    }

}
*/