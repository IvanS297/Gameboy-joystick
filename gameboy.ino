#include <myButton.h>
#include <Keyboard.h>

Button btn_A(3); // кнопка A
Button btn_B(4); // кнопка B
Button btn_X(2); // кнопка X
Button btn_Y(5); // кнопка Y
Button btn_S(6); // кнопка START
Button btn_s(7); // кнопка SELECT
 
Joystick joy(A0, A1);//
void setup() {
  //while (!Serial) {}
  //Serial.begin(9600);
  Keyboard.begin();
}
//
void loop() {
  btn_A.tick();
  btn_B.tick();
  btn_X.tick();
  btn_Y.tick();
  btn_S.tick();
  btn_s.tick();
  joy.tick();
//
  if (btn_A.isClicked()) { Keyboard.press('5'); } else { Keyboard.release('5'); }
  if (btn_B.isClicked()) { Keyboard.press('6'); } else { Keyboard.release('6'); }
  if (btn_X.isClicked()) { Keyboard.press('7'); } else { Keyboard.release('7'); }
  if (btn_Y.isClicked()) { Keyboard.press('8'); } else { Keyboard.release('8'); }
  if (btn_S.isClicked()) { Keyboard.press('9'); } else { Keyboard.release('9'); }
  if (btn_s.isClicked()) { Keyboard.press('0'); } else { Keyboard.release('0'); }
  if (joy.JOY_UP_HOLD()) { Keyboard.press('3'); } else { Keyboard.release('3'); }
  if (joy.JOY_DOWN_HOLD()) { Keyboard.press('4'); } else { Keyboard.release('4'); }
  if (joy.JOY_RIGHT_HOLD()) { Keyboard.press('2'); } else { Keyboard.release('2'); }
  if (joy.JOY_LEFT_HOLD()) { Keyboard.press('1'); } else { Keyboard.release('1'); }
}