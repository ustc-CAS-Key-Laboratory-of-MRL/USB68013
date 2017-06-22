
import os
import time


def CheckDirAndCreate(path):
    if not os.path.exists(path):
        os.makedirs(path)
def gettimestr():
    return time.strftime(' %Y%m%d-%H_%M_%S',time.localtime(time.time()))
#time.sleep(1.0)




d="backup"
CheckDirAndCreate(d)
frecord=file(d+'/'+'README','a')

backup_filenames=['dllmain.cpp']
timestring=gettimestr()
frecord.write(timestring+'  ')
frecord.write( raw_input('Input record:') )
frecord.write('\n')
frecord.close()

for i in backup_filenames:
    f=file(i,'rb')
    a=f.read()
    f.close()

    
    
    f=file(d+"/"+timestring+' - '+i,'wb')
    f.write(a)
    f.close()
