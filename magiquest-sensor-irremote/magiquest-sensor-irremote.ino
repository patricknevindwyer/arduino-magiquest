#include <IRremote.h>
#include <IRremoteInt.h>

#define MAGIQUEST_PERIOD     1150
#define MAGIQUEST_MARK_ZERO  280
#define MAGIQUEST_SPACE_ZERO 850
#define MAGIQUEST_MARK_ONE   580
#define MAGIQUEST_SPACE_ONE  600
#define MAGIQUEST_BITS 56

#define ERR 0
#define DECODED 1

#define MAGIQUEST 11

union magiquest {
  uint64_t llword;
  uint8_t    byte[8];
//  uint16_t   word[4];
  uint32_t  lword[2];
  struct {
    uint16_t magnitude;
    uint32_t wand_id;
    uint8_t  padding;
    uint8_t  scrap;
  } cmd ;
} ;
int recv_pin = A0;
IRrecv irrecv(recv_pin);

decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }

  Serial.println("Comms enabled - beginning sensing");

  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
 
    magiquest data;
    decodeMagiQuest(&results, &data);
    Serial.print("wand_id: ");
    Serial.println(results.value);
    Serial.print("magnitude: ");
    Serial.println(data.cmd.magnitude);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}


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
  mdata->cmd.magnitude = data.cmd.magnitude;
  return DECODED;
}
