/**
 * determineCsPin
 * Not sure what CS pin your SD card or module uses? This will figure it out via brute force.
 * Be sure you have the serial monitor open when running!
 * Tip: using SD cards of different capacites will make it much easier to match a pin number to a physical SD card slot.
 */



#include <SPI.h>
#include <SD.h>



//
// Configurables
//

//! The minimum pin number to try searching
static uint8_t minPin = 1;

//! The maximum pin number to try searching
static uint8_t maxPin = 28;

//! If true, will tell you which pin is currently being tried. If false, will only report when a SD card is found.
static bool bVerbose = true;

//
// End configurables
// Please do not touch below this line
//



void setup()
{
    // Aziz, light!
    Serial.begin(9600);
    // Very good, thank you, Aziz.

    // Sanity check
    if (minPin > maxPin)
    {
        Serial.println(F("Bad configuration: minPin is greater than maxPin."));
        while (1) {}
    }
    if (maxPin < minPin)
    {
        Serial.println(F("Bad configuration: maxPin is less than minPin."));
        while (1) {}
    }
}



void loop()
{
    if (bVerbose)
    {
        Serial.print(F("Trying pin "));
    }
    else
    {
        Serial.println(F("Running..."));
    }

    for (uint8_t currentPin = minPin; currentPin < maxPin + 1; currentPin++)
    {
        if (bVerbose) {
            Serial.print(currentPin);
            Serial.print(F("... "));
        }

        Sd2Card card;
        if (card.init(SPI_HALF_SPEED, currentPin))
        {
            SdVolume volume;

            Serial.println();
            Serial.print(F("\nFound a card on CS Pin "));
            Serial.println(currentPin);

            // Display some info about the card so that you can tell which is which.
            Serial.print(F("Card type is "));
            switch (card.type())
            {
            case SD_CARD_TYPE_SD1:
                Serial.println(F("SD1"));
                break;
            case SD_CARD_TYPE_SD2:
                Serial.println(F("SD2"));
                break;
            case SD_CARD_TYPE_SDHC:
                if (card.cardSize() < 70000000)
                {
                    Serial.println(F("SDHC"));
                }
                else
                {
                    Serial.println(F("SDXC"));
                }
                break;
            default:
                Serial.println(F("Unable to determine!"));
                break;
            }

            if (!volume.init(card))
            {
                Serial.println(F("Volume has not been formatted."));
            }
            else
            {
                Serial.print(F("Volume type:\tFAT"));
                Serial.println(volume.fatType(), DEC);

                Serial.println(F("Volume size:"));
                uint32_t volSize = volume.blocksPerCluster() * volume.clusterCount() / 2;
                Serial.print(volSize);
                Serial.println(F(" Kb"));
                Serial.print(volSize / 1024);
                Serial.println(F(" Mb"));
                Serial.print(float(volSize / 1024.0 / 1024.0));
                Serial.println(F(" Gb"));
            }

            Serial.println();
        }
        else
        {
            // What if we didn't find anything?
            if (currentPin == maxPin)
            {
                Serial.println(F("\n\nUnable to find any SD cards."));

                Serial.print(F("Checked pins "));
                Serial.print(minPin);
                Serial.print(F(" to "));
                Serial.print(maxPin);
                Serial.println(F(", inclusive."));

                Serial.print(F("Please double-check your wiring and make sure that there is an SD card inserted."));
            }
        }
    }



    // Do it again?
    Serial.print(F("\nPress any key to repeat.\n"));
    while (!Serial.available()) { }
    Serial.read();
    Serial.print("\n\n\n");
}
