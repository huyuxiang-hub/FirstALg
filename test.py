#!/usr/bin/env python



import argparse
parser = argparse.ArgumentParser(description='count to script')
#parser.add_argument("--name", type=str, default="0", help='input name')
parser.add_argument("--num", type=int, default=1,help='input total num')
parser.add_argument("--Type",type=int, default=2,help='input storage type')
parser.add_argument("--type2-branch-buffer",type=int,default=32000,help='TBD')
parser.add_argument("--type1-cmp",type=int,default=0,help='TBD')
parser.add_argument("--type2-cmp",type=int,default=0,help='TBD')
parser.add_argument("--type5-read-time",type=int,default=1,help='TBD')
parser.add_argument("--type7-hit-num",type=int,default=500000,help='TBD')
args = parser.parse_args()
#print(args.name)
#print(args.age)



import Sniper
task = Sniper.TopTask("task")  # create a Task instance
task.setEvtMax(1)  # events loop number (3 times)
task.setLogLevel(2)  # the SniperLog print level

iotask = task
iotask = task.createTask("Task/detsimiotask")
import DataRegistritionSvc
iotask.createSvc("DataRegistritionSvc")
import BufferMemMgr
bufMgr = iotask.createSvc("BufferMemMgr")

import BufferMemMgr
bufMgr = task.createSvc("BufferMemMgr")

import RootIOSvc
ro = iotask.createSvc("RootOutputSvc/OutputSvc")
output_streams = {}
output_streams["/Event/Sim"] ="splitevent"
ro.property("OutputStreams").set(output_streams)




import FirstAlg
alg = task.createAlg("FirstAlg")  # create a FirstAlg instance
alg.property("TheValue").set(args.num)
alg.property("Thetype").set(args.Type)
alg.property("type2-branch-buffer").set(args.type2_branch_buffer)
alg.property("type1-compress").set(args.type1_cmp)
alg.property("type2-compress").set(args.type2_cmp)
alg.property("type7-hit-number").set(args.type7_hit_num)
alg.property("type5-read-time").set(args.type5_read_time)
#alg.property("Message").set(" the value is ")

 # = root writer ==
print("== Root Writer ==")
import RootWriter
rootwriter = task.createSvc("RootWriter")
rootwriter.property("Output").set({"DCS":"dcs.root"})

# = DataCollSvc =
print("== Data Collector Svc ==")
import DataCollSvc
data_coll_svc = task.createSvc("DataCollSvc")

# = timer svc =
try:
   import JunoTimer
   task.createSvc("JunoTimerSvc")
except:
   pass

task.run()
