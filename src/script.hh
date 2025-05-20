/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#pragma once

#include <stddef.h>
#include <stdint.h>
#include "engine.hh"

namespace vvv::engine_script {

// The instruction format uses only 2 bits for the opcode, which means there can only be 4 opcodes.
enum Opcode {
    OPCODE_WAIT,
    OPCODE_UPDATE_X_DIR,
    OPCODE_UPDATE_SPEED,
    OPCODE_TOGGLE_REVERSE_MODE,
};

union __attribute__((packed)) Instruction {
    static constexpr Instruction create(Opcode opcode, uint16_t imm) {
        Instruction inst = {};
        inst.opcode = opcode;
        inst.imm_u = imm;

        return inst;
    }

    static constexpr Instruction create(Opcode opcode, int16_t imm) {
        Instruction inst = {};
        inst.opcode = opcode;
        inst.imm_s = imm;

        return inst;
    }

    struct {
        Opcode opcode : 2;
        uint16_t imm_u : 14;
    };

    struct {
        Opcode _opcode : 2;
        int16_t imm_s : 14;
    };
};

class ScriptRunner {
public:
    constexpr ScriptRunner()
        : m_engine{nullptr}
        , m_code{nullptr}
        , m_ip{0}
        , m_code_len{0}
        , m_pause_end_ts{0}
    {}


    inline void reset() {
        m_ip = 0;
        m_pause_end_ts = 0;
    }

    inline void set_code(Instruction const* code, size_t len) {
        m_ip = 0;
        m_code = code;
        m_code_len = len;
        m_pause_end_ts = 0;
    }

    inline void set_engine(Engine* engine) {
        m_engine = engine;
        reset();
    }

    void process();

private:
    Engine* m_engine;
    Instruction const* m_code;
    size_t m_ip;
    size_t m_code_len;
    size_t m_pause_end_ts;
};

} // namespace vvv::engine_script
