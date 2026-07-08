AVR driver for dh11 moisture and temp sensor
connnect PD2 to data line
bool read_dh11(uint8_t* humidity_int,uint8_t* humidity_dec,uint8_t* temp_int, uint8_t* temp_dec,uint8_t* checksum )
- here the function returns if the data is true or not
- give 5 integer pointer for temperature(int), temperature(decimal), humidity(int),humidity(decimal),check sum.
