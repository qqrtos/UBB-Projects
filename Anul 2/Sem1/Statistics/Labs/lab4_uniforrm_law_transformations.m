pkg load statistics;

% 2a)
p = input('2a-p: ');
N = input('2a-N: ');

# test this later
#U = rand(N, 1);
#X = U < p;

#unique_val = unique(X);
#unique_freq = histc(X, unique_val);
#unique_prob = unique_freq / N

success=0;
failure=0;

for i=1:N
  x=rand();
  if (x < p)
    success = success + 1;
  else
    failure = failure + 1;
  endif  
endfor

appprox_p = success/N

% 2b)
prob = input('2b-prob: ')
trials = input('2b-trials: ')
sim = input('2b-nr-sim: ')

for i=1:N
  vec = rand(1, trials);
    
endfor
