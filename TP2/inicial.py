import os

A, B, C, D = 1.2, 0.6, 0.8, 0.3
STEP = 0.1

def f(x, y):
    return A*x - B*x*y

def g(x, y):
    return D*x*y - C*y

def pasoGauss(x, y):
    xp1 = x + STEP*f(x, y)
    yp1 = y + STEP*g(x, y)
    return xp1, yp1

#====COSAS DEL RUNGE-KUTTA====
def m1(x, y):
    return f(x, y)

def k1(x, y):
    return g(x, y)

def m2(x, y):
    return f(x + (STEP*m1(x,y))/2, y + (STEP*k1(x,y))/2)

def k2(x, y):
    return g(x + (STEP*m1(x,y))/2, y + (STEP*k1(x,y))/2)

def m3(x, y):
    return f(x + (STEP*m2(x,y))/2, y + (STEP*k2(x,y))/2)

def k3(x, y):
    return g(x + (STEP*m2(x,y))/2, y + (STEP*k2(x,y))/2)

def m4(x, y):
    return f(x + STEP*m3(x,y), y + STEP*k2(x,y))

def k4(x, y):
    return g(x + STEP*m2(x,y), y + STEP*k2(x,y))
#====COSAS DEL RUNGE-KUTTA====

def pasoRK4(x, y):
    xp1 = x + (STEP/6)*(m1(x, y) + 2*m2(x, y) + 2*m3(x, y) + m4(x, y))
    yp1 = y + (STEP/6)*(k1(x, y) + 2*k2(x, y) + 2*k3(x, y) + k4(x, y))
    return xp1, yp1

def main():
    t0, x0, y0 = 0, 2, 1
    tt, xx, yy = [t0], [x0], [y0]
    
    t, x, y = t0, x0, y0
    while t <= 30:
        t = t + STEP
        x, y = pasoRK4(x, y)
        tt.append(t)
        xx.append(x)
        yy.append(y)

    outputPath = os.path.join(os.getcwd(), "output.csv")
    with open(outputPath, "w") as file:
        file.write("t;x;y\n")
        for point in zip(tt, xx, yy):
            file.write(f'{point[0]:.5f};{point[1]:.5f};{point[2]:.5f}\n')

if __name__ == "__main__":
    main()
