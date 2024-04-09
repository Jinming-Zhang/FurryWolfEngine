from bindings.modules import FurrywolfEngine
import os
import multiprocessing
import threading


class ProcessManager:
    engineEditorDic = {}

    def RunEngine(projectDir, editor):
        print("Number of CPU:", multiprocessing.cpu_count())
        parentConn, childConn = multiprocessing.Pipe()

        process = multiprocessing.Process(
            target=RunEngineProcess,
            args=(projectDir, childConn))
        process.start()

        ProcessManager.engineEditorDic[process] = editor
        t = threading.Thread(
            target=ProcessManager.checkProcessStatus, args=(parentConn, process))
        t.start()

    def checkProcessStatus(parentConn, process):
        status = parentConn.recv()
        if (status[0] == 0):
            print("Engine exited succesfully")
            ProcessManager.engineEditorDic[process].engineClosed()
        else:
            print("Engine sending something weird")
        process.kill()


def RunEngineProcess(projectDir, conn):
    os.chdir(projectDir)
    print(projectDir)
    FurrywolfEngine.RavUp(projectDir)
    conn.send([0])
