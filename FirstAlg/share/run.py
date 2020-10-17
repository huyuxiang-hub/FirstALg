#!/usr/bin/python

import Sniper
task = Sniper.Task("task")
task.asTop()
task.setLogLevel(3)

import FirstAlg
alg = task.createAlg("FirstAlg/alg_example")
alg.property("EvtTimeGap").set(300000)

import BufferMemMgr
bufMgr = task.createSvc("BufferMemMgr")
bufMgr.property("TimeWindow").set([-0.01, 0.01]);

import DataRegistritionSvc
task.property("svcs").append("DataRegistritionSvc")

import RootIOSvc
import os
if os.path.exists("result.root") :
    ## for reading
    riSvc = task.createSvc("RootInputSvc/InputSvc")
    riSvc.property("InputFile").set(["result.root"])
    alg.property("RunMode").set(1)
    alg.setLogLevel(2)
else :
    ## for generating
    roSvc = task.createSvc("RootOutputSvc/OutputSvc")
    roSvc.property("OutputStreams").set({"/Event/PhyEvent": "result.root"})
    alg.property("RunMode").set(2)

task.setEvtMax(10)
task.show()
task.run()
