#ifndef VIGENERE_H
#define VIGENERE_H

#include <QString>

class Vigenere
{
public:
    static QString encryptVigenere(const QString &input, const QString &key);
    static QString decryptVigenere(const QString &input, const QString &key);

};

#endif // VIGENERE_H
