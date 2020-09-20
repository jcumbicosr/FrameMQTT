/*
 *
 * 
 *  WaspMQTTClient.cpp
 *
 *  The WaspMQTTClient library implements the MQTT protocol to work
 *  with the waspmote's 3G module. There were no such implementation
 *  for waspmote, although the MQTT protocol is a very good solution,
 *  especially for remote, low energy cost applications with unreliable
 *  network connection.
 *
 *  Version:		1.0
 *
 *  Design:		Glaros Anastasios (glrs)
 *
 *  Implementation:	Glaros Anastasios (glrs)
 *
*/


/*
 *  TODO: Implement unsubscribe function
*/

#include "FrameMQTT.h"

//version 2.1.2

const char* const alphanum ="0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

/* - - - - - - - CONSTRUCTORS - - - - - - - */

FrameMQTT::FrameMQTT() {
	_id_max = 23;
}


/* * * * * * * * * * * * * * * * * */
/* * *  MQTT CLIENT FUNCTIONS  * * */
/* * * * * * * * * * * * * * * * * */

/* - - - - - - CONNECT FUNCTIONS - - - - - - */

void FrameMQTT::conectar() 
{
	return conectar(NULL, NULL);
}

void FrameMQTT::conectar( const char *id) 
{
	return conectar(id, NULL, NULL);
}

void FrameMQTT::conectar( const char *user, const char *key )
{
	return conectar(user, key, MQTT_KEEPALIVE);
}

void FrameMQTT::conectar( const char *user, const char *key, uint16_t keepalive) 
{
	char clientID[9];

     
	// Generate ClientID
	for (int i = 0; i < 8; i++) {
		clientID[i] = alphanum[random(62)];
	}
	clientID[8]='\0';
	
	return conectar(clientID, user, key, keepalive);
}

void FrameMQTT::conectar(const char *id, const char *user, const char *key, uint16_t keepalive) 
{
	
	uint8_t i = 0;
	uint8_t k = 0;
	uint8_t len_total = 0;
	uint8_t id_length = strlen( id );
	uint8_t flags = 2; //bit 1 -> clean session
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	//longitud de ID
	if( id_length > _id_max)
	{	
		id_length = 23;
	}
	
	//Longitud si existe User y Password
	if(user != NULL)
	{
		k = strlen(user) + 2;  		// +2 bytes para longitud de 'user' 
		flags = flags | 0x80;  		// bit 7 -> User flag
		if(key != NULL)
		{
			k += strlen(key) + 2;	// +2 bytes para longitud de 'password' 
			flags = flags | 0x40;	// bit 6 -> Password flag
		}
	}
	buffer[length] = MQTTCONNECT;
	length++;
	
	len_total = 12 + id_length + k;		//Longitud total de trama
	i = len_total/128;
	if(i > 0)
	{
		buffer[length] = (len_total % 128) | 0x80;
		length++;
		buffer[length] = i;
		length++;
	}
	else
	{
		buffer[length] = len_total;
		length++;
	}
	
	
	buffer[length] = 0;
	length++;
	buffer[length] = 4;
	length++;
	buffer[length] = 'M';
	length++;
	buffer[length] = 'Q';
	length++;
	buffer[length] = 'T';
	length++;
	buffer[length] = 'T';
	length++;
	buffer[length] = 4;
	length++;
	buffer[length] = flags;		//Connect flags
	length++;
	buffer[length] = ((keepalive) >> 8);
	length++;
	buffer[length] = ((keepalive) & 0xFF);
	length++;
	
	buffer[length] = 0;
	length++;
	buffer[length] = id_length;
	length++;
	
	// Añadir client ID
	for(i = 0; i < id_length ; i++)
	{
		buffer[length] = id[i];
		length++;
	}
	
	// Añadir User y Password
	if(user != NULL)
	{
		
		buffer[length] = 0;
		length++;
		buffer[length] = strlen(user);
		length++;
		for(i = 0; i < strlen(user) ; i++)
		{
			buffer[length] = user[i];
			length++;
		}
		if(key != NULL)
		{
			
			buffer[length] = 0;
			length++;
			buffer[length] = strlen(key);
			length++;
			for(i = 0; i < strlen(key) ; i++)
			{
				buffer[length] = key[i];
				length++;
			}
			
		}	
	}

}

void FrameMQTT::pub_ThingSpeak(const char *channel, const char *apikey, const char *body){
	return pub_ThingSpeak(channel, apikey, (uint8_t*)body, strlen(body));

}

