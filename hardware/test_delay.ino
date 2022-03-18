#include "painlessMesh.h"
#include "painlessmesh/ota.hpp"
#include "plugin/performance.hpp"
// https://github.com/arkhipenko/Dictionary

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

std::list<uint32_t> nodes;
bool calc_delay = false;

//std::list<uint32_t> nodesId_delay_avg;
//std::list<uint32_t> nodesId_delay_N;
//std::list<uint32_t> nodesId_list;
//int nodesId_inc=0




Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

uint32_t lastTime = 0;

Task taskSendMessage(500 , TASK_FOREVER, &sendMessage);

void sendMessage() {
  String msg = String(mesh.getNodeTime());
  //msg += mesh.getNodeId();
  //msg += " with node time: ";
  //msg += String(mesh.getNodeTime());
  mesh.sendBroadcast(msg);

  //if (calc_delay) {
  //  SimpleList<uint32_t>::iterator node = nodes.begin();
  //  while (node != nodes.end()) {
  //    mesh.startDelayMeas(*node);
  //    node++;
  //  }
  //  calc_delay = false;
  //}

  //Serial.printf("Mesh stability: %u\n", mesh.stability);
  //Serial.printf("Sending message: %s with delay %u\n", msg.c_str(), mesh.getNodeTime() - lastTime);
  //lastTime = mesh.getNodeTime();

  taskSendMessage.setInterval(500);
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  //atoi()

  //int nodeId__delay_index=nodes.IndexOf();
  //nodesId_delay_N[nodeId__delay_index]
  //if 

  uint32_t mesh_delay=atoi(msg.c_str());
  mesh_delay=mesh.getNodeTime()-mesh_delay;
  
  //Serial.printf("Received message: %s at nodetime %u\n", msg.c_str(), mesh.getNodeTime());
  Serial.printf("Received message: %u with delay %u\n", from, mesh_delay);
  //Serial.printf("At nodetime: %u", String(mesh.getNodeTime()));
}



void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  Serial.printf("--> Topology, %s\n", mesh.subConnectionJson(true).c_str());

}

void changedConnectionCallback() {
  nodes = mesh.getNodeList();

  Serial.printf("Changed connections\n");
  Serial.printf("Num nodes: %d\n", nodes.size());
  Serial.printf("Connection list:");

  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
  //calc_delay = true;


  Serial.printf("All known nodes: ", mesh.getNodeList());
  Serial.printf("Topology: ", mesh.subConnectionJson()); 
  
}

void droppedConnectionCallback(uint32_t nodeId) {
  Serial.printf("Dropped Connection %u\n", nodeId);
};

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void nodeDelayCallback(uint32_t nodeId, int32_t delay) {
  Serial.println("Delay from: " + String(nodeId)+  +" , with delay: " + String(delay));
}



void setup() {
  Serial.begin(115200);

  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes(CONNECTION);  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  //mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  //mesh.onDroppedConnection(&droppedConnectionCallback); // la til denne
  //mesh.onNodeDelayReceived(&nodeDelayCallback); // la til denne


  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
