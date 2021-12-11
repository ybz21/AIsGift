# 材料
ESP32

SX1278

ST7789

# 连接
## esp32管脚

sx1278传输器
nss     5
rst     22
dio     21
mosi    23
miso    19
sck     18

st7789 显示器
miso    12
mosi    13 
sck     14
cs      15
dc      2
rst     4

# 代码
## 引用库

User_Setup.h

'''
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
'''