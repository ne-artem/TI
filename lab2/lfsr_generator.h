#ifndef LFSR_GENERATOR_H
#define LFSR_GENERATOR_H

#include <cstdint>
#include <QString>
#include <QByteArray>

class LFSRGenerator {
public:
    LFSRGenerator();

    /**
     * Устанавливает начальное состояние из строки "0101..."
     * @return true, если строка валидна и состояние установлено
     */
    bool setSeed(const QString &binaryStr);

    /**
     * Генерирует блок байтов (гамму) на основе текущего состояния регистра.
     * Каждые 8 тактов работы регистра формируют 1 байт.
     */
    uint8_t getNextBit();

    /**
     * Сбрасывает регистр к последнему установленному начальному значению
     */
    void reset();

private:
    uint32_t m_state;
    uint32_t m_initialSeed;

    // Один такт работы LFSR (полином x^32 + x^28 + x^27 + x + 1)
    void shift();
};

#endif // LFSR_GENERATOR_H
