import cv2
import numpy as np
import serial
import time

# Initialize the Haar Cascade face and mouth detectors
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
mouth_cascade = cv2.CascadeClassifier('haarcascade_mcs_mouth.xml')

# Initialize the video capture and serial communication
cap = cv2.VideoCapture(0)
ArduinoSerial = serial.Serial('com7', 9600, timeout=0.1)
time.sleep(1)

while True:
    # Capture a frame from the video feed
    ret, frame = cap.read()
    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Detect faces in the grayscale image
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    # Loop through each detected face
    for (x,y,w,h) in faces:
        # Draw a rectangle around the face
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
        # Extract the region of interest (ROI) for the mouth
        roi_gray = gray[y+(h//2):y+h, x:x+w]
        roi_color = frame[y+(h//2):y+h, x:x+w]
        # Detect mouths in the mouth ROI
        mouths = mouth_cascade.detectMultiScale(roi_gray, 1.3, 5)
        # Loop through each detected mouth
        for (mx,my,mw,mh) in mouths:
            # Draw a rectangle around the mouth
            cv2.rectangle(roi_color,(mx,my),(mx+mw,my+mh),(0,255,0),2)
            # Check if the mouth ROI is smiling or not
            if my + mh/2 > h/2:
                # Send a signal to Arduino if smiling
                ArduinoSerial.write(b'1')

    # Display the video feed
    cv2.imshow('Smile Detector',frame)

    # Exit the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture and close the serial communication
cap.release()
ArduinoSerial.close()
cv2.destroyAllWindows()
