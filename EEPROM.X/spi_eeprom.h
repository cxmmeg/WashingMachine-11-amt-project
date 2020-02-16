char read_byte_eeprom(unsigned char highAdd, unsigned char lowAdd);
char write_byte_eeprom(unsigned char highAdd, unsigned char lowAdd, unsigned char data);
void get_preset(char *buf, char preset_num);
void set_preset(char *data, char preset_num);
void reset_presets(void);