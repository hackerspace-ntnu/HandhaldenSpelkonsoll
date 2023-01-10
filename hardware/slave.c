#include "comms.h"


/**
  * @brief Callback when data is received 
  * @param     mac  peer MAC address (who sent the data)
  * @param     incomingData  data received
  * @param     len  length of data
*/
void on_data_recv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  uint8_t* dataReceived;
  print_mac(mac);
  memcpy(&dataReceived, incomingData, sizeof(dataReceived)*6);

  printf("data Received: ");
  print_mac(dataReceived);
   
}

int main() {


  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    printf("Error initializing ESP-NOW");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }

  printf("%s", "initialized ESP-NOW");



  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(on_data_recv);

}