import time
import picamera

with picamera.PiCamera() as camera:
    camera.resolution = (2592, 1944)
    time.sleep(2) # camera warm-up time
    camera.capture('foo.jpg')
