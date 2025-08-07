#include <iostream>
#include <ostream>


// TODO: task 7.2 a)
template<class myType>
class ComplexNumber
{
public:
    ComplexNumber() noexcept = default;

    template<class T>
    ComplexNumber(T real, T imaginary) : real_number(real), imaginary_number(imaginary) {};

    //template<class TN>
    ComplexNumber<myType> operator+(const ComplexNumber<myType>&) const;

    template<class T>
    friend std::ostream& operator<<(std::ostream&, const ComplexNumber<T>&);

    myType getIm() { return imaginary_number; };
    myType getRe() { return real_number ; }

private:
    myType real_number{};
    myType imaginary_number{};
};

// TODO: task 7.2 b)

template<class myType>
ComplexNumber<myType> ComplexNumber<myType>::operator+(const ComplexNumber<myType>& other) const
{
    ComplexNumber<myType> complex = ComplexNumber();
    complex.real_number = this->real_number + other.real_number;
    complex.imaginary_number = this->imaginary_number + other.imaginary_number;

    return complex;
}

// TODO: task 7.2 c)
template<class myType>
std::ostream& operator<<(std::ostream& out, const ComplexNumber<myType>& complex)
{
    char val;
    if(complex.imaginary_number >= 0) {
        val = '+';
    } else {
        val = '\0';
    }

    return out << complex.real_number << val << complex.imaginary_number << 'i';
}