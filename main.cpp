/**
  @file main.cpp
  @brief This is the sample code for DFROBOT Air Quality Sensor.
  @ref https://github.com/DFRobot/DFRobot_AirQualitySensor
  @date 2024/08/21
  @author masa-night
*/

#include "mbed.h"
#include <cstdint>

I2C airquality(I2C_SDA, I2C_SCL);
RawSerial pc(USBTX,USBRX,9600);

#define AIRQUALITY_I2C_ADDR       0x19 << 1
#define PARTICLE_PM1_0_STANDARD   0X05
#define PARTICLE_PM2_5_STANDARD   0X07
#define PARTICLE_PM10_STANDARD    0X09

uint16_t get_particle_concentration(char type);


int main() {
  while(1) {
    uint16_t concentration[3];
    concentration[0] = get_particle_concentration(PARTICLE_PM1_0_STANDARD);
    concentration[1] = get_particle_concentration(PARTICLE_PM2_5_STANDARD);
    concentration[2] = get_particle_concentration(PARTICLE_PM10_STANDARD);

    pc.printf("PM1.0: %d [ug/m^3]\r\n", concentration[0]);
    pc.printf("PM2.5: %d [ug/m^3]\r\n", concentration[1]);
    pc.printf("PM10: %d [ug/m^3]\r\n", concentration[2]);
    pc.printf("\r\n");

    wait(1);
  }
}

uint16_t get_particle_concentration(char type) {
  char buf[2] = {0x00};
  const event_callback_t callback;

  airquality.write(AIRQUALITY_I2C_ADDR, &type, 1);
  airquality.read(AIRQUALITY_I2C_ADDR, buf, 2);

  uint16_t concentration = ((uint16_t)buf[0] << 8) + (uint16_t)buf[1];
  return concentration;
}
