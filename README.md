This repository shows some ways of using C++ templates to enforce stronger than usual typing. This
can be used to prevent errors at compile-time such as assigning a speed to a variable representing
a surface area, or comparing apples to donkeys.

# Basic

```
basic_unittype.h and basic.cc
```

The most basic definition is just a wrapper around some numerical type, such as int, float or
mpq_class. It takes an extra typename which is used as a marker, so that this must match for the
parameters being used. It is still possible to convert, using the .value() member function, and the
explicit conversion from a numerical type argument to basic_unit.

This is similar to the Ada practice of defining your own derived types. For example, the below code
will not compile because it doesn't make any sense to compare apples with oranges.

```
struct Apples {};
struct Oranges {};

basic_unit<int,Apples> apples(5);
basic_unit<int,Oranges> oranges(5);

bool same = apples == oranges;
```

All operators must be explicitly defined in basic_unit to pass on that operation to the underlying
type. For example, below we make clear that adding is only possible between identically defined unit
types, but it should be possible to use `*=` on integer apples with a plain, unadorned float:

```
	SelfType operator+(SelfType rhs){
		return SelfType( value() + rhs.value() );
	}

  template<typename OtherNumericType>
  void operator*=(OtherNumericType rhs) {
    m_value *= rhs;
  }
```

# SI - internal standard units for physics calculations

```
si.h and si.cc
```

The basic restraint, which is supported natively in Ada, is not correct in some cases. For instance,
when multiplying two lengths, it is incorrect to assign this to a length variable. The result of
multiplying two lengths should be a surface area.

Again, the defined type accepts a type template parameter which is the underlying type for the calculations,
but now we add a number of non-type, integer template parameters to the unit class template representing the
dimensions desired. The first 3 integer represent Length, Mass and Time in that order, so for
example:

```
unit<float, 1, 0, 0> length(3); // 3 metres
unit<float, 3, 0, 0> volume(3); // 3 cubic metres
unit<float, 0, 0, -1> frequency(3); // 3 times per second
unit<float, 1, 0, -1> speed(3); // 3 metres per second
```

Unlike with the basic_unit example, assigning the product of two lengths to a length is now illegal:

```
length = length * length; // illegal
volume = length * length * length; // 3m * 3m * 3m = 27 cubic metres
```

# MPL_SI

Some of the code in si.h can be made simpler by using boost::mpl::vector_c to represent the
dimensions. Instead of this:

```
template<int L2, int M2, int T2, int Curr2 = 0, int Temp2 = 0, int Lum2 = 0, int Sub2 = 0>
const unit<BaseValue, L+L2, M+M2, T+T2, Curr+Curr2, Temp+Temp2, Lum+Lum2, Sub+Sub2> operator*(const unit<BaseValue, L2, M2, T2, Curr2, Temp2, Lum2, Sub2> & rhs) const{
  return unit<BaseValue, L+L2, M+M2, T+T2, Curr+Curr2, Temp+Temp2, Lum+Lum2, Sub+Sub2>(this->value*rhs.value);
}
```

We have only to instantiate mpl::transform (call a metaprogramming, compile-time function) and apply
that to obtain the correct dimensions for the output variable:

```
template<class D1, class D2>
struct multiplyDimensions : mpl::transform<D1,D2,mpl::plus<_,_> > {};

template<class otherDimensions>
quantity<T, typename multiplyDimensions<Dimensions,otherDimensions>::type> operator*(quantity<T,otherDimensions> rhs){
	return quantity<T, typename multiplyDimensions<Dimensions,otherDimensions>::type>( value() * rhs.value() );
}
```

In additional, mpl_si adds the concept of Units; it should be impossible to assign nautical miles to
imperial miles, for example. These are implemented akin to the first basic example, as a marker
typename that must match. There is still a flaw a need to work out; if we define the unit as a
simple marker, there must be some way to aggregate units when doing arithmetic on quantities, so
that the unit of the following will in some way represent newtons:

```
quantity<float, mass> m(2.5f);
quantity<float, acceleration> a(1.0f);

m * a; // expression should be in float Newtons
```

This example also shows how static_assert can be used to make compiler errors more helpful.

```
clang++ -Wall -Wfatal-errors -std=c++11 mpl_si.cc -o mpl_si
In file included from mpl_si.cc:1:
./mpl_si.h:93:3: fatal error: static_assert failed "Tried to assign incompatible SI types"
                static_assert( mpl::equal<Dimensions,otherDimensions>::type::value, "Tried to assign incompatible SI types" );
                ^              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
mpl_si.cc:8:16: note: in instantiation ... etc.
        len1 = len1 + quantity<float, mass>(2.0f); // won't compile, mass + length != length
                      ^
1 error generated.
Makefile:12: recipe for target 'mpl_si' failed
make: *** [mpl_si] Error 1
```

