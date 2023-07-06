# 演算法分析機測
# 學號: 10927141 / 10927143 / 10927144
# 姓名: 黃詳諺 / 王胤迦 / 陳建成
# 中原大學資訊工程系

def lis(vec, count):
    lisarray = []
    lis_lengths = [1] * len(vec)

    for i in range(len(vec)):
        temp = [vec[i]]

        for j in range(i):
            if vec[j] < vec[i] and lis_lengths[j] + 1 > lis_lengths[i]:
                temp = lisarray[j] + [vec[i]]
                lis_lengths[i] = lis_lengths[j] + 1

        lisarray.append(temp)

    max_length = max(lis_lengths)
    lisarray = [sublist for sublist in lisarray if len(sublist) == max_length]

    print("Case", count)
    print("Length of LIS =", max_length)
    print("LIS =", end=" ")
    for i, sublist in enumerate(lisarray):
        print(sublist, end="")
        if i != len(lisarray) - 1:
            print(",", end=" ")
    print()

if __name__ == "__main__":
    seq = []
    count = 1

    size = int(input())
    while size != 0:
        seq = list(map(int, input().split()))

        lis(seq, count)
        seq.clear()
        count += 1
        size = int(input())

