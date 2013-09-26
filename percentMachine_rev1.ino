
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;

//int state = 0;

enum TestState
{
  intro  = 0,
  start  = 1,
  finish = 2,
  idle   = 3

};

TestState state;

void setup() 
{

  Serial.begin(9600);

  //start the shield
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  MP3player.setVolume(0x0000,0x0000); //max is 0x0000 min is 0xFEFE

}

//do something else now
void loop() 
{

  switch (state)
  {
    case intro:
    {
      Serial.println("intro");
        //start playing track 1
      MP3player.playTrack(1);
      
      state = start;
      break;
    }
    case start:
    {
      if (!MP3player.isPlaying())
      {
        Serial.println("start");
        MP3player.playTrack(2);
        delay(2000);
      
        state = finish;
      }
      break;
    }
    case finish:
    {
      Serial.println("finish");
      delay(2000);
      
      state = idle;
      break;
    }
    default:
    {
      break;
    }
  }
}

