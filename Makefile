SUBDIRS			:=	program1 program2

CC = g++
STDFLAGS = -std=c++11
LDLIBS = -pthread

export CC
export STDFLAGS
export LDLIBS


all: subdirs

.PHONY: subdirs
subdirs: $(SUBDIRS)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

.PHONY: clean
clean: $(SUBDIRS)
	@for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done

.PHONY: purge
purge: clean $(SUBDIRS)
	@for dir in $(SUBDIRS); do \
		$(MAKE) purge -C $$dir; \
	done

