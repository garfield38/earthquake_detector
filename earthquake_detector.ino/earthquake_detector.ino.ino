/*
 * Author: Louis Moreau (https://github.com/luisomoreau)
 * Contributors: Harrison Smith (https://github.com/DStar1), Daniella Gerard (https://github.com/dgerard42)
 * Date: 2018/04/18
 * Description:
 * This program is using a modified HidnSeek device (accelerometer changed to the MMA8652FC) 
 * (https://github.com/hidnseek/hidnseek) to detect earthquakes and send the relative information using Sigfox network.
 * 
 */

#include "LowPower.h"
#include "TinyGPS.h"
#include <SoftwareSerial.h>
#include "Wire.h"
#include "mma8652.h"

/****************** Pins usage ***************************************/
#define rxGPS            0     // PD0 RX Serial from GPS
#define txGPS            1     // PD1 TX Serial to GPS
#define usbDP            2     // PD2 Shutdown supply after power off
#define accINT           3     // PD3 Accelerometer Interruption
#define usbDM            4     // PD4
#define txSigfox         5     // PD5 TX Serial to Sigfox modem
#define bluLEDpin        6     // PD6 Piezzo Output
#define redLEDpin        7     // PD7 Red LED Status
#define rxSigfox         8     // PB0 RX Serial from Sigfox modem
#define shdPin           9     // PB1 Shutdown pin
#define rstPin          10     // PB2 SS   SDCARD
#define msiPin          11     // PB3 MOSI SDCARD
#define msoPin          12     // PB4 MISO SDCARD
#define sckPin          13     // PB5 SCK  SDCARD
#define sensorA0        A0     // PC0 VUSB present
#define sensorBatt      A1     // PC1 battery voltage
#define chg100mA        A2
#define satLEDpin       A3
#define sensorA4        A4     // PC4 A4 SDA
//                      A5     // PC5 A5 SCL
#define sensorA6        A6     // PC6
#define chgFLAG         A7
/*********************************************************************/

// Info
 


#define DEBUG 1

// Variables

   //Sigfox
uint8_t msg[12];

    //GPS
    //Position structure, data stored as degrees, decimals minutes
  typedef struct {
    int32_t latitude;       ///< Latitude in 1/100000 degrees, South if < 0, North otherwise
    int32_t longitude;        ///< Longitude in 1/100000 degrees, West if < 0, East otherwise
    int16_t altitude;       ///< Altitude in meters above sea level
  } GPS_Position;

  //Date & Time structure
  typedef struct {
    uint16_t year;          ///< Year UTC
    uint8_t seconds;        ///< Seconds 0..59
    uint8_t minutes;        ///< Minutes 0..59
    uint8_t hours;          ///< Hours 0..23
    uint8_t day;            ///< Days 1.31
    uint8_t month;          ///< Month 1..12
  } GPS_DateTime;

  // Quality structure
  typedef struct {
    uint16_t hdop;          ///< Horizontal Degree Of Precision, 0 .. 20 * 100
    uint16_t hAcc;          ///< Horizontal estimated Accuracy in meters
    uint8_t sat;            ///< Number of satellites used for fix, maximum 20
  } GPS_Quality;

  // GPS fix structure types
  typedef enum {
    TD_GEOLOC_NO_FIX = 0,
    TD_GEOLOC_TIME_FIX = 1,
    TD_GEOLOC_DATE_FIX = 2,
    TD_GEOLOC_2D_FIX = 3,
    TD_GEOLOC_3D_FIX = 4
  } GPS_FixType;

  //Geoloc information saved in logger */
  typedef struct {
    GPS_Position position;  ///< Position information
    GPS_DateTime datetime;     ///< Date & time information
  } GPS_Log;

  // Full structure containing all updated informations
  typedef struct {
    GPS_DateTime datetime;    ///< Date & time information
    GPS_Position position;    ///< Position information
    GPS_Quality quality;      ///< Quality information
    uint32_t speed;           ///< Speed information (in km/h)
    GPS_FixType type;         ///< Type of fix information available
    uint32_t duration;        ///< Fix duration in seconds
  } GPS_Fix;


  //Accelero

  //Battery


