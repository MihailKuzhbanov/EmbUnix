#XML Generator
#Script return .ST file, ready for translation to .C

import wx
import os, sys, platform, time, traceback, getopt
import version

from docutil import *
from IDEFrame import IDEFrame, AppendMenu
from IDEFrame import TITLE, EDITORTOOLBAR, FILEMENU, EDITMENU, DISPLAYMENU, PROJECTTREE, POUINSTANCEVARIABLESPANEL, LIBRARYTREE, PAGETITLES
from IDEFrame import EncodeFileSystemPath, DecodeFileSystemPath
from editors.Viewer import Viewer
from PLCControler import PLCControler
from dialogs import ProjectDialog
from dialogs.AboutDialog import ShowAboutDialog

import PLCControler as PC

filepathXML = "/home/username/Beremiz/NextProjectNew/plc.xml"
filepathST = "/home/username/Beremiz/NextProjectNew/generated_plc.st"

app = PLCControler()
app.OpenXMLFile(filepathXML)
app.SaveXMLFile(filepathXML)
res = app.GenerateProgram(filepathST)
print(res[0])
