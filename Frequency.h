#ifndef FREQUENCY_H
#define FREQUENCY_H


#include <stdint.h>
#include <iostream>

class Frequency
{
    public:
        Frequency();
        Frequency(uint64_t newValue, char newSeries = '\0');
        virtual ~Frequency();

        void setSeries(char newSeries);
        void setValue(uint64_t newValue);

        char getSeries() const;
        uint64_t getValue() const;

        // overload operators
        Frequency operator+ (Frequency data);
        bool operator< (Frequency data) const;
        bool operator> (Frequency data) const;
        friend std::ostream& operator<< (std::ostream& out, const Frequency& data);

    private:

        char series;
        uint64_t value;
};
#endif // FREQUENCY_H
