#include <type_traits> //for std::is_same

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
namespace mpl = boost::mpl;
using namespace mpl::placeholders;

typedef mpl::vector_c<int,1,0,0,0,0,0,0> mass;
typedef mpl::vector_c<int,0,1,0,0,0,0,0> length;
typedef mpl::vector_c<int,0,0,1,0,0,0,0> time;
typedef mpl::vector_c<int,0,0,0,1,0,0,0> charge;
typedef mpl::vector_c<int,0,0,0,0,1,0,0> temperature;
typedef mpl::vector_c<int,0,0,0,0,0,1,0> luminosity;
typedef mpl::vector_c<int,0,0,0,0,0,0,1> angle;
typedef mpl::vector_c<int,0,0,0,0,0,0,0> scalar;

//composites
typedef mpl::vector_c<int,0,2,0,0,0,0,0> area;
typedef mpl::vector_c<int,0,1,-1,0,0,0,0> velocity;
typedef mpl::vector_c<int,0,1,-2,0,0,0,0> acceleration;
typedef mpl::vector_c<int,1,1,-1,0,0,0,0> momentum;
typedef mpl::vector_c<int,1,1,-2,0,0,0,0> force;

//units
struct Newton {
	typedef force dimension;
};

struct Metre {
	typedef length dimension;
};

struct Centimetre {
	typedef length dimension;
};

struct Gram {
	typedef mass dimension;
};

struct Second {
	typedef time dimension;
};

struct MetresPerSecondPerSecond {
	typedef acceleration dimension;
};

//default units for each dimension
template<class Dimensions>
struct DefaultUnit {};
template<> struct DefaultUnit<length> { typedef Metre type; };
template<> struct DefaultUnit<mass> { typedef Gram type; };
template<> struct DefaultUnit<force> { typedef Newton type; };
template<> struct DefaultUnit<time> { typedef Second type; };
template<> struct DefaultUnit<acceleration> { typedef MetresPerSecondPerSecond type; };

//template instantiations for manipulation the mpl::vector_c dimensions
template<class D1, class D2>
struct multiplyDimensions : mpl::transform<D1,D2,mpl::plus<_,_> > {};

template<class D1, class D2>
struct divideDimensions : mpl::transform<D1,D2,mpl::minus<_,_> > {};

//main class for clients to use
template<class T, class Dimensions, class Unit = typename DefaultUnit<Dimensions>::type>
struct quantity {
	static_assert(mpl::equal<typename Unit::dimension,Dimensions>::type::value, "Unit - Dimension mismatch e.g. mass of 5 cm");

	explicit quantity(T x) : m_value(x) {
	}

	quantity<T,Dimensions,Unit> operator+(quantity<T,Dimensions,Unit> rhs){
		return quantity<T,Dimensions,Unit>( value() + rhs.value() );
	}

	quantity<T,Dimensions,Unit> operator-(quantity<T,Dimensions,Unit> rhs){
		return quantity<T,Dimensions,Unit>( value() - rhs.value() );
	}

	template<class otherDimensions>
	quantity<T, typename multiplyDimensions<Dimensions,otherDimensions>::type> operator*(quantity<T,otherDimensions> rhs){
		return quantity<T, typename multiplyDimensions<Dimensions,otherDimensions>::type>( value() * rhs.value() );
	}

	template<class otherDimensions>
	quantity<T, typename divideDimensions<Dimensions,otherDimensions>::type> operator/(quantity<T,otherDimensions> rhs){
		return quantity<T, typename divideDimensions<Dimensions,otherDimensions>::type>( value() / rhs.value() );
	}

	template<class otherDimensions>
	quantity(quantity<T, otherDimensions> const & rhs) : m_value( rhs.value() ) {
		static_assert( mpl::equal<Dimensions,otherDimensions>::type::value, "Tried to assign incompatible SI types" );
	}

	T value() const { return m_value; }
private:
	T m_value;
};

