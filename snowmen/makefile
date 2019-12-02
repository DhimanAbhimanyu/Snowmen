CXXFLAGS += -Wall

SRC = snowmen.cpp
INC = util.hpp consts.hpp
OP = snowmen

LIBS = -lGL -lGLU -lm -lglut

all:: $(OP)

clean::
	-$(RM) $(OP)

$(OP): $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
