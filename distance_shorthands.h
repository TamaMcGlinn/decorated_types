template<typename ValueType, typename UnitType = Metre>
using distance = dimensioned<ValueType, UnitType, 1>;

template<typename ValueType, typename UnitType = Metre>
using surface = dimensioned<ValueType, UnitType, 2>;

template<typename ValueType, typename UnitType = Metre>
using volume = dimensioned<ValueType, UnitType, 3>;
