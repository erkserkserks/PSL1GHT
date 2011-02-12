TARGETS	:=	geohot ps3load raw2h sprxlinker cgcomp PS3Py

all:
	@for dir in $(TARGETS); do \
		$(MAKE) --no-print-directory -C $$dir; \
	done

clean:
	@for dir in $(TARGETS); do \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install:
	@mkdir -p $(PSL1GHT)/host/bin
	@for dir in $(TARGETS); do \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

.PHONY: all install clean
