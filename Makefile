compile=clang++ -Wall -Wfatal-errors -std=c++1y -I ~/code/boost_1_64_0 -o numerals -lgmpxx -lgmp

targets=basic metre dimensioned si mpl_si

all: $(targets)

basic: basic_unittype.h basic.cc
	$(compile) basic.cc -o basic

metre: metre.cc
	$(compile) metre.cc -o metre

dimensioned: dimensioned.h dimensioned.cc distance_units.h distance_shorthands.h time_units.h time_shorthands.h
	$(compile) dimensioned.cc -o dimensioned

si: si.h si.cc
	$(compile) si.cc -o si

mpl_si: mpl_si.h mpl_si.cc
	$(compile) mpl_si.cc -o mpl_si

tags: *.cc *.h
	find . -name "*.cc" -or -name "*.h" > cscope.files
	cscope -bcqR
	ctags -R

clean:
	rm -f *~ cscope* tags $(targets)
