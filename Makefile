AUXFILES := Makefile # Non-source, non-object
PROJDIRS := src include
CPPSRCFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.cpp")
CPPHDRFILES := $(shell find $(PROJDIRS) -mindepth 1 -maxdepth 3 -name "*.h")
CPPOBJFILES := $(patsubst %.cpp,%.o,$(CPPSRCFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPSRCFILES))
ALLFILES := $(CPPSRCFILES) $(CPPHDRFILES) $(AUXFILES)

.PHONY: clean

CPPFLAGS := -g -Wall -Wextra 
INCLUDES := -I./include
LIBS := -lmagic

all: hawking

hawking: $(CPPOBJFILES)

	g++ $(CPPFLAGS) $(INCLUDES) -o hawking $(CPPOBJFILES) $(LIBS)

%.o: %.cpp Makefile
	g++ $(CPPFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	-@$(RM) $(wildcard $(CPPOBJFILES) hawking)

todolist:
	-@for file in $(ALLFILES); do fgrep -H -e TODO -e FIXME -e ENHANCE $$file; done; true
