CXXFLAGS += -Wall

SRC = snowmen.cpp vector3f.cpp consts.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))
OP = snowmen

LIBS = -lGL -lGLU -lm -lglut

all:: $(OP)

clean::
	-$(RM) $(OP) $(OBJ)

asdf::
	-echo a $(SRC) B $(OBJ) C $(OP)

$(OP): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
