#include "SensorDRV2605.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "DRV2605";

SensorDRV2605::SensorDRV2605() : _port(I2C_NUM_0), _address(DRV2605_SLAVE_ADDRESS), _initialized(false) {
}

bool SensorDRV2605::begin(i2c_port_t port, uint8_t address) {
    _port = port;
    _address = address;
    
    ESP_LOGI(TAG, "Attempting to initialize DRV2605 at address 0x%02X on port %d", _address, _port);
    
    // First try to read the status register
    uint8_t status = readRegister8(DRV2605_REG_STATUS);
    ESP_LOGI(TAG, "DRV2605 Status register: 0x%02X", status);
    
    // Extract chip ID (bits 7-5)
    uint8_t chipID = (status >> 5) & 0x07;
    ESP_LOGI(TAG, "DRV2605 Chip ID: 0x%02X", chipID);
    
    // Check for valid chip IDs
    if (chipID != 0x03 && chipID != 0x04 && chipID != 0x06 && chipID != 0x07) {
        ESP_LOGE(TAG, "Invalid chip ID: 0x%02X (expected 0x03, 0x04, 0x06, or 0x07)", chipID);
        return false;
    }
    
    ESP_LOGI(TAG, "Valid DRV2605 chip detected, initializing...");
    
    // Initialize following factory code sequence
    writeRegister8(DRV2605_REG_MODE, 0x00);  // out of standby
    vTaskDelay(pdMS_TO_TICKS(10));  // Small delay after mode change
    
    writeRegister8(DRV2605_REG_RTPIN, 0x00);  // no real-time-playback
    writeRegister8(DRV2605_REG_WAVESEQ1, 1);  // strong click
    writeRegister8(DRV2605_REG_WAVESEQ2, 0);  // end sequence
    writeRegister8(DRV2605_REG_OVERDRIVE, 0);  // no overdrive
    writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
    writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
    writeRegister8(DRV2605_REG_BREAK, 0);
    writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);
    
    // ERM open loop configuration (from factory code)
    uint8_t feedback = readRegister8(DRV2605_REG_FEEDBACK);
    writeRegister8(DRV2605_REG_FEEDBACK, feedback & 0x7F);  // turn off N_ERM_LRA
    
    uint8_t control3 = readRegister8(DRV2605_REG_CONTROL3);
    writeRegister8(DRV2605_REG_CONTROL3, control3 | 0x20);  // turn on ERM_OPEN_LOOP
    
    ESP_LOGI(TAG, "DRV2605 initialization complete");
    _initialized = true;
    return true;
}

void SensorDRV2605::setMode(uint8_t mode) {
    writeRegister8(DRV2605_REG_MODE, mode);
}

void SensorDRV2605::selectLibrary(uint8_t lib) {
    writeRegister8(DRV2605_REG_LIBRARY, lib);
}

void SensorDRV2605::setWaveform(uint8_t slot, uint8_t wave) {
    if (slot >= 8) return;
    writeRegister8(DRV2605_REG_WAVESEQ1 + slot, wave);
}

void SensorDRV2605::run() {
    writeRegister8(DRV2605_REG_GO, 1);
}

void SensorDRV2605::stop() {
    writeRegister8(DRV2605_REG_GO, 0);
}

void SensorDRV2605::useERM() {
    writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
}

void SensorDRV2605::useLRA() {
    writeRegister8(DRV2605_REG_FEEDBACK, readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
}

bool SensorDRV2605::isGoing() {
    return (readRegister8(DRV2605_REG_GO) & 0x01) != 0;
}

void SensorDRV2605::setRealtimeValue(uint8_t rtp) {
    writeRegister8(DRV2605_REG_RTPIN, rtp);
}

uint8_t SensorDRV2605::readRegister8(uint8_t reg) {
    uint8_t data;
    esp_err_t err = i2c_master_write_read_device(_port, _address, &reg, 1, &data, 1, pdMS_TO_TICKS(100));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Read register 0x%02X failed: %s", reg, esp_err_to_name(err));
        return 0;
    }
    return data;
}

void SensorDRV2605::writeRegister8(uint8_t reg, uint8_t val) {
    uint8_t data[2] = {reg, val};
    esp_err_t err = i2c_master_write_to_device(_port, _address, data, 2, pdMS_TO_TICKS(100));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Write register 0x%02X failed: %s", reg, esp_err_to_name(err));
    }
}