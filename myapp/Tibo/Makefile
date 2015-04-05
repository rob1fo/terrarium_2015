
-include $(TOPDIR)/.config	# Current configuration

# Sub-directories containing system tasks/libraries

SUBDIRS  = tibo_test1

# Create the list of installed runtime modules (INSTALLED_DIRS)

ifeq ($(CONFIG_WINDOWS_NATIVE),y)
define ADD_DIRECTORY
  INSTALLED_DIRS  += $(if $(wildcard .\$1\Makefile),$1,)
endef
else
define ADD_DIRECTORY
  INSTALLED_DIRS  += $(if $(wildcard ./$1/Makefile),$1,)
endef
endif

$(foreach DIR, $(SUBDIRS), $(eval $(call ADD_DIRECTORY,$(DIR))))

all: nothing
.PHONY: nothing context depend clean distclean

define SDIR_template
$(1)_$(2):
	$(Q) $(MAKE) -C $(1) $(2) TOPDIR="$(TOPDIR)" APPDIR="$(APPDIR)"
endef

$(foreach SDIR, $(INSTALLED_DIRS), $(eval $(call SDIR_template,$(SDIR),depend)))
$(foreach SDIR, $(INSTALLED_DIRS), $(eval $(call SDIR_template,$(SDIR),clean)))
$(foreach SDIR, $(INSTALLED_DIRS), $(eval $(call SDIR_template,$(SDIR),distclean)))

nothing:

install:

context:

depend: $(foreach SDIR, $(INSTALLED_DIRS), $(SDIR)_depend)

clean: $(foreach SDIR, $(INSTALLED_DIRS), $(SDIR)_clean)

distclean: $(foreach SDIR, $(INSTALLED_DIRS), $(SDIR)_distclean)
