# FrameMQTT

An Arduino library for creating MQTT protocol frames/packets. This library provides a simple interface to generate MQTT protocol packets for IoT applications, particularly designed for use with Arduino platforms.

## Features

- **MQTT Packet Generation**: Create MQTT CONNECT, PUBLISH, SUBSCRIBE, UNSUBSCRIBE, DISCONNECT, and PING packets
- **ThingSpeak Integration**: Built-in support for publishing data to ThingSpeak channels
- **Flexible Authentication**: Support for username/password authentication
- **Lightweight**: Minimal memory footprint suitable for resource-constrained devices

## Installation

### Arduino IDE

1. Download the library as a ZIP file from GitHub
2. In Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library**
3. Select the downloaded ZIP file
4. The library will be installed and ready to use

### Manual Installation

1. Download or clone this repository
2. Copy the `FrameMQTT` folder to your Arduino libraries directory:
   - Windows: `Documents\Arduino\libraries\`
   - macOS: `~/Documents/Arduino/libraries/`
   - Linux: `~/Arduino/libraries/`

## Usage

### Basic Example

```cpp
#include <FrameMQTT.h>

void setup() {
  Serial.begin(9600);

  // Connect to MQTT broker
  MQTT.conectar("myClientID", "username", "password");

  // Send the connect packet
  Serial.write(MQTT.buffer, MQTT.length);

  // Publish a message
  MQTT.publicar("sensors/temperature", "25.5");
  Serial.write(MQTT.buffer, MQTT.length);

  // Disconnect
  MQTT.desconectar();
  Serial.write(MQTT.buffer, MQTT.length);
}

void loop() {
  // Your code here
}
```

### ThingSpeak Publishing

```cpp
#include <FrameMQTT.h>

char *channel = "YOUR_CHANNEL_ID";
char *apiKey = "YOUR_API_KEY";
char *data = "field1=25.5&field2=60.2";

void setup() {
  Serial.begin(9600);

  // Publish to ThingSpeak
  MQTT.pub_ThingSpeak(channel, apiKey, data);
  Serial.write(MQTT.buffer, MQTT.length);
}

void loop() {
  // Your code here
}
```

### Subscribe to Topics

```cpp
#include <FrameMQTT.h>

void setup() {
  Serial.begin(9600);

  // Connect first
  MQTT.conectar();

  // Subscribe to a topic with QoS 0
  MQTT.suscribir("sensors/#", 0);
  Serial.write(MQTT.buffer, MQTT.length);
}

void loop() {
  // Your code here
}
```

## API Reference

### Constructor

```cpp
FrameMQTT MQTT;  // Global instance available
```

### Connection Methods

#### `void conectar()`
Creates a CONNECT packet with auto-generated client ID and default keep-alive (300 seconds).

#### `void conectar(const char *id)`
Creates a CONNECT packet with specified client ID.

#### `void conectar(const char *user, const char *key)`
Creates a CONNECT packet with username and password, auto-generated client ID.

#### `void conectar(const char *user, const char *key, uint16_t keepalive)`
Creates a CONNECT packet with username, password, and custom keep-alive interval.

#### `void conectar(const char *id, const char *user, const char *key, uint16_t keepalive)`
Creates a CONNECT packet with all parameters specified.

### Publishing Methods

#### `void publicar(const char* topic, const char* body)`
Creates a PUBLISH packet for the specified topic with string payload.

#### `void pub_ThingSpeak(const char *channel, const char *apikey, const char *body)`
Creates a PUBLISH packet formatted for ThingSpeak with string payload.

#### `void pub_ThingSpeak(const char *channel, const char *apikey, const uint8_t *body, uint16_t len)`
Creates a PUBLISH packet formatted for ThingSpeak with binary payload.

### Subscription Methods

#### `void suscribir(const char* topic)`
Subscribes to a topic with QoS 0 (default).

#### `void suscribir(const char* topic, uint8_t qos)`
Subscribes to a topic with specified QoS level (0, 1, or 2).

#### `void suscribir(uint8_t* topic, uint8_t len, uint8_t qos)`
Subscribes to a topic with binary topic name and specified QoS.

#### `void desSuscribir(const char* topic)`
Unsubscribes from a topic.

### Other Methods

#### `void desconectar()`
Creates a DISCONNECT packet.

#### `void ping()`
Creates a PINGREQ packet to keep the connection alive.

### Properties

#### `uint8_t buffer[MQTT_MAX_PACKET_SIZE]`
Buffer containing the generated MQTT packet. Send this buffer over your network connection.

#### `uint16_t length`
Length of the current packet in the buffer.

## Constants

- `MQTT_MAX_PACKET_SIZE`: Maximum packet size (150 bytes)
- `MQTT_KEEPALIVE`: Default keep-alive interval (300 seconds)

## Examples

The library includes two example sketches:

1. **CloudMQTT**: Demonstrates basic MQTT operations (connect, publish, subscribe, ping, disconnect)
2. **ThingSpeak**: Shows how to publish data to ThingSpeak using the library

To run the examples:
1. Open Arduino IDE
2. Go to **File > Examples > FrameMQTT**
3. Select the desired example
4. Upload to your Arduino board
5. Open Serial Monitor to see the generated packets

## Notes

- This library generates MQTT protocol packets but does not handle the actual network communication. You need to send the `buffer` contents over your network connection (WiFi, Ethernet, GSM, etc.)
- The library is designed for resource-constrained devices and has a maximum packet size limit
- Client IDs are automatically generated if not specified (8-character alphanumeric string)
- The library supports MQTT protocol version 3.1.1

## Author

Glaros Anastasios (glrs)

Originally designed for Waspmote platform, adapted for Arduino.