/*
 * rfm22.c
 *
 *  Created on: Dec 16, 2024
 *      Author: mihal
 */
#include "rfm22.h"

void rfm22_tx_init(void)
{
	 uint8_t data;
	 data = spi_read(0x00);
    spi_write(0x07, 0x80);
    // Disable interrupts
    spi_write(0x06, 0x00);

    // Set device to READY mode
    spi_write(0x07, 0x01);

    // Set frequency to 434 MHz
    spi_write(0x75, 0x53);
    spi_write(0x76, 0x64);
    spi_write(0x77, 0x00);

    // Set maximum TX power
    spi_write(0x6D, 0x07);

    // Set FIFO mode for TX
    spi_write(0x71, 0x20);

    // Set packet length
    spi_write(0x3E, 1);
    spi_write(0x34, 64);

    // Set synchronization word
    spi_write(0x36, 0x2D);
    spi_write(0x37, 0xD4);

    // Enable CRC, Packet TX Handling
    spi_write(0x30, 0x8c);
    //spi_write(0x30, 0x8C);
    spi_write(0x6E, 0x27); // Data Rate, vyšší bajt
    spi_write(0x6F, 0x52); // Data Rate, nižší bajt
    spi_write(0x70, 0x20); // Modulácia: FSK, FIFO režim
    spi_write(0x34, 0x14); // Preamble Length
    spi_write(0x35, 0x14); // Preamble Detection Length
    spi_write(0x3F, 0x00); // Header Control

    spi_write(0x08, 0x03);
    spi_write(0x08, 0x00);

    data = spi_read(0x00);


}

void rfm22_send(uint8_t *data, uint8_t length)


{
	uint8_t reg4,reg3;
	spi_write(0x08, 0x03);
	spi_write(0x08, 0x00);
	    reg3 = spi_read(0x03);
	    reg4 = spi_read(0x04);
    // Write data to TX FIFO
	for (int i = 0; i < 20; i++) {
             spi_write(0x7F, 0x20); // Zapíšte bajty do TX FIFO
           }
    reg3 = spi_read(0x03);
    // Set device to TX mode
    spi_write(0x07, 0x09);
    reg4 = spi_read(0x04);

	do {
	    reg3 = spi_read(0x03); // Čítanie Interrupt Status 2
	} while ((reg3 & 0x04) == 0); // Čakať na ITXDONE (Bit 4)

    // Return to READY mode after transmission
	spi_write(0x08, 0x03);
	spi_write(0x08, 0x00);
	spi_write(0x07, 0x01);
}


