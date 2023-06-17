#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

''' example test data
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
0 0
'''

#import time
#start_time = time.time()
#total_time = time.time() - start_time
#print( total_time )

class GameShortest:
    def __init__(self,line, row, col):
 
        self.line = line
        self.sta = ''
        self.en = ''
        self.row = row
        self.col = col
        self.px,self.py = -1,-1
        self.paths = []
        self.len = -1
 
        self.pre()
        self.BFS()
        
    def Print(self, cnt = int ):
        print("Maze #" + str(cnt))
        if self.len == -1:
            print("Impossible")
        else:
            for path in self.paths:
                print(path)

    def pre(self):
        mp = []
        for pos in range(0, len(self.line), self.col):
            mp.append(self.line[pos:pos + self.col])
 
        for pos, enum in enumerate(self.line):
            cx, cy = pos // self.col, pos % self.col
            if enum == '4':
                self.px, self.py = cx, cy      
                # print(cx, cy)
        staDic = {'0': '0', '1': '0', '2': '2', '3': '0', '4': '4'}
        enDic = {'0': '0', '1': '1', '2': '0', '3': '3', '4': '0'}
        for x in self.line:
            self.sta += staDic[x]
            self.en += enDic[x]

    def is_ok(self,sta):
        for s,e in zip(sta,self.en):
            if e == '3' and s != '2':
                return False
        return True
 
    def BFS(self):
        dirs = [[-1,0,'n','N'],[1,0,'s','S'],[0,1,'e','E'],[0,-1,'w','W']]
        states = [[self.sta,'',self.px,self.py]]
        visi = {}
        visi[self.sta] = 1
 
        s_len = 1000
        while len(states)>0:
            sta, path, px, py = states[0]
            ppos = px*self.col + py
            states = states[1:]
            if len(path)>s_len:
                break
            if self.is_ok(sta):
                if self.len == -1 or len(path) == self.len:
                    self.paths.append(path)
                    self.len = len(path)
                continue

            for dir in dirs:
                cx, cy = px + dir[0], py + dir[1]
                pos = cx*self.col+cy
                nx, ny = px + 2*dir[0], py + 2*dir[1]
                npos = nx*self.col+ny
                if not (nx>=0 and nx<self.col and ny>=0 and ny<self.col and pos >= 0 and pos < (self.row*self.col) and npos >= 0 and npos < (self.row*self.col) ): ## error here!!
                    continue
                if sta[pos] == '2' and sta[npos] == '0' and self.en[npos] != '1':
                    digits = [int(x) for x in sta]
                    digits[ppos],digits[pos],digits[npos] = 0,4,2
                    new_sta = ''.join(str(x) for x in digits)
                    if new_sta not in visi:
                        visi[new_sta] = 1
                        states.append([new_sta, path+dir[3], cx, cy])
                elif sta[pos] == '0' and self.en[pos] !='1':
                    digits = [int(x) for x in sta]
                    digits[ppos], digits[pos]  = 0, 4
                    new_sta = ''.join(str(x) for x in digits)
                    if new_sta not in visi:
                        visi[new_sta] = 1
                        states.append([new_sta, path + dir[2], cx, cy])
 
if __name__ == '__main__':

    cnt = 1
    while True :
        
        r, c = map(int, input().split())
        if r == 0 and c == 0:
            break
        line = ""
        for i in range (r) :
            line += input()
        
        line = line.replace('.', '0')
        line = line.replace('#', '1')
        line = line.replace('B', '2')
        line = line.replace('T', '3')
        line = line.replace('S', '4')
        #print(line)
        gs = GameShortest(line, r, c)
        gs.Print(cnt)
        cnt += 1