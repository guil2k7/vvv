/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#include <Arduino.h>
#include "engine.hh"
#include "script.hh"

using namespace vvv;
using namespace vvv::engine_script;

static Instruction const SCRIPT[] = {
    Instruction::create(OPCODE_UPDATE_X_DIR, 0),
    Instruction::create(OPCODE_UPDATE_SPEED, 100),
    Instruction::create(OPCODE_WAIT, 5000),
    Instruction::create(OPCODE_UPDATE_X_DIR, 127),
    Instruction::create(OPCODE_WAIT, 5000),
    Instruction::create(OPCODE_UPDATE_X_DIR, -127),
    Instruction::create(OPCODE_WAIT, 5000),
    Instruction::create(OPCODE_UPDATE_X_DIR, 0),
    Instruction::create(OPCODE_UPDATE_SPEED, 255),
    Instruction::create(OPCODE_WAIT, 5000),
    Instruction::create(OPCODE_TOGGLE_REVERSE_MODE, 0),
    Instruction::create(OPCODE_WAIT, 5000),
    Instruction::create(OPCODE_UPDATE_SPEED, 0)
};

static Engine g_engine;
static ScriptRunner g_script_runner;

void setup() {
    g_engine.left_wheel.dir_pin_a = 7;
    g_engine.left_wheel.dir_pin_b = 6;
    g_engine.left_wheel.speed_pin = 9;
    g_engine.left_wheel.led_pin = 13;

    g_engine.right_wheel.dir_pin_a = 5;
    g_engine.right_wheel.dir_pin_b = 4;
    g_engine.right_wheel.speed_pin = 3;
    g_engine.right_wheel.led_pin = 12;

    g_engine.setup_pins();
    g_engine.reset_wheels();
    g_engine.update_speed(200);

    g_script_runner.set_code(SCRIPT, sizeof(SCRIPT) / sizeof(SCRIPT[0]));
}

void loop() {
    g_script_runner.process();
    delay(15);
}
