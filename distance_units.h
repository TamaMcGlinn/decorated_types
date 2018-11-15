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
