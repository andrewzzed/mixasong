load("FMINST")
rtsetparams(44100, 1)
makegen(1, 10, 1000, 1)
makegen(2, 24, 1000, 0, 0, 3.5,1, 7,0)
makegen(3, 24, 1000, 0,1, 7,0)
FMINST(0, 7, 8.00, 179, 0, 10, 20000)
