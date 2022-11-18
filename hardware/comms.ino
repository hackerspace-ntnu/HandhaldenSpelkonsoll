#include <esp_now.h>
#include <WiFi.h>


uint8_t dummy_address[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8_t* my_mac_address;
uint8_t* other_mac_address;

bool CONNECTION_MADE = false;

/**
 * @brief Add new peer
 * @param mac peer MAC address
*/
void add_new_peer(const uint8_t* mac) {
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
       
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        for(;;) delay(1); 
    }
}

/**
 * @brief Print to serial monitor (in HEX)
 * @param mac MAC address
*/
void serial_print_mac(const uint8_t* mac) {
  for (int i=0; i<6; i++) {
    Serial.print(mac[i], HEX);
    if (i<5) Serial.print(":");
  }
}

/** 
 * @brief check whether the given data is equal
 * @param a1 data to compare
 * @param a2 data to compare with
 * @return true if the given data is equal, false otherwise 
*/
bool compare_data(const uint8_t* a1, const uint8_t* a2,  int len) {
    for (int i=0; i<len; i++) {
        if (a1[i] != a2[i]) {
          return false;
        }
    }
    return true;
}   

/**
  * @brief Callback when data is sent 
  * @param     mac  peer MAC address (who sent the data)
  * @param     status Status of sending ESPNOW data
*/
void on_data_sent(const uint8_t* mac, esp_now_send_status_t status) {
  Serial.println("on_data_sent");
  serial_print_mac(mac);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success 1" : "Delivery Fail 1");
  if (status == 0) {
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
void on_data_recv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  Serial.println("on_data_recv");
  serial_print_mac(mac);
 
  if (!compare_data(my_mac_address, incomingData, len)) {
    Serial.println("Received a new mac address");
    memcpy(other_mac_address, incomingData, len);
    
    add_new_peer(other_mac_address);

    CONNECTION_MADE = true;

    //delete the dummy peer
    esp_now_del_peer(dummy_address);
  }

  int data_recv;
  memcpy(&data_recv, incomingData, len);
  Serial.print("Received: ");
  Serial.println(data_recv);
  Serial.println("-------------------------------");    
}

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.macAddress(my_mac_address);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    for(;;) delay(1);
  }

  // Register callbacks for sending and receiveing data
  esp_now_register_send_cb(on_data_sent);
  esp_now_register_recv_cb(on_data_recv);       

  add_new_peer(dummy_address);     
}

void loop() {
    // Send message via ESP-NOW 
    esp_err_t result;
    if (!CONNECTION_MADE) {
      // broadcast my mac address for others to receive
        result = esp_now_send(dummy_address, my_mac_address, sizeof(my_mac_address)*6);
    } else {
        result = esp_now_send(other_mac_address, (uint8_t*)42, sizeof(int));
    }
   
    Serial.println(esp_err_to_name(result));
    delay(3000);
}