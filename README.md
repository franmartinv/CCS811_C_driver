# CCS811 sensor API
## Author
Name:			Francisco Martín Villegas

Email:			f.martinvillegas00@gmail.com

Colleague:		University of Almería (Spain)

## Introduction
This package contains the CCS811 air quality sensor and the BME680 temperature, pressure and humidity sensor.

You can see my BME680 C driver here: https://github.com/franmartinv/BME680_C_driver

The sensor driver package includes CCS811.c and CCS811.h files.


## Integration details
* Integrate CCS811.c and CCS811.h file in to the project.
* Include the CCS811.h file in your code like below.
``` c
#include "CCS811.h"
```

## File information
* CCS811.h : This header file has the constants, function declarations, macros and datatype declarations.
* CCS811.c : This source file contains the definitions of the sensor driver APIs.

## Supported sensor interfaces
* SPI 4-wire	:	SDI, SDO and CSB pins
* I2C			:	SDA and SDC pins
* WAK pins		: 	connect to GND to wake up the sensor

SPI 3-wire is currently not supported in the API.
## Usage guide
### Initializing the master
First you need to initialize the I2C master with:
```c
hal_i2c_init();
```
### Initializing the sensor
Then initialize the sensor using:
```c
CCS811_init(mode_number);
```

You need to give it the mode number of the sensor.

#### Example for I2C
Create some UINT8_T variables to save TVOC and eco2, and the call the function:
```c
CCS811_read_CO2_TVOC(mode_number, &eco2, &TVOC);
```

### Sensor data units
> Both of sensor variables are read in ppm


### Templates for function
``` c
/**
 * @brief	Master initialition
 *
 */
void hal_i2c_init();

/**
 * @brief		Data writing in CCS811 (Define register and write data in it)
 *
 * @param[in]	CCS811_register			:	(uint8_t)		command of the register where we want to write
 * @param[in]	CCS811_register_value	:	(uint8_t)		value to introduce inside the register
 *
 * @param[out]	ret						:	(esp_err_t)		variable that indicates if there was a problem
 *
 */
esp_err_t CCS811_write_register(uint8_t CCS811_register, uint8_t CCS811_register_value)

*
 * 	@brief		Data writing in CCS811 (only defines data register direction)
 *
 *  @param[in]		CCS811_register		:	(uint8_t)		command of the register where we want to write
 *  @param[in]	 	size				: 	(unsigned)		number of bytes that you whant to write
 *
 *  @param[out]		ret					:	(uint8_t)		variable that indicates if there was a problem
 *
 */
esp_err_t CCS811_write_byte(uint8_t CCS811_register, unsigned size)

**
 * @brief		Function for write multiple bytes in a register
 *
 * @param[in]		CCS811_register		:	(uint8_t)		register addres where we want to write
 * @param[in]		buffer_in			:	(uint8_t)		buffer that we whant to write
 * @param[in]		size				:	(unsigned)		number of bytes that we whant to write
 *
 */
esp_err_t CCS811_write_data_register(uint8_t CCS811_register, uint8_t *buffer_in, unsigned size)

/**
 * @brief	Type 2 of data writting and reading in registers - reading of 1 byte
 *
 * @param[in]		*buffer_out			: (uint8_t)		pointer to buffer_out array where we save the read byte
 * @param[in]		CCS811_register		: (uint8_t)		register where we want to operate
 * @param[in]		size				: (unsigned)	number of bytes that we are going to read
 *
 */
esp_err_t CCS811_write_read_byte(uint8_t * buffer_out, uint8_t CCS811_register, unsigned size)

/**
 * @brief		Type 2.5 of writting and reading in registers - Reading of 1 byte
 *
 * @param[in]		*buffer_out			: (uint16_t)		pointer of the variable where we are going to save the data
 * @param[in]		CCS811_register		: (uint8_t)			register where we want to operate
 * @param[in]		size				: (unsigned)		number of bytes that we are going to read
 *
 */
esp_err_t CCS811_write_read_byte2(uint8_t *buffer_out, uint8_t CCS811_register, unsigned size)

/**
 * @brief		Software reset of sensor for switch it to boot-mode
 *
 */
esp_err_t CCS811_software_reset()

/**
 * @brief		Select operating mode of the CCS811.
 * 				First it reads the LSB, then it compares if the value introduced.
 * 				Because we need to stop the sensor for some time to use it correctly.
 *
 *	@param[in]	mode_number	:	(uint8_t)	sensor operation mode number. It is indicated in CCS811.h
 *											It will work if it is equal to global values
 *
 */
int CCS811_mode(uint8_t mode_number)

/*
 * @brief	Baseline configuration. It is automatically by the sensor, but only read and then write.
 * 			The value of the baseline is transparent for the engineer.
 *
 */
void CCS811_configuring_baseline()

/**
 * @brief		CCS811 slave initialition
 *
 * @param[in]	mode_number	:	(uint8_t)	sensor operating mode (0,1,2,3,4)
 *
 */
int CCS811_init(uint8_t mode_number)

/**
 * @brief		Temperature and humidity compensation using BME680 temperature, pressure and humidity sensor
 *
 * @param[in]	*NVM_coef		:	(BME680_calib_t)	pointer to BME680_calib_t which stores the BME680 calibration data
 *
 */
void CCS811_temperature_humidity_compensation(BME680_calib_t *NVM_coef, float *hum_comp, float *tempe_comp, float *press_comp)

/**
 * @brief			CO2 and TVOC sensors read
 *
 * @param[in]		mode_number				:	(uint8_t)			Depending on the mode number, a delay time will be left for them to be sampled the data and the go to read it
 * @param[in]		*eco2					:	(uint8_t)			pointer to variable eco2 that will contain the value of eco2 (carbon dioxide)
 * @param[in]		*TVOC					:	(uint8_t)			pointer to TVOC variable that will contain the value of TVOC (particles in suspension)
 * @param[in]		*hum_comp				:	(float)				pointer to compensate humidity variable
 * @param[in]		*tempe_comp				:	(float)				pointer to compensate temperature variable
 * @param[in]		*press_comp				:	(float)				pointer to compensate pressure variable
 * @param[in]		*NVM_coef				:	(BME680_calib_t)	pointer to BME680_calib_t which stores the BME680 calibration data
 *
 */

int CCS811_read_all_variables(uint8_t mode_number, uint16_t *eco2, uint16_t *TVOC, float *hum_comp, float *tempe_comp, float *press_comp, BME680_calib_t *NVM_coef)



```
