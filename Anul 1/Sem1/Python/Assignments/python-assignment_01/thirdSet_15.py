def sumDiv(a):
     '''
          This function calculates the sum of number a's divisors.
          Input: a
          Output: s, sum of the divisers
     '''
     s=0
     for d in range(1,a//2+1):
          if a%d==0:
               s+=d
     return s


ok=False
n=int(input("Give a number: "))
for i in range(n-1,1,-1):
     if i==sumDiv(i):
          print(i)
          ok=True
          break
if ok==False:
     print("There is no smaller perfect number than " + str(n))
