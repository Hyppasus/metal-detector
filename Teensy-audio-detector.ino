// Simple WAV file player example
//
// Requires the audio shield:
//   http://www.pjrc.com/store/teensy3_audio.html
//
// Data files to put on your SD card can be downloaded here:
//   http://www.pjrc.com/teensy/td_libs_AudioDataFiles.html
//
// This example code is in the public domain.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code

AudioControlSGTL5000     audioShield;     
AudioInputI2S            audioInput;     
AudioOutputI2S           audioOutput;           
AudioPlaySdWav           playWav1;       
AudioAnalyzePeak         peak1;          


const int myInput = AUDIO_INPUT_LINEIN;

AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioConnection          patchCord3(audioInput, peak1);
//AudioConnection          patchCord4(audioInput, 0, audioOutput, 0);
//AudioConnection          patchCord5(audioInput, 1, audioOutput, 1);

void setup() {
  //int led = 13;
  Serial.begin(9600);
  //pinMode(led, OUTPUT);  
  //digitalWrite(led, HIGH);  
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(1);

  SPI.setMOSI(7);
  SPI.setSCK(14);
  if (!(SD.begin(10))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

//elapsedMillis fps;

void playFile(const char *filename)
{
  //Serial.print("Playing file: ");
  //Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // audioShield.volume(vol);
      //Serial.println(monoPeak);
    //}
  if (peak1.available()){
     float monoPeak = peak1.read() * 10;
      Serial.println(monoPeak);
   //if (fps > 12) {   
     if (monoPeak > 0.5) {
        audioShield.volume(1);
        //digitalWrite(led, HIGH);   
        delay(500);
        //for(int i=0; i<100; i++){
        //audioShield.volume(abs(i-100)*0.01);
        //delay(10);
        
      }else{
        
       audioShield.volume(0);
        //digitalWrite(led, LOW); 
        delay(500);
      
     }

  }
  }
}




void loop() {
  playFile("00.WAV");
  delay(100);



}

