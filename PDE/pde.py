import math
import matplotlib.pyplot as plt

n = 1000
t = 8
nu = 12
l = 4*math.pi
a = 3


def u1(x, t, k):
    mu1 = (-nu+math.sqrt(nu**2-4*a**2*(math.pi*k/l)**2))/2
    Ak = (2*l*(l*math.sin(math.pi*k)*math.sin(l)+math.pi*k*math.cos(math.pi*k)*math.cos(k) -
               math.pi*k))/(l**3-l*math.pi**2*k**2)+(2*l*(math.cos(math.pi*k)-1))/(l*math.pi*k)
    return Ak*math.e**(t*mu1)*math.sin(math.pi*k*x/l)


def u2(x, t, k0):
    Ak0 = (2*l*(l*math.sin(math.pi*k0)*math.sin(l)+math.pi*k0*math.cos(math.pi*k0)*math.cos(k0) -
                math.pi*k0))/(l**3-l*math.pi**2*k0**2)+(2*l*(math.cos(math.pi*k0)-1))/(l*math.pi*k0)
    return Ak0*math.e**(t*-nu/2)*math.sin(math.pi*k0*x/l)


def u3(x, t, k):
    Ak = (2*l*(l*math.sin(math.pi*k)*math.sin(l)+math.pi*k*math.cos(math.pi*k)*math.cos(k) -
               math.pi*k))/(l**3-l*math.pi**2*k**2)+(2*l*(math.cos(math.pi*k)-1))/(l*math.pi*k)
    return Ak*math.e**(t*-nu/2)*math.cos((t*math.sqrt(4*a**2*(math.pi*k/l)**2 - nu**2))/2)*math.sin(math.pi*k*x/l)


x = []
y = []

for i in range(n+1):
    s = 0
    x.append(i*l/n)
    for k in range(1, 1002):
        if l*math.pi**2*k**2 == l**3:
            continue
        D = nu**2-4*a**2*(math.pi*k/l)**2
        if D > 0:
            #print(f'D>0, {D} {k}')
            s += u1(x[i], t, k)
        elif D == 0:
            #print(f'D==0, {D} {k}')
            s += u2(x[i], t, k)
        else:
            #print(f'D<0, {D} {k}')
            s += u3(x[i], t, k)

    y.append(s)

plt.plot(x, y, color='blue', label='u(x, t)', linewidth=0.75)
plt.grid()
plt.xlabel('x')
plt.ylabel('u')
plt.title('u(x,t)')
plt.savefig(f'u_at_{t}.png')
