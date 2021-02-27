% practic ex4
A = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023]
B = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975]

n1 = length(A)
n2 = length(B)

%significance level
alpha = 0.05

%confidence level
oneminusalpha = 1 - alpha

%variance
vA = var(A)
vB = var(B)


% a)
% variance -> 2
fA = tinv(alpha/2, n1+n2-2);
fB = tinv(1 - alpha/2, n1+n2-2); % quantiles for two-tailed test (for rejection region)

% part a. 
% The null hypothesis H0: sigma1^2 = sigma2^2
% The alt. hypothesis H1: sigma1^2 ~= sigma2^2
% two-tailed for comparing the variances
[H, P, CI, stats] = vartest2(A, B, "alpha", alpha);

fprintf('\n part a. Comparing variances\n')
fprintf('Two-tailed test for comparing variances\n')
if H == 0
    fprintf('H is %d\n', H)
    fprintf('So the null hypothesis is not rejected,\n')
    fprintf('i.e. the variances seem to be equal\n')
    fprintf('the rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, fA, fB, inf)
    fprintf('the value of the test statistic F is %6.4f\n', stats.fstat)
    fprintf('the P-value for the variances test is %6.4f\n', P)
else
    fprintf('H is %d\n', H)
    fprintf('So the null hypothesis is rejected,\n')
    fprintf('i.e. the variances seem to be different\n')
    fprintf('the rejection region for F is (%6.4f,%6.4f)U(%6.4f,%6.4f)\n', -inf, fA, fB, inf)
    fprintf('the value of the test statistic F is %6.4f\n', stats.fstat)
    fprintf('the P-value for the variances test is %6.4f\n', P)
end


