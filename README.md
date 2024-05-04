For Arduino
Tested on Arduino UNO
Encoder with signal ABZ
Give a string with a float value through serial port (9600 bds)
"1.000" for 1 turn


Parameters can be change through serial communication :
(text printed at start)

To change a parameter, send a letter with a value"
'd' Direction of rotation (\"d1\" or \"d-1\")"
'i' Coder impulsions for one full rotation (\"i1024\", \"i360\", ...)"
'p' Period in millisecond between each serial message (\"p25\", \"p1000\", ...)"
'f' float precision of the serial printed measure (\"f0\", \"f4\", ...)"
't' print time in serial message (\"t0\" or \"t1\")"

Time (in millisecond) is a unsigned long and its limit is reached in 49 days.
