#if(ARDUINO) && (ARDUINO)>= 100
 #include "Arduino.h"
 #define WireSend(args) Wire.write(args)
 #define WireRead(args) Wire.read(args)
 #define printByte(args) Serial.write(args)
 #define printlnByte(args)  Serial.write(args), Serial.println()

#else
 #include "WProgram.h"
 #define WireSend(args) Wire.send(args)
 #define WireRead(args) Wire.receive(args)
 #define printByte(args) Serial.print(args,BYTE)
 #define printlnByte(args)  Serial.println(args,BYTE)
	
#endif
 
 #include <Wire.h>
 #define BUFFER_LENGTH 80 // NMEA sentences are max 80 char

class Jasper_LEA6I2C{
   public:
   Jasper_LEA6I2C();
   //void initReceive(void);
   //void readNMEASentence(char *buff);
   
   private:  

};