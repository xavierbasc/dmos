// ----------------------------------
// inspired by dmcp from swissmicros
// 

#define PLATFORM_VERSION "0.01"
#define LCD_X 128
#define LCD_Y 64

// HW interface
void LCD_clear();
void LCD_init();
void LCD_power_on();
void LCD_power_off(int clear);

// Drawing Prototypes
void lcd_clear_buf();
void lcd_refresh();

// Keyboard
int read_key(int *k1, int *k2);

// Drawing
void setpixel(uint8_t *buff, uint8_t x, uint8_t y, uint8_t color);
void draw_line(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void update_display(uint8_t *buff);