void FrameMQTT::pub_ThingSpeak(const char *channel, const char *apikey, const uint8_t *body, uint16_t len)
{
	
	uint8_t i = 0;
	uint16_t topic_length = 0;
	uint16_t total_length = 0;
	uint8_t x = 0;
	char topic[50];
	
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	snprintf(topic, sizeof(topic),"channels/%s/publish/%s", channel, apikey);
	topic_length = strlen( topic );
	
	total_length = 2 + topic_length + len;
	
	buffer[0] = MQTTPUBLISH;
	x = total_length/128;
	if (x > 0){
		length++;
		buffer[length] = (total_length % 128) | 0x80;
		length++;
		buffer[length] = x;
	}else{
		length++;
		buffer[length] = total_length;
	}
	
	length++;
	buffer[length] = 0;
	length++;
	buffer[length] = topic_length;
	length++;
	
	//topic
	for (i = 0; i < topic_length ; i++){
		buffer[length] = topic[i];
		length++;
	}
	
	//body
	for (i = 0; i < len ; i++){
		buffer[length] = body[i];
		length++;
	}
}

void FrameMQTT::publicar(const char* topic, const char* body)
{
	uint8_t x = 0;
	uint8_t len_topic = strlen(topic);
	uint16_t len_body = strlen(body);
	uint16_t len_total = 2 + len_topic + len_body;
	
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	buffer[length] = MQTTPUBLISH;
	length++;
	x = len_total/128;
	if (x > 0)
	{	
		buffer[length] = (len_total % 128) | 0x80;
		length++;
		buffer[length] = x;
		length++;
	}
	else
	{
		buffer[length] = len_total;
		length++;
	}
	
	buffer[length] = 0;
	length++;
	buffer[length] = len_topic;
	length++;
	
	//topic
	for (x = 0; x < len_topic ; x++){
		buffer[length] = topic[x];
		length++;
	}
	
	//body
	for (x = 0; x < len_body ; x++){
		buffer[length] = body[x];
		length++;
	}
	
}

void FrameMQTT::desconectar(void) 
{
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	buffer[0] = MQTTDISCONNECT;
	buffer[1] = 0x00;
	length = 2;

}

void FrameMQTT::suscribir(const char* topic){
	return suscribir((uint8_t*)topic, strlen(topic), 0);
}

void FrameMQTT::suscribir(const char* topic, uint8_t qos){
	return suscribir((uint8_t*)topic, strlen(topic), qos);
}

void FrameMQTT::suscribir(uint8_t* topic, uint8_t len, uint8_t qos){
	uint8_t x = 0;
	//2 header + 2 len Topic + topic + 1 Requested QoS
	uint8_t	len_total = 5 + len;
	
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	if(qos > 1)
		return;
	
	buffer[length] = MQTTSUBSCRIBE | MQTTQOS1_HEADER_MASK; //1000 0010
	length++;
	//remaining length
	buffer[length] = len_total;
	length++;
	//Packet Identifier
	buffer[length] = 0;
	length++;
	buffer[length] = 1;
	length++;
	//len topic
	buffer[length] = 0;
	length++;
	buffer[length] = len;
	length++;
	//topic
	for (x = 0; x < len ; x++){
		buffer[length] = topic[x];
		length++;
	}
	
	//nivel qos
	buffer[length] = qos;
	length++;
	
}

void FrameMQTT::desSuscribir(const char* topic){
	uint8_t x=0;
	uint8_t len_topic = strlen(topic);
	// 2 header + 2 len Topic + topic
	uint8_t	len_total = 4 + len_topic;
	
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	buffer[length] = MQTTUNSUBSCRIBE | MQTTQOS1_HEADER_MASK;  // 1010 0010
	length++;
	// remaining length
	buffer[length] = len_total;
	length++;
	// Packet Identifier
	buffer[length] = 0;
	length++;
	buffer[length] = 1;
	length++;
	// len topic
	buffer[length] = 0;
	length++;
	buffer[length] = len_topic;
	length++;
	//topic
	for (x = 0; x < len_topic ; x++){
		buffer[length] = topic[x];
		length++;
	}
	
}

void FrameMQTT::ping(){
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	// init counter
	length=0;
	
	buffer[0] = MQTTPINGREQ;	// 1100 0000
	buffer[1] = 0;				// remaining length
	length = 2;
}


/* 
void FrameMQTT::showMQTT(void) 
{
	
	for(int i = 0; i <31 ; i++)
	{
		USB.print( '=');
	}
	USB.println();
	
	USB.print(F("Length: "));
	USB.println(length);
	
	USB.print(F("Message (STR): "));
	USB.println(buffer,length);
	for(int i = 0; i <31 ; i++)
	{
		USB.print( '=');
	}
	USB.println();
} 
*/

FrameMQTT MQTT = FrameMQTT();