// Sigfox
SoftwareSerial Sigfox =  SoftwareSerial(txSigfox, rxSigfox);


// GPS
SoftwareSerial GPS =  SoftwareSerial(txGPS, rxGPS);

// Accelerometer

void setup() {
  if(DEBUG){
    Serial.begin(9600);
    delay(100);
  } 
  
  Sigfox.begin(9600);
  delay(100);
  getID();
  delay(100);
  
  GPS.begin(4800);
  delay(100);

  //Declare other variables

}

void loop() {
  
}

/***************************************************************************//**
 * @brief
   This function is used to setup the device in the field.
   It must get the GPS information: Lat, Long, Alt and store them in memory
   It must sync the internal clock
   If the GPS acquisition went well, it must send a Sigfox message with:
   - The message type indicator (setup)
   - The battery level
   - The lat, long, alt
   If it went wrong (no GPS information for instance):
   - The message type indicator
   - The battery level
 *
 * @param[in] none at the moment

 ******************************************************************************/
static void setupDevice(){
  
}

/***************************************************************************//**
 * @brief
 *   Start the GPS and try to get a fix. If the GPS is already running then no
 *   effect.
 *
 * @param[in] timeout
 *  timeout in seconds. On timeout expiration the timeout parameter of the
 *  callback will be set to true. No further action is being performed and
 *  shutting down the GPS or not is left to the user application and should be
 *  done using GPS_StopFix.
 *
 * @param[in] precision
 *   Stop the GPS when fix type precision has fullfiled requirements
 *
 *
 ******************************************************************************/
void startGPSFix(uint16_t timeout, GPS_FixType precision){
  
}


/***************************************************************************//**
 * @brief
 *  Power down the GPS
 *
 * @param[in] none at the moment
 ******************************************************************************/
static void StopGPSFix(){
  
}


/***************************************************************************//**
 * @brief
 *  GPS fix callback
 *
 * @param[in] fix
 *   The GPS fix data structure.
 *
 * @param[in] timeout
 *   Flag that indicates whether a timeout occurred if set to true.
 ******************************************************************************/
static void GPSFix(GPS_Fix * fix, bool timeout){
  StopGPSFix();
  
}



/***************************************************************************//**
 * @brief
 *  Calibrate internal clock
 *
 * @param[in] fix
 *   The GPS fix data structure.
 *
 * @param[in] timeout
 *   Flag that indicates whether a timeout occurred if set to true.
 ******************************************************************************/
void calibrateClock(){
  
}




//Send Sigfox Message
void sendMessage(uint8_t msg[], int size){
  // This function is used to send the Sigfox messages
  
  String status = "";
  char output;

  Sigfox.print("AT$SS=");
  for(int i= 0;i<size;i++){
    Sigfox.print(String(msg[i], HEX));
    if(DEBUG){
      Serial.print("Byte:");
      Serial.println(msg[i], HEX);
    }
  }

  Sigfox.print("\r");

  while (!Sigfox.available()){
     blink();
  }
  while(Sigfox.available()){
    output = (char)Sigfox.read();
    status += output;
    delay(10);
  }
  if(DEBUG){
    Serial.println();
    Serial.print("Status \t");
    Serial.println(status);
  }
}

//Get Sigfox ID
String getID(){
  String id = "";
  char output;

  Sigfox.print("ATI7\r");
  while (!Sigfox.available()){
     blink();
  }
  while(Sigfox.available()){
    output = Sigfox.read();
    id += output;
    delay(10);
  }
  if(DEBUG){
    Serial.println("Sigfox Device ID: ");
    Serial.println(id);
  }
  return id;
}

// Blink can be used for debug
void blink(){
  digitalWrite(bluLEDpin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(bluLEDpin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}
