#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4,5); // CE, CSN

const byte direccion[6] = "00001";

void setup() {

  Serial.begin(115200);

  SPI.begin(18,19,23); // SCK, MISO, MOSI

  if (!radio.begin()) {
    Serial.println("NRF24L01 no detectado");
    while(1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(0, direccion);
  radio.startListening();

  Serial.println("Receptor listo...");
}

void loop() {

  if (radio.available()) {

    char texto[32] = "";

    radio.read(&texto, sizeof(texto));

    Serial.print("Mensaje recibido: ");
    Serial.println(texto);

  }

}