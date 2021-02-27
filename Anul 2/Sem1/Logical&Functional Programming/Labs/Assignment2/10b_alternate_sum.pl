%alternate_sum_with_sign(List: list, sign: integer, Res: integer)
%(i, i, o)
alternate_sum_with_sign([], _, 0).

alternate_sum_with_sign([H|T], Sign, Res):- alternate_sum_with_sign(T, Sign*(-1), Res1),
                                            Res is (Res1 + (H * Sign)).

alternate_sum([H|T], Res):- alternate_sum_with_sign([H|T], 1, Res).


%:-begin_tests(test).

%test(alternate_sum):-
%    alternate_sum([1,2,3,4], Res),
%    assertion(Res == -2).

%test(alternate_sum):-
%    alternate_sum([10,10,10,10], Res),
%    assertion(Res == 0).

%:-end_tests(test).
