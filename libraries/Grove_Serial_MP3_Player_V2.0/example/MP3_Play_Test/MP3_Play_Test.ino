/*
 * MP3_Play_Test.ino
 * A quick start example for Grove-Serial MP3 Player V2.0
 * Note: The MP3 chip of Grove-Serial MP3 Player V2.0 is different from Grove-Serial MP3 Player V1.0
 * Description: This demo let you can send instruction 1-8 to control the Grove-Serial MP3 Player, via the serial port.
 *
 * Copyright (c) 2015 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Wuruibin
 * Created Time: Dec 2015
 * Modified Time:
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>

// Note: You must define a SoftwareSerial class object that the name must be mp3, 
//       but you can change the pin number according to the actual situation.
SoftwareSerial mp3(2, 3);

/*
void setup()
{
    mp3.begin(9600);
    Serial.begin(9600); 
    delay(100);
    
    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x10);                // Set the volume, the range is 0x00 to 0x1E.
}
*/

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
    mp3.begin(9600);
    Serial.begin(9600); 
    delay(100);
    
    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x10);                // Set the volume, the range is 0x00 to 0x1E.
    
    // initialize the LED pin as an output:
    //pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
}



void loop(){
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    int prev_state = LOW;

    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH && prev_state != buttonState) {
        // turn LED on:
        //digitalWrite(ledPin, HIGH);
        Serial.println("high");
        PlayNext();
    }
    else {
        // turn LED off:
        //digitalWrite(ledPin, LOW);
        Serial.println("low");
    }
    prev_state = buttonState;
    delay(1000);
}

/*
void loop()
{
    char recvChar = 0;
    while(Serial.available())
    {
        recvChar = Serial.read();
    }
    Serial.print("Send: ");
    Serial.println( recvChar );
    
    switch (recvChar)
    {
        case '1':
            SpecifyMusicPlay(1);
            Serial.println("Specify the music index to play");
            break;
        case '2':
            PlayPause();
            Serial.println("Pause the MP3 player");
            break;
        case '3':
            PlayResume();
            Serial.println("Resume the MP3 player");
            break;
        case '4':
            PlayNext();
            Serial.println("Play the next song");
            break;
        case '5':
            PlayPrevious();
            Serial.println("Play the previous song");
            break;
        case '6':
            PlayLoop();
            Serial.println("Play loop for all the songs");
            break;
        case '7':
            IncreaseVolume();
            Serial.println("Increase volume");
            break;
        case '8':
            DecreaseVolume();
            Serial.println("Decrease volume");
            break;
        default:
            break;
    }
    
    delay(1000);
    
//    printReturnedData();
}
*/

