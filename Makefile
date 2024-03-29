# $Id: Makefile,v 1.16 1999/12/06 04:49:24 paulmcav Exp $
#
##### MACROS #####

# linux settings
LIBDIR	= -L/usr/X11R6/lib

# sfsu settings
INCDIR = -I/usr/local/include -I.
#LIBDIR = -L$(HOME)/lib -L/usr/openwin/lib

XLIBS	= -lX11 -lXext -lXi -lXmu

# glx / mesagl
GL	= GL

GL_LIBS	= $(LIBDIR) -lglut -lGLU -l$(GL) -lm $(XLIBS)

#debugging!
#MALLOC	= -static -lefence
#PROF = -pg
#OPTIMIZE = -O3 -funroll-loops

CC	= g++
CFLAGS	= $(INCDIR) -Wall -g $(PROF) $(OPTIMIZE)
LD	= $(CC)
LDFLAGS	= -lpng $(PROF)
LIBS	= $(GL_LIBS) $(MALLOC)
OBJ	= obj/

##### RULES #####

VPATH	= .:$(OBJ)

.SUFFIXES:

$(OBJ)%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)%.d: %.cpp
	@rm -f $@
	@$(SHELL) -ec '$(CC) -MM $(CPPFLAGS) $< | \
	sed -e "1s|^|$(OBJ)|" -e "s|:| $@:|" \
	> $@; \
	[ -s $@ ] || rm -f $@'

$(OBJ)%.d: %.c
	@rm -f $@
	@$(SHELL) -ec '$(CC) -MM $(CPPFLAGS) $< | \
	sed -e "1s|^|$(OBJ)|" -e "s|:| $@:|" \
	> $@; \
	[ -s $@ ] || rm -f $@'

##### TARGETS #####

TARGETS= glpool

all: do-it-all

ifeq (.depend,$(wildcard .depend))
include .depend
do-it-all: $(TARGETS)
else
do-it-all: dep
endif

sources	=$(wildcard *.cc)

GLPOOL	= glpool.o \
	  glcWindow.o \
	  glcViewport.o \
	  glUtil.o \
	  glpng.o \
	  glm.o \
	  cAudio.o \
	  cTexMaps.o \
	  cWMain.o \
	  cVmain.o \
	  cVstatus.o \
	  cTable.o \
	  cBall.o \
	  cBallList.o 

SOUDI	= soudi.o

TEST	= test.o glm.o

SCOTT	= scott.o 

glpool	: ${addprefix $(OBJ),$(GLPOOL)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

test	: ${addprefix $(OBJ),$(TEST)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	
soudi	: ${addprefix $(OBJ),$(SOUDI)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	
scott	: ${addprefix $(OBJ),$(SCOTT)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	
dep	: ${addprefix $(OBJ),$(sources:.cc=.d)}
	@echo Creating dependencies.
	@echo "include ${addprefix $(OBJ), $(sources:.cc=.d)}" > .depend

tags	:
	@ctags -f .tags *.cc *.c *.h

cleanbak:
	find . -name "*~" -exec rm -f '{}' ';'
	
clean	: cleanbak
	rm -f core $(OBJ)*.o

semiclean: clean
	rm -f .depend
	rm -f $(OBJ)*.d

realclean: semiclean
	rm -f $(TARGETS)

archive	: semiclean
	strip $(TARGETS)
	tar -cvf - * | gzip -c > ../glpool.tar.gz
	
