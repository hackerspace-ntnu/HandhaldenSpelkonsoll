#include <esp_now.h>
#include <WiFi.h>


uint8_t broadcast_address[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t* my_mac_address;
uint8_t* other_mac_address;

bool CONNECTION_MADE = false;

void serialPrintMAC(const uint8_t *mac) {
  for (int i=0; i<6; i++) {
    Serial.print(mac[i], HEX);
    if (i<5) Serial.print(":");
  }
}

bool check_mac(const uint8_t* mac, int len) {
    // check if the received mac is not my own mac
    for (int i=0; i<len; i++) {
        if (my_mac_address[i] != mac[i]) {
            return true;
        }
    }
    return false;
}   

/**
  * @brief Callback when data is sent 
  * @param     mac  peer MAC address (who sent the data)
  * @param     status Status of sending ESPNOW data
*/
void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println("on_data_sent");
  serialPrintMAC(mac_addr);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success 1" : "Delivery Fail 1");
  if (status ==0) {
    Serial.println("Delivery Success 2");
  }
  else {
    Serial.println("Delivery fail 2");
  }
  Serial.println();
}  
/**
  * @brief Callback when data is received 
  * @param     mac  peer MAC address (who sent the data)
  * @param     incomingData  data received
  * @param     len  length of data
*/
void on_data_recv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  Serial.println("on_data_recv");
  serialPrintMAC(mac);
 
  if (check_mac(incomingData, len)) { // the received mac is not mine
    memcpy(other_mac_address, incomingData, len);

    // add peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, other_mac_address, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
       
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        for(;;) {      delay(1);  } // do not initialize wait forever
    }

  }

  int data_recv;
  memcpy(&data_recv, incomingData, len);
  Serial.print("Received: ");
  Serial.println(data_recv);

  Serial.println();    
}

void handle_error(esp_err_t error) {
    switch(error) {
        case ESP_OK:
            Serial.println("All good");
            break;
        case ESP_ERR_ESPNOW_NOT_INIT:
            Serial.println("esp-now not initialized!");
            break;
        case ESP_ERR_ESPNOW_FULL:
            Serial.println("peer list is full!");
            break;
        case ESP_ERR_ESPNOW_ARG:
            Serial.println("invalid argument!");
            break;
        case ESP_ERR_ESPNOW_NO_MEM:
            Serial.println("out of memory!");
            break;
        case ESP_ERR_ESPNOW_EXIST:
            Serial.println("peer has existed, whatever that means");
            break;
        default:
            Serial.println("error not recognized!");
    }
}

void setup() {

  Serial.begin(115200);

  Serial.println("Starting...\n");

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.macAddress(my_mac_address);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }

  Serial.println("initialized ESP-NOW");


  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(on_data_sent);

   // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcast_address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

   // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    for(;;) {      delay(1);  } // do not initialize wait forever
  }     

  esp_now_register_recv_cb(on_data_recv);       
}

void loop() {

    // Send message via ESP-NOW 
    esp_err_t result;
    if (!CONNECTION_MADE) {
        result = esp_now_send(broadcast_address, my_mac_address, sizeof(my_mac_address)*6);
    } else {
        result = esp_now_send(other_mac_address, (uint8_t*)42, sizeof(int));
    }
   
    handle_error(result);
    delay(3000);
}