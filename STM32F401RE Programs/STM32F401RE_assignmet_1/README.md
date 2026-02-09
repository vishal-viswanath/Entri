STM32F401RE Nucleo GPIO Demo

Multi-function GPIO demonstration on "STM32F401RE" board using "bare-metal driver".

* Features ✅

Function : On-board LED, External LED 1, External LED 2, User Button
GPIO Pin : PA5, PA6, PA7, PC13
Behavior : Toggle on Button Press(debounced), Blink 250ms ON → 250ms OFF, Opposite phase of PA6,Active LOW

* Key Implementations ✅
  
  1.Non-blocking Delay
  2.Button Debouncing

* Expected Behavior ✅
  
 1. Power ON → PA6 & PA7 blink alternately (250ms each)
 2. Press B1 → PA5 toggles ONCE (no bounce!)


Author: [Vishal Viswanath]
Board: STM32F401RE 
Driver: Custom bare-metal code
  
