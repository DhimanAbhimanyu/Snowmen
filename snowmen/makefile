CXX = g++
CXXFLAGS += -Wall

INC = colors.hpp vectors.hpp tree.hpp drawing.hpp
INC += display_colors.hpp light0_consts.hpp moving_object.hpp
INC += consts.hpp globals.hpp snowman_position.hpp
INC += displaygroupfunc.hpp display.hpp draw.hpp
INC += globals.hpp rotation.hpp snowman.hpp shading.hpp

SRC = main.cpp display.cpp snowman.cpp shading.cpp tree.cpp drawing.cpp

DEP = $(patsubst %.cpp,.%.d,$(SRC))
OBJ = $(patsubst %.cpp,%.o,$(SRC))
OP = snowmen

LIBS = -lGL -lGLU -lm -lglut -lGLEW

all:: $(OP)

clean::
	-$(RM) $(OP) $(OBJ)

tags:: TAGS

wc::
	wc $(INC) $(SRC)

qwer::
	-echo inc $(INC) src $(SRC)

$(OP): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -c -MF $@ $<

TAGS: $(SRC) $(INC)
	etags -o $@ $^

include $(DEP)
