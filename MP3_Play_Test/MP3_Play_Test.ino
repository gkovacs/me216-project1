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
#include <math.h>

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
const int fwd_buttonPin = 7;     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin

const int back_buttonPin = 6;     // the number of the pushbutton pin

const int play_buttonPin = 8;

const int preset_buttonPin = 4;

// variables will change:
int fwd_buttonState = 0;         // variable for reading the pushbutton status
int back_buttonState = 0;
int play_buttonState = 0;
int preset_buttonState = 0;

int prev_fwd_buttonState = LOW;
int prev_back_buttonState = LOW;
int prev_play_buttonState = LOW;
int prev_preset_buttonState = LOW;

int adcPin = A0;
int adcIn = 0;

bool isPlaying = false;

void setup() {
    mp3.begin(9600);
    Serial.begin(9600); 
    delay(100);
    
    SelectPlayerDevice(0x02);       // Select SD card as the player device.
    SetVolume(0x1E);                // Set the volume, the range is 0x00 to 0x1E.
    
    // initialize the LED pin as an output:
    //pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(fwd_buttonPin, INPUT);
    pinMode(back_buttonPin, INPUT);
}

void loop(){
    // read the state of the pushbutton value:
    fwd_buttonState = digitalRead(fwd_buttonPin);
    back_buttonState = digitalRead(back_buttonPin);
    play_buttonState = digitalRead(play_buttonPin);
    preset_buttonState = digitalRead(preset_buttonPin);
    
    adcIn = analogRead(adcPin);
    int volume = (int)(round(adcIn * 30.0 / 1024.0));
    SetVolume(volume);

    //Serial.println(volume);

    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (fwd_buttonState == HIGH && prev_fwd_buttonState != fwd_buttonState) {
        isPlaying = true;
        PlayNext();
    }
    if (back_buttonState == HIGH && prev_back_buttonState != back_buttonState) {
        isPlaying = true;
        PlayPrevious();
        //SpecifyMusicPlay(1);
    }
    if (play_buttonState != prev_play_buttonState) {
      if (play_buttonState == HIGH) {
        PlayResume();
      } else if (play_buttonState == LOW) {
        PlayPause();
      }
      /*
      if (isPlaying) {
        PlayPause();
        isPlaying = false;
      } else {
        PlayResume();
        isPlaying = true;
      }
      */
    }
    if (preset_buttonState == HIGH && prev_preset_buttonState != preset_buttonState) {
      isPlaying = true;
      SpecifyMusicPlay(1);
    }
    
    prev_fwd_buttonState = fwd_buttonState;
    prev_back_buttonState = back_buttonState;
    prev_play_buttonState = play_buttonState;
    prev_preset_buttonState = preset_buttonState;
    delay(100);
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

