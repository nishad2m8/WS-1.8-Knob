#ifndef SENSOR_DRV2605_HPP
#define SENSOR_DRV2605_HPP

#include <Arduino.h>
#include "driver/i2c.h"

#define DRV2605_SLAVE_ADDRESS 0x5A

#define DRV2605_REG_STATUS          0x00
#define DRV2605_REG_MODE            0x01
#define DRV2605_REG_RTPIN           0x02
#define DRV2605_REG_LIBRARY         0x03
#define DRV2605_REG_WAVESEQ1        0x04
#define DRV2605_REG_WAVESEQ2        0x05
#define DRV2605_REG_WAVESEQ3        0x06
#define DRV2605_REG_WAVESEQ4        0x07
#define DRV2605_REG_WAVESEQ5        0x08
#define DRV2605_REG_WAVESEQ6        0x09
#define DRV2605_REG_WAVESEQ7        0x0A
#define DRV2605_REG_WAVESEQ8        0x0B
#define DRV2605_REG_GO              0x0C
#define DRV2605_REG_OVERDRIVE       0x0D
#define DRV2605_REG_SUSTAINPOS      0x0E
#define DRV2605_REG_SUSTAINNEG      0x0F
#define DRV2605_REG_BREAK           0x10
#define DRV2605_REG_AUDIOCTRL       0x11
#define DRV2605_REG_AUDIOLVL        0x12
#define DRV2605_REG_AUDIOMAX        0x13
#define DRV2605_REG_AUDIOOUTMIN     0x14
#define DRV2605_REG_AUDIOOUTMAX     0x15
#define DRV2605_REG_RATEDV          0x16
#define DRV2605_REG_CLAMPV          0x17
#define DRV2605_REG_AUTOCALCOMP     0x18
#define DRV2605_REG_AUTOCALEMP      0x19
#define DRV2605_REG_FEEDBACK        0x1A
#define DRV2605_REG_CONTROL1        0x1B
#define DRV2605_REG_CONTROL2        0x1C
#define DRV2605_REG_CONTROL3        0x1D
#define DRV2605_REG_CONTROL4        0x1E
#define DRV2605_REG_VBAT            0x21
#define DRV2605_REG_LRARESON        0x22

#define DRV2605_MODE_INTTRIG        0x00
#define DRV2605_MODE_EXTTRIGEDGE    0x01
#define DRV2605_MODE_EXTTRIGLVL     0x02
#define DRV2605_MODE_PWMANALOG      0x03
#define DRV2605_MODE_AUDIOVIBE      0x04
#define DRV2605_MODE_REALTIME       0x05
#define DRV2605_MODE_DIAGNOS        0x06
#define DRV2605_MODE_AUTOCAL        0x07

class SensorDRV2605 {
public:
    SensorDRV2605();
    
    bool begin(i2c_port_t port = I2C_NUM_0, uint8_t address = DRV2605_SLAVE_ADDRESS);
    
    void setMode(uint8_t mode);
    void selectLibrary(uint8_t lib);
    void setWaveform(uint8_t slot, uint8_t wave);
    void run();
    void stop();
    void useERM();
    void useLRA();
    
    bool isGoing();
    
    void setRealtimeValue(uint8_t rtp);
    
    uint8_t readRegister8(uint8_t reg);
    void writeRegister8(uint8_t reg, uint8_t val);

private:
    i2c_port_t _port;
    uint8_t _address;
    bool _initialized;
};

#endif