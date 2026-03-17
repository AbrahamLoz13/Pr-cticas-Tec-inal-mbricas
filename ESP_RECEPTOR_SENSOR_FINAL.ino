#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN
const byte direccion[6] = "00001";

const int pinLed = 2;

void setup() {
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);

  SPI.begin(18, 19, 23); // SCK, MISO, MOSI

  if (!radio.begin()) {
    Serial.println("Error: NRF24L01 no detectado en RX");
    while (1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(0, direccion);
  radio.startListening();

  Serial.println("RX escuchando...");
}

void loop() {
  if (radio.available()) {
    int datoRecibido = 0;
    radio.read(&datoRecibido, sizeof(datoRecibido));

    Serial.print("Dato: ");
    Serial.println(datoRecibido);

    //  Lógica con sensor IR
    if (datoRecibido == LOW) {
      digitalWrite(pinLed, HIGH); // Obstáculo detectado
    } else {
      digitalWrite(pinLed, LOW);  // Sin obstáculo
    }
  }
}