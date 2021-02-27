x = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96]

% variance = sigma^2
v = var(x)

%size
n = length(x)

%mean
m = mean(x)

%a

%confidence level
oneminusalpha = 0.95

%significance level
alpha = 1 - oneminusalpha

% we choose 1.2 from confidence intervals file
% we want to find the average(=mean) and sigma is unknown
samp_std = std(x); % we use the sample std. dev.

% limits of the confidence interval
m1b = mean(x) + tinv(alpha/2, n - 1) * samp_std/sqrt(n);
m2b = mean(x) - tinv(alpha/2, n - 1) * samp_std/sqrt(n);

fprintf('b) the confidence interval for the mean (sigma unknown) is: (m1b, m2b) = (%4.3f ,%4.3f)\n',m1b, m2b)


%b

%significance level
alpha = 0.01

%confidence level
oneminusalpha = 1 - alpha

m0b = 3

[H, P, CI, stats] = ttest(x,m0b,"alpha",alpha,"tail","left"); % 1, for left-tailed

t1 = tinv(alpha, n-1); % quantile for left-tailed test
RR = [t1, Inf]; % rejection region for left-tailed test
fprintf('\n H is %d', H)
if H==1
    fprintf('\n So the null hypothesis is rejected,\n') 
    fprintf('i.e. the data suggests that the average is smaller than 3.\n')
else
    fprintf('\n So the null hypothesis is not rejected,\n')
    fprintf('i.e. the data suggests that the average IS NOT smaller 3.\n')
end    