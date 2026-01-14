#include <FrameMQTT.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Probando FrameMQTT..."));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Probando paquete de conexion MQTT"));
  // El ID de paquete se genera foma aleatoria
  MQTT.conectar("user","password");
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);
  
  delay(100);
  Serial.println(F("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"));
  Serial.println(F("Probando paquete de publicar MQTT"));
  MQTT.publicar("/topic/sensor","payload");
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);

  delay(100);
  Serial.println(F("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"));
  Serial.println(F("Probando paquete de desconectar MQTT"));
  MQTT.desconectar();
  //MQTT.showMQTT();
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);

  delay(100);
  Serial.println(F("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"));
  Serial.println(F("Probando paquete de suscribir MQTT"));
  MQTT.suscribir("topic/sensor");
  //MQTT.showMQTT();
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);
  delay(100);

  Serial.println(F("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"));
  Serial.println(F("Probando paquete de dessuscribir MQTT"));
  MQTT.desSuscribir("topic/sensor");
  //MQTT.showMQTT();
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);
  delay(100);

  Serial.println(F("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"));
  Serial.println(F("Probando paquete de ping MQTT"));
  MQTT.ping();
  //MQTT.showMQTT();
  Serial.print(F("Length ="));
  Serial.println(MQTT.length);
  Serial.write(MQTT.buffer, MQTT.length);
  delay(5000);
}
