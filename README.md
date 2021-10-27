# autolight
© 2021 John W. Bredall

A lightweight ambient light sensor daemon

## Description

autolight is a small C program that reads lux values from the ambient light sensor, and adjusts the screen brightness accordingly. It is designed to be incredibly simple, lightweight, and customizable.

## Getting Started

### Dependencies

* `gcc` and `make`

### Installing

1. Download the source code and change directories into the source tree:
```
$ git clone https://github.com/jbredall/autolight.git
$ cd autolight
```
2. Configure autolight to run on your system first by running:
```
$ ./configure
```
3. To build autolight and run tests, run:
```
$ make
```
4. To install autolight, then run:
```
$ sudo make install # installs to /usr/local/bin
```
(Optional) To install to a different directory (such as installing locally), run
```
$ PREFIX=/your/path/here make install # installs to /your/path/here/bin
```
You will of course want to make sure that `/your/path/here` is defined in `$PATH`.

### Executing program

To use autolight, simply run
```
$ autolight
```
For best results, configure your system to run the above command in the background at startup.

## Configuration
autolight stores its configuration in `$PREFIX/etc/autolight.conf` (default `/usr/local/etc/autolight.conf`) and offers the following settings:
- `screen-device`: The name of the screen whos backlight is to be adjusted.
- `als-device`: The name of the ambient light sensor device
- `kbd-device`: The name of the keyboard backlight interface
- `plug-device`: The name of the AC adapter
- `lid-device`: The name of the lid button so autolight knows then the lid is shut
- `als-min-lux`: The lux at which the screen should be at minimum brightness (default: 50)
- `als-max-lux`: The lux at which the screen should be at maximum brightness (default: 1000000)
- `als-polling-period`: The time in seconds between each successive poll of the ALS. If set to 0, autolight will match the ALS's own frequency (i.e. as fast as the ALS allows) (default: 0)
- `brightness-threshold-fraction`: What fraction in logspace (between 0 and 1) the ambient brightness must change by for autolight to adjust the screen brightness. Larger values require a greater ambient light change, and vice versa (default: 0.3)
- `brightness-unplugged-modifier`: What fraction (between 0 and 1) to multiply the screen brightness by when the laptop is unplugged. Set to 1 to disable dimming when unplugged (default: 0.9)

## TODO
- [x] feat: allow configuration between runtime
- [x] feat: disable features if devices are not found
- [] refactor: clean up code
- [] docs: explain configuration
- [] docs: comment everything

## License

This project is licensed under the GNU General Public License - see the COPYING file for details
