#include <myButton.h>

Button::Button(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

uint8_t Button::getPin() { return _pin; }

uint16_t Button::getClickTimeout() { return _click_timeout; }

uint8_t Button::getHoldTimeout() { return _hold_timeout; }

void Button::setClickTimeout(uint8_t timeout) { _click_timeout = timeout; }

void Button::setHoldTimeout(uint8_t timeout) { _hold_timeout = timeout; }

void Button::tick() {
    _state = !digitalRead(_pin);

    // НАЖАТИЕ КНОПКИ
    if (_state && !_flag && millis() - btn_timer > _click_timeout) {
        _flag = true;
        btn_timer = millis();
        click_found = true;
    }

    // ЗАЖАТИЕ КНОПКИ
    if (_state && _flag && millis() - btn_timer > _hold_timeout) {
        btn_timer = millis();
        holded = true;
    }

    // ОТПУСКАНИЕ КНОПКИ
    if (!_state && _flag && millis() - btn_timer > _click_timeout) {
        _flag = false;
        btn_timer = millis();
        click_found = false;
    }
}

bool Button::isClicked() { if (click_found) { return true; } else { return false; } }

bool Button::isHold() {
    if (holded) {
        holded = false;
        return true;
    }
    else {
        return false;
    }
}


// Реализация джойстика

Joystick::Joystick(uint8_t X, uint8_t Y) {
    _X_pin = X;
    _Y_pin = Y;
    pinMode(_X_pin, INPUT);
    pinMode(_Y_pin, INPUT);
}

uint16_t* Joystick::getDeadZone() { return _deadzone; }

void Joystick::tick() {
    _valx = analogRead(_X_pin);
    _valy = analogRead(_Y_pin);

    // Проверка на движения джойстика впределах мёртвой зоне
    if (_valx > _deadzone[0]) { j2b.right_state = true; } else { j2b.right_state = false; }
    if (_valx < _deadzone[1]) { j2b.left_state = true; } else { j2b.left_state = false; }
    if (_valy > _deadzone[2]) { j2b.up_state = true; } else { j2b.up_state = false; }
    if (_valy < _deadzone[3]) { j2b.down_state = true; } else { j2b.down_state = false; }


    // Проверкана "клик", "удержание" и "отпускание"
    // Поворот вправо
    if (Pressed(&j2b.right_state, &j2b.right_flag, &right_tmr, _click_timeout)) { j2b.right = true; }
    if (Holded(&j2b.right_state, &j2b.right_flag, &right_tmr, _hold_timeout)) { j2b.right_hold = true; }
    if (Released(&j2b.right_state, &j2b.right_flag, &right_tmr, _click_timeout)) { j2b.right = false; }

    // Поворот влево
    if (Pressed(&j2b.left_state, &j2b.left_flag, &left_tmr, _click_timeout)) { j2b.left = true; }
    if (Holded(&j2b.left_state, &j2b.left_flag, &left_tmr, _hold_timeout)) { j2b.left_hold = true; }
    if (Released(&j2b.left_state, &j2b.left_flag, &left_tmr, _click_timeout)) { j2b.left = false; }

    // Поворот вверх
    if (Pressed(&j2b.up_state, &j2b.up_flag, &up_tmr, _click_timeout)) { j2b.up = true; }
    if (Holded(&j2b.up_state, &j2b.up_flag, &up_tmr, _hold_timeout)) { j2b.up_hold = true; }
    if (Released(&j2b.up_state, &j2b.up_flag, &up_tmr, _click_timeout)) { j2b.up = false; }

    // Поворот вниз
    if (Pressed(&j2b.down_state, &j2b.down_flag, &down_tmr, _click_timeout)) { j2b.down = true; }
    if (Holded(&j2b.down_state, &j2b.down_flag, &down_tmr, _hold_timeout)) { j2b.down_hold = true; }
    if (Released(&j2b.down_state, &j2b.down_flag, &down_tmr, _click_timeout)) { j2b.down = false; }


}

bool Joystick::Pressed(bool* state, bool* flag, uint32_t* tmr, uint16_t timeout) {
    if (*state && !*flag && millis() - *tmr > timeout) {
        *tmr = millis();
        *flag = true;
        return true;
    } else {
        return false;
    }
}

bool Joystick::Holded(bool* state, bool* flag, uint32_t* tmr, uint16_t timeout) {
    if (*state && *flag && millis() - *tmr > timeout) {
        *tmr = millis();
        *flag = true;
        return true;
    } else { return false; }
}

bool Joystick::Released(bool* state, bool* flag, uint32_t* tmr, uint16_t timeout) {
    if (!*state && *flag && millis() - *tmr > timeout) {
        *tmr = millis();
        *flag = false;
        return true;
    } else { return false; }
}

bool Joystick::JOY_RIGHT() {
    if (j2b.right) {
        j2b.right = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_LEFT() {
    if (j2b.left) {
        j2b.left = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_DOWN() {
    if (j2b.down) {
        j2b.down = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_UP() {
    if (j2b.up) {
        j2b.up = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_RIGHT_HOLD() {
    if (j2b.right_hold) {
        j2b.right_hold = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_LEFT_HOLD() {
    if (j2b.left_hold) {
        j2b.left_hold = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_UP_HOLD() {
    if (j2b.up_hold) {
        j2b.up_hold = false;
        return true;
    }
    else {
        return false;
    }
}

bool Joystick::JOY_DOWN_HOLD() {
    if (j2b.down_hold) {
        j2b.down_hold = false;
        return true;
    }
    else {
        return false;
    }
}