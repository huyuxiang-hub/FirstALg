#!/bin/bash

test_type=$1;
echo "test_type=" $test_type

if [ $test_type -eq 8 ]
then
     cat >split_io_data.txt<<EOF
num_of_hit             average_time(ms)
EOF
     for (( i=1 ; i <=2; i++ ))
     do
        echo $i
        #python test.py --num $i --Type ${test_type} >> type8.log.txt
        python test.py --num $i --Type ${test_type}
     done
    
     root draw_type8.C
  

fi



if [ $test_type -eq 1 ] || [ $test_type -eq 2 ] || [ $test_type -eq 4 ]
then

if [ -f test_mem.sh ]
then 
     rm -rf test_mem.sh
fi


#para_2=(" "  "--type2-branch-buffer" "--type2-branch-buffer"  "--type2-branch-buffer")
#para_val_2=(" " "3200" "320" "320000")

#para_2=(" "  "--type2-branch-buffer" "--type2-branch-buffer")
#para_val_2=(" " "3200" "320")

#para_2=(" " "--type2-cmp")
#para_val_2=(" " 1)

para_2=(" ")
para_val_2=(" ")

#para_1=(" " "--type1-cmp")
#para_val_1=(" " 1)

para_1=(" " )
para_val_1=(" ")

para_4=(" " )
para_val_4=(" ")

if [ ${test_type} -eq 1 ]
then
   cat>gra-info-main-${test_type}<<EOF
Memory number_of_array(M)  memory_need(MB) 
EOF
size=${#para_1[*]}
fi


if [ ${test_type} -eq 2 ]
then
    cat>gra-info-main-${test_type}<<EOF
Memory number_of_hit(M)  memory_need(MB)
EOF
    size=${#para_2[*]}
fi

if [ ${test_type} -eq 4 ]
then
    cat>gra-info-main-${test_type}<<EOF
Read-the-Root-file number_of_hit(M)  memory_need(MB)
EOF
    size=${#para_4[*]}
fi

   
cat>gra-info-sub-$test_type<<EOF
${size}
EOF

    for (( k=1 ; k <=${size} ; k++ ))
       do
          if [ -f TYPE-${test_type}-${k}  ]
          then
            rm -rf TYPE-${test_type}-${k}
          fi
          cat>"test_mem.sh"<<EOF
#!/bin/bash
cur_pid=\$\$
parent_id=\$( ps l | awk -v pid=\$cur_pid '\$3==pid {print  \$4}' )
rss=\$(ps l | awk -v id=\$parent_id '\$3==id {print  \$8}' )
echo -n " " \${rss} " " >> TYPE-${test_type}-$k
EOF
          chmod +x "test_mem.sh"     


 
          for i in {1..6}
          do
             echo $i
             echo  -n " " $i >> TYPE-${test_type}-${k}
             /usr/bin/time -v python test.py --num $i --Type ${test_type}  $(eval echo '$'{para_$test_type['$'['$'k-1]]}) $(eval echo '$'{para_val_$test_type['$'['$'k-1]]})  >& mem.txt
             grep Maximum mem.txt | awk -F ": " '{print $2}' >> TYPE-${test_type}-${k}
          done 


          awk '{print $1, ($4-$2)/1024}' TYPE-${test_type}-$k >& TYPE-${test_type}-$k-tmp       
if [ $k -eq 1 ] 
then
   cat>>gra-info-sub-$test_type<<EOF
TYPE-${test_type}-$k-tmp  default  $k $[$k+19] 1.5
EOF
else         
   cat>>gra-info-sub-$test_type<<EOF
TYPE-${test_type}-$k-tmp  $(eval echo '$'{para_$test_type['$'['$'k-1]]}-'$'{para_val_$test_type['$'['$'k-1]]}) $k $[$k+19] 1.5
EOF
fi
    done

root -l 'draw_mem.C("./gra-info-main-'${test_type}'" , "./gra-info-sub-'${test_type}'")'

fi


