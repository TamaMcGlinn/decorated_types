#include <iostream>
using std::cout; using std::endl;

template<typename ValueType, int dimension = 1>
struct metre {
  typedef metre<ValueType,dimension> SelfType;

  template<int dim>
  using m = metre<ValueType, dim>; // shorthand for "same value-typed metre"

  metre(const ValueType & rhs) : m_value(rhs){}

  const SelfType operator+(const SelfType & rhs) const{
    return metre(m_value+rhs.m_value);
  }

  const SelfType operator-(const SelfType & rhs) const{
    return metre(m_value-rhs.m_value);
  }

  void operator+=(const SelfType & rhs){
    m_value += rhs.value;
  }

  void operator-=(const SelfType & rhs){
    m_value -= rhs.value;
  }

  template<int otherDimension>
  const m<dimension+otherDimension> operator*(const m<otherDimension> & rhs) const{
    return m<dimension+otherDimension>(m_value * rhs.value());
  }

  template<int otherDimension>
  const m<dimension-otherDimension> operator/(const m<otherDimension> & rhs) const{
    return m<dimension-otherDimension>(m_value / rhs.value());
  }

private:
  static std::string GetDimensionalSuffix(){
    if (dimension == 0){
      return "";
    } else {
      std::string numSuffix = dimension != 1 ? std::to_string(dimension) : "";
      return "m" + numSuffix;
    }
  }

public:
  friend std::ostream& operator <<(std::ostream& outputStream, const SelfType & self) {
    outputStream << self.m_value << ' ' << GetDimensionalSuffix();
    return outputStream;
  }

  ValueType value() const {
    return m_value;
  }

private:
  ValueType m_value;
};

int main(){
  metre<int> m = 3.0;
  metre<int> n = 3.0;
  metre<int,2> s = m * n;
  cout << m << " * " << n << " = " << s << endl;
  metre<int> h(5);
  metre<int,3> v = s * h;
  cout << s << " * " << h << " = " << v << endl;
}
