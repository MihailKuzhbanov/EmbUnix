#XML Generator
#Script return .ST file, ready for translation to .C


from IDEFrame import EncodeFileSystemPath, DecodeFileSystemPath
import PLCControler as PC

filepathXML = "/home/username/Beremiz/NextProjectNew/plc.xml"
filepathST = "/home/username/Beremiz/NextProjectNew/generated_plc.st"

app = PLCControler()
app.OpenXMLFile(filepathXML)
app.SaveXMLFile(filepathXML)
res = app.GenerateProgram(filepathST)
print(res[0])
