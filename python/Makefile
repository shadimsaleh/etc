all: my_sample.so pysample.so

my_sample.so: my_sample.o
	g++ -shared -o $@ $< -lboost_python -lGL -L/opt/local/lib -lRTC -lcoil 
#	g++ -bundle -o $@ $< -lboost_python -L/opt/local/lib -lpython2.7 

my_sample.o: my_sample.cpp
	g++ -o $@ -c $< -I/usr/include/python2.6 -I/usr/include/rtm/idl
#	g++ -o $@ -c $< -I/opt/local/include -I/opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

pysample.so: pysample.o
	g++ -shared -o $@ $< -lboost_python

pysample.o: pysample.cpp
	g++ -o $@ -c $< -I/usr/include/python2.6

clean:
	-rm *~ *.o *.so
