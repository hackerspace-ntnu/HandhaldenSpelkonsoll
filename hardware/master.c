#include "comms.h"

uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t* masterMACAddress;
uint8_t* slaveMACAddress;


/**
  * @brief Callback when data is sent 
  * @param     mac  peer MAC address (who sent the data)
  * @param     status Status of sending ESPNOW data
*/
void on_data_sent(const uint8_t *mac, esp_now_send_status_t status) {
  printf("%s", "OnDataSent");
  print_mac(mac);
  printf("%s", (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success 1" : "Delivery Fail 1"));
  if (status == 0) {
    printf("%s", "Delivery Success 2");
  }
  else {
    printf("%s", "Delivery fail 2");
  }
}  
/**
  * @brief Callback when data is received 
  * @param     mac  peer MAC address (who sent the data)
  * @param     incomingData  data received
  * @param     len  length of data
*/
void on_data_recv(const uint8_t *mac, const uint8_t *incomingData, int len) {
   println("OnDataRecv");
   _print_MAC(mac);
  uint8_t dataReceived;
  memcpy(&dataReceived, incomingData, len);

   print("Data Received: ");
   println(dataReceived);   
}




int main(){
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
     printf("%s", "Error initializing ESP-NOW");
  }

   printf("%s", "initialized ESP-NOW");


  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(on_data_sent);

   // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

   // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
     printf("Failed to add peer");
  }     

  esp_now_register_recv_cb(on_data_recv);       
    // Send message via ESP-NOW 
    esp_err_t result = esp_now_send(broadcastAddress, masterMACAddress, sizeof(masterMACAddress)*6);

    printf("%s", esp_err_to_name(result));
}