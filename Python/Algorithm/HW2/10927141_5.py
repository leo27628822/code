#   演算法分析機測
#   學號: 10927141 / 10927143 / 10927144
#   姓名: 黃詳諺 / 王胤迦 / 陳建成
#   中原大學資訊工程系

from collections import deque

def is_valid_move(x, y, n):
    # 檢查移動是否在棋盤內
    return 0 <= x < n and 0 <= y < n

def position_to_coordinates(position):
    # 將位置轉換為座標
    if ( position[0] >= 'a' and position[0] <= 'h') :
        col = ord(position[0]) - ord('a')
        row = int(position[1]) - 1
    else :
        col = ord(position[1]) - ord('a')
        row = int(position[0]) - 1
    return row, col

def coordinates_to_position(coordinates):
    # 將座標轉換為位置
    if ( coordinates[0] >= 0 and coordinates[0] <= 7 ) :
        col = chr(coordinates[0] + ord('a'))
        row = str(coordinates[1] + 1)
    else :
        col = chr(coordinates[1] + ord('a'))
        row = str(coordinates[0] + 1)
    return col + row

def parse_input(input_string):
    # 解析輸入，獲取起始位置和目標位置
    positions = input_string.strip().split()
    start_position = positions[0]
    target_position = positions[1]
    return start_position, target_position

def min_knight_moves(start, target, n):
    # 可移動的八個方向
    moves = [(1, 2), (2, 1), (-1, 2), (-2, 1), (1, -2), (2, -1), (-1, -2), (-2, -1)]

    queue = deque([(start, 0)])  # 使用deque作為BFS的佇列
    visited = set([start])  # 記錄已訪問的位置

    while queue:
        position, steps = queue.popleft()
        x, y = position

        if position == target:
            return steps  # 找到目標位置，返回步數

        # 嘗試所有可行的移動
        for move in moves:
            dx, dy = move
            new_x, new_y = x + dx, y + dy

            if is_valid_move(new_x, new_y, n) and (new_x, new_y) not in visited:
                queue.append(((new_x, new_y), steps + 1))
                visited.add((new_x, new_y))

    return -1  # 若無法到達目標位置，返回-1

if __name__ == '__main__' :
    n = 8  # 棋盤大小
    while True:
        input_string = input("請輸入起始位置和目標位置（輸入0 0結束）: ")
        if input_string == "0 0":
            break

        start_position, target_position = parse_input(input_string)
    
        start = position_to_coordinates(start_position)
        target = position_to_coordinates(target_position)
    
        min_steps = min_knight_moves(start, target, n)
        if min_steps == -1:
            print("無法到達目標位置")
        else:
            start_position_display = start_position
            target_position_display = target_position
            print(f"From {start_position_display} to {target_position_display}, Knight Moves = {min_steps}")
    
