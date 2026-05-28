#include "task3.h"

const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t rotr(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }
uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
uint32_t bsig0(uint32_t x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
uint32_t bsig1(uint32_t x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
uint32_t ssig0(uint32_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
uint32_t ssig1(uint32_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

/*QString sha256(QString input) {

    int len = input.length();
    vector<uint8_t> message(len + 1 + (64 - (len + 1) % 64));

    for (int i = 0; i < len; i++) {
        message[i] = input[i];
    }
    message[len] = 0x80;
    uint64_t bit_len = len * 8;
    for (int i = 0; i < 8; i++) {
        message[message.size() - 8 + i] = bit_len >> (56 - i * 8);
    }

    uint32_t h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;


    for (int i = 0; i < message.size(); i += 64) {
        uint32_t w[64];
        for (int j = 0; j < 16; j++) {
            w[j] = (message[i + j * 4] << 24) | (message[i + j * 4 + 1] << 16) | (message[i + j * 4 + 2] << 8) | message[i + j * 4 + 3];
        }
        for (int j = 16; j < 64; j++) {
            w[j] = ssig1(w[j - 2]) + w[j - 7] + ssig0(w[j - 15]) + w[j - 16];
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        for (int j = 0; j < 64; j++) {
            uint32_t temp1 = h + bsig1(e) + ch(e, f, g) + k[j] + w[j];
            uint32_t temp2 = bsig0(a) + maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    ostringstream ss;
    ss << hex << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
    return ss.str();
}*/

QString sha256(QString input) {
    int len = input.length();
    QByteArray message(len + 1 + (64 - (len + 1) % 64), 0);

    for (int i = 0; i < len; i++) {
        message[i] = input[i].toLatin1();
    }
    message[len] = 0x80;
    uint64_t bit_len = len * 8;
    for (int i = 0; i < 8; i++) {
        message[message.size() - 8 + i] = (bit_len >> (56 - i * 8)) & 0xFF;
    }

    uint32_t h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;

    for (int i = 0; i < message.size(); i += 64) {
        uint32_t w[64];
        for (int j = 0; j < 16; j++) {
            w[j] = (static_cast<uint8_t>(message[i + j * 4]) << 24) |
                   (static_cast<uint8_t>(message[i + j * 4 + 1]) << 16) |
                   (static_cast<uint8_t>(message[i + j * 4 + 2]) << 8) |
                   static_cast<uint8_t>(message[i + j * 4 + 3]);
        }
        for (int j = 16; j < 64; j++) {
            w[j] = ssig1(w[j - 2]) + w[j - 7] + ssig0(w[j - 15]) + w[j - 16];
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        for (int j = 0; j < 64; j++) {
            uint32_t temp1 = h + bsig1(e) + ch(e, f, g) + k[j] + w[j];
            uint32_t temp2 = bsig0(a) + maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    return QString("%1%2%3%4%5%6%7%8").arg(h0, 8, 16, QLatin1Char('0'))
        .arg(h1, 8, 16, QLatin1Char('0'))
        .arg(h2, 8, 16, QLatin1Char('0'))
        .arg(h3, 8, 16, QLatin1Char('0'))
        .arg(h4, 8, 16, QLatin1Char('0'))
        .arg(h5, 8, 16, QLatin1Char('0'))
        .arg(h6, 8, 16, QLatin1Char('0'))
        .arg(h7, 8, 16, QLatin1Char('0'));
}

QString generateRandomString(int length) {
    static const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    QRandomGenerator randomGenerator;

    for (int i = 0; i < length; ++i) {
        int index = randomGenerator.bounded(possibleCharacters.length());
        QChar randomChar = possibleCharacters.at(index);
        randomString.append(randomChar);
    }

    return randomString;
}


QVariantMap token_sha_256() {
    QVariantMap task;
    QString pass = generateRandomString(10);
    QString res = sha256(pass);
    res = res.toUpper();
    task["text"] = QString("для строки "+ pass + " используйте метод sha256 для шифрования строки.");
    task["answer"] = res;
    return task;
}

QString test_sha_256(QString pass) {
    QString res = sha256(pass);
    res = res.toUpper();
    return res;
}

