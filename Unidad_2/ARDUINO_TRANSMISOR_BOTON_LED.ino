#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10);   // CE, CSN

const byte direccion[6] = "00001";

int boton = 8;
int valor;

void setup() {

  Serial.begin(9600);

  pinMode(boton, INPUT);

  if (!radio.begin()) {
    Serial.println("NRF no detectado");
    while(1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);

  radio.setPALevel(RF24_PA_LOW);   // DISTANCIA CORTA
 
  radio.openWritingPipe(direccion);
  radio.stopListening();

  Serial.println("Transmisor listo");
}

void loop() {

  valor = digitalRead(boton);

  Serial.print("Boton: ");
  Serial.println(valor);

  radio.write(&valor, sizeof(valor));

  delay(200);
}