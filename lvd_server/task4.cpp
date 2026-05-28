#include "task4.h"

QString generaterandomstring(int length) {
    static const QString possibleCharacters("abcdefghijklmnopqrstuvwxyz");

    QString randomString;
    QRandomGenerator randomGenerator;

    for (int i = 0; i < length; ++i) {
        int index = randomGenerator.bounded(possibleCharacters.length());
        QChar randomChar = possibleCharacters.at(index);
        randomString.append(randomChar);
    }

    return randomString;
}

QString vigenere(const QString& Key, const QString& text) {
    QString alphabet = "abcdefghijklmnopqrstuvwxyz "; // Bảng chữ cái và dấu cách
    QString code; // Chuỗi đã mã hóa
    QString key = Key;
    while (key.length() < text.length()) { // Vòng lặp lặp lại khóa nếu độ dài của khóa nhỏ hơn độ dài của văn bản
        key.push_back(key); // Thêm khóa vào chính nó
    }

    for (int i = 0; i < text.length(); i++) { // Vòng lặp mã hóa từng ký tự trong văn bản
        int t = alphabet.indexOf(text[i]); // Tìm vị trí của ký tự trong bảng chữ cái
        int k = alphabet.indexOf(key[i]); // Tìm vị trí của ký tự khóa trong bảng chữ cái

        if (t != -1 && k != -1) { // Nếu ký tự và ký tự khóa nằm trong bảng chữ cái
            int sum = (t + k) % alphabet.length(); // Tính tổng vị trí của ký tự và ký tự khóa

            code += alphabet[sum]; // Mã hóa ký tự và thêm vào chuỗi đã mã hóa
        }
    }

    return code;
}

QVariantMap result_Vigenere() {
    QVariantMap task;
    QString key = generaterandomstring(4);
    QString text = generaterandomstring(10);
    QString code = vigenere( key, text);
    task["text"] = QString("заданный ключ: " + key + " и строка: " + text + ", из заданных данных,"
                           "используйте метод шифрования Виженера для завершения упражнения.");
    task["answer"] = code;
    return task;
}

/*QString vigenere(QString key, QString text) //  ключ шифрования, исходный текст
{
    QString alphabet = "abcdefghijklmnopqrstuvwxyz "; // Алфавит и пробел
    QString code; // зашифрованный текст

    while (key.length() < text.length()) { // Цикл повторения ключа, если его длина меньше длины текста
        key += key; // Добавление ключа к себе самому
    }

    size_t i = 0;
    while (i < text.length()) { // Цикл шифрования каждого символа текста
        size_t j = 0;
        size_t t, k = 0;
        while (alphabet[j]) { // Цикл поиска позиции символа в алфавите
            if (alphabet[j] == text[i]) { // Если символ текста найден в алфавите
                t = j; break; // Сохранить его позицию в t и выйти из цикла
            } j++;
        }
        j = 0;
        while (alphabet[j]) { // Цикл поиска позиции символа ключа в алфавите
            if (alphabet[j] == key[i]) { // Если символ ключа найден в алфавите
                k = j; break; // Сохранить его позицию в k и выйти из цикла
            } j++;
        }
        if ((t + k) < 27) { // Если сумма позиций символов меньше длины алфавита
            code += alphabet[t + k]; // Зашифровать символ и добавить к зашифрованному тексту
        }
        if ((t + k) >= 27) { // Если сумма позиций символов больше или равна длине алфавита
            code += alphabet[t + k - 27]; // Зашифровать символ (с учетом "обхода" алфавита) и добавить к зашифрованному тексту
        }
        i++; // Переход к следующему символу текста
    }

    return code;
}*/
