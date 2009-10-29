DIST_TARGET_PATH := $(IMAGE)/system/development/headers

all:

deps:

install:
	@cp -rp * $(DIST_TARGET_PATH)/
	@ln -s atheos $(DIST_TARGET_PATH)/syllable
	rm -rf $(DIST_TARGET_PATH)/CVS
	rm $(DIST_TARGET_PATH)/Makefile

doc:

install-doc:

dist: install

clean:
