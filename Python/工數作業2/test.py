import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import math
from math import factorial
import sympy

def f( x ) :
    y = x + x**2 + x* np.exp(x)
    return y

x = np.linspace( 0, 1 )
y = f( x )
plt.plot( x, y )
plt.xlabel( 'x' )
plt.ylabel( 'y' )
plt.title( 'Plot of f(x,y)' )

plt.text( 0.6, 0.3, 'Copyright @ 10927143' )
plt.show( )