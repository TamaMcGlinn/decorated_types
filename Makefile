compile=clang++ -Wall -Wfatal-errors -std=c++11

all: basic dimensioned si mpl_si

basic: basic_unittype.h basic.cc
	$(compile) basic.cc -o basic

dimensioned: dimensioned.h dimensioned.cc
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
	rm -f *~ basic mpl_si si cscope* tags
