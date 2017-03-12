#include <IRremote.h>
#include <IRremoteInt.h>

// MagiQuest protocol for IR
#define MAGIQUEST_PERIOD     1150
#define MAGIQUEST_MARK_ZERO  280
#define MAGIQUEST_SPACE_ZERO 850
#define MAGIQUEST_MARK_ONE   580
#define MAGIQUEST_SPACE_ONE  600
#define MAGIQUEST_BITS 56

// we use an alternate `decode_type` for our IRremote decoding
#define MAGIQUEST 11

// The magiquest payload is a bit different from the
// standard IRremote payload
union magiquest {
  uint64_t llword;
  uint8_t    byte[8];
  uint32_t  lword[2];
  struct {
    uint16_t magnitude;
    uint32_t wand_id;
    uint8_t  padding;
    uint8_t  scrap;
  } cmd ;
} ;

// hoist IRremote DEFs into our namespace for quick compatibility
#define ERR 0
#define DECODED 1

// Use analog 0 as our receiver
int recv_pin = A0;
IRrecv irrecv(recv_pin);

// Results as read from the IR sensor. We need to run this through
// the decodeMagiQuest function to get useful data.
decode_results results;
magiquest data;

void setup() {

  // Let's use comms for debug
  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }

  Serial.println("Comms enabled - beginning sensing");

  // turn on IR receiver
  irrecv.enableIRIn();
}

void loop() {
  
  // Wait and decode
  if (irrecv.decode(&results)) {
 
    // translate the bit stream into something we can use
    // to understand a MagiQuest wand
    decodeMagiQuest(&results, &data);
    Serial.print("wand_id: ");
    Serial.println(results.value);
    Serial.print("magnitude: ");
    Serial.println(data.cmd.magnitude);

    // keep receiving data 
    irrecv.resume(); 
  }

  // wait a bit, and then back to receiving and decoding
  delay(100);
}

/*
 * This decodeMagiQuest method cribbed from mpflaga (https://github.com/mpflaga/Arduino-IRremote) 
 * mode of the Arduino IRremote library. Excised and updated to work with current IRremote
 * library.
 * 
 * https://github.com/mpflaga/Arduino-IRremote/blob/master/IRremote.cpp
 * 
 */
int32_t  decodeMagiQuest(decode_results *results, magiquest *mdata) {
  magiquest data;
  data.llword = 0;

  int16_t offset = 1;
  uint16_t mark_;
  uint16_t space_;
  uint8_t multiple_;

  if (irparams.rawlen < 2 * MAGIQUEST_BITS) {
    return ERR;
  }

  while (offset + 1 < irparams.rawlen) {
    mark_ = results->rawbuf[offset];
    space_ = results->rawbuf[offset+1];
    multiple_ = space_ / mark_;
    // it is either 25% + 75% or 50% + 50%

    if (MATCH_MARK(space_ + mark_, MAGIQUEST_PERIOD)) {
      if (multiple_ > 1) {
        data.llword <<= 1;
      } else {
        data.llword = (data.llword << 1) | 1;
      }
    } else {
      return ERR;
    }
    offset++;
    offset++;
  }
  // Success
  results->bits = (offset + 1) / 2;
  if (results->bits < 12) {
    results->bits = 0;
    return ERR;
  }
  //results->magiquestMagnitude = data.cmd.magnitude;
  results->value = data.cmd.wand_id;
  results->decode_type = MAGIQUEST;

  // fill in our magiquest struct
  mdata->cmd.magnitude = data.cmd.magnitude;
  mdata->cmd.wand_id = data.cmd.wand_id;
  return DECODED;
}
