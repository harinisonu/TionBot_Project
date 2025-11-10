#ifndef EMOTES_H
#define EMOTES_H
#include "TionBot.h"

// Declare all emote bitmaps as extern
extern const unsigned char PROGMEM emotes0[];
extern const unsigned char PROGMEM emotes1[];
extern const unsigned char PROGMEM emotes2[];
extern const unsigned char PROGMEM emotes3[];
extern const unsigned char PROGMEM emotes4[];
extern const unsigned char PROGMEM emotes5[];
extern const unsigned char PROGMEM emotes6[];
extern const unsigned char PROGMEM emotes7[];
extern const unsigned char PROGMEM emotes8[];
extern const unsigned char PROGMEM emotes9[];
extern const unsigned char PROGMEM emotes10[];
extern const unsigned char PROGMEM emotes11[];
extern const unsigned char PROGMEM emotes12[];
extern const unsigned char PROGMEM emotes13[];
extern const unsigned char PROGMEM emotes14[];
extern const unsigned char PROGMEM emotes15[];
extern const unsigned char PROGMEM emotes16[];
extern const unsigned char PROGMEM emotes17[];
extern const unsigned char PROGMEM emotes18[];
extern const unsigned char PROGMEM emotes19[];
extern const unsigned char PROGMEM emotes20[];
extern const unsigned char PROGMEM emotes21[];
extern const unsigned char PROGMEM emotes22[];
extern const unsigned char PROGMEM emotes23[];
extern const unsigned char PROGMEM emotes24[];
extern const unsigned char PROGMEM emotes25[];
extern const unsigned char PROGMEM emotes26[];
extern const unsigned char PROGMEM emotes27[];
extern const unsigned char PROGMEM emotes28[];
extern const unsigned char PROGMEM emotes29[];
extern const unsigned char PROGMEM emotes30[];
extern const unsigned char PROGMEM emotes31[];
extern const unsigned char PROGMEM emotes32[];
extern const unsigned char PROGMEM emotes33[];
extern const unsigned char PROGMEM emotes34[];
extern const unsigned char PROGMEM emotes35[];
extern const unsigned char PROGMEM emotes36[];
extern const unsigned char PROGMEM emotes37[];
extern const unsigned char PROGMEM emotes38[];
extern const unsigned char PROGMEM emotes39[];
extern const unsigned char PROGMEM emotes40[];
extern const unsigned char PROGMEM emotes41[];
extern const unsigned char PROGMEM emotes42[];
extern const unsigned char PROGMEM emotes43[];
extern const unsigned char PROGMEM emotes44[];
extern const unsigned char PROGMEM emotes45[];
extern const unsigned char PROGMEM emotes46[];
extern const unsigned char PROGMEM emotes47[];
extern const unsigned char PROGMEM emotes48[];
extern const unsigned char PROGMEM emotes49[];

extern const uint8_t* emotesArray[];

// Show emotion eyes at (x, y) with delay tt
// void showEmotes(int xx, int yy, int tt);

void updateEmoteAnimation();  // Non-blocking
void resetEmoteAnimation();   // Reset to frame 0

#endif
