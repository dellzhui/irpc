pyinstaller --onefile -w --clean --hidden-import tkinter --hidden-import tkinter.filedialog --hidden-import tkinter.messagebox --hidden-import json --hidden-import json .\irpc_server.py

del /F /S /Q build irpc_server.spec
rd build\irpc_server build

@pause