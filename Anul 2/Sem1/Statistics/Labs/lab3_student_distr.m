# pb 1 - student distribution
n = input("n: ");

# a)
cdf = tcdf(0, n)
cdf2 = 1 - cdf

# b)
# P(a <= X <= b) = F(b) - F(a)
a = tcdf(1, n)
b = tcdf(-1, n)
res = b - a
