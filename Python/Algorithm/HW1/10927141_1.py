#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
8
-2 1 -3 4 -1 2 1 -5
16
13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7
3
1 1 1
5
4 3 2 1 1

'''

import numpy as np
#import time
#start_time = time.time()
#total_time = time.time() - start_time
#print( total_time )

'''
def FindMaximumSubArray( A, low, high ):
    if low == high-1 :
        return low, high, A[low]
    else :
        mid = ( low + high ) // 2
        left_low, left_high, left_sum = FindMaximumSubArray( A, low, mid )
        right_low, right_high, right_sum = FindMaximumSubArray( A, mid, high )
        cross_low, cross_high, cross_sum = FindMaxCrossingSubArray( A, low, mid, high )
        if left_sum >= right_sum and left_sum >= cross_sum :
            return left_low, left_high, left_sum
        elif right_sum >= left_sum and right_sum >= cross_sum :
            return right_low, right_high, right_sum
        else :
            return cross_low, cross_high, cross_sum

def FindMaxCrossingSubArray( A, low, mid, high ):
    left_sum = float('-inf')
    sum = 0
    max_left = mid
    for i in range ( mid-1, low-1, -1 ) :
        sum += A[i]
        if sum > left_sum :
            left_sum = sum
            max_left = i
    
    right_sum = float('-inf')
    sum = 0
    max_right = mid + 1
    for i in range ( mid, high ) :
        sum += A[i]
        if sum > right_sum :
            right_sum = sum
            max_right = i

    return max_left, max_right, left_sum + right_sum
    '''
def PrintArr( A, size ):
    n = 0
    while n != size:
        print( A[n], end="" )
        if n != size:
            print( " ", end="" )
        n += 1
    print()

def Find_Maximum_Subarray( A ):
	n = len( A )
	low, high, sum = _Find_Maximum_Subarray( A, 0, n - 1 )
	
	print( "Maximum-Subarray Problem:" )
	print( "Low =", low+1, "High =", high+1, "Sum =", sum )


def _Find_Maximum_Subarray( A, low, high ):
	if high == low:
		return low, high, A[low]
	else:
		mid = ( low + high ) // 2 
		
		left_low, left_high, left_sum    = _Find_Maximum_Subarray( A, low, mid )
		right_low, right_high, right_sum = _Find_Maximum_Subarray( A, mid + 1, high )		
		cross_low, cross_high, cross_sum = _Find_Max_Crossing_Subarray( A, low, mid, high )
		
		if ( left_sum > right_sum and left_sum >= cross_sum ):
			return left_low, left_high, left_sum
		elif ( right_sum >= left_sum and right_sum >= cross_sum ):
			return right_low, right_high, right_sum
		else:
			return cross_low, cross_high, cross_sum


def _Find_Max_Crossing_Subarray( A, low, mid, high ):
	left_sum = -3000000
	sum = 0
	for i in range( mid, low - 1, -1 ):
		sum += A[i]
		if sum > left_sum:
			left_sum = sum		
			max_left = i
		
	right_sum = -3000000
	sum = 0
	for j in range( mid + 1, high + 1 ):
		sum += A[j]
		if sum > right_sum:
			right_sum = sum	
			max_right = j
	
	cross_low  = max_left
	cross_high = max_right
	cross_sum  = left_sum + right_sum
	
	return cross_low, cross_high, cross_sum

if __name__ == '__main__':
    
    while True :
        size = int( input() )
        if size == 0 :
            break
        elif size < 0 :
            print( "Error: size must be positive." )
            continue

        A = np.array( input().split(), dtype=int )

        Find_Maximum_Subarray( A )

        #print( "Low = " + str( low+1 ), end = "" )
        #print( ", High = " + str( high+1 ), end = "" )
        #print( ", Sum = " + str( sum ), end = "\n" )
        # PrintArr( A, size )