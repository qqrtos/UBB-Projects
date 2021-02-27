def palindrome(x):
     '''
          Function return the palindrome of a number.
          Input: x - guaranteed integer
          Output: the palindrome of x
     '''
     
     p=0
     while x is not 0:
          p=p*10+x%10
          x=x//10
     return p



def isNumber(x):
     '''
          This function checks whether x is an integer or not.
          Input: x
          Output: True or False
     '''
     
     try:
          x=int(x)
          return True
     except ValueError:
          print("That's not a number.")
          return False



n1=input("Give the number: ")
if isNumber(n1)==True:
     if int(n1)==palindrome(int(n1)):
          print("Number is equal to it's palindrome.")
     else:
          print("Number is not equal to it's palindrome.")


