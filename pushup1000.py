#!/usr/bin/python3

import subprocess

from datetime import datetime

from time import sleep

def wait_second(seconds=[0, 20, 40]):

    unmatched = True

    while unmatched:

        dt = datetime.now()

        if int(dt.second) in seconds:

            unmatched = False

            break
        
        sleep(0.125)
        
    return 0
        
def festival_voice(msg_type):

    msg = 'Hello'
    
    if (msg_type == 'pushup'):
    
        msg = 'Perform a pushup.'

    if (msg_type == 'wait'):
        
        msg = 'Wait until the next batch of pushups.'
        
    input_str = '(SayText "' + msg + '")'

    res = subprocess.run(["festival", "--pipe"], input=input_str, text=True, capture_output=True)
    if (res.returncode != 0):
        print('Trouble calling festival with SayText string.')
        return -1
        
    return 0


def routine(portion, delay_seconds):

    speech_seconds = 3

    if delay_seconds > speech_seconds:

        adjusted_delaysec = (delay_seconds - speech_seconds * 0.5)
        
        while portion > 0:

            print('Perform a pushup.')
        
            festival_voice('pushup')        
        
            sleep(adjusted_delaysec)

            portion -= delay_seconds

    return 0


def main(percent, num_hours = 12, delay_seconds = 40):

    num_seconds = (num_hours * 3600)

    # delay_seconds = (num_seconds / 1000)

    portionA = (num_seconds / 2) * percent

    portionB = (num_seconds / 2) * percent    

    routine(portionA, delay_seconds)
    
    festival_voice('wait')
        
    sleep(3600 * 3)

    routine(portionB, delay_seconds)
    
    return 0


if __name__ == '__main__':

    wait_second()
    
    percent = 0.20

    main(percent)
