from tkinter import *

from tkinter import messagebox

window = Tk()

window.title("unit 1")

window.geometry('350x200')

def clicked():

   messagebox.showinfo('basics', 'print,input,read,write')
   res = messagebox.askyesno('feedback','learnt print/read/write/input')

btn = Button(window,text='unit1', command=clicked)

btn.grid(column=0,row=0)

window.mainloop()
