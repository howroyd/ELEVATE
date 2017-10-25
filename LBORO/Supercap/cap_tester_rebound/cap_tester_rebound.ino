#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <SPI.h>
#include <SD.h>
#include <dht.h>

#define DHT22_PIN 5
#define FILENAME "datalog.txt"

const uint32_t SAMPLE_INTERVAL_MS = 30000;
#define FILE_BASE_NAME "Data"

const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";

File myFile;

dht DHT;

struct
{
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};

const uint8_t chipSelect = 4;

// Time in micros for next data record.
uint32_t logTime;

// Write data header.
void writeHeader(File file) {
  file.print(F("RESTART"));
  file.println();
}

// Log a data record.
void logData(File file,  String data) {
  file.print(data);
}
//------------------------------------------------------------------------------

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }



  // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    Serial.println(F("FILE_BASE_NAME too long"));
  }
  while (SD.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      Serial.println(F("Can't create file name"));
    }
  }

  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
  //MFS.initialize();    // initialize multi-function shield library

  MFS.write("degC");

  Serial.println(F("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)"));

  myFile = SD.open(fileName, FILE_WRITE);
  writeHeader(myFile);
  myFile.close();

  // Start on a multiple of the sample interval.
  logTime = micros() / (1000UL * SAMPLE_INTERVAL_MS) + 1;
  logTime *= 1000UL * SAMPLE_INTERVAL_MS;
}



void loop() {
  
    // Time for next record.
    logTime += 1000UL * SAMPLE_INTERVAL_MS;

    // Wait for log time.
    int32_t diff;
    do {
      diff = micros() - logTime;
    } while (diff < 0);
  
  //delay(2000);
  String data = "";

  data += "DHT22, ";

  uint32_t start = micros();
  int chk = DHT.read22(DHT22_PIN);
  uint32_t stop = micros();

  stat.total++;
  switch (chk)
  {
    case DHTLIB_OK:
      stat.ok++;
      data += F("OK, ");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      stat.crc_error++;
      data += F("Checksum error, ");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      stat.time_out++;
      data += F("Time out error, ");
      break;
    default:
      stat.unknown++;
      data += F("Unknown error, ");
      break;
  }

  if (chk == DHTLIB_OK) {
    // DISPLAY DATA
    data += String(DHT.humidity, 1);
    data += F(", ");
    data += String(DHT.temperature, 1);
    data += F(", ");
    data += String(stop - start);
    data += '\n';

    Serial.print(data);

    MFS.write(DHT.temperature, 1);

    myFile = SD.open(fileName, FILE_WRITE);
    logData(myFile, data);
    myFile.close();

  }
  else Serial.print(F("No data\n"));
}
