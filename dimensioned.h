#include <string>

struct Metre {
  template<typename ValueType>
  static ValueType to_metres(ValueType in) {
    return in;
  }
  template<typename ValueType>
  static ValueType from_metres(ValueType in) {
    return in;
  }
  static std::string print(){
    return "m";
  }
};

struct Foot {
  template<typename ValueType>
  static ValueType to_metres(ValueType in) {
    return in / 3.1; // TODO put in actual value
  }
  template<typename ValueType>
  static ValueType from_metres(ValueType in) {
    return in * 3.1;
  }
  static std::string print(){
    return "ft";
  }
};

struct Centimetre {
  template<typename ValueType>
  static ValueType to_metres(ValueType in) {
    return in / 100.0;
  }
  template<typename ValueType>
  static ValueType from_metres(ValueType in) {
    return in * 100.0;
  }
  static std::string print(){
    return "cm";
  }
};

struct Kilometre {
  template<typename ValueType>
  static ValueType to_metres(ValueType in) {
    return in * 1000.0;
  }
  template<typename ValueType>
  static ValueType from_metres(ValueType in) {
    return in / 1000.0;
  }
  static std::string print(){
    return "km";
  }
};

template<typename ValueType, typename UnitType, int N>
struct dimensioned
{
  typedef dimensioned<ValueType, UnitType, N> SelfType;

  explicit dimensioned(ValueType v) : m_value(v) {}

  template<typename OtherUnit>
  dimensioned(const dimensioned<ValueType,OtherUnit,N> & rhs) {
    m_value = rhs.value();
    for(int i = 0; i < N; ++i){
      m_value = UnitType::template from_metres<ValueType>(OtherUnit::template to_metres<ValueType>(m_value));
      // this ensures that 1m2 = 100 * 100 cm2 - apply the conversion from_metres (times 100) twice
      
      // note that one or the other or none of these two loops is entered, as
      // (0 < N && 0 < -N) is false for all N
    }
    for(int i = 0; i < -N; ++i){
      m_value = UnitType::template to_metres<ValueType>(OtherUnit::template from_metres<ValueType>(m_value));
      // to understand the negative version of the loop;
      // we are talking about frequencies here; 
      // at x = 0 m, we want to place 0 posts per metre.
      // this rate should increase as x increases,
      // at a rate of 5 posts per metre per metre
      // so at x = 3 there should be 3 * 5 posts per metre, or 3 * 5 / 3.1 posts per foot
      // conversion question is, this frequency of 5 posts per metre per metre is how many posts per foot per foot?
      // 5 / 3.1 posts per foot per metre
      // 5 / 3.1 / 3.1 posts per foot per foot
    }
  }

  SelfType operator+ (const SelfType & rhs) {
    return SelfType(m_value + rhs.m_value);
  }

  template<typename OtherUnit>
  SelfType operator+ (const dimensioned<ValueType,OtherUnit,N> & rhs) {
    return SelfType(m_value + UnitType::template from_metres<ValueType>(OtherUnit::template to_metres<ValueType>(rhs.value())));
  }

  template<int otherN>
  dimensioned<ValueType,UnitType,N+otherN> operator* (const dimensioned<ValueType,UnitType,otherN> & rhs) {
    return dimensioned<ValueType,UnitType,N+otherN>(m_value * rhs.m_value);
  }

  template<int otherN,typename OtherUnit>
  dimensioned<ValueType,UnitType,N+otherN> operator* (const dimensioned<ValueType,OtherUnit,otherN> & rhs) {
    return dimensioned<ValueType,UnitType,N+otherN>(m_value * 
        UnitType::template from_metres<ValueType>(OtherUnit::template to_metres<ValueType>(rhs.value())));
  }

  friend std::ostream& operator <<(std::ostream& outputStream, const SelfType & self) { 
    std::string dimensionSuffix = N != 1 ? std::to_string(N) : "";
    outputStream << self.m_value << ' ' << UnitType::print() << dimensionSuffix;
    return outputStream;
  }

  ValueType value() const {
    return m_value;
  }

  private:
    ValueType m_value;
};

