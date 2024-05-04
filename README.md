For Arduino<br/>
Tested on Arduino UNO<br/>
Encoder with signal ABZ<br/>
Give a string with a float value through serial port (9600 bds)<br/>
"1.000" for 1 turn<br/>
<br/>
<br/>
Parameters can be change through serial communication :<br/>
(text printed at start)<br/>
<br/>
To change a parameter, send a letter with a value"<br/>
'd' Direction of rotation (\"d1\" or \"d-1\")"<br/>
'i' Coder impulsions for one full rotation (\"i1024\", \"i360\", ...)"<br/>
'p' Period in millisecond between each serial message (\"p25\", \"p1000\", ...)"<br/>
'f' float precision of the serial printed measure (\"f0\", \"f4\", ...)"<br/>
't' print time in serial message (\"t0\" or \"t1\")"<br/>
<br/>
Time (in millisecond) is a unsigned long and its limit is reached in 49 days.<br/>
