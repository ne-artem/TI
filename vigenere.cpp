#include "vigenere.h"
#include <QList>
#include <QChar>

QList<QChar> alphabet = {
    u'А', u'Б', u'В', u'Г', u'Д', u'Е', u'Ё', u'Ж', u'З',
    u'И', u'Й', u'К', u'Л', u'М', u'Н', u'О', u'П', u'Р',
    u'С', u'Т', u'У', u'Ф', u'Х', u'Ц', u'Ч', u'Ш', u'Щ',
    u'Ъ', u'Ы', u'Ь', u'Э', u'Ю', u'Я'
};

QString Vigenere::encryptVigenere(const QString &input, const QString &key) {

    QString cipherText, processedKey;

    for (QChar ch : key) {
        if (alphabet.contains(ch)) {
            processedKey.append(ch);
        }
    }

    int ind = 0;
    for(int i = 0; i < input.length(); i++){
        if (alphabet.contains(input[i])){
            int inputIndex = alphabet.indexOf(input[i]);
            int keyIndex = alphabet.indexOf(processedKey[ind]);
            int newIndex = (inputIndex + keyIndex) % alphabet.size();
            cipherText.append(alphabet[newIndex]);
            processedKey[ind] = alphabet[(keyIndex + 1) % alphabet.size()];
            ind = (ind + 1) % processedKey.size();
        } else{
            cipherText.append(input[i]);
        }

    }

    return cipherText;
}

QString Vigenere::decryptVigenere(const QString &input, const QString &key) {

    QString decryptText, processedKey;

    for (QChar ch : key) {
        if (alphabet.contains(ch)) {
            processedKey.append(ch);
        }
    }

    int ind = 0;
    for(int i = 0; i < input.length(); i++){
        if (alphabet.contains(input[i])){
            int inputIndex = alphabet.indexOf(input[i]);
            int keyIndex = alphabet.indexOf(processedKey[ind]);
            int newIndex = ((inputIndex - keyIndex) + alphabet.size()) % alphabet.size();
            decryptText.append(alphabet[newIndex]);
            processedKey[ind] = alphabet[(keyIndex + 1) % alphabet.size()];
            ind = (ind + 1) % processedKey.size();
        } else{
            decryptText.append(input[i]);
        }

    }

    return decryptText;
}
