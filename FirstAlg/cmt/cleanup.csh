# echo "cleanup FirstAlg v0 in /junofs/users/huyuxiang/juno/offline/Examples"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc830/Pre-Release/J20v1r1-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtFirstAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtFirstAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=FirstAlg -version=v0 -path=/junofs/users/huyuxiang/juno/offline/Examples  $* >${cmtFirstAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=FirstAlg -version=v0 -path=/junofs/users/huyuxiang/juno/offline/Examples  $* >${cmtFirstAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtFirstAlgtempfile}
  unset cmtFirstAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtFirstAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtFirstAlgtempfile}
unset cmtFirstAlgtempfile
exit $cmtcleanupstatus

