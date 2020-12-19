/*-----------------------------------------*\
|  EVGAGPUv3Controller.h                    |
|                                           |
|  Definitions and types for EVGA GPU RGB   |
|  V3 (Ampere) lighting controller          |
|                                           |
|   |
\*-----------------------------------------*/

#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char	evga_dev_id;

enum
{
   EVGA_GPU_V3_REG_MODE = 0xC1,
   EVGA_GPU_V3_REG_BRIGHTNESS = 0xC2,
   EVGA_GPU_V3_REG_RED = 0xC2,
   EVGA_GPU_V3_REG_GREEN = 0xC3,
   EVGA_GPU_V3_REG_BLUE = 0xC4,
     

};

enum
{
    EVGA_GPU_V3_MODE_OFF                = 0x00,
    EVGA_GPU_V3_MODE_STATIC             = 0x04,
    //EVGA_GPU_V3_MODE_RAINBOW            = 0x0F,
    //EVGA_GPU_V3_MODE_BREATHING          = 0x22,
};

class EVGAGPUv3Controller
{
public:
    EVGAGPUv3Controller(i2c_smbus_interface* bus, evga_dev_id dev);
    ~EVGAGPUv3Controller();

    std::string     GetDeviceLocation();

    unsigned char   GetRed();
    unsigned char   GetGreen();
    unsigned char   GetBlue();

    void            SetColor(unsigned char red, unsigned char green, unsigned char blue);
    void            SetMode(unsigned char mode);

private:
    i2c_smbus_interface*    bus;
    evga_dev_id             dev;

};
