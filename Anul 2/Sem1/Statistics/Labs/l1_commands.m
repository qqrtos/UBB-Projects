x = 1 #normal declaration - prints results

x = 1; #semicolon ignores the printy statement

array = [1,2,3,4,5,6] #declaring an arrayfun

array = 1:1:10 #initialValue : stepSize : finalValue

array = 10:-1:1 #decreasing arrray

matrix = [1,2,3; 4,5,6; 7,8,9] #matrix_type

matrix(1:2, 2:3) #get rows 1-2 and cols 2-3

# help input --- use the command help for anything

function outputName = functionName(in) 
  # save function in a separate script and call it using 'functionName'
  outputName = 2 * in;  
 end

#cosider 2 matrices: A and B. Multiply them using A*b.
#using this: A.*B means A is a scalar and the multiplication is done with a scalar
#if A is a matrix tho, A.*B means that we add the 2 matrices - somehow
#to square all the elements inside a vector, use x.^2

eye(3) #identity matrix 3x3

#fprintf does writes to file lol

#clc -> clears screen
#clear var -> clears variables