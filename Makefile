# /currconv/Makefile

MODULES = currconv

EXTENSION = currconv

DATA = currconv--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

all:
	@rm -f $(LD_LIBRARY_PATH)/postgresql/libgetconv.so
	@cp ./libgetconv.so $(LD_LIBRARY_PATH)/postgresql
	
unistall:
	@rm -f $(LD_LIBRARY_PATH)/postgresql/libgetconv.so
