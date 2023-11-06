import numpy as np
import cv2
import serial
import time

CAMERA_DEVICE_ID = 0
IMAGE_WIDTH = 640
IMAGE_HEIGHT = 480
THRESHOLD=0.4
path = "\\home\\toolmen\\workspace\\test.jpg"
fps = 0

def color_detection(img):
    hsv_img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
    # Set range for red color and  
    # define mask 
    # Red test
    red_lower1 = np.array([0,43,70])   
    red_upper1 = np.array([10,255,255]) 
    red_lower2 = np.array([170,43,50])  
    red_upper2 = np.array([180,255,255])  
    red_mask1 = cv2.inRange(hsv_img, red_lower1, red_upper1)
    red_mask2 = cv2.inRange(hsv_img, red_lower2, red_upper2) 
    red_mask = cv2.bitwise_or(red_mask1, red_mask2)
    
    total_pixels= red_mask.shape[0]*red_mask.shape[1]
    red_pixel = np.count_nonzero(red_mask == 255.0)
    ratio = red_pixel/total_pixels
    print("ratio: ",ratio)
   
    
    if ratio > THRESHOLD:          # find out red region
        return "stop\n"
    else:
        return "active\n"



def visualize_fps(image, fps: int):
    if len(np.shape(image)) < 3:
        text_color = (255, 255, 255)  # white
    else:
        text_color = (0, 255, 0)  # green
    row_size = 20  # pixels
    left_margin = 24  # pixels

    font_size = 1
    font_thickness = 1

    # Draw the FPS counter
    fps_text = 'FPS = {:.1f}'.format(fps)
    text_location = (left_margin, row_size)
    cv2.putText(image, fps_text, text_location, cv2.FONT_HERSHEY_PLAIN,
                font_size, text_color, font_thickness)

    return image

if __name__=='__main__':
    # initialize serial setting
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    # start stream video
    try:
        cap = cv2.VideoCapture(CAMERA_DEVICE_ID)
        cap.set(3, IMAGE_WIDTH)
        cap.set(4, IMAGE_HEIGHT)
        cap.set(cv2.CAP_PROP_BUFFERSIZE, 2)
        sample_start = time.time()
        while 1:
            cvt,frame =cap.read()
            #capturr picture:
            cv2.imwrite(path, frame, [cv2.IMWRITE_JPEG_QUALITY, 95])
  
            start_time = time.time()
           
            #Detection: 
            if (time.time()-sample_start)>=3:
                sample_start=time.time()
                sample_result=color_detection(frame)        
                ser.write(sample_result.encode('utf-8'))        #sent result to arduino

            
            cv2.imshow('frame', visualize_fps(frame, fps))
            # record end time
            end_time = time.time()

            # calculate FPS
            seconds = end_time - start_time
            fps = 1.0 / seconds
            print("Estimated fps:{0:0.1f}".format(fps))

            # if key pressed is 'Esc' then exit the loop
            if cv2.waitKey(33) == 27:
                break


    except Exception as e:
        print(e)
    finally:
        cv2.destroyAllWindows()
        cap.release()