#-- start of make_header -----------------

#====================================
#  Library FirstAlg
#
#   Generated Fri Oct 30 15:46:34 2020  by huyuxiang
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_FirstAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FirstAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_FirstAlg

FirstAlg_tag = $(tag)

#cmt_local_tagfile_FirstAlg = $(FirstAlg_tag)_FirstAlg.make
cmt_local_tagfile_FirstAlg = $(bin)$(FirstAlg_tag)_FirstAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

FirstAlg_tag = $(tag)

#cmt_local_tagfile_FirstAlg = $(FirstAlg_tag).make
cmt_local_tagfile_FirstAlg = $(bin)$(FirstAlg_tag).make

endif

include $(cmt_local_tagfile_FirstAlg)
#-include $(cmt_local_tagfile_FirstAlg)

ifdef cmt_FirstAlg_has_target_tag

cmt_final_setup_FirstAlg = $(bin)setup_FirstAlg.make
cmt_dependencies_in_FirstAlg = $(bin)dependencies_FirstAlg.in
#cmt_final_setup_FirstAlg = $(bin)FirstAlg_FirstAlgsetup.make
cmt_local_FirstAlg_makefile = $(bin)FirstAlg.make

else

cmt_final_setup_FirstAlg = $(bin)setup.make
cmt_dependencies_in_FirstAlg = $(bin)dependencies.in
#cmt_final_setup_FirstAlg = $(bin)FirstAlgsetup.make
cmt_local_FirstAlg_makefile = $(bin)FirstAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)FirstAlgsetup.make

#FirstAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'FirstAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = FirstAlg/
#FirstAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

FirstAlglibname   = $(bin)$(library_prefix)FirstAlg$(library_suffix)
FirstAlglib       = $(FirstAlglibname).a
FirstAlgstamp     = $(bin)FirstAlg.stamp
FirstAlgshstamp   = $(bin)FirstAlg.shstamp

FirstAlg :: dirs  FirstAlgLIB
	$(echo) "FirstAlg ok"

cmt_FirstAlg_has_prototypes = 1

#--------------------------------------

ifdef cmt_FirstAlg_has_prototypes

FirstAlgprototype :  ;

endif

FirstAlgcompile : $(bin)FirstAlg.o ;

#-- end of libary_header ----------------
#-- start of libary ----------------------

FirstAlgLIB :: $(FirstAlglib) $(FirstAlgshstamp)
	$(echo) "FirstAlg : library ok"

$(FirstAlglib) :: $(bin)FirstAlg.o
	$(lib_echo) "static library $@"
	$(lib_silent) [ ! -f $@ ] || \rm -f $@
	$(lib_silent) $(ar) $(FirstAlglib) $(bin)FirstAlg.o
	$(lib_silent) $(ranlib) $(FirstAlglib)
	$(lib_silent) cat /dev/null >$(FirstAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

#
# We add one level of dependency upon the true shared library 
# (rather than simply upon the stamp file)
# this is for cases where the shared library has not been built
# while the stamp was created (error??) 
#

$(FirstAlglibname).$(shlibsuffix) :: $(FirstAlglib) requirements $(use_requirements) $(FirstAlgstamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) if test "$(makecmd)"; then QUIET=; else QUIET=1; fi; QUIET=$${QUIET} bin="$(bin)" ld="$(shlibbuilder)" ldflags="$(shlibflags)" suffix=$(shlibsuffix) libprefix=$(library_prefix) libsuffix=$(library_suffix) $(make_shlib) "$(tags)" FirstAlg $(FirstAlg_shlibflags)
	$(lib_silent) cat /dev/null >$(FirstAlgshstamp)

$(FirstAlgshstamp) :: $(FirstAlglibname).$(shlibsuffix)
	$(lib_silent) if test -f $(FirstAlglibname).$(shlibsuffix) ; then cat /dev/null >$(FirstAlgshstamp) ; fi

FirstAlgclean ::
	$(cleanup_echo) objects FirstAlg
	$(cleanup_silent) /bin/rm -f $(bin)FirstAlg.o
	$(cleanup_silent) /bin/rm -f $(patsubst %.o,%.d,$(bin)FirstAlg.o) $(patsubst %.o,%.dep,$(bin)FirstAlg.o) $(patsubst %.o,%.d.stamp,$(bin)FirstAlg.o)
	$(cleanup_silent) cd $(bin); /bin/rm -rf FirstAlg_deps FirstAlg_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
FirstAlginstallname = $(library_prefix)FirstAlg$(library_suffix).$(shlibsuffix)

FirstAlg :: FirstAlginstall ;

install :: FirstAlginstall ;

FirstAlginstall :: $(install_dir)/$(FirstAlginstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(FirstAlginstallname) :: $(bin)$(FirstAlginstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(FirstAlginstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##FirstAlgclean :: FirstAlguninstall

uninstall :: FirstAlguninstall ;

FirstAlguninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(FirstAlginstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of libary -----------------------
#-- start of dependencies ------------------
ifneq ($(MAKECMDGOALS),FirstAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
ifneq ($(MAKECMDGOALS),FirstAlgprototype)

$(bin)FirstAlg_dependencies.make : $(use_requirements) $(cmt_final_setup_FirstAlg)
	$(echo) "(FirstAlg.make) Rebuilding $@"; \
	  $(build_dependencies) -out=$@ -start_all $(src)FirstAlg.cc -end_all $(includes) $(app_FirstAlg_cppflags) $(lib_FirstAlg_cppflags) -name=FirstAlg $? -f=$(cmt_dependencies_in_FirstAlg) -without_cmt

-include $(bin)FirstAlg_dependencies.make

endif
endif
endif

FirstAlgclean ::
	$(cleanup_silent) \rm -rf $(bin)FirstAlg_deps $(bin)FirstAlg_dependencies.make
#-- end of dependencies -------------------
#-- start of cpp_library -----------------

ifneq (,)

ifneq ($(MAKECMDGOALS),FirstAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)FirstAlg.d

$(bin)$(binobj)FirstAlg.d :

$(bin)$(binobj)FirstAlg.o : $(cmt_final_setup_FirstAlg)

$(bin)$(binobj)FirstAlg.o : $(src)FirstAlg.cc
	$(cpp_echo) $(src)FirstAlg.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(FirstAlg_pp_cppflags) $(lib_FirstAlg_pp_cppflags) $(FirstAlg_pp_cppflags) $(use_cppflags) $(FirstAlg_cppflags) $(lib_FirstAlg_cppflags) $(FirstAlg_cppflags) $(FirstAlg_cc_cppflags)  $(src)FirstAlg.cc
endif
endif

else
$(bin)FirstAlg_dependencies.make : $(FirstAlg_cc_dependencies)

$(bin)FirstAlg_dependencies.make : $(src)FirstAlg.cc

$(bin)$(binobj)FirstAlg.o : $(FirstAlg_cc_dependencies)
	$(cpp_echo) $(src)FirstAlg.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(FirstAlg_pp_cppflags) $(lib_FirstAlg_pp_cppflags) $(FirstAlg_pp_cppflags) $(use_cppflags) $(FirstAlg_cppflags) $(lib_FirstAlg_cppflags) $(FirstAlg_cppflags) $(FirstAlg_cc_cppflags)  $(src)FirstAlg.cc

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: FirstAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(FirstAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

FirstAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library FirstAlg
	-$(cleanup_silent) cd $(bin) && \rm -f $(library_prefix)FirstAlg$(library_suffix).a $(library_prefix)FirstAlg$(library_suffix).$(shlibsuffix) FirstAlg.stamp FirstAlg.shstamp
#-- end of cleanup_library ---------------
