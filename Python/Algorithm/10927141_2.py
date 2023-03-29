#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
8 12
1 2
1 3
1 5
2 4
2 6
3 4
3 7
4 8
5 6
5 7
6 8
7 8
0 0
'''

import sys
#import time
#start_time = time.time()
#total_time = time.time() - start_time
#print( total_time )

class Undigraph :
    def __init__( self, v, e ) :
        self.vertex = v
        self.edge = e 
        self.adj_list = [ [] for _ in range (v) ]  # adjacency list 鄰接表
    
    def add_edge( self, x:int, y:int ) :
        if y not in self.adj_list[x] :
            self.adj_list[x].append(y)

        if x not in self.adj_list[y] :
            self.adj_list[y].append(x)

    def number_of_vertex( self ) :
        return self.vertex
    
    def number_of_edge( self ) :
        return self.edge
    
    def get_edges_of( self, x ) :
        return self.adj_list[x]
    
def HamiltonianCycle( graph, v, path, pos ) :
    if pos == graph.number_of_vertex() :
        if v in graph.get_edges_of( path[0] ) :
            return True
        else :
            return False
    else :
        for i in graph.get_edges_of( v ) :
            if i not in path :
                path[pos] = i
                if HamiltonianCycle( graph, i, path, pos+1 ) :
                    return True
                path[pos] = -1
        return False
    
def HamiltonPath( graph, v, path, pos ) :
    if pos == graph.number_of_vertex() :
        return True
    else :
        for i in graph.get_edges_of( v ) :
            if i not in path :
                path[pos] = i
                if HamiltonPath( graph, i, path, pos+1 ) :
                    return True
                path[pos] = -1
        return False

if __name__ == '__main__' :

    while True :
        v, e = map( int, input().split() )
        if v == 0 and e == 0:
            sys.exit()
        while v <= 0 or e <= 0 :
            v, e = map( int, input("Input error please try again!\n").split() )
            if v == 0 and e == 0:
                sys.exit()
        
        graph = Undigraph( v, e )
        for i in range (e) :
            x, y = map( int, input().split() )
            while x <= 0 or y <= 0 or x == y or x > v or y > v :
                x, y = map( int, input("Input error please try again!\n").split() )
            graph.add_edge(x-1, y-1)

        path = [-1 for _ in range(v)]
        path[0] = 0
        if HamiltonianCycle( graph, 0, path, 1 ) :
            for i in range (v) :
                print( path[i]+1, end=" " )
            print( path[0]+1 )
        else :
            print( "Hamiltonian Cycle Not Exists!" )

        '''
        print( graph.number_of_vertex() )
        print( graph.number_of_edge() )
        for i in range (v) :
            print( graph.get_edges_of(i) )
        '''