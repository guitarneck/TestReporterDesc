# TestReporterDesc
A reporter for UnitTest++, in Desc style.

# In Makefile

```make
REPORTER ?= desc

ifeq ($(REPORTER),desc)
 -include Makefile-desc.mk
endif

mploc := /opt/local

CXX	:= g++
CXXFLAGS:= -std=c++11 -I${mploc}/include/
LDFLAGS := -L${mploc}/lib -lUnitTest++ ${reporter_dir}/${reporter_lib}

.PHONY: reporters
reporters:
	$(info building reporter)
	@cd ${reporter_dir}; make all
```
