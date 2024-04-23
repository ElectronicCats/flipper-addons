#include <ModbusRTUSlave.h>
#define SLAVE 1

const byte dePin = 13;
ModbusRTUSlave modbus(Serial1, dePin); // serial port, driver enable pin for rs-485

bool discreteInputs[4] = {1,1,1,1};
uint16_t inputRegisters[1] = {100};

bool coils[4] = {1,0,1,0};
uint16_t holdingRegisters[1] = {500};

void setup() {

  modbus.configureCoils(coils, 4);                       // bool array of coil values, number of coils
  modbus.configureDiscreteInputs(discreteInputs, 4);     // bool array of discrete input values, number of discrete inputs
  modbus.configureHoldingRegisters(holdingRegisters, 1); // unsigned 16 bit integer array of holding register values, number of holding registers
  modbus.configureInputRegisters(inputRegisters, 1);     // unsigned 16 bit integer array of input register values, number of input registers

  modbus.begin(SLAVE, 9600);
}

void loop() {
  
  modbus.poll();
  
}
