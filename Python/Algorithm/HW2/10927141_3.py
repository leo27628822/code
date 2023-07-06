# 演算法分析機測
# 學號: 10927141 / 10927143 / 10927144
# 姓名: 黃詳諺 / 王胤迦 / 陳建成
# 中原大學資訊工程系
import sys

class Node:
    def __init__(self, value):
        self.value = value
        self.children = []

def find_node_height(tree_list, num) :
    global h
    if tree_list[num][1] == 0:
        h[num] = 0
    else :
        mx = 0
        
        for i in range(1,len(tree_list[num])):
            find_node_height(tree_list, tree_list[num][i]-1)
            mx = max(mx, h[tree_list[num][i]-1]+1)
        h[num] = mx

def find_root(tree_list):
    n = len(tree_list)
    child_set = set()
    for sublist in tree_list:
        if sublist != [0]:
            for child_value in sublist[1:]:
                child_set.add(child_value)
    for i in range(1, n + 1):
        if i not in child_set:
            return i
    return None

if __name__ == "__main__":
    sys.setrecursionlimit(100000)
    count = 1
    while True:
        n = int(input())
        if n == 0:
            break
        else:
            tree = [[] for _ in range(n)] 
            for i in range(n):
                tree[i].append(i+1)
            
        for i in range(n):
            line = input().split()
            read = int(line[0])
            if read == 0:
                tree[i].append(0)
                continue
            else:
                for j in range(read):
                    temp = int(line[j+1])
                    tree[i].append(temp)

        #for i in range(len(tree)):
        #    print("i = ", i, "  ",   tree[i])

        root = find_root(tree)
        #root 會是節點的value 而不是tree的index
        print("Rooted Tree ", count)
        print("Root: ", root)
        #print(tree[root-1])
        #continue

        h = [0 for _ in range(n)]

        find_node_height(tree, root-1) #root 會是節點的value 而不是tree的index 所以要減一
        #continue
        #print(h)
        
        total_height = 0
        for i in range(n):
            total_height += h[i]

        print("Total_height: ", total_height)

        count += 1