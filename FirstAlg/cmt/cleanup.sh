# echo "cleanup FirstAlg v0 in /junofs/users/huyuxiang/juno/offline/Examples"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/sl6_amd64_gcc830/Pre-Release/J20v1r1-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtFirstAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtFirstAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=FirstAlg -version=v0 -path=/junofs/users/huyuxiang/juno/offline/Examples  $* >${cmtFirstAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=FirstAlg -version=v0 -path=/junofs/users/huyuxiang/juno/offline/Examples  $* >${cmtFirstAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtFirstAlgtempfile}
  unset cmtFirstAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtFirstAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtFirstAlgtempfile}
unset cmtFirstAlgtempfile
return $cmtcleanupstatus

