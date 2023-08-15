# Determine CS Pin

Have you ever gotten an SD Card reader hooked up to your Arduino, but then realized you don't know what the Chip Select pin for that reader is? If so,  Determine CS Pin is exactly what you're looking for.

Note that this will work with anything that behaves like an SD card, even if it actually isn't - like the [Adafruit SPI Flash SD Card](https://www.adafruit.com/product/4899), for instance.



## Usage

1. Insert an SD card into each reader you would like to test
1. Make sure all readers are wired correctly
1. Upload this sketch to your Arduino
1. Watch the Serial monitor for results



## Configuration Options

All configurable variables are found near the beginning of the sketch.

- `minPin` - The minimum pin number to try searching. Value should not be greater than `maxPin`.
- `maxPin` - The maximum pin number to try searching. Value should not be less than `minPin`.
- `bVerbose` - If true, will tell you which pin is currently being tried. If false, will only report when a SD card is found.

To search a single pin, set minPin and maxPin to the same value.
