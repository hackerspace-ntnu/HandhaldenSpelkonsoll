#include <Arduino.h>
#include <esp_now.h>
#include "WiFi.h"

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success 1" : "Delivery Fail 1");
  if (status ==0){
    Serial.println("Delivery Success 2");
  }
  else{
    Serial.println("Delivery fail 2");
  }

  Serial.println();
}       

void setup()
{

  Serial.begin(115200);

  Serial.println("Starting...\n");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }

  Serial.println("initialized ESP-NOW");


  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

   // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

   // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }            
}

int dataToSend = 1;
void loop()
{
    dataToSend++;

    // Send message via ESP-NOW (size of an int is 4 bytes on ESP32)
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &dataToSend, 4);
   
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    //Serial.println(WiFi.macAddress());    
    delay(1000);
}