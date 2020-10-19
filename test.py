#!/usr/bin/env python



import argparse
parser = argparse.ArgumentParser(description='count to script')
#parser.add_argument("--name", type=str, default="0", help='input name')
parser.add_argument("--num", type=int, default=1,help='input total num')
parser.add_argument("--Type",type=int, default=2,help='input storage type')
args = parser.parse_args()
#print(args.name)
#print(args.age)



import Sniper
task = Sniper.Task("task")  # create a Task instance
task.setEvtMax(100)  # events loop number (3 times)
task.setLogLevel(2)  # the SniperLog print level

import FirstAlg
alg = task.createAlg("FirstAlg")  # create a FirstAlg instance
alg.property("TheValue").set(args.num)
alg.property("Thetype").set(args.Type)
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
