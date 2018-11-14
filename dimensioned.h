#include <string>

// TODO template this for float
struct Metre {
  static float to_metres(float in) {
    return in;
  }
  static float from_metres(float in) {
    return in;
  }
  static std::string print(){
    return "m";
  }
};

struct Foot {
  static float to_metres(float in) {
    return in / 3.1; // TODO put in actual value
  }
  static float from_metres(float in) {
    return in * 3.1;
  }
  static std::string print(){
    return "ft";
  }
};

struct Centimetre {
  static float to_metres(float in) {
    return in / 100.0;
  }
  static float from_metres(float in) {
    return in * 100.0;
  }
  static std::string print(){
    return "cm";
  }
};

struct Decimetre {
  static float to_metres(float in) {
    return in / 10.0;
  }
  static float from_metres(float in) {
    return in * 10.0;
  }
  static std::string print(){
    return "dm";
  }
};

struct NauticalMile {
  static float to_metres(float in) {
    return in * 1600.0; // TODO put in actual value
  }
  static float from_metres(float in) {
    return in / 1600.0;
  }
  static std::string print(){
    return "m";
  }
};

struct Kilometre {
  static float to_metres(float in) {
    return in * 1000.0;
  }
  static float from_metres(float in) {
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
      m_value = UnitType::from_metres(OtherUnit::to_metres(m_value));
    }
  }

  SelfType operator+ (const SelfType & rhs) {
    return SelfType(m_value + rhs.m_value);
  }

  template<typename OtherUnit>
  SelfType operator+ (const dimensioned<ValueType,OtherUnit,N> & rhs) {
    return SelfType(m_value + UnitType::from_metres(OtherUnit::to_metres(rhs.value())));
  }

  template<int otherN>
  dimensioned<ValueType,UnitType,N+otherN> operator* (const dimensioned<ValueType,UnitType,otherN> & rhs) {
    return dimensioned<ValueType,UnitType,N+otherN>(m_value * rhs.m_value);
  }

  template<int otherN,typename OtherUnit>
  dimensioned<ValueType,UnitType,N+otherN> operator* (const dimensioned<ValueType,OtherUnit,otherN> & rhs) {
    return dimensioned<ValueType,UnitType,N+otherN>(m_value * UnitType::from_metres(OtherUnit::to_metres(rhs.value())));
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

