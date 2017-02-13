#include "Frequency.h"

Frequency::Frequency()
{

}

Frequency::Frequency(uint64_t newValue, char newSeries /*= 0*/)
{
    setValue(newValue);
    setSeries(newSeries);
}

Frequency::~Frequency()
{

}

void Frequency::setSeries(char newSeries)
{
    this->series = newSeries;
}

void Frequency::setValue(uint64_t newValue)
{
    this->value = newValue;
}

char Frequency::getSeries() const
{
    return this->series;
}

uint64_t Frequency::getValue() const
{
    return this->value;
}

Frequency Frequency::operator+ (Frequency data)
{
    Frequency newData;
    newData.setValue(this->value + data.getValue() );
    newData.setSeries(0);
    return newData;
}

bool Frequency::operator< (Frequency data) const
{
    return this->value < data.getValue();
}

bool Frequency::operator> (Frequency data) const
{
    return this->value > data.getValue();
}

std::ostream& operator<< (std::ostream& out, const Frequency& data)
{
    out << data.getSeries() << ' ' << data.getValue();
    return out;
}
