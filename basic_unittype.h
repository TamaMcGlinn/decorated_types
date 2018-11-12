
struct Apples {};
struct Oranges {};

template<typename NumericType, typename Unit>
struct basic_unit {
  typedef basic_unit<NumericType, Unit> SelfType;

	explicit basic_unit(NumericType x) : m_value(x) {
	}

	basic_unit(SelfType const & rhs) : m_value( rhs.value() ) {
	}

	bool operator==(SelfType const & rhs) {
	  return value() == rhs.value();
	}

	SelfType operator+(SelfType rhs){
		return SelfType( value() + rhs.value() );
	}

	SelfType operator-(SelfType rhs){
		return SelfType( value() - rhs.value() );
	}

	SelfType operator*(SelfType rhs){
		return SelfType( value() * rhs.value() );
	}

	SelfType operator/(SelfType rhs){
		return SelfType( value() / rhs.value() );
	}

  template<typename OtherNumericType>
	SelfType operator*(OtherNumericType rhs){
		return SelfType( value() * rhs );
	}

  template<typename OtherNumericType>
	SelfType operator/(OtherNumericType rhs){
		return SelfType( value() / rhs );
	}

  template<typename OtherNumericType>
  void operator*=(OtherNumericType rhs) {
    m_value *= rhs;
  }

	NumericType value() const { return m_value; }
private:
	NumericType m_value;
};


