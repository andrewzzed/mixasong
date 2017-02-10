rtsetparams(44100, 2)
load("HENON")
load("TRANS")
load("JDELAY")
bus_config("HENON", "aux 0-1 out")
bus_config("TRANS3", "aux 0-1 in", "out 0-1")
srand()

b = maketable("line", "nonorm", 1000, 0,0.25, 1,0.35)
HENON(0, dur=10, amp=10000, a=1.3, b)
trans = makeLFO("tri", 1, -3.02, -3.0)
TRANS3(0, 0, dur, 1, trans)
