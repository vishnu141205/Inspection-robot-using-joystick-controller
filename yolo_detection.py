import cv2
import serial
import time
from ultralytics import YOLO

arduino = None
while arduino is None:
    try:
        arduino = serial.Serial('COM8', 9600, timeout=1)
        time.sleep(2)
        print("Connected to Arduino successfully!")
    except Exception as e:
        print(f"Waiting for Arduino on COM8... Error: {e}")
        time.sleep(3)

model = YOLO("yolov8m.pt")

cap = cv2.VideoCapture(0)

last_action = ""
print_interval = 1.0      
detect_interval = 0.5     
last_print = time.time()
last_detect = time.time()

while True:

    ret, frame = cap.read()
    if not ret:
        break

    current_time = time.time()

    # Run YOLO every 0.5 sec
    if current_time - last_detect > detect_interval:

        results = model(frame)

        detected_direction = "Searching..."
        detected_object = "None"

        for r in results:
            for box in r.boxes:

                label = model.names[int(box.cls[0])]
                conf = float(box.conf[0])

                if conf > 0.6:  

                    x1, _, x2, _ = box.xyxy[0].cpu().numpy()

                    center_x = (x1 + x2) / 2
                    frame_width = frame.shape[1]

                    detected_object = label

                    if center_x < frame_width / 3:
                        detected_direction = "MOVE LEFT"

                    elif center_x > 2 * frame_width / 3:
                        detected_direction = "MOVE RIGHT"

                    else:
                        detected_direction = "MOVE BACK"

                    break

        last_detect = current_time

        
        if (current_time - last_print > print_interval) or (detected_direction != last_action):

            if detected_object != "None":
                print(f"[AI INSPECTION] Object: {detected_object} | Action: {detected_direction}")
                arduino.write((detected_direction + "\n").encode())
            else:
                print("[AI INSPECTION] Status: Clear - No object detected")

            last_action = detected_direction
            last_print = current_time

    cv2.imshow("YOLO Detection", frame)

    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()