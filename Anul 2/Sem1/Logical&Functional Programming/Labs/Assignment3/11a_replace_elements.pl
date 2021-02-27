%replace_element(L1: list, Elem: integer, NewElem: integer, Result:
% list)
% (i, i, i, o)
replace_element([], _, _, []):- !.

replace_element([H|T], Elem, NewElem, [NewElem|Result]):- H=:=Elem, replace_element(T, Elem, NewElem, Result).%, !.

replace_element([H|T], Elem, NewElem, [H|Result]):- H=\=Elem, replace_element(T, Elem, NewElem, Result).%, !.


%:-begin_tests(test).

%test(replace_element):-
%    replace_element([1,3,1,5], 1, 10, Res),
%    assertion(Res == [10, 3, 10, 5]).

%test(replace_element):-
%    replace_element([], 1, 5, Res),
%    assertion(Res == []).

%test(replace_element):-
%    replace_element([1,2,3], 5, 1, Res),
%    assertion(Res == [1,2,3]).

%:-end_tests(test).
