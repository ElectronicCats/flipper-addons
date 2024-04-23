//#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>

const uint8_t rxPin = 10;
const uint8_t txPin = 11;
const uint8_t dePin = 2;
const uint8_t ledPin = 13;

ModbusRTUMaster modbus(Serial1, dePin); // serial port, driver enable pin for rs-485 (optional)

bool coils[4] = {0};
bool discreteInputs[4]= {0};
uint16_t holdingRegisters[1]= {0};
uint16_t inputRegisters[1]= {0};

const bool testCoils[4] = {1,0,1,0};
const uint16_t testInputs[4] = {1,1,1,1};
const uint16_t testInputRegs[1] = {100};
const uint16_t testRegs[1] = {500};

void setup() {  
  modbus.begin(9600); // baud rate, config (optional)
  pinMode(13,OUTPUT);
}
void showResult(bool err = false){
  digitalWrite(ledPin, 1);
  if(err){
    while(1){
      digitalWrite(ledPin,0);
      delay(100);
      digitalWrite(ledPin,1);
      delay(100);
    }
  }

}
void loop() {
  modbus.readCoils(1,0, coils, 4);
  delay(100);
  modbus.readHoldingRegisters(1,0, holdingRegisters, 1);
  delay(100);
  modbus.readDiscreteInputs(1, 0, discreteInputs, 4);              // slave id, starting data address, bool array to place discrete input values, number of discrete inputs to read
  delay(100);
  modbus.readInputRegisters(1, 0, inputRegisters, 1); 
  for(int i =0; i<4; i++){
    if(coils[i] != testCoils[i]) showResult(true);
    if(discreteInputs[i] != testInputs[i]) showResult(true);
  }
  if(holdingRegisters[0]!= testRegs[0] || inputRegisters[0]!= testInputRegs[0]) showResult(true);
  showResult();
}
