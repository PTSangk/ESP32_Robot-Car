import cv2
import mediapipe as mp
#import RPi.GPIO as GPIO
import time
import datetime




# Setup GPIO pins for L298N
'''motor_pins = {
    'left_motor_forward': (17, 27),
    'left_motor_backward': (18, 24),
    'right_motor_forward': (22, 19),
    'right_motor_backward': (23, 16)
    

}
def rotateMotorWithDelay(motor_pins, delay_time, left_forward, left_backward, right_forward, right_backward):
    GPIO.output(motor_pins['left_motor_forward'], left_forward)
    GPIO.output(motor_pins['left_motor_backward'], left_backward)
    GPIO.output(motor_pins['right_motor_forward'], right_forward)
    GPIO.output(motor_pins['right_motor_backward'], right_backward)
    time.sleep(delay_time)
    GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
    GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
    GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
    GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)

GPIO.setmode(GPIO.BCM)
for pin in motor_pins.values():
   GPIO.setup(pin, GPIO.OUT)'''

mp_pose = mp.solutions.pose
pose = mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5)

# Continuously capture images from the camera and run inference
cap = cv2.VideoCapture(0)  # Open the camera

while cap.isOpened():

    ret, frame = cap.read()
    if not ret:
        continue
    # Convert the image from BGR to RGB as required by the TFLite model.    
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = pose.process(rgb_frame)
    #timestamp 
    timestamp = datetime.datetime.now().strftime("%d-%m-%Y %H:%M:%S")

    if results.pose_landmarks: 
    
        #print("NOSE_Visibility")
        NOSE_Visibility = results.pose_landmarks.landmark[mp_pose.PoseLandmark.NOSE].visibility
        #print(NOSE_Visibility)
        print(f"{timestamp} >> NOSE_Visibility: {NOSE_Visibility}")
        #print("NOSE_Visibility")
        NOSE_Visibility = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_SHOULDER].visibility
        #print(NOSE_Visibility)
        print(f"{timestamp} >> NOSE_Visibility: {NOSE_Visibility}")
        #print("RIGHT_HIP_Visibility")
        RIGHT_HIP_Visibility = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_HIP].visibility
        #print(RIGHT_HIP_Visibility)
        print(f"{timestamp} >> RIGHT_HIP_Visibility: {RIGHT_HIP_Visibility}")
        #print("RIGHT_KNEE_Visibility")
        #RIGHT_KNEE_Visibility = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_KNEE].visibility
        #print(RIGHT_KNEE_Visibility)
        #print(f"RIGHT_KNEE_Visibility: {RIGHT_KNEE_Visibility}")
        #print("Average")
        Average = (NOSE_Visibility + NOSE_Visibility + RIGHT_HIP_Visibility ) / 3
        #print(Average)
        print(f"{timestamp} >> Average: {Average}")

        if Average >= 0.9: #classify is person in screen
    
        #if results.pose_landmarks:
            left_threshold = 0.4
            right_threshold = 0.6

            left_shoulder_x = results.pose_landmarks.landmark[mp_pose.PoseLandmark.LEFT_SHOULDER].x
            right_shoulder_x = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_SHOULDER].x

            person_width = abs(right_shoulder_x - left_shoulder_x) * frame.shape[1]
            average_shoulder_width = 0.4
            distance = (average_shoulder_width * frame.shape[1]) / person_width

            print(f"{timestamp} >> Distance from camera: {distance} meters")

            # Control motors based on positions and distance
            if left_shoulder_x < left_threshold:
                print(f"{timestamp} >> Person is on the left")
                #rotateMotorWithDelay(motor_pins, 0.02, GPIO.LOW, GPIO.HIGH, GPIO.HIGH, GPIO.LOW)  # หมุนซ้ายเป็นระยะเวลา 0.1 วินาที
            elif right_shoulder_x > right_threshold:
                print(f"{timestamp} >> Person is on the right")
                #rotateMotorWithDelay(motor_pins, 0.02, GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH)  # หมุนขวาเป็นระยะเวลา 0.1 วินาที
            elif distance > 2.0:
                print(f"{timestamp} >> Person is far")
                # Control all motors to move backward (adjust motor_pins accordingly)
                '''GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
                GPIO.output(motor_pins['left_motor_backward'], GPIO.HIGH)
                GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
                GPIO.output(motor_pins['right_motor_backward'], GPIO.HIGH)'''
                
            elif 1.0 < distance < 2.0:
                print(f"{timestamp} >> Person is between 1-2 meters, stopping the car")
                # Stop all motors (adjust motor_pins accordingly)
            #    '''GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
            #     GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
            #     GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
            #     GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)'''
            elif distance < 1.0:
                print(f"{timestamp} >> Person is near")
                # Control all motors to move forward (adjust motor_pins accordingly)
            #    ''' GPIO.output(motor_pins['left_motor_forward'], GPIO.HIGH)
            #     GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
            #     GPIO.output(motor_pins['right_motor_forward'], GPIO.HIGH)
            #     GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)'''
            else:
                print(f"{timestamp} >> Person is in the center")
                # Stop all motors (adjust motor_pins accordingly)
                # '''GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
                # GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
                # GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
                # GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)'''
        else:
            print(f"{timestamp} >> Classification: No person detected. Stopping the car.")      
            # '''GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
            # GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
            # GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
            # GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)'''  
            
    else:
        print(f"{timestamp} >>  No person detected on screen. Stopping the car..")
        # Stop all motors when no person is detected
        # '''GPIO.output(motor_pins['left_motor_forward'], GPIO.LOW)
        # GPIO.output(motor_pins['left_motor_backward'], GPIO.LOW)
        # GPIO.output(motor_pins['right_motor_forward'], GPIO.LOW)
        # GPIO.output(motor_pins['right_motor_backward'], GPIO.LOW)'''

    cv2.imshow('MediaPipe Pose', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        cap.release()
        cv2.destroyAllWindows()
        break

cap.release()
#GPIO.cleanup()
cv2.destroyAllWindows()

