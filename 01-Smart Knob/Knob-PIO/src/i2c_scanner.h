#ifndef I2C_SCANNER_H
#define I2C_SCANNER_H

#include "driver/i2c.h"
#include "esp_log.h"

class I2CScanner {
public:
    static void scan(i2c_port_t port) {
        static const char *TAG = "I2CScanner";
        ESP_LOGI(TAG, "Scanning I2C bus on port %d...", port);
        
        int count = 0;
        for (uint8_t address = 1; address < 127; address++) {
            esp_err_t err = i2c_master_write_to_device(port, address, nullptr, 0, pdMS_TO_TICKS(10));
            
            if (err == ESP_OK) {
                ESP_LOGI(TAG, "Found device at address 0x%02X", address);
                count++;
            }
        }
        
        if (count == 0) {
            ESP_LOGW(TAG, "No I2C devices found!");
        } else {
            ESP_LOGI(TAG, "Found %d device(s) on I2C bus", count);
        }
    }
};

#endif