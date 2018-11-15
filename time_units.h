struct Second {
  template<typename ValueType>
  static ValueType to_seconds(ValueType in) {
    return in;
  }
  template<typename ValueType>
  static ValueType from_seconds(ValueType in) {
    return in;
  }
  static std::string print(){
    return "s";
  }
};
struct Minute {
  template<typename ValueType>
  static ValueType to_seconds(ValueType in) {
    return in * 60.0;
  }
  template<typename ValueType>
  static ValueType from_seconds(ValueType in) {
    return in / 60.0;
  }
  static std::string print(){
    return "min";
  }
};
struct Hour {
  template<typename ValueType>
  static ValueType to_seconds(ValueType in) {
    return in * 3600.0;
  }
  template<typename ValueType>
  static ValueType from_seconds(ValueType in) {
    return in / 3600.0;
  }
  static std::string print(){
    return "h";
  }
};
