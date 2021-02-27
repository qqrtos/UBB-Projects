def frequency_array(x):
     '''
          This function creates a frequency array for the digits of number x.
          Input: x
          Output: list lis that contains the value 1 at index i if i is a digit of x
     '''
     lis=[0]*9
     while x is not 0:
          lis[int(x%10)]=1
          x//=10
     return lis




ok=True
n1=int(input("Let n1= "))
n2=int(input("Let n2= "))
l=frequency_array(n1)

while n2 is not 0:
     if l[int(n2%10)] is 0:
          print ("The numbers don't have the property P")
          ok=False
          break
     n2//=10
if ok is True:
     print("The numbers have the same digits.")
