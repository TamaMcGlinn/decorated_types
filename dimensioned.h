#include <string>

namespace dimensional {

  #include "distance_units.h"
  #include "time_units.h"

  template<typename ValueType, typename DistanceUnit, int DistanceDimension = 1, typename TimeUnit = Second, int TimeDimension = 0>
  struct dimensioned
  {
    typedef dimensioned<ValueType,DistanceUnit,DistanceDimension,TimeUnit,TimeDimension> SelfType;
    
    // the following shorthand refers to dimensioned with only the same valuetype
    template<typename distU, int distD, typename timeU, int timeD>
    using dim = dimensioned<ValueType, distU, distD, timeU, timeD>;

    //implicit conversion from ValueType
    dimensioned(ValueType v) : m_value(v) {}
    
    //implicit conversion to   ValueType - preferably this 
    //should only be possible if all dimensions are 0
    operator ValueType(){ return m_value; }

    template<typename OtherDistanceUnit, typename OtherTimeUnit>
    dimensioned(const dim<OtherDistanceUnit,DistanceDimension,OtherTimeUnit,TimeDimension> & rhs) {
      m_value = rhs.value();
      for(int i = 0; i < DistanceDimension; ++i){
        m_value = DistanceUnit::template from_metres<ValueType>(OtherDistanceUnit::template to_metres<ValueType>(m_value));
        // this ensures that 1m2 = 100 * 100 cm2 - apply the conversion from_metres (times 100) twice
        
        // note that one or the other or none of these two loops is entered, as
        // (0 < N && 0 < -N) is false for all N
      }
      for(int i = 0; i < -DistanceDimension; ++i){
        m_value = DistanceUnit::template to_metres<ValueType>(OtherDistanceUnit::template from_metres<ValueType>(m_value));
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
      for(int i = 0; i < TimeDimension; ++i){
        m_value = TimeUnit::template from_seconds<ValueType>(OtherTimeUnit::template to_seconds<ValueType>(m_value));
      }
      for(int i = 0; i < -TimeDimension; ++i){
        m_value = TimeUnit::template to_seconds<ValueType>(OtherTimeUnit::template from_seconds<ValueType>(m_value));
      }
    }

    SelfType operator+ (const SelfType & rhs) const {
      return SelfType(m_value + rhs.m_value);
    }

    SelfType operator- (const SelfType & rhs) const {
      return SelfType(m_value - rhs.m_value);
    }

    void operator+= (const SelfType & rhs) {
      m_value += rhs.m_value;
    }

    void operator-= (const SelfType & rhs) {
      m_value -= rhs.m_value;
    }

    template<typename ScalarType>
    SelfType operator* (const ScalarType & rhs) const {
      return SelfType(m_value * rhs);
    }

    template<typename ScalarType>
    void operator*= (const ScalarType & rhs) {
      m_value *= rhs;
    }

    template<typename AnyValueType, typename AnyDistanceUnit, typename AnyTimeUnit>
    void operator*= (const dimensioned<AnyValueType,AnyDistanceUnit,0,AnyTimeUnit,0> & rhs) {
      m_value *= rhs.value();
    }

    template<typename OtherDistanceUnit, int OtherDistanceDimension, typename OtherTimeUnit, int OtherTimeDimension>
    dim<DistanceUnit,DistanceDimension+OtherDistanceDimension,TimeUnit,TimeDimension+OtherTimeDimension> operator* (
        const dim<OtherDistanceUnit,OtherDistanceDimension,OtherTimeUnit,OtherTimeDimension> & rhs) const {
      const dim<DistanceUnit,OtherDistanceDimension,TimeUnit,OtherTimeDimension> & unitsConverted = rhs;
      return dim<DistanceUnit,DistanceDimension+OtherDistanceDimension,TimeUnit,TimeDimension+OtherTimeDimension>(
          m_value * unitsConverted.value()
      );
    }

    template<typename ScalarType>
    SelfType operator/ (const ScalarType & rhs) const {
      return SelfType(m_value / rhs);
    }

    template<typename ScalarType>
    void operator/= (const ScalarType & rhs) {
      m_value /= rhs;
    }

    template<typename AnyValueType, typename AnyDistanceUnit, typename AnyTimeUnit>
    void operator/= (const dimensioned<AnyValueType,AnyDistanceUnit,0,AnyTimeUnit,0> & rhs) {
      m_value /= rhs.value();
    }

    template<typename OtherDistanceUnit, int OtherDistanceDimension, typename OtherTimeUnit, int OtherTimeDimension>
    dim<DistanceUnit,DistanceDimension-OtherDistanceDimension,TimeUnit,TimeDimension-OtherTimeDimension> operator/ (
        const dim<OtherDistanceUnit,OtherDistanceDimension,OtherTimeUnit,OtherTimeDimension> & rhs) const {
      const dim<DistanceUnit,OtherDistanceDimension,TimeUnit,OtherTimeDimension> & unitsConverted = rhs;
      return dim<DistanceUnit,DistanceDimension-OtherDistanceDimension,TimeUnit,TimeDimension-OtherTimeDimension>(
          m_value / unitsConverted.value()
      );
    }

  private:
    template<int dimension, typename Unit>
    static std::string GetDimensionalSuffix() {
      if (dimension == 0){
        return "";
      } else {
        std::string numSuffix = dimension != 1 ? std::to_string(dimension) : "";
        return Unit::print() + numSuffix;
      }
    }

  public:
    friend std::ostream& operator <<(std::ostream& outputStream, const SelfType & self) {
      std::string distanceDimensionSuffix = GetDimensionalSuffix<DistanceDimension, DistanceUnit>();
      std::string timeDimensionSuffix = GetDimensionalSuffix<TimeDimension, TimeUnit>();
      outputStream << self.m_value << ' ' << distanceDimensionSuffix << timeDimensionSuffix;
      return outputStream;
    }

    ValueType value() const {
      return m_value;
    }

    private:
      ValueType m_value;
  };

  #include "distance_shorthands.h"
  #include "time_shorthands.h"
};
