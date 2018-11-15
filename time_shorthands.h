template<typename ValueType, typename UnitType = Second>
using time = dimensioned<ValueType, Metre, 0, UnitType, 1>;

template<typename ValueType, typename DistanceUnitType = Metre, typename TimeUnitType = Second>
using speed = dimensioned<ValueType, DistanceUnitType, 1, TimeUnitType, -1>;

