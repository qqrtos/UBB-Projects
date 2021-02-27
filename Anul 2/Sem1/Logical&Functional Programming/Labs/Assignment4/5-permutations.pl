%is_in_list(L: list, Elem: integer) - deterministic
% (i, i)
% is_in_list(l1..ln, e) = true, l1 = e
%                         false, n = 0
%                         is_in_list(l2..ln, e), otherwise
is_in_list([H|_], Elem):- H =:= Elem, !, true.

is_in_list([_|T], Elem):- is_in_list(T, Elem).

is_in_list([], _):- false.

%candidate(N: integer, I: integer)
% (i, o)
% candidate(n) = n
%                candidate(n-1), n>1
candidate(N, N).

candidate(N, I):- N>1,
                  N1 is N-1,
                  candidate(N1, I).

%permutations(N: integer, M: integer, L: list) - underterministic
% (i, i, o)
% permutations(n, m) = aux_permutations(n, m, 1, [candidate(n)])
permutations(N, M, L):- candidate(N, I),
                        aux_permutations(N, M, L, 1, [I]).

%aux_permutations(N: integer, M: integer, L: integer, Lg: integer, L1: list) - underterministic
% (i, i, o, i, i)
% aux_permutations(n, m, lg, col1..coln) = col, lg = n
%                                   aux_permutations(n, m, lg+1,
%                                                    c U col), where c =
%                                                          candidate(n)
%                                                    if abs(col1 - c) >=
%                                                                       m
%                                                        and not
%                                                        is_in_list(col1..coln,
%                                                        c)
%
aux_permutations(N, _, Col, N, Col):- !.

aux_permutations(N, M, L, Lg, [H|T]):- candidate(N, I),
                                       abs(H-I)>=M,
                                       \+ is_in_list([H|T], I),
                                       Lg1 is Lg+1,
                                       aux_permutations(N, M, L, Lg1, [I|[H|T]]).
