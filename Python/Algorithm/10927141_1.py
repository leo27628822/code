#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
8
-2 1 -3 4 -1 2 1 -5
16
13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7
'''

import numpy as np
import time

def FindMaximumSubArray( A, low, high ):
    if low == high :
        return low, high, A[low]
    else :
        mid = ( low + high ) // 2
        left_low, left_high, left_sum = FindMaximumSubArray( A, low, mid )
        right_low, right_high, right_sum = FindMaximumSubArray( A, mid+1, high )
        cross_low, cross_high, cross_sum = FindMaxCrossingSubArray( A, low, mid, high )
        if left_sum >= right_sum and left_sum >= cross_sum :
            return left_low, left_high, left_sum
        elif right_sum >= left_sum and right_sum >= cross_sum :
            return right_low, right_high, right_sum
        else :
            return cross_low, cross_high, cross_sum

def FindMaxCrossingSubArray( A, low, mid, high ):
    left_sum = -2147483648
    sum = 0
    max_left = mid
    for i in range ( mid, low, -1 ) :
        sum += A[i]
        if sum > left_sum :
            left_sum = sum
            max_left = i
    
    right_sum = -2147483648
    sum = 0
    max_right = mid + 1
    for i in range ( mid+1, high ) :
        sum += A[i]
        if sum > right_sum :
            right_sum = sum
            max_right = i

    return max_left, max_right, left_sum + right_sum

def PrintArr( A, size ):
    n = 0
    while n != size:
        print( A[n], end="" )
        if n != size:
            print( " ", end="" )
        n += 1
    print()

if __name__ == '__main__':
    
    while True :
        size = int( input() )
        if size == 0 :
            break
        elif size < 0 :
            print( "Error: size must be positive." )
            continue

        A = np.array( input().split(), dtype=int )
        low, high, sum = FindMaximumSubArray( A, 0, size-1 )

        print( "Low = " + str( low+1 ), end = "" )
        print( ", High = " + str( high+1 ), end = "" )
        print( ", Sum = " + str( sum ), end = "\n" )
        # PrintArr( A, size )