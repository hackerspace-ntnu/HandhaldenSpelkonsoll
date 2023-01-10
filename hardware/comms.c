#include "comms.h"


/**
 * @brief Print to   monitor (in HEX)
 * @param mac MAC address
*/
void print_mac(const uint8_t* mac) {
  for (int i=0; i<6; i++) {
    printf("%x", mac[i]);
    if (i<5) printf("%c", ":");
  }
}


/**
 * @brief Add new peer
 * @param mac peer MAC address
*/
void add_new_peer(const uint8_t* mac) {
    esp_now_peer_info_t peerInfo = {};
    print_mac(mac);
    memcpy(peerInfo.peer_addr, mac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
       
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        printf("%s", "Failed to add peer");
    }
}


/** 
 * @brief check whether the given data is equal
 * @param a1 data
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
  printf("%s", "on_data_sent");
  printf("%s", "Sent from: ");
   _print_mac(mac);
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
void on_data_recv(const uint8_t* mac, const uint8_t* incomingData, int len) {
  printf("%s", "on_data_recv");
  printf("%s", "Sent from: ");
   _print_mac(mac);

  if (CONNECTION_MADE){
    int data_recv;
    memcpy(&data_recv, incomingData, len);
    print("Received: ");
    printf("%i", data_recv);
    printf("%s", "-------------------------------");   
    return;
  } 
  
  if (!compare_data(my_mac_address, incomingData, len)) {
    printf("%s", "Received a new mac address");
    memcpy(&other_mac_address, incomingData, len);
    printf("%s", "Got: ");
    print_mac(other_mac_address);
    add_new_peer(other_mac_address);

    CONNECTION_MADE = true;
    printf("%s", "Deleting dummy peer");
    esp_now_del_peer(dummy_address);
  }  
}


  

int main() {

    esp_wifi_get_mac(ESP_IF_WIFI_STA, my_mac_address);
    printf("%s", "my mac address");
    print_mac(my_mac_address);

    if (esp_now_init() != ESP_OK) {
        printf("%s", "Error initializing ESP-NOW");
    }

    // Register callbacks for sending and receiveing data
    esp_now_register_send_cb(on_data_sent);
    printf("%s", "adding dummy peer");
    add_new_peer(dummy_address);     
    esp_now_register_recv_cb(on_data_recv);       


    // Send message via ESP-NOW 
    int d = 42;
    esp_err_t result;
    if (!CONNECTION_MADE) {
        printf("%s", "sending my MAC address");
        result = esp_now_send(dummy_address, my_mac_address, sizeof(my_mac_address)*6);
    } else {
        printf("%s", "sending data");
        result = esp_now_send(other_mac_address, (uint8_t*)&d, sizeof(d));
    }
   
    printf("%s", esp_err_to_name(result));
}
