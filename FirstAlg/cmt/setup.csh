# echo "setup FirstAlg v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/juno/offline/Examples"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc830/Pre-Release/J20v1r1-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtFirstAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtFirstAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=FirstAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/juno/offline/Examples  -no_cleanup $* >${cmtFirstAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=FirstAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/juno/offline/Examples  -no_cleanup $* >${cmtFirstAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtFirstAlgtempfile}
  unset cmtFirstAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtFirstAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtFirstAlgtempfile}
unset cmtFirstAlgtempfile
exit $cmtsetupstatus

