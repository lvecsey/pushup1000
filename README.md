
*Overview*

Wait for the 0, 20, or 40th second to elapse. You should have your clock synchronized. Then, every 40 seconds from there perform a good form pushup.

At first you might complete say 100 of these in the morning, and 100 in the evening. Just adjust the percentage in the program if you are able to perform more.

*Festival*

The program is designed to use the festival program for speech synthesis. With your audio output, it will let you know when to perform the next pushup.

```console
sudo apt-get install festival
```

**Testing**

```console
echo '(SayText "Hello")' | festival -pipe
```

You should hear some audio output from your PC or device. If it doesn't work you may need to further configure festival or adjust your audio output.

*Configuration*

Edit the percent line in *pushup1000.py* to a value between about 0.01 and 1.0 depending on your fitness ability.

*Running*

```console
python3 ./pushup1000.py
```

*Links*


