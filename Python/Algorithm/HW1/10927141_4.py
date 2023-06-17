#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

""" example test data
10
4 7 2 9 6 0 8 1 5 3
3
0 2 1
0
"""

#import time
#start_time = time.time()
#total_time = time.time() - start_time
#print( total_time )

if __name__ == '__main__' :
    while True :
        try :
            num = int( input() )
            if num == 0 : 
                break
                
            friend = list( map(int, input().split() ) )
            count = 0
            
            for i in range( num ):
                if friend[i] != -1 :     # '-1'表示已經找過
                    current = i            #走到哪
                    while True :
                        next = friend[ current ]
                        friend[ current ] = -1                        
                        if next == i : break   
                    
                        current = next 
                        
                    count = count + 1
                    
            print( count )
            
            
        except :
            continue