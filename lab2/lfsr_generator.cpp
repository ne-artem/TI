#include "lfsr_generator.h"

LFSRGenerator::LFSRGenerator() : m_state(1), m_initialSeed(1) {}

bool LFSRGenerator::setSeed(const QString &binaryStr) {
    if (binaryStr.isEmpty()) return false;

    bool ok;
    // Преобразуем двоичную строку в число
    uint32_t seed = binaryStr.toUInt(&ok, 2);

    if (!ok || seed == 0) {
        // Состояние из всех нулей недопустимо для LFSR
        return false;
    }

    m_initialSeed = seed;
    m_state = seed;
    return true;
}

void LFSRGenerator::reset() {
    m_state = m_initialSeed;
}

void LFSRGenerator::shift() {
    // Отводы согласно полиному: x^32 (бит 31), x^28 (бит 27), x^27 (бит 26), x^1 (бит 0)
    uint32_t b32 = (m_state >> 31) & 1u;
    uint32_t b28 = (m_state >> 27) & 1u;
    uint32_t b27 = (m_state >> 26) & 1u;
    uint32_t b1  = (m_state >> 0)  & 1u;

    uint32_t feedback = b32 ^ b28 ^ b27 ^ b1;

    // Сдвиг вправо и вставка бита обратной связи в самый левый разряд
    m_state = (m_state << 1) | (feedback & 1u);
}

// В lfsr_generator.cpp
uint8_t LFSRGenerator::getNextBit() {
    // 1. Берем младший бит (тот самый "1", который в твоей таблице Excel справа)
    uint8_t bit = static_cast<uint8_t>((m_state >> 31) & 1u);

    // 2. Выполняем ОДИН сдвиг (переходим к следующей строке таблицы)
    shift();

    return bit;
}
