# pb 1 - normal distribution

mu = input("Moo: ");
sigma = input("Sigma: ");

# a)
cdf = normcdf(0, mu, sigma) # = 0
cdf2 = 1 - cdf # >= 0

# b)
# P(a <= X <= b) = F(b) - F(a)
a = normcdf(1, mu, sigma)
b = normcdf(-1, mu, sigma)
p = b - a

# c)
alpha = input("Alpha: ");
res = norminv(alpha, mu, sigma)

# d)
beta = input("Beta: ");
res = norminv(1-beta, mu, sigma)