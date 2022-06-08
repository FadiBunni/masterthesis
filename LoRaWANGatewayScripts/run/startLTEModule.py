import RPi.GPIO as GPIO            # import RPi.GPIO module  
from time import sleep             # lets us have a delay 
GPIO.setmode(GPIO.BCM)             # choose BCM or BOARD  
GPIO.setup(24, GPIO.OUT)           # set GPIO24 as an output   

GPIO.output(24,1)
sleep(7)
GPIO.output(24,0)


GPIO.cleanup()                 # resets all GPIO ports used by this program  
