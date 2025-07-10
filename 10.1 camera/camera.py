import cv2

cap = cv2.VideoCapture(8)

while True:
    _, frame = cap.read()
    if _:
        cv2.imshow("show", frame)
        cv2.waitKey(1)