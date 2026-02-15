#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QString>

class Playfair
{
public:
    static QString decryptPlayfair(const QString &input, const QString &key);
    static QString encryptPlayfair(const QString &input, const QString &key);
private:
    static QVector<QVector<QChar>> generateMatrix(const QString &key);
};

#endif // PLAYFAIR_H
