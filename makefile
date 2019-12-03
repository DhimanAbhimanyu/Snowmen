CXX = g++
CXXFLAGS += -Wall

INC = branch.hpp colors.hpp display_colors.hpp displaygroupfunc.hpp
INC += display.hpp draw.hpp drawing.hpp globals.hpp light0_consts.hpp
INC += moving_object.hpp object.hpp rotation.hpp shading.hpp snowman.hpp
INC += snowman_position.hpp tree.hpp tree_position.hpp tree_set.hpp util.hpp
INC += vectors.hpp branch.hpp branch_position.hpp
INC += leaf.hpp leaf_position.hpp

SRC = branch.cpp display.cpp drawing.cpp main.cpp shading.cpp
SRC += snowman.cpp tree.cpp branch.cpp leaf.cpp

DEP = $(patsubst %.cpp,.%.d,$(SRC))
OBJ = $(patsubst %.cpp,%.o,$(SRC))
OP = snowman

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
