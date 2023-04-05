from tkinter import *

from tkinter import Menu

window = Tk()

window.title("application")

menu = Menu(window)

new_item = Menu(menu)

new_item.add_command(label='New')

new_item.add_separator()

new_item.add_command(label='Open')

new_item.add_separator()

new_item.add_command(label='Edit')
#new_item.add_separator()

new_item.add_command(label='close all')

menu.add_cascade(label='File', menu=new_item)

window.config(menu=menu)

window.mainloop()
