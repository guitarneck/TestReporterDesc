CXX			= g++
CXXFLAGS	= -std=c++11 -I/opt/local/include/
LDFLAGS		= 

EXEC		= TestReporterDesc
LIB			= TestReporterDesc.a

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

OBJ = TestReporterDesc.o 

all: $(EXEC) \
	clean

$(EXEC): $(OBJ) 
	@ar cr $(LIB) $^

TestReporterDesc.o: TestReporterDesc.cpp \
                    TestReporterDesc.h

.PHONY: clean clean-build clean-all

clean-all: clean clean-build

clean:
	@rm -f $(OBJ)

clean-build: | clean
	@rm -f $(LIB)
