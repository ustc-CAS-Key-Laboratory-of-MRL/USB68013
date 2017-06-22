#coding=UTF-8
import wx
import os

# wildcard = "C source (*.c)|*.c|"     \
           # "C++ source (*.cpp)|*.cpp|" \
           # "All files (*.*)|*.*"
wildcard = "C/C++ source (*.c*)|*.c*"     \

prefix='extern "C" __declspec(dllexport) '


app=wx.App()
b=wx.Frame(None)

dlg = wx.FileDialog(
            b, message="Choose a file",
            defaultDir=os.getcwd(), 
            defaultFile="",
            wildcard=wildcard,
            style=wx.OPEN
            )

# Show the dialog and retrieve the user response. If it is the OK response, 
# process the data.
if dlg.ShowModal() == wx.ID_OK:
    # This returns a Python list of files that were selected.
    path = dlg.GetPath()


# Destroy the dialog. Don't do this until you are done with it!
# BAD things can happen otherwise!
dlg.Destroy()


f=file(path,'r')
lines=f.readlines()
f.close()

import re

p=re.compile("\w+\s\w+\(.*\)")
f=file(path+'.txt','w')
for i in lines:
    # clear '\n'
    i=i[:-1]
    if len(i)<4:
        continue
    
    
    match=p.match(i)
    if match!=None:
        f.write(prefix)
        f.write(match.group())
        f.write(';\n')
        
f.close()

import sys
reload(sys)
sys.setdefaultencoding("gb2312")

os.system(path+'.txt')
