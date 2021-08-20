#ifndef State_H
#define State_H
#include <Arduino.h>
class State
{
  public:
    int ypr[3];// y p r
    int real[3];// x y z
    int world[3];// x y z
    int quat[4];// w x y z
    int euler[3];// x y z

    bool mute_ypr[3] = {false, false, false};// y p r
    bool mute_real[3] = {true, true, true};// x y z
    bool mute_world[3] = {true, true, true};// x y z
    bool mute_euler[3] = {true, true, true};// x y z
    bool mute_quat[4] = {true, true, true, true};// w x y z
  
    int cc_ypr[3] = {3,4,5};// y p r
    int cc_real[3] = {6,7,8};// x y z
    int cc_world[3] = {9,10,11};// x y z
    int cc_euler[3] = {12,13,14};// x y z
    int cc_quat[4] = {15,16,17,18};// w x y z

    bool op_alwaysOn = false;

    bool bufferInit = false;
  
    bool toggle(String type, int index){
      if(type == "ypr"){
        mute_ypr[index]=!mute_ypr[index];
        return mute_ypr[index];
      }
      if(type == "real"){
        mute_real[index]=!mute_real[index];
        return mute_real[index];
      }
      if(type == "world"){
        mute_world[index]=!mute_world[index];
        return mute_world[index];
      }
      if(type == "quat"){
        mute_quat[index]=!mute_quat[index];
        return mute_quat[index];
      }
      if(type == "euler"){
        mute_euler[index]=!mute_euler[index];
        return mute_euler[index];
      }
    }
    void set(int type, int index, bool value){
      switch(type){
        case 0:
          mute_ypr[index]=value;
          Serial.print("Set YPR  ");
          Serial.print(index);
          Serial.print(" to ");
          Serial.println(bool(value));
          break;
        case 1:
          mute_real[index]=value;
          Serial.print("Set REAL ");
          Serial.print(index);
          Serial.print(" to ");
          Serial.println(bool(value));
          break;
        case 2:
          mute_world[index]=value;
          break;
        case 3:
          mute_euler[index]=value;
          break;
      }
    }
    // void set(String type, int index, bool value){
    //   if(type == "ypr"){
    //     mute_ypr[index]=value;
    //   }
    //   if(type == "real"){
    //     mute_real[index]=value;
    //   }
    //   if(type == "world"){
    //     mute_world[index]=value;
    //   }
    //   if(type == "quat"){
    //     mute_quat[index]=value;
    //   }
    //   if(type == "euler"){
    //     mute_euler[index]=value;
    //   }
    // }
    // void setCC(String type, int index, bool value){
    //   if(type == "ypr"){
    //     cc_ypr[index]=value;
    //   }
    //   if(type == "real"){
    //     cc_real[index]=value;
    //   }
    //   if(type == "world"){
    //     cc_world[index]=value;
    //   }
    //   if(type == "quat"){
    //     cc_quat[index]=value;
    //   }
    //   if(type == "euler"){
    //     cc_euler[index]=value;
    //   }
    // }
};
#endif