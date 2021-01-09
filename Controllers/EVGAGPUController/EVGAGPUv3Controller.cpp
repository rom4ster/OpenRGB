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

int lazy_write(evga_dev_id d, i2c_smbus_interface * b, u8 reg_start, u8 size, u8 * data) {
    for (int i = 0; i < size; i ++) {
        if (b->i2c_smbus_write_byte_data(d,reg_start+i,data[i]) < 0) {
            return -1;
        }
    }
    return 0;

}
void EVGAGPUv3Controller::SetColor(unsigned char red, unsigned char green, unsigned char blue)

{

    int ret = 0;
   /* bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xE5);
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
    bus->i2c_smbus_write_byte_data(dev, 0x0E,                               0xE0);*/


    u8 PREDATA_REG = 0xB2;
    u8 POSTDATA_REG = 0xC0;
    u8 predata [] {0x04,0xC6, 0xEB, 0xEA, 0x15};
    //u8 postdata [] {0x09, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
    u8 data [4] {0x00};
	data[0] = 0x04;
    data [1] = 0xFF;
    data [2] = red;
    data [3] = green;
    data [4] = blue;

    ret = bus->i2c_smbus_write_i2c_block_data(dev,PREDATA_REG,5,predata);
    ret = bus->i2c_smbus_write_i2c_block_data(dev,EVGA_GPU_V3_REG_MODE,5,data);


    //ret = lazy_write(dev,bus,PREDATA_REG,4,predata);
    //ret = lazy_write(dev,bus,EVGA_GPU_V3_REG_MODE,4,data);
    //ret = lazy_write(dev,bus,POSTDATA_REG,10,postdata);




}





void EVGAGPUv3Controller::SetMode(unsigned char mode)
{
    //bus->i2c_smbus_write_byte_data(dev, EVGA_GPU_v3_REG_MODE, mode);
}
