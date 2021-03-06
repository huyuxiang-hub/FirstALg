#-- start of make_header -----------------

#====================================
#  Document FirstAlg_python
#
#   Generated Fri Dec 11 15:19:34 2020  by huyuxiang
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_FirstAlg_python_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FirstAlg_python_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FirstAlg_python

FirstAlg_tag = $(tag)

#cmt_local_tagfile_FirstAlg_python = $(FirstAlg_tag)_FirstAlg_python.make
cmt_local_tagfile_FirstAlg_python = $(bin)$(FirstAlg_tag)_FirstAlg_python.make

else

tags      = $(tag),$(CMTEXTRATAGS)

FirstAlg_tag = $(tag)

#cmt_local_tagfile_FirstAlg_python = $(FirstAlg_tag).make
cmt_local_tagfile_FirstAlg_python = $(bin)$(FirstAlg_tag).make

endif

include $(cmt_local_tagfile_FirstAlg_python)
#-include $(cmt_local_tagfile_FirstAlg_python)

ifdef cmt_FirstAlg_python_has_target_tag

cmt_final_setup_FirstAlg_python = $(bin)setup_FirstAlg_python.make
cmt_dependencies_in_FirstAlg_python = $(bin)dependencies_FirstAlg_python.in
#cmt_final_setup_FirstAlg_python = $(bin)FirstAlg_FirstAlg_pythonsetup.make
cmt_local_FirstAlg_python_makefile = $(bin)FirstAlg_python.make

else

cmt_final_setup_FirstAlg_python = $(bin)setup.make
cmt_dependencies_in_FirstAlg_python = $(bin)dependencies.in
#cmt_final_setup_FirstAlg_python = $(bin)FirstAlgsetup.make
cmt_local_FirstAlg_python_makefile = $(bin)FirstAlg_python.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)FirstAlgsetup.make

#FirstAlg_python :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'FirstAlg_python'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FirstAlg_python/
#FirstAlg_python::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of install_python_header ------


installarea = ${CMTINSTALLAREA}
install_python_dir = $(installarea)

ifneq ($(strip "$(source)"),"")
src = ../$(source)
dest = $(install_python_dir)/python
else
src = ../python
dest = $(install_python_dir)
endif

ifneq ($(strip "$(offset)"),"")
dest = $(install_python_dir)/python
endif

FirstAlg_python :: FirstAlg_pythoninstall

install :: FirstAlg_pythoninstall

FirstAlg_pythoninstall :: $(install_python_dir)
	@if [ ! "$(installarea)" = "" ] ; then\
	  echo "installation done"; \
	fi

$(install_python_dir) ::
	@if [ "$(installarea)" = "" ] ; then \
	  echo "Cannot install header files, no installation source specified"; \
	else \
	  if [ -d $(src) ] ; then \
	    echo "Installing files from $(src) to $(dest)" ; \
	    if [ "$(offset)" = "" ] ; then \
	      $(install_command) --exclude="*.py?" $(src) $(dest) ; \
	    else \
	      $(install_command) --exclude="*.py?" $(src) $(dest) --destname $(offset); \
	    fi ; \
	  else \
	    echo "no source  $(src)"; \
	  fi; \
	fi

FirstAlg_pythonclean :: FirstAlg_pythonuninstall

uninstall :: FirstAlg_pythonuninstall

FirstAlg_pythonuninstall ::
	@if test "$(installarea)" = ""; then \
	  echo "Cannot uninstall header files, no installation source specified"; \
	else \
	  echo "Uninstalling files from $(dest)"; \
	  $(uninstall_command) "$(dest)" ; \
	fi


#-- end of install_python_header ------
#-- start of cleanup_header --------------

clean :: FirstAlg_pythonclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FirstAlg_python.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

FirstAlg_pythonclean ::
#-- end of cleanup_header ---------------
