/*
 * CCS81 - Air quality sensor
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "CCS811.h"
#include "BME680.h"

void hal_i2c_init();

void app_main(void)
{
	BME680_calib_t		NVM_coef;
	uint16_t		mode_number;
	uint16_t		eco2, TVOC;
	float			hum_comp, tempe_comp, press_comp;

	mode_number = 1;

	hal_i2c_init();				// Master initialition

	vTaskDelay(100/portTICK_RATE_MS);

	BME680_init(&NVM_coef);			// BME680 slae initialition

	vTaskDelay(100/portTICK_RATE_MS);

	CCS811_init(mode_number);		// CCS811 slave initialition

	vTaskDelay(100/portTICK_RATE_MS);

	printf("\nco2 y TVOC read from the sensor:\n\n");

	while(1) {
		CCS811_read_all_variables(mode_number, &eco2, &TVOC, &hum_comp, &tempe_comp, &press_comp, &NVM_coef);
		printf("eco2: %d\nTVOC: %d ppm\nTemperature: %f Celsius\nPressure: %f hPa\nRelative humidity: %f\n\n", eco2, TVOC, tempe_comp, press_comp, hum_comp);

		vTaskDelay(1000/portTICK_RATE_MS);
	}

}
