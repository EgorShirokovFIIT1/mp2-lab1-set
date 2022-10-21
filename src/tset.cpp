#include "tset.h"

static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
    return TBitField(BitField);
}

int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const
{
    if (Elem >= MaxPower || Elem < 0)
    {
        throw "Element is out of universe";
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)
{
    if (Elem >= MaxPower || Elem < 0)
    {
        throw "Element is out of universe";
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    if (Elem >= MaxPower || Elem < 0)
    {
        throw "Element is out of universe";
    }
    BitField.ClrBit(Elem);
}



TSet& TSet::operator=(const TSet& s)
{
    if (this == &s)
    {
        return *this;
    }
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s)
{
    int MAXPower = max(s.MaxPower, MaxPower);
    TSet tmp(MAXPower);
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem)
{
    TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem)
{
    TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s)
{
    int MAXPower = max(s.MaxPower, MaxPower);
    TSet tmp(MAXPower);
    tmp.BitField = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void)
{
    TSet tmp(~BitField);
    return tmp;
}

istream& operator>>(istream& istr, TSet& s)
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s)
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << " ";
        }
        ostr << endl;
    }
    return ostr;
}
