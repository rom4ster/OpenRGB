/*-----------------------------------------*\
|  EVGAGPUv3Controller.cpp                  |
|                                           |
|  Driver for EVGA GPU RGB v3 (Turing)      |
|  lighting controller                      |
|                                           |
|  Adam Honse (CalcProgrammer1) 9/13/2020   |
\*-----------------------------------------*/

#include "EVGAGPUv3Controller.h"

EVGAGPUv3Controller::EVGAGPUv3Controller(i2c_smbus_interface* bus, evga_dev_id dev)
{
    this->bus = bus;
    this->dev = dev;
}

EVGAGPUv3Controller::~EVGAGPUv3Controller()
{

}

std::string EVGAGPUv3Controller::GetDeviceLocation()
{
    std::string return_string(bus->device_name);
    char addr[5];
    snprintf(addr, 5, "0x%02X", dev);
    return_string.append(", address ");
    return_string.append(addr);
    return("I2C: " + return_string);
}

unsigned char EVGAGPUv3Controller::GetRed()
{
    return(bus->i2c_smbus_read_byte_data(dev, EVGA_GPU_V3_REG_RED));
}

unsigned char EVGAGPUv3Controller::GetGreen()
{
    return(bus->i2c_smbus_read_byte_data(dev, EVGA_GPU_V3_REG_GREEN));
}

unsigned char EVGAGPUv3Controller::GetBlue()
{
    return(bus->i2c_smbus_read_byte_data(dev, EVGA_GPU_V3_REG_BLUE));
}

void EVGAGPUv3Controller::SetColor(unsigned char red, unsigned char green, unsigned char blue)
{
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xE5);
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xE9);
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xF5);
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xF9);
    
    bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_V3_REG_MODE,       0x04);
    bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_V3_REG_RED,        red);
    bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_V3_REG_GREEN,      green);
    bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_V3_REG_BLUE,       blue);
    bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_V3_REG_BRIGHTNESS, 0xFF);

    bus->i2c_smbus_write_byte_data(dev, 0x08,                               0x01);
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xF0);
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xE0);
}



void EVGAGPUv3Controller::SetMode(unsigned char mode)
{
    //bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_v3_REG_MODE, mode);
}
