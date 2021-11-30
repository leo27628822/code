# 10927143 王胤迦
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import math
from math import factorial
import sympy

X = np.linspace(-2*np.pi,2*np.pi,100)
Y = np.linspace(-2*np.pi,2*np.pi,100)
x,y = np.meshgrid(X,Y)
z = x*np.sin(y) + y*np.cos(x) - 0.5*(y**2)

plt.figure(2)
plt.contour( x,y,z,30 ) 
plt.xlabel( 'x' )
plt.ylabel( 'y' )
plt.title ( 'Contour Plot of f(x,y)' )
plt.text ( 1.7, -5, 'Copyright @ 10927143' ) # 請加上你的數位簽章
plt.show ()