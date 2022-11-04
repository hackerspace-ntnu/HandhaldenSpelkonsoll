#include <esp_now.h>
#include <WiFi.h>


uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

String masterMACAddress = "";
String slaveMACAddress = "";

void serialPrintMAC(const uint8_t *mac) {
  Serial.println("MAC");
  for (int i=0; i<6; i++) {
    Serial.print(mac[i], HEX);
    if (i<5) Serial.print(":");
  }
}


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  serialPrintMAC(mac_addr);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success 1" : "Delivery Fail 1");
  if (status ==0){
    Serial.println("Delivery Success 2");
  }
  else{
    Serial.println("Delivery fail 2");
  }

  Serial.println();
}  

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  serialPrintMAC(mac);
  String dataReceived;
  memcpy(&dataReceived, incomingData, sizeof(dataReceived));

  Serial.print("Data Received: ");
  Serial.println(dataReceived);

  Serial.println();    
}

void handleError(esp_err_t error) {
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
  masterMACAddress = WiFi.macAddress();
  Serial.print("Master MAC Address: ");
  Serial.println(masterMACAddress);

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

  esp_now_register_recv_cb(OnDataRecv);       
}

String dataToSend = WiFi.macAddress();
void loop() {

    // Send message via ESP-NOW (size of an int is 4 bytes on ESP32)
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &dataToSend, sizeof(dataToSend));
   
    handleError(result);
    delay(3000);
}