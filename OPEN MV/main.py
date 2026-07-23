import sensor, image, time
from matrix_mini import send_data, uart, green_led
import fill_light

# Khởi tạo cảm biến
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

sensor.set_vflip(True)
sensor.set_hmirror(True)


fill_light.on()

color_thresholds = [
    (26, 18, -128, -15, 127, -128),
    (26, 0, 39, 127, -128, 38),
    (33, 0, 33, 127, -128, 127),
    (30, 8, -128, -14, 127, -128),
    (22, 0, 16, 127, -128, 127)
]

fps_clock = time.clock()

target_info = (-1, 0, 0, 0)


MIN_BLOB_DENSITY = 0.5


cached_target = (-1, 0, 0, 0)
missing_frame_count = 0
MAX_MISSING_FRAMES = 4


def detect_object(color_index, frame):
    global target_info

    blobs = frame.find_blobs(
        [color_thresholds[color_index]],
        pixels_threshold=300,
        area_threshold=200,
        merge=False,
        x_stride=2,
        y_stride=2
    )

    if blobs:
        detected_id = color_index
        if color_index in (2, 4):
            detected_id = 1
        elif color_index == 3:
            detected_id = 0

        for candidate in blobs:

            rect_area = candidate.w() * candidate.h()
            blob_density = candidate.pixels() / rect_area if rect_area > 0 else 0

            if blob_density < MIN_BLOB_DENSITY:
                continue

            center_x = candidate.cx()
            center_y = candidate.cy()
            object_area = round(candidate.area() / 2)

            frame.draw_rectangle(candidate.rect())
            frame.draw_cross(center_x, center_y)

            if center_y > target_info[2]:
                target_info = (detected_id, center_x, center_y, object_area)


while True:
    fill_light.brightness(100)

    if uart.any():
        command = uart.read(1)
        if command == b'G':
            fps_clock.tick()

            frame = sensor.snapshot()
            target_info = (-1, 0, 0, 0)
            detect_object(0, frame)
            detect_object(1, frame)
            detect_object(2, frame)
            detect_object(3, frame)
            detect_object(4, frame)

            if target_info[0] != -1:

                cached_target = target_info
                missing_frame_count = 0
                send_data([target_info[0], target_info[1], target_info[2], target_info[3]])
            else:

                if missing_frame_count < MAX_MISSING_FRAMES and cached_target[0] != -1:

                    missing_frame_count += 1
                    send_data([cached_target[0], cached_target[1], cached_target[2], cached_target[3]])
                else:

                    send_data([255, 0, 0, 0])

        elif command == b'L':
            green_led.on()
