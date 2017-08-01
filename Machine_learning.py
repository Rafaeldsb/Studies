import numpy as np
import matplotlib.pyplot as plt

n = 0.5

point = [
    [.3,    .7,     1],
    [-.6,   .3,     0],
    [.1,   -.8,    0],
    [.6,    -.45,   1]
]

w = [.8, -.5]


def o(x, y):
    return x*w[0] + y*w[1]


def l(u):
    if u >= 0:
        return 1
    else:
        return 0


def training():
    h = 0
    print("w¹ = {:.3f}   w² = {:.3f}".format(w[0], w[1]))
    while True:
        er = 0
        for i in range(len(point)):
            x = point[i][0]
            y = point[i][1]
            c = point[i][2]

            e = c - l(o(x, y))

            w[0] = w[0] + n * e * x
            w[1] = w[1] + n * e * y
            if e != 0:
                print("w¹ = {:.3f}   w² = {:.3f}".format(w[0], w[1]))
                er = 1

        h = h + 1
        if h == 1000000 or er == 0:
            break


def print_graph():
    for i in range(len(point)):
        if point[i][2] == 1:
            plt.plot(point[i][0], point[i][1], 'b.')
        else:
            plt.plot(point[i][0], point[i][1], 'r.')
    a = (w[0]/w[1])

    print("g(x) = {:.2f}x".format( a))

    x1 = np.arange(-0.5, 0.5,0.2)
    y1 = a * x1

    plt.plot(x1, y1, 'g')

    plt.axis([-0.9, 0.9, -0.9, 0.9])
    plt.grid()

    plt.show()

# - 0,88 = -.3m # m = -0,88/0,3


training()
print_graph()
