import matplotlib.pyplot as plt

# x-axis values
#x = [1,2,3,4,5,6,7,8,9,10]
# y-axis values
#y = [1,2,3,4,5,6,7,8,9,10]
for i in range (10):
    for j in range (10):
        a=i
        b=j
        plt.scatter(i, j,  color= "black",marker= ".", s=50)
        print("(%f,%f)" %(a,b))

# x-axis label
#plt.xlabel('x - axis')
# frequency label
#plt.ylabel('y - axis')
# plot title
#plt.title('My canvas')
# showing legend
#plt.legend()

# function to show the plot
plt.show()
