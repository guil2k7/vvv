/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#include <Arduino.h>
#include "Vehicle.hh"
#include "Script.hh"

using namespace VVV;

static Instruction const SCRIPT[] = {
    Instruction::createImmS(OPCODE_SET_DIRECTION, 0),
    Instruction::createImmU(OPCODE_SET_SPEED, 100),
    Instruction::createImmU(OPCODE_WAIT, 5000),
    Instruction::createImmS(OPCODE_SET_DIRECTION, 255),
    Instruction::createImmU(OPCODE_WAIT, 5000),
    Instruction::createImmS(OPCODE_SET_DIRECTION, -255),
    Instruction::createImmU(OPCODE_WAIT, 5000),
    Instruction::createImmS(OPCODE_SET_DIRECTION, 0),
    Instruction::createImmU(OPCODE_SET_SPEED, 255),
    Instruction::createImmU(OPCODE_WAIT, 5000),
    Instruction::createImmU(OPCODE_TOGGLE_REVERSE_MODE, 0),
    Instruction::createImmU(OPCODE_WAIT, 5000),
    Instruction::createImmU(OPCODE_SET_SPEED, 0)
};

static Vehicle* g_vehicle = nullptr;
static ScriptRunner* g_scriptRunner = nullptr;

void setup() {
    g_vehicle = new Vehicle(Axis(5, 4, 3), Axis(7, 6, 9));
    g_vehicle->init();

    g_scriptRunner = new ScriptRunner();
    g_scriptRunner->vehicle = g_vehicle;
    g_scriptRunner->setCode(SCRIPT, sizeof(SCRIPT) / sizeof(SCRIPT[0]));
}

void loop() {
    g_scriptRunner->process();
    delay(15);
}
