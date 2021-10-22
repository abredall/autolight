# autolight

Adjust screen brightness based on input from an ambient light sensor

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

## TODO
- [x] feat: allow configuration between runtime
- [x] feat: disable features if devices are not found
- [] docs: explain configuration
- [] docs: comment everything

## License

This project is licensed under the MIT License - see the LICENSE file for details
