#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
2 2
0 0
'''

#import time
#start_time = time.time()
#total_time = time.time() - start_time
#print( total_time )

class Node :

    def __init__( self, west_wolf, west_sheep, east_wolf = 0, east_sheep = 0, boat = "W" ) :
        self.west_wolf = west_wolf
        self.west_sheep = west_sheep
        self.east_wolf = east_wolf
        self.east_sheep = east_sheep
        self.boat = boat            # W:West E:East

    def print_status( self ) :
        print( "(" + repr( self.west_wolf ) + "," + repr( self.west_sheep ) + "," + self.boat + ")" )

    def move_one_wolf( self ) :
        if self.boat == "W" :
            if self.west_wolf == 0 :
                return False
            self.west_wolf -= 1
            self.east_wolf += 1
            self.boat = "E"
        else :
            if self.east_wolf == 0 :
                return False
            self.west_wolf += 1
            self.east_wolf -= 1
            self.boat = "W"
        return True
    
    def move_one_sheep( self ) :
        if self.boat == "W" :
            if self.west_sheep == 0 :
                return False
            self.west_sheep -= 1
            self.east_sheep += 1
            self.boat = "E"
        else :
            if self.east_sheep == 0 :
                return False
            self.west_sheep += 1
            self.east_sheep -= 1
            self.boat = "W"
        return True
    
    def move_one_wolf_one_sheep( self ) :
        if self.boat == "W" :
            if self.west_wolf == 0 or self.west_sheep == 0 :
                return False
            self.west_wolf -= 1
            self.west_sheep -= 1
            self.east_wolf += 1
            self.east_sheep += 1
            self.boat = "E"
        else :
            if self.east_wolf == 0 or self.east_sheep == 0 :
                return False
            self.west_wolf += 1
            self.west_sheep += 1
            self.east_wolf -= 1
            self.east_sheep -= 1
            self.boat = "W"
        return True
    
    def move_two_wolves( self ) :
        if self.boat == "W" :
            if self.west_wolf < 2 :
                return False
            self.west_wolf -= 2
            self.east_wolf += 2
            self.boat = "E"
        else :
            if self.east_wolf < 2 :
                return False
            self.west_wolf += 2
            self.east_wolf -= 2
            self.boat = "W"
        return True
    
    def move_two_sheep( self ) :
        if self.boat == "W" :
            if self.west_sheep < 2 :
                return False
            self.west_sheep -= 2
            self.east_sheep += 2
            self.boat = "E"
        else :
            if self.east_sheep < 2 :
                return False
            self.west_sheep += 2
            self.east_sheep -= 2
            self.boat = "W"
        return True
    
    def safe( self ) :
        if self.west_wolf > self.west_sheep and self.west_sheep != 0 :
            return False
        elif self.east_wolf > self.east_sheep and self.east_sheep != 0 :
            return False
        else :
            return True
        
    def goal( self ) :
        if self.west_wolf == 0 and self.west_sheep == 0 :
            return True
        else :
            return False
        
    def same( self, node_chk ) :
        if self.west_wolf == node_chk.west_wolf and self.west_sheep == node_chk.west_sheep and self.east_wolf == node_chk.east_wolf and self.east_sheep == node_chk.east_sheep and self.boat == node_chk.boat :
            return True
        else :
            return False

class River_Crossing_Problem :

    def __init__( self, m:int, n:int ) :
        self.node = Node( m, n )
        self.list = [self.node]

    def print_list( self ) :
        for i in self.list :
            i.print_status()

    def repeat( self, node_chk ) :
        for node in self.list :
            if node.same( node_chk ) :
                return True
        return False

    def cross( self, node_cur ) :
        if node_cur.goal() :
            return True

        # 2 Wolves
        node_next = Node( node_cur.west_wolf, node_cur.west_sheep, node_cur.east_wolf, node_cur.east_sheep, node_cur.boat)
        if node_next.move_two_wolves() :
            if node_next.safe() and not self.repeat( node_next ) :
                self.list.append( node_next )
                if self.cross( node_next ) :
                    return True
        
        # 1 Wolf 1 Sheep
        node_next = Node( node_cur.west_wolf, node_cur.west_sheep, node_cur.east_wolf, node_cur.east_sheep, node_cur.boat)
        if node_next.move_one_wolf_one_sheep() :
            if node_next.safe() and not self.repeat( node_next ) :
                self.list.append( node_next )
                if self.cross( node_next ) :
                    return True
        
        # 1 Wolf
        node_next = Node( node_cur.west_wolf, node_cur.west_sheep, node_cur.east_wolf, node_cur.east_sheep, node_cur.boat)
        if node_next.move_one_wolf() :
            if node_next.safe() and not self.repeat( node_next ) :
                self.list.append( node_next )
                if self.cross( node_next ) :
                    return True
        
        # 2 Sheep
        node_next = Node( node_cur.west_wolf, node_cur.west_sheep, node_cur.east_wolf, node_cur.east_sheep, node_cur.boat)
        if node_next.move_two_sheep() :
            if node_next.safe() and not self.repeat( node_next ) :
                self.list.append( node_next )
                if self.cross( node_next ) :
                    return True
                
        # 1 Sheep
        node_next = Node( node_cur.west_wolf, node_cur.west_sheep, node_cur.east_wolf, node_cur.east_sheep, node_cur.boat)
        if node_next.move_one_sheep() :
            if node_next.safe() and not self.repeat( node_next ) :
                self.list.append( node_next )
                if self.cross( node_next ) :
                    return True
        
        self.list.pop()
        return False
        
if __name__ == '__main__' :
    
    while True :

        try : 
            m, n = map( int, input().split() )
            if m == 0 and n == 0 :
                break
            elif m < 0 or n < 0 :
                continue
        except :
            continue
        
        owner  = River_Crossing_Problem( m, n )
        if owner.cross( owner.node ) :
            owner.print_list()
        else : 
            print( "No Solution!" )