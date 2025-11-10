#include "Emotes.h"
#include "TionBot.h"

//=========================
// 🔹 Animation State
//=========================
int currentEmoteFrame = 0;

//=========================
// 🔹 Update Emote Animation (Non-Blocking)
//=========================
void updateEmoteAnimation() {
  display.clearDisplay();
  display.drawBitmap(0, 0, emotesArray[currentEmoteFrame], 128, 64, SSD1306_WHITE);
  display.display();
  
  // Advance to next frame (loop after 49)
  currentEmoteFrame = (currentEmoteFrame + 1) % 50;
}

//=========================
// 🔹 Reset Animation to First Frame
//=========================
void resetEmoteAnimation() {
  currentEmoteFrame = 0;
}
