/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#pragma once

#include <stddef.h>
#include <stdint.h>
#include "Vehicle.hh"

namespace VVV {

// The instruction format uses only 2 bits for the opcode, which means there can only be 4 opcodes.
enum Opcode {
    OPCODE_WAIT,
    OPCODE_SET_DIRECTION,
    OPCODE_SET_SPEED,
    OPCODE_TOGGLE_REVERSE_MODE,
};

union __attribute__((packed)) Instruction {
    static constexpr Instruction createImmU(Opcode opcode, uint16_t imm) {
        Instruction inst = {};
        inst.opcode = opcode;
        inst.immU = imm;

        return inst;
    }

    static constexpr Instruction createImmS(Opcode opcode, int16_t imm) {
        Instruction inst = {};
        inst.opcode = opcode;
        inst.immS = imm;

        return inst;
    }

    struct {
        Opcode opcode : 2;
        uint16_t immU : 14;
    };

    struct {
        Opcode _opcode : 2;
        int16_t immS : 14;
    };
};

class ScriptRunner {
public:
    Vehicle* vehicle;

    constexpr ScriptRunner()
        : vehicle{nullptr}
        , m_code{nullptr}
        , m_ip{0}
        , m_codeLength{0}
        , m_pauseEndTs{0}
    {
    }

    inline void reset() {
        m_ip = 0;
        m_pauseEndTs = 0;
    }

    inline void setCode(Instruction const* code, size_t length) {
        m_ip = 0;
        m_code = code;
        m_codeLength = length;
        m_pauseEndTs = 0;
    }

    void process();

private:
    Instruction const* m_code;
    size_t m_ip;
    size_t m_codeLength;
    size_t m_pauseEndTs;
};

} // namespace VVV::EngineScript
