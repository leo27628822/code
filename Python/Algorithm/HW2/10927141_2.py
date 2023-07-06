# 演算法分析機測
# 學號: 10927141 / 10927143 / 10927144
# 姓名: 黃詳諺 / 王胤迦 / 陳建成
# 中原大學資訊工程系

def knapsack(W, weights, values):
    n = len(weights)
    dp = [0] * (W + 1)
    selected = [[] for _ in range(W + 1)]

    for i in range(n):
        for j in range(W, weights[i] - 1, -1):
            if values[i] + dp[j - weights[i]] > dp[j]:
                dp[j] = values[i] + dp[j - weights[i]]
                selected[j] = selected[j - weights[i]] + [i]

    return dp[W], selected

if __name__ == "__main__":
    while True:
        W = int(input())
        n = int(input())

        if W == 0 and n == 0:
            break

        weights = []
        values = []

        for _ in range(n):
            w, v = map(int, input().split())
            weights.append(w)
            values.append(v)

        result, selected = knapsack(W, weights, values)
        print("Total Value =", result)
        if result > 0:
            print("Take Items:", ", ".join(str(i + 1) for i in selected[-1]))
