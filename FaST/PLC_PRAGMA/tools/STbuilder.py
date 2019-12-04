#XML Generator
#Script return .ST file, ready for translation to .C

from IDEFrame import EncodeFileSystemPath, DecodeFileSystemPath
from PLCControler import PLCControler

filepathXML = "/home/pi/PLC_PRAGMA/input/plc.xml"
#TODO: change path to relative or local or global var
filepathST = "/home/pi/PLC_PRAGMA/input/generated_plc.st"

app = PLCControler()
app.OpenXMLFile(filepathXML)
res = app.GenerateProgram(filepathST)
print(res[0])
