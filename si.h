namespace SI {
  //Length, Mass, Time, Current, Temperature, Luminosity, Substance
  template<class BaseValue, int L, int M, int T, int Curr = 0, int Temp = 0, int Lum = 0, int Sub = 0>
  class unit {
    public:
      unit(const BaseValue val) : value(val) {}
      
      BaseValue value;
      
      const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> operator+(const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> & rhs) const{
        return unit(this->value+rhs.value);
      }
      
      const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> operator-(const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> & rhs) const{
        return unit(this->value-rhs.value);
      }
      
      void operator+=(const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> & rhs){
        this->value += rhs.value;
      }
      
      void operator-=(const unit<BaseValue, L, M, T, Curr, Temp, Lum, Sub> & rhs){
        this->value -= rhs.value;
      }
      
      template<int L2, int M2, int T2, int Curr2 = 0, int Temp2 = 0, int Lum2 = 0, int Sub2 = 0>
      const unit<BaseValue, L+L2, M+M2, T+T2, Curr+Curr2, Temp+Temp2, Lum+Lum2, Sub+Sub2> operator*(const unit<BaseValue, L2, M2, T2, Curr2, Temp2, Lum2, Sub2> & rhs) const{
        return unit<BaseValue, L+L2, M+M2, T+T2, Curr+Curr2, Temp+Temp2, Lum+Lum2, Sub+Sub2>(this->value*rhs.value);
      }
      
      template<int L2, int M2, int T2, int Curr2 = 0, int Temp2 = 0, int Lum2 = 0, int Sub2 = 0>
      const unit<BaseValue, L-L2, M-M2, T-T2, Curr-Curr2, Temp-Temp2, Lum-Lum2, Sub-Sub2> operator/(const unit<BaseValue, L2, M2, T2, Curr2, Temp2, Lum2, Sub2> & rhs) const{
        return unit<BaseValue, L-L2, M-M2, T-T2, Curr-Curr2, Temp-Temp2, Lum-Lum2, Sub-Sub2>(this->value/rhs.value);
      }
      
      operator BaseValue() const{ return value; }
      
    private:
  };

  //typedef unit<BaseValue, 1, 0, 0> length<BaseValue>
  //Length, Mass, Time, Current, Temperature, Luminosity, Substance
  //using alias declarations instead of typedefs, to allow you to pass down the required BaseValue instead of hardcoding
   template<class BaseValue>
   using length = unit<BaseValue, 1, 0, 0>;
   template<class BaseValue>
   using mass = unit<BaseValue, 0, 1, 0>;
   template<class BaseValue>
   using time = unit<BaseValue, 0, 0, 1>;
   template<class BaseValue>
   using current = unit<BaseValue, 0, 0, 0, 1, 0, 0, 0>;
   template<class BaseValue>
   using temperature = unit<BaseValue, 0, 0, 0, 0, 1, 0, 0>;
   template<class BaseValue>
   using luminosity = unit<BaseValue, 0, 0, 0, 0, 0, 1, 0>;
   template<class BaseValue>
   using substance = unit<BaseValue, 0, 0, 0, 0, 0, 0, 1>;
 
   //composite units
   template<class BaseValue>
   using speed = unit<BaseValue, 1, 0, -1>;
   template<class BaseValue>
   using acceleration = unit<BaseValue, 1, 0, -2>;
   template<class BaseValue>
   using area = unit<BaseValue, 2, 0, 0>;
   template<class BaseValue>
   using volume = unit<BaseValue, 3, 0, 0>;

  //for using non-standard measurements there is a to and a from function for each
   template<class BaseValue>
   const temperature<BaseValue> toCelsius(const temperature<BaseValue> K){
     return K-temperature<BaseValue>(273.15);
   }
   template<class BaseValue>
   const temperature<BaseValue> fromCelsius(const temperature<BaseValue> C){
     return C+temperature<BaseValue>(273.15);
   }
};
