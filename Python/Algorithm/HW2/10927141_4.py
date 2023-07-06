#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
5
0 11 2 5 3
11 0 8 4 1
2 8 0 6 12
5 4 6 0 15
3 1 12 15 0
9
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
0
'''

import numpy as np
import sys

def laplacian_matrix( adjacency_matrix ) :
    # 計算每一行的和，即每個節點的度數
    degrees = np.sum( adjacency_matrix, axis=1 )
    
    # 創建度矩陣
    degree_matrix = np.diag( degrees )
    
    # 計算拉普拉斯矩陣
    laplacian = degree_matrix - adjacency_matrix
    
    return laplacian

def number_of_spanning_trees( adjacency_matrix ) :
    # 計算拉普拉斯矩陣
    laplacian = laplacian_matrix( adjacency_matrix )
    
    # 刪除第一行和第一列
    laplacian = np.delete( laplacian, 0, axis=0 )
    laplacian = np.delete( laplacian, 0, axis=1 )
    
    # 計算行列式
    determinant = np.linalg.det( laplacian )
    
    return abs( round( determinant ) )

def prim_algorithm( graph, v ):
    num_vertices = v
    selected_vertices = [0]
    total_cost = 0

    while len( selected_vertices ) < num_vertices :
        min_cost = sys.maxsize # 9223372036854775807
        for i in range( num_vertices ) :
            if i in selected_vertices :
                for j in range( num_vertices ):
                    if j not in selected_vertices and graph[i][j] != '-' and graph[i][j] != 0:
                        if min_cost > graph[i][j]:
                            min_cost = graph[i][j]
                            new_vertex = j
        total_cost += min_cost
        selected_vertices.append( new_vertex )

    #print( selected_vertices ) # 印出最小生成樹的頂點: [0, 2, 4, 1, 3]
    # MST不唯一，Prim's Algorithm 回傳其中一解 (保證 optimal solution)
    return total_cost

if __name__ == '__main__' :
    while True :
        v = int( input() )
        while v < 0 or v > 20 :
            v = int( input("0 ~ 20!\n") )
	    
        if v == 0 :
            break
	
        graph = [ list( input().split() ) for _ in range( v ) ]
        
        adjacency_matrix = [ [ 0 for j in range( v ) ] for i in range( v ) ]
        for i in range( v ) :
            for j in range( v ) :
                if graph[i][j] != 0 and graph[i][j] != '-' :
                    graph[i][j] = int( graph[i][j] )
                    adjacency_matrix[i][j] = 1

        print( "Number of Spanning Trees = ", number_of_spanning_trees( adjacency_matrix ) )
        print( "Minimum Cost = ", prim_algorithm( graph, v ) )