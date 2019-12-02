CXXFLAGS += -Wall

SRC = snowmen.cpp
OP = snowmen

LIBS = -lGL -lGLU -lm -lglut

all:: $(OP)

clean::
	-$(RM) $(OP)

$(OP): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
