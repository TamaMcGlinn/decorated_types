#include "mpl_si.h"

int main(){
	quantity<float, length, Metre> len1(1.0f);
	quantity<float, length> len2(3.0f); // default to SI unit; metre
	quantity<float, length, Metre> result(1.0f);
	result = len1 + len2;
	//len1 = len1 + quantity<float, mass>(2.0f); // won't compile, mass + length != length

	quantity<float, length, Centimetre> cms(1.0f);
	//result = cms; // won't compile, cannot assign metres to centimetres

	quantity<float, force> f(9.81f);
	quantity<float, mass> m(2.5f);
	quantity<float, acceleration> a(1.0f);

	//m * a; // TODO: should be valid expression of type float Newtons
}
