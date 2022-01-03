import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import math
from math import factorial
import sympy

def f( x ) :
    y = 50*np.cos(10*math.sqrt(10)*x)
    return y

x = np.linspace( 0, 2 )
y = f( x )
plt.plot( x, y )
plt.xlabel( 't' )
plt.ylabel( 'Q' )
plt.title( 'Plot of Q(t)' )

plt.text( 0.6, 0.3, 'Copyright @ 10927143' )
plt.show( )