#ifndef _ROS_vp_x10_voice_X10_h
#define _ROS_vp_x10_voice_X10_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace vp_x10_voice
{

  class X10 : public ros::Msg
  {
    public:
      int16_t command1;
      int16_t command2;
      int16_t repeatTime;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_command1;
      u_command1.real = this->command1;
      *(outbuffer + offset + 0) = (u_command1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_command1.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command1);
      union {
        int16_t real;
        uint16_t base;
      } u_command2;
      u_command2.real = this->command2;
      *(outbuffer + offset + 0) = (u_command2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_command2.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command2);
      union {
        int16_t real;
        uint16_t base;
      } u_repeatTime;
      u_repeatTime.real = this->repeatTime;
      *(outbuffer + offset + 0) = (u_repeatTime.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_repeatTime.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->repeatTime);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_command1;
      u_command1.base = 0;
      u_command1.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_command1.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->command1 = u_command1.real;
      offset += sizeof(this->command1);
      union {
        int16_t real;
        uint16_t base;
      } u_command2;
      u_command2.base = 0;
      u_command2.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_command2.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->command2 = u_command2.real;
      offset += sizeof(this->command2);
      union {
        int16_t real;
        uint16_t base;
      } u_repeatTime;
      u_repeatTime.base = 0;
      u_repeatTime.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_repeatTime.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->repeatTime = u_repeatTime.real;
      offset += sizeof(this->repeatTime);
     return offset;
    }

    const char * getType(){ return "vp_x10_voice/X10"; };
    const char * getMD5(){ return "412ad5f78068f9ac88fb2866fbc7c142"; };

  };

}
#endif