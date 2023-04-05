from tkinter import filedialog
from tkinter import *
root = Tk()
filename =  filedialog.asksaveasfilename(initialdir = "/",title = "Select file",filetypes = (("jpeg files","*.jpg"),("all files","*.*")))
print (filename)
attachment = open(filename, "rb")