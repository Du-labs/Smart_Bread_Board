from tkinter import *
root = Tk()
root.title('Grapic')
canvas = Canvas(root,width=500,height=300,bg="red")
canvas.pack()
for i in range(36):
    x=50 + (i*40)
    canvas.create_line(x,800,x,-850,width=4)
for i in range(24):
    y=100 - (i*40)
    canvas.create_line(1600,-y,10,-y,width=4)
root.mainloop()