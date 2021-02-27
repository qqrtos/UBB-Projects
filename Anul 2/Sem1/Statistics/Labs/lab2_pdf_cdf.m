n = input("Pick the number of trials: ")
p = input("Pick the probability of sucess: ")

#2a)
x = 0:0.5:n;
y = binopdf(x,n,p);
plot(x, y)
title("PDF")

ContinueExec = input("Type something to continue. ");

#2b)
x = 0:0.5:n;
y = binocdf(x,n,p);
plot(x, y)
title("CDF")
