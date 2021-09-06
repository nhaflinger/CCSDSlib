swig -c++ -python -o ccsdslib_wrap.cpp ccsdslib.i
g++ -fPIC -c ccsdslib_wrap.cpp  -I/usr/include/python3.8
g++  -shared -lpython3.8  ccsdslib_wrap.o  -L../CCSDSlib -lCCSDS -o _ccsdslib.so
