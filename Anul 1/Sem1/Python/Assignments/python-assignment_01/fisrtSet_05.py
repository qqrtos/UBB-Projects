import math

def isPrime(a):
     """
          This function checks whether a given number is prime or not.
          Input: number a
          Output: True or False
     """
     
     if a<2 or (a>2 and a%2==0):
          return False
     
     for d in range(3,int(math.sqrt(a))+1,2):
          if a%d==0:
               return False
          
     return True




def smallerPrime(x):
     """
          This function calculates the first prime lower than a given number.
          Input: number x
          Output: returns the first prime number that's lower than x. If there is no such
               number, returns None.
     """
     
     if x%2==0:
          x-=1
     else:
          x-=2
          
     while x>1:
          if isPrime(x)==True:
               return x
          x-=2;




k=int(input("Give a number: "))
y=smallerPrime(k)
if y is not None:
     print(y)
else:
     print("There is no prime number smaller than " + str(k))

