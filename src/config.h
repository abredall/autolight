#ifndef CONFIG_H
#define CONFIG_H

extern char SENSOR[];
extern char ADAPTER[];

extern float POLLING_PER;

extern const unsigned int MIN_LUX;
extern const unsigned long int MAX_LUX;

extern const float BRI_THRESHOLD_FRAC;
extern const float BRI_UNPLUGGED_MODIFIER;

extern char BRI_FILE[];
extern char MAX_BRI_FILE[];
extern char PLUG_STATE_FILE[];
extern char LID_STATE_FILE[];

#endif
