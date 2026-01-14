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
#define MQTT_KEEPALIVE    (uint16_t)300    // keepAlive interval in Seconds

/** DEFINED VALUES - MESSAGE TYPE **/
#define MQTTCONNECT     1 << 4  // Client request to connect to Server
#define MQTTCONNACK     2 << 4  // Connect Acknowledgment
#define MQTTPUBLISH     3 << 4  // Publish message
#define MQTTPUBACK      4 << 4  // Publish Acknowledgment
#define MQTTPUBREC      5 << 4  // Publish Received (assured delivery part 1)
#define MQTTPUBREL      6 << 4  // Publish Release (assured delivery part 2)
#define MQTTPUBCOMP     7 << 4  // Publish Complete (assured delivery part 3)
#define MQTTSUBSCRIBE   8 << 4  // Client Subscribe request
#define MQTTSUBACK      9 << 4  // Subscribe Acknowledgment
#define MQTTUNSUBSCRIBE 10 << 4 // Client Unsubscribe request
#define MQTTUNSUBACK    11 << 4 // Unsubscribe Acknowledgment
#define MQTTPINGREQ     12 << 4 // PING Request
#define MQTTPINGRESP    13 << 4 // PING Response
#define MQTTDISCONNECT  14 << 4 // Client is Disconnecting
#define MQTTReserved    15 << 4 // Reserved

#define MQTTQOS0_HEADER_MASK        (0 << 1)
#define MQTTQOS1_HEADER_MASK        (1 << 1)
#define MQTTQOS2_HEADER_MASK        (2 << 1)

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
	
	void conectar( const char *user, const char *key, uint16_t keepalive);
	
	void conectar( const char *id, const char *user, const char *key, uint16_t keepalive);
	
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
  
  
  
  
  
  
  
  
  
  
