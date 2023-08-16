''' All this script does is launch all the c++ programs in 
    the correct order (Using python cause I'm lazy)
'''
import subprocess

subprocess.Popen(["start", "data_gen_a.exe"], shell=True)
subprocess.Popen(["start", "data_gen_b.exe"], shell=True)
subprocess.Popen(["start", "cmd", "/k", "data_display.exe"], shell=True)
