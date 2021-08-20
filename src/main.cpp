#include <Arduino.h>
#include "setupMPU.h"

#include "State.h"

#define BTN 17

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

State st;

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  Serial.println("START");
  setupMPU();
  pinMode(BTN, INPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

int norm180(float val){
  val = (val * 180/M_PI) + 180;
  float factor = 127.00/360.00;
  val = val * factor;
  return int(val);
}

int normAcc(int val, float maxG=0.2){
  // Returns avg value around 64
  // Negative acc approaches 0
  // Positive approaches 127
  int cap = maxG * 8192;//8192=1G
  if(val > cap ){
    val = cap ;
  }
  if(val < -cap ){
    val = -cap ;
  }
  float factor = (127.00/2)/cap;
  val = (127/2)+(val * factor);
  return val;
}

String mode = "test";
String modes[] = {
  "y","p","r","a","test"
};
int modesLen = 5;
int modeIndex = 0;

//int crx = 0;

void readSerial(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    String read = Serial.readString();
    Serial.println(read);
    int type = int(read.charAt(0)-48);
    int index = int(read.charAt(1)-48);
    bool value = bool(read.charAt(2)-48);
    Serial.println(type);
    Serial.println(index);
    Serial.println(value);//111
    st.set(type, index, value);
    // if(read == "set_ypr_on"){
    //   st.mute_ypr[0] = true;
    //   st.mute_ypr[1] = true;
    //   st.mute_ypr[2] = true;
    // }
    // if(read == "set_ypr_off"){
    //   st.mute_ypr[0] = false;
    //   st.mute_ypr[1] = false;
    //   st.mute_ypr[2] = false;
    // }
    // if(read == "toggle_ypr_y"){
    //   bool res = st.toggle("ypr", 0);
    //   Serial.println(res);
    // }
    // if(read == "toggle_ypr_p"){
    //   bool res = st.toggle("ypr", 1);
    //   Serial.println(res);
    // }
    // if(read == "toggle_ypr_r"){
    //   bool res = st.toggle("ypr", 2);
    //   Serial.println(res);
    // }

    // if(read == "toggle_real_x"){
    //   bool res = st.toggle("real", 0);
    //   Serial.println(res);
    // }
    // if(read == "toggle_real_y"){
    //   bool res = st.toggle("real", 1);
    //   Serial.println(res);
    // }
    // if(read == "toggle_real_z"){
    //   bool res = st.toggle("real", 2);
    //   Serial.println(res);
    // }
  }
}

void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    readSerial();
    // read a packet from FIFO
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet
      if(st.bufferInit == false){
        Serial.println("Buffer Initialized");
        st.bufferInit = true;
      }
      mpuRead();

      //
      /*
      y
      p
      r
      rx
      ry
      rz
      wx
      wy
      wz
      qw
      qx
      qy
      qz
      e0
      e1
      e2
      */
      //
      // int y = norm180(ypr[0]);
      // int p = norm180(ypr[1]);
      // int r = norm180(ypr[2]);
      st.ypr[0] = norm180(ypr[0]);
      st.ypr[1] = norm180(ypr[1]);
      st.ypr[2] = norm180(ypr[2]);
      //Serial.println(ypr[2]);
      
      // int rx = normAcc(aaReal.x);
      // int ry = normAcc(aaReal.y);
      // int rz = normAcc(aaReal.z);

      st.real[0] = normAcc(aaReal.x);
      st.real[1] = normAcc(aaReal.y);
      st.real[2] = normAcc(aaReal.z);
      
      // float wx = normAcc(aaWorld.x);
      // float wy = normAcc(aaWorld.y);
      // float wz = normAcc(aaWorld.z);

      st.world[0] = normAcc(aaWorld.x);
      st.world[1] = normAcc(aaWorld.y);
      st.world[2] = normAcc(aaWorld.z);

      int e0 = norm180(euler[0]);
      int e1 = norm180(euler[1]);
      int e2 = norm180(euler[2]);

      float qw = q.w;
      float qx = q.x;
      float qy = q.y;
      float qz = q.z;
      
      if(digitalRead(BTN)==1 || st.op_alwaysOn){

        if(st.mute_ypr[0]==false){
          usbMIDI.sendControlChange(st.cc_ypr[0], st.ypr[0], 1);
        }
        if(st.mute_ypr[1]==false){
          usbMIDI.sendControlChange(st.cc_ypr[1], st.ypr[1], 1);
        }
        if(st.mute_ypr[2]==false){
          Serial.println(st.ypr[2]);
          usbMIDI.sendControlChange(st.cc_ypr[2], st.ypr[2], 1);
        }

        if(st.mute_real[0]==false){
          usbMIDI.sendControlChange(st.cc_real[0], st.real[0], 1);
        }
        if(st.mute_real[1]==false){
          usbMIDI.sendControlChange(st.cc_real[1], st.real[1], 1);
        }
        if(st.mute_real[2]==false){
          usbMIDI.sendControlChange(st.cc_real[2], st.real[2], 1);
        }
      }else{
        //Serial.println("NO PRESS");
      }
          
          
      // blink LED to indicate activity
      blinkState = !blinkState;
      digitalWrite(LED_PIN, blinkState);
      delay(25);
  }else{
    if(st.bufferInit){
      Serial.println("WAITING FOR BUFFER");
    }
  }
}