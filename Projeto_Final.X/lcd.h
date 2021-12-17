#ifndef LCD
#define LCD
  void lcdCommand(char value);
  void lcdChar(char value);
  void lcdString(char msg[]);
  void lcdNumber(int value);
  void lcdPosition(unsigned char line, unsigned char col);
  void lcdInit(void);
#endif
