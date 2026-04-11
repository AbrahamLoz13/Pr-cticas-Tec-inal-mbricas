#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4,5);   // CE, CSN

const byte direccion[6] = "00001";

int valor;
int led = 2;

void setup() {

  Serial.begin(115200);

  pinMode(led, OUTPUT);

  SPI.begin(18,19,23); // SCK, MISO, MOSI

  if (!radio.begin()) {
    Serial.println("NRF no detectado");
    while(1);
  }

  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);

  // ===== PRUEBAS DE DISTANCIA =====
  radio.setPALevel(RF24_PA_LOW);   // DISTANCIA CORTA
  //radio.setPALevel(RF24_PA_HIGH); // DISTANCIA MEDIA
  //radio.setPALevel(RF24_PA_MAX);  // DISTANCIA MAXIMA

  radio.openReadingPipe(0, direccion);
  radio.startListening();

  Serial.println("Receptor listo");
}

void loop() {

  if (radio.available()) {

    radio.read(&valor, sizeof(valor));

    Serial.print("Recibido: ");
    Serial.println(valor);

    if(valor == 1){
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }

  }

}