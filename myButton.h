#include <stdint.h>
#pragma once
#include <Arduino.h>

class Button {
public:
  Button(uint8_t pin);
  uint8_t getPin();
  uint16_t getClickTimeout();
  uint8_t getHoldTimeout();

  void setClickTimeout(uint8_t timeout);
  void setHoldTimeout(uint8_t timeout);
  void tick();

  bool isClicked();
  bool isHold();
private:
  uint8_t _pin;
  uint8_t _click_timeout = 60;
  uint16_t _hold_timeout = 700;
  bool _flag = false;
  bool _state = false;
  bool click_found = false;
  bool holded = false;
  uint32_t btn_timer = 0;
};


typedef struct {
	bool up_state = false;
	bool down_state = false;
	bool right_state = false;
	bool left_state = false;
	bool up_flag = false;
	bool down_flag = false;
	bool right_flag = false;
	bool left_flag = false;
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;
	bool right_hold = false;
	bool left_hold = false;
	bool up_hold = false;
	bool down_hold = false;
} JOY_2_BUTTONS;

class Joystick {
public:
	Joystick(uint8_t X, uint8_t Y);

	//void setDeadZone(uint16_t deadzone[4]);
	uint16_t* getDeadZone();
	void tick();
	bool JOY_RIGHT();
	bool JOY_LEFT();
	bool JOY_UP();
	bool JOY_DOWN();
	bool JOY_RIGHT_HOLD();
	bool JOY_LEFT_HOLD();
	bool JOY_UP_HOLD();
	bool JOY_DOWN_HOLD();

private:
	uint8_t _X_pin;
	uint8_t _Y_pin;
	uint8_t _click_timeout = 60;
	uint16_t _deadzone[4] = {530, 490, 530, 490};
	uint16_t _valx = 0;
	uint16_t _valy = 0;
	uint16_t _hold_timeout = 200;
	uint32_t right_tmr = 0;
	uint32_t left_tmr = 0;
	uint32_t up_tmr = 0;
	uint32_t down_tmr = 0;
	JOY_2_BUTTONS j2b;
	bool Pressed(bool*, bool*, uint32_t*, uint16_t);
	bool Holded(bool*, bool*, uint32_t*, uint16_t);
	bool Released(bool*, bool*, uint32_t*, uint16_t);
};
