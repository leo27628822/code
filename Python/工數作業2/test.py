import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import math
from math import factorial
import sympy

def f1( t ) :
    x = 5/3 - np.exp(-t/2)*8/5-np.exp(-3*t)/15
    return x
def f2( t ) :
    y = 2/3-np.exp(-t/2)*26/15+np.exp(-3*t)*16/15
    return y

t = np.linspace( 0, 10 )
y1 = f1(t)
y2 = f2(t)
plt.plot( t,y1,'-',t,y2,'--' )
plt.xlabel( 't' )
plt.ylabel( 'I1(t) & I2(t)' )
plt.title( 'Plot of System of differential equations' )

plt.text( 3.5, 0, 'Copyright @ 10927143' )
plt.show( )