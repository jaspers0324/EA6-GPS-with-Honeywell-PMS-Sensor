#include <SoftwareSerial.h>
#include <Jasper_LEA6I2C.h>
#include <Jasper_hpma115S0.h>

SoftwareSerial hpmaSerial(10, 11); // Feather TX, Feather RX
int GPSAddress = 0x42; // GPS I2C Address
Jasper_HPMA115S0 hpma115S0(hpmaSerial);

void setup()
{
  Wire.begin(); //I2C Initialize
  Serial.begin(9600);//set baud rate
  hpmaSerial.begin(9600);
  hpma115S0.Init();
  hpma115S0.StartParticleMeasurement();
}

void initReceive() 
{
  Wire.beginTransmission(GPSAddress);
  WireSend(0xff); //To send data address      
  Wire.endTransmission(); 
 
  Wire.beginTransmission(GPSAddress);
  Wire.requestFrom(GPSAddress,10); //Require 10 bytes read from the GPS device
}

void readNMEASentence(char *buff){
    int i = 0; // index of data received
    bool readingData = 0; // reading data off the wire

    while(1){
      initReceive(); //Receive data initialization    
      while(Wire.available())   
      { 
        buff[i] = WireRead(); // receive serial data
        if(readingData || buff[i]=='$') // sentences start with $
        { 
          // sentences end in new-line
          if(i>0 && buff[i] =='\r') {
            i = readingData = 0; // reset counters
            Wire.endTransmission(); // end receiving
            return;
          }
          readingData = 1;
          i++;
        }   
      }
      Wire.endTransmission(); //End receiving
    }
}

void loop()
{   
    String sentence = "";
    char buff[BUFFER_LENGTH];
    readNMEASentence(buff);

    // clean up the sentence and convert to a string
    for(int i=0; i<(BUFFER_LENGTH); i++){
      if(buff[i] == '\r'){
        i=BUFFER_LENGTH;
      }
      else{
        sentence += buff[i];
      }
    }
    Serial.println(sentence);

    unsigned int pm2_5, pm10;
    if (hpma115S0.ReadParticleMeasurement(&pm2_5, &pm10)) {
    Serial.println("PM 2.5: " + String(pm2_5) + " ug/m3" );
    Serial.println("PM 10: " + String(pm10) + " ug/m3" );
    }
    delay (2000);
}
