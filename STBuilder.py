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

filepath = "/home/username/Beremiz/projects/plc.xml"

PC.GenerateProgram(filepath)
