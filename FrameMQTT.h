/*
 *
 * 
 *  WaspMQTTClient.h
 *
 *  The WaspMQTTClient library implements the MQTT protocol to work
 *  with the waspmote's 3G module. There were no such implementation
 *  for waspmote, although the MQTT protocol is a very good solution,
 *  especially for remote, low energy cost applications with unreliable
 *  network connection.
 *
 *  Version:		2.0.0
 *
 *  Design:		Glaros Anastasios (glrs)
 *
 *  Implementation:	Glaros Anastasios (glrs)
 *
 */


#ifndef FrameMQTT_h
#define FrameMQTT_h

//includes
#include "Arduino.h"


/** DEFINE MAX SIZES **/
#define MQTT_MAX_PACKET_SIZE    150     // Maximum packet size
//#define MQTT_MAX_TOPIC_SIZE     150     // Maximum topic size
//#define MQTT_MAX_MESSAGE_SIZE   150     // Maximum message size


/** DEFINE KEEP ALIVE VALUE **/
#define MQTT_KEEPALIVE    300    // keepAlive interval in Seconds


/** DEFINED VALUES - MESSAGE TYPE 
#define MQTT_Reserved     0  // Reserved
#define MQTT_CONNECT      16  // Client request to connect to Server
#define MQTT_CONNACK      32  // Connect Acknowledgment
#define MQTT_PUBLISH      48  // Publish message
#define MQTT_PUBACK       4 << 4  // Publish Acknowledgment
#define MQTT_PUBREC       5 << 4  // Publish Received (assured delivery part 1)
#define MQTT_PUBREL       6 << 4  // Publish Release (assured delivery part 2)
#define MQTT_PUBCOMP      7 << 4  // Publish Complete (assured delivery part 3)
#define MQTT_SUBSCRIBE    8 << 4  // Client Subscribe request
#define MQTT_SUBACK       9 << 4  // Subscribe Acknowledgment
#define MQTT_UNSUBSCRIBE  10 << 4  // Client Unsubscribe request
#define MQTT_UNSUBACK     11 << 4  // Unsubscribe Acknowledgment
#define MQTT_PINGREQ      12 << 4  // PING Request
#define MQTT_PINGRESP     13 << 4  // PING Response
#define MQTT_DISCONNECT   224  // Client is Disconnecting
#define MQTT_Reserved     15 << 4  // Reserved

**/

/** DEFINED VALUES - QoS 
#define MQTT_QOS0    0 << 1    // At most once (Fire and Forget)
#define MQTT_QOS1    1 << 1    // At least once (Acknowledged delivery)
#define MQTT_QOS2    2 << 1    // Exactly once (Assured delivery)

**/


class FrameMQTT {
private:
	uint8_t _id_max;
  
public:

	FrameMQTT();
	
	uint8_t  buffer[MQTT_MAX_PACKET_SIZE];
	uint16_t length;
	
	void conectar();
	
	void conectar( const char *id);
	
	void conectar( const char *user, const char *key);
	
	void conectar( const char *id, const char *user, const char *key);
	
	void pub_ThingSpeak(const char *channel, const char *apikey, const char *body);
	
	void pub_ThingSpeak(const char *channel, const char *apikey, const uint8_t *body, uint16_t len);
	
	void publicar(const char* topic, const char* body);
	
	void desconectar(void);
	
	void suscribir(const char* topic);
	
	void suscribir(const char* topic, uint8_t qos);
	
	void suscribir( uint8_t* topic, uint8_t len, uint8_t qos);
	
	void desSuscribir(const char* topic);
	
	void ping();
	
	//void showMQTT(void);
 
};

extern FrameMQTT MQTT;
#endif
  
  
  
  
  
  
  
  
  
  
