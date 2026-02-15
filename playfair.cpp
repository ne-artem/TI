#include "playfair.h"
#include <QSet>
#include <QChar>
#include <QVector>
#include <QPair>
#include <QList>

using Position = QPair<int, int>; // <row, col>

Position findPos(const QVector<QVector<QChar>>& matrix, QChar ch) {
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            if (matrix[row][col] == ch) {
                return Position(row, col);
            }
        }
    }
    return Position(-1, -1); // не найдено
}

QVector<QVector<QChar>> Playfair::generateMatrix(const QString &key) {

    QVector<QVector<QChar>> mat(5, QVector<QChar>(5, 'A'));

    QList <QChar> alphabet = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    QString clearKey;
    clearKey.replace('J', 'I');
    for (QChar ch : key) {
        if (alphabet.contains(ch)) {
            clearKey.append(ch); // или можно добавить оригинальный ch, если нужно сохранить регистр
        }
    }

    int ind = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(ind < clearKey.length()){
                if(alphabet.contains(clearKey[ind])){
                    mat[i][j] = clearKey[ind];
                    alphabet.removeOne(clearKey[ind]);
                }
                else j--;
                ind++;
            }else {
                mat[i][j] = *alphabet.begin();
                alphabet.removeOne(mat[i][j]);
            }
        }
    }

    return mat;
}

QString Playfair::encryptPlayfair(const QString &input, const QString &key) {

    QString processedText = input;
    processedText.replace('J', 'I');
    QVector<QVector<QChar>> mat  = generateMatrix(key);;
    QString cipherText;
    QList<QChar> alphabet = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    // if(processedText.length() % 2 != 0){
    //     QChar lastChar = processedText[processedText.length()-1];
    //     if(alphabet.contains(lastChar)){
    //         if(lastChar == 'X') processedText.append('W');
    //         else processedText.append('X');
    //     }
    // }

    for(int i = 0; i < processedText.length(); i++){

        QChar first = processedText[i];
        if(!alphabet.contains(first)){
            cipherText.append(first);
            continue;
        }
        QChar second;
        if(i == processedText.length()-1){
                if(first == 'X') second = 'W';
                else second = 'X';
        } else{
        second = processedText[i + 1];
        if(!alphabet.contains(second)){
            if(first == 'X') second = 'W';
            else second = 'X';
        } else if(second == first){
            if(first == 'X') second = 'W';
            else second = 'X';
        }else i++;
        }

        Position posF = findPos(mat, first),
            posS = findPos(mat, second);

        if (posF.first == posS.first){
            cipherText.append(mat[posF.first][(posF.second+1)%5]);
            cipherText.append(mat[posS.first][(posS.second+1)%5]);
        }
        else if (posF.second == posS.second){
            cipherText.append(mat[(posF.first+1)%5][posF.second]);
            cipherText.append(mat[(posS.first+1)%5][posS.second]);
        }
        else{
            cipherText.append(mat[posF.first][posS.second]);
            cipherText.append(mat[posS.first][posF.second]);
        }
    }

    return cipherText;
}

QString Playfair::decryptPlayfair(const QString &input, const QString &key){

    QString processedText = input;
    processedText.replace('J', 'I');
    QVector<QVector<QChar>> mat  = generateMatrix(key);;
    QString decryptText;
    QList<QChar> alphabet = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    // if(processedText.length() % 2 != 0){
    //     QChar lastChar = processedText[processedText.length()-1];
    //     if(alphabet.contains(lastChar)){
    //         if(lastChar == 'X') processedText.append('W');
    //         else processedText.append('X');
    //     }
    // }

    for(int i = 0; i < processedText.length(); i++){

        QChar first = processedText[i];
        if(!alphabet.contains(first)){
            decryptText.append(first);
            continue;
        }

        QChar second;
        if(i == processedText.length()-1){
            if(first == 'X') second = 'W';
            else second = 'X';
        } else{
            second = processedText[i + 1];
            if(!alphabet.contains(second)){
                if(first == 'X') second = 'W';
                else second = 'X';
            } else if(second == first){
                if(first == 'X') second = 'W';
                else second = 'X';
            }else i++;
        }
        Position posF = findPos(mat, first),
            posS = findPos(mat, second);

        if (posF.first == posS.first){
            decryptText.append(mat[posF.first][(posF.second+4)%5]);
            decryptText.append(mat[posS.first][(posS.second+4)%5]);
        }
        else if (posF.second == posS.second){
            decryptText.append(mat[(posF.first+4)%5][posF.second]);
            decryptText.append(mat[(posS.first+4)%5][posS.second]);
        }
        else{
            decryptText.append(mat[posF.first][posS.second]);
            decryptText.append(mat[posS.first][posF.second]);
        }
    }

    return decryptText;
}
