import sys
import time
import torch
import win32api
import win32con
from PyQt5.QtWidgets import QApplication


# data setting
GAME_WIDTH = 2560
GAME_HEIGHT = 1440

IMG_PATH = 'screenshot.bmp'

HUBCONF_FOLDER_PATH = r'.'
MODEL_PATH = 'best.pt'
CONFIDENCE_THRESHOLD = 0.4

MOVE_DELAY1 = 0.049
MOVE_DELAY2 = 0.033
ONE_SHOT_DELAY = 0.5


def screenshot(screen, img_path):
    img = screen.grabWindow(0).toImage()
    img.save(img_path)


def inference_by_image(model, img_path):
    results = model(img_path)
    results_pandas = results.pandas()

    # box coordinates
    x_mins = results_pandas.xyxy[0]['xmin']
    x_maxs = results_pandas.xyxy[0]['xmax']
    y_mins = results_pandas.xyxy[0]['ymin']
    y_maxs = results_pandas.xyxy[0]['ymax']

    confidences = results_pandas.xyxy[0]['confidence']

    return x_mins, x_maxs, y_mins, y_maxs, confidences


def get_points_by_threshold(zip_object, threshold):
    points = []
    for x_min, x_max, y_min, y_max, conf in zip_object:
        if conf > threshold:
            points.append([int(x_min), int(x_max), int(y_min), int(y_max)])
    return points


def get_center_pos(points):
    center_pos = []
    for point in points:
        x_center = int(point[1] - (point[1] - point[0]) // 2)
        y_center = int(point[3] - (point[3] - point[2]) // 2)
        center_pos.append([x_center, y_center])
    return center_pos


def get_move_offsets(center_pos, game_width, game_height):
    move_offsets = []
    for center in center_pos:
        x_offset = int(center[0] - game_width // 2)
        y_offset = int(center[1] - game_height // 2)
        move_offsets.append([x_offset, y_offset])
    return move_offsets


def fine_tuning(x_offset, y_offset):
    if x_offset > 0:
        x_offset += 43
    if y_offset > 0:
        y_offset += 44

    if x_offset < 0:
        x_offset -= 37
    if y_offset < 0:
        y_offset -= 44
    if y_offset < -200:
        y_offset -= 45
    elif y_offset < -150:
        y_offset -= 30

    return x_offset, y_offset


def move_and_click_by_offsets(x_offset, y_offset, move_delay1, move_delay2):
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, x_offset, y_offset, 0, 0)
    time.sleep(move_delay1)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)
    time.sleep(move_delay2)
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, -x_offset, -y_offset, 0, 0)


def main():
    # init model
    device = torch.device('cuda')
    model = torch.hub.load(HUBCONF_FOLDER_PATH, 'custom', MODEL_PATH,
                           source='local', force_reload=False)
    model = model.to(device)

    # init PyQt
    app = QApplication(sys.argv)
    screen = QApplication.primaryScreen()

    # inference and move to shot
    while True:
        screenshot(screen, IMG_PATH)
        x_mins, x_maxs, y_mins, y_maxs, confidences = inference_by_image(model, IMG_PATH)
        points = get_points_by_threshold(zip(x_mins, x_maxs, y_mins, y_maxs, confidences),
                                         CONFIDENCE_THRESHOLD)
        
        if len(points) == 3:
            center_pos = get_center_pos(points)
            move_offsets = get_move_offsets(center_pos, GAME_WIDTH, GAME_HEIGHT)

            for x_offset, y_offset in move_offsets:
                x_offset, y_offset = fine_tuning(x_offset, y_offset)
                move_and_click_by_offsets(x_offset, y_offset, MOVE_DELAY1, MOVE_DELAY2)
                time.sleep(ONE_SHOT_DELAY)   
        

if __name__ == '__main__':
    main()