# $Id: Makefile,v 1.5 1999-10-19 22:29:10 paulmcav Exp $
#
##### MACROS #####

# linux settings
LIBDIR	= -L/usr/X11R6/lib

# sfsu settings
#INCDIR = -I$(HOME)/include
#LIBDIR = -L$(HOME)/lib -L/usr/openwin/lib

XLIBS	= -lX11 -lXext -lXi -lXmu

# glx / mesagl
GL	= MesaGL
#GL	= GL

GL_LIBS	= $(LIBDIR) -lglut -lMesaGLU -l$(GL) -lm $(XLIBS)

#debugging!
#MALLOC	 -static -lefence

CC	= g++
CFLAGS	= $(INCDIR) -Wall -g
LD	= $(CC)
LDFLAGS	=
LIBS	= $(GL_LIBS) $(MALLOC)
OBJ	= obj/

##### RULES #####

VPATH	= .:$(OBJ)

.SUFFIXES:

$(OBJ)%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)%.d: %.cc
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
	  cMenu.o \
	  cHelp.o \
	  readtex.o

SOUDI	= soudi.o

TEST	= test.o

glpool	: ${addprefix $(OBJ),$(GLPOOL)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

test	: ${addprefix $(OBJ),$(TEST)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	
soudi	: ${addprefix $(OBJ),$(SOUDI)}
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
	
dep	: ${addprefix $(OBJ),$(sources:.cc=.d)}
	@echo Creating dependencies.
	@echo "include ${addprefix $(OBJ), $(sources:.cc=.d)}" > .depend

tags	:
	@ctags *.cc *.c *.h

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
	
