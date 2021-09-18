// TODO: Make all of these read from a config
// TODO: Add multi-monitor support

// How often to check the ALS in seconds.
// Default: 0 (match ALS's frequency, i.e. as fast as the device allows)
float POLLING_PER=0;

// Values read by the ALS for which the screen should be dimmest or brightest
// Default: 10 and 9000000
const unsigned int MIN_LUX=50;
const unsigned long int MAX_LUX=9000000;

// Amount that ambient brightness must change before we change the screen brightness
// Default: 0.1
const float BRI_THRESHOLD_FRAC=0.1;

// What to modify the brightness by when the laptop is unplugged
// Default: 0.9
const float BRI_UNPLUGGED_MODIFIER=0.9;

char BRI_FILE[]="/sys/class/backlight/acpi_video0/brightness";
char MAX_BRI_FILE[]="/sys/class/backlight/acpi_video0/max_brightness";
char PLUG_STATE_FILE[]="/sys/class/power_supply/ADP1/online";
char LID_STATE_FILE[]="/proc/acpi/button/lid/LID0/state";
