#!/bin/bash
 
#/junofs/users/huyuxiang/jobmom.sh $$ 

mem_used=`free -m | sed -n '2p' |awk '{print $3}'`
echo ${mem_used}

echo "hello shell!"
