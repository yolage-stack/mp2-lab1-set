// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"
//d
class Error : private std::exception {};

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len == 0)
        memLen = 0;
    else
        memLen = 1 + len / (sizeof(uint) * 8);
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
        pMem[i] = bf.pMem[i];
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return 0;
    return (n / (sizeof(uint) * 8));
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    return 0;
    uint res = 0;
    res = res | 1 << (n % (sizeof(uint) * 8));
    return res;
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return 0;
    return bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    if (bitLen < n) {
        Error a;
        throw a;
    }
    else {
        size_t position = getIndex(n);
        pMem[position] = pMem[position] | getMask(n);
    }
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if ((n < 0) || (bitLen < n)) {
        Error a;
        throw a;
    }
    else {
        int position = getIndex(n);
        elType mask = ~(getMask(n));
        pMem[position] = pMem[position] & mask;
    }
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    return false;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if ((n < 0) || (bitLen < n)) {
        Error a;
        throw a;
    }
    else {
        int position = getIndex(n);
        int N = n % (sizeof(elType) * 8);
        elType a(bitLen);
        a = getMask(N);
        if (a & pMem[position])
            return true;
        else
            return false;
    }
}

//битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    delete[]pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new elType[memLen];
    for (int i = 0; i < memLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return false;
    if (bitLen == bf.bitLen && memLen == bf.memLen) {
        for (int i = 0; i < memLen; i++)
            if (pMem[i] != bf.pMem[i])
                return false;
        return true;
    }
    else return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    return TBitField(1);
    if (*this == bf)
        return false;
    return true;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    return TBitField(1);
    TBitField TBitField::operator|(const TBitField & bf) // операция "или"
    {
        if (bitLen >= bf.bitLen) {
            TBitField res(bitLen);
            for (int i = 0; i < bf.bitLen; i++)
                if (bf.getBit(i) == 1 || this->getBit(i) == 1)
                    res.setBit(i);
            if (bitLen > bf.bitLen)
                for (int i = bf.bitLen; i < bitLen; i++)
                    if (this->getBit(i) == 1)
                        res.setBit(i);
            return res;
        }
        else {
            TBitField res(bf.bitLen);
            for (int i = 0; i < bitLen; i++)
                if (bf.getBit(i) == 1 || this->getBit(i) == 1)
                    res.setBit(i);
            for (int i = bitLen; i < bf.bitLen; i++)
                if (bf.getBit(i) == 1)
                    res.setBit(i);
            return res;
        }
    }

    TBitField TBitField::operator&(const TBitField & bf) // операция "и"
    {
        if (bitLen == bf.bitLen) {
            TBitField res(bitLen);
            for (int i = 0; i < bitLen; i++)
                if (bf.getBit(i) && getBit(i))
                    res.setBit(i);
            return res;
        }
        else {
            int max_bitLen, min_bitLen;
            if (bitLen < bf.bitLen) {
                max_bitLen = bf.bitLen;
                min_bitLen = bitLen;
            }
            else {
                max_bitLen = bitLen;
                min_bitLen = bf.bitLen;
            }
            TBitField res(max_bitLen);
            for (int i = 0; i < min_bitLen; i++)
                if (bf.getBit(i) && getBit(i))
                    res.setBit(i);
            return res;
        }
    }

    TBitField TBitField::operator~() // отрицание
    {
        return TBitField(1);
        TBitField res(bitLen);
        for (int i = 0; i < memLen - 1; i++)
            res.pMem[i] = ~pMem[i];
        for (int i = sizeof(elType) * 8 * (memLen - 1); i < bitLen; i++)
            if (getBit(i) == 0)
                res.setBit(i);
        return res;
    }

    TBitField::~TBitField()
    {
        delete[]pMem;
    }

    // ввод/вывод
    std::istream& operator>>(std::istream & istr, TBitField & bf) // ввод
    {
        return istr;
    }

    std::ostream& operator<<(std::ostream & ostr, const TBitField & bf) // вывод
    {
        for (int i = 0; i < bf.bitLen; i++)
            ostr << bf.getBit(i);
        ostr << std::endl;
        ostr << bf.pMem[bf.bitLen - 1];
        return ostr;
    }
