#1 2 3 2 5 2 3 7 2 3 2 5...


def extractFactor(a, e):
     '''
          This function extracts a prime factor from a number.

          Input: a-number
                 e-factor of a

          Output: a after dividing it by e however many times possible.
     '''
     while a%e==0:
          a=a//e
     return a




def nthNumber(n):
     '''
          Let sequence1=[1,2,3,4,5,6,7,8...]
              sequence2=[1,2,3,2,5,2,3,7...] <- the one given by the problem.
              
          This function builds the given sequence2 without memorizing the elements.
          The variable x is a number from sequence1, which then gets broken into it's
          prime divisors. For each prime divisor, the variable i gets indented,
          so that we can count the position of the factor in the sequence2. The
          variable res keeps the value for the element at the index i in the sequnce2.

          Input: n

          Output: res, which is the number present in the sequence2 at index n
     '''
     x=1
     i=1
     res=1
     while i < n:
          d=2
          aux=x
          while aux is not 1:
               if aux%d==0:
                    aux=extractFactor(aux,d)
                    res=d
                    i+=1
               if i is n:
                    return res
               d+=1
          x+=1
     return res




n=int(input("Give a number: "))
print(nthNumber(n))

#for i in range(1,n):
#     print(nthNumber(i))
