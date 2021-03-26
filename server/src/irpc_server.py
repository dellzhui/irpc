import os
import json
import threading
from tkinter import filedialog
from tkinter import *
import socketserver

HOST, PORT = "0.0.0.0", 10201

file_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(0, file_dir)

class IRPCConfig:

    @staticmethod
    def get_config():
        try:
            with open('config.json', 'r') as f:
                return json.loads(f.read())
        except Exception as err:
            print('load_configs err:[' + str(err) + ']')
        return None

    @staticmethod
    def update_config(config):
        try:
            with open('config.json', 'w') as f:
                f.write(json.dumps(config))
        except Exception as err:
            print('load_configs err:[' + str(err) + ']')

class DBHandleTask(threading.Thread):
    def __init__(self, cb, paras):
        self.cb = cb
        self.paras = paras
        super().__init__()

    def run(self):
        if(self.cb != None):
            self.cb(self.paras)

class IRPCTCPHandler(socketserver.BaseRequestHandler):
    def __init__(self, request, client_address, server):
        self.config = IRPCConfig.get_config()
        super().__init__(request, client_address, server)

    def __get_cmd_from_request(self):
        try:
            cmd = None
            content = json.loads(self.data.decode()[0:-2])
            if(content['cmd_name'] == 'explorer'):
                cmd = 'start /b explorer {}'.format(content['paras'])
            elif(content['cmd_name'] == 'notepad'):
                cmd = 'start /b {} {}'.format(self.config['notepad_path'], content['paras'])
            print('cmd is {}'.format(cmd))
            return cmd
        except Exception as err:
            print('__get_cmd_from_request err:[' + str(err) + ']')
        return None

    def handle(self):
        self.data = self.request.recv(1024).strip()
        try:
            os.system(self.__get_cmd_from_request())
        except ImportError as err:
            print('handle err:[' + str(err) + ']')
        self.request.sendall('Command accepted complete'.encode(encoding='utf-8'))

class IRPCGui:
    def __init__(self):
        self.root = Tk()
        self.root.title('iRPC')

        self.e_Notepad = Entry(self.root)
        self.start_button = Button(self.root, text='启动', width=10, command=self.submit)
        self.started_button = Button(self.root, text='已启动', width=10)
        self.restart_button = Button(self.root, text='重启', width=10, command=self.restart)

        self.e_Notepad.insert(0, '输入文本编辑器路径')
        self.e_Notepad.grid(row=0, column=0, padx=10, pady=5)

        Button(self.root, text='浏览', width=10, command=self.open_src_file).grid(row=0, column=1, sticky=W, padx=10, pady=5)

        self.server = socketserver.TCPServer((HOST, PORT), IRPCTCPHandler)

        self.config = IRPCConfig.get_config()
        if(self.config == None or self.config == {} or self.config['notepad_path'] == None or self.config['notepad_path'] == ''):
            self.config = {}
        else:
            self.e_Notepad.delete(0, END)
            self.e_Notepad.insert(0, self.config['notepad_path'])
            self.submit()

    def open_src_file(self, dir='.'):
        try:
            notepad_path = filedialog.askopenfilename(title='open src file', initialdir=dir, filetypes=[('All Files', '*')])
            if(notepad_path != None and notepad_path != ''):
                self.e_Notepad.delete(0, END)
                self.e_Notepad.insert(0, notepad_path)
                self.config['notepad_path'] = notepad_path
                IRPCConfig.update_config(self.config)
                self.start_button.grid(row=4, column=0, sticky=W, padx=10, pady=5)
        except Exception as err:
            print('open_src_file err:[' + str(err) + ']')

    def tcp_server_task(self, paras):
        with self.server:
            self.server.serve_forever()

    def start_server(self):
        task = DBHandleTask(self.tcp_server_task, {'HOST':HOST, 'PORT':PORT})
        task.start()

    def submit(self):
        self.start_button.destroy()
        self.start_server()
        self.started_button.grid(row=4, column=0, sticky=W, padx=10, pady=5)
        self.restart_button.grid(row=4, column=1, sticky=W, padx=10, pady=5)

    def start(self):
        self.root.mainloop()

    def restart(self):
        self.root.destroy()
        self.server.shutdown()
        self.__init__()
        self.start()

def main(argv):
    gui = IRPCGui()
    gui.start()

if __name__ == "__main__":
   main(sys.argv[0:])
