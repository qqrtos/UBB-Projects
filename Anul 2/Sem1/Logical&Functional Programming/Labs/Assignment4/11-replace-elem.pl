%replace_element(L1: list, Elem: integer, NewElem: integer, Result: list) - deterministic
% (i, i, i, o)
% replace_element(l1..ln, elem, newElem) = newElem U
%                                              replace_element(l2..ln,
%                                              elem, newElem), if l1 =
%                                              elem
%                                          elem U
%                                              replace_element(l2..ln,
%                                              elem, newElem), if l1 !=
%                                              elem
%                                          [], n = 0
replace_element([], _, _, []):- !.

replace_element([H|T], Elem, NewElem, [NewElem|Result]):- H=:=Elem, replace_element(T, Elem, NewElem, Result).%, !.

replace_element([H|T], Elem, NewElem, [H|Result]):- H=\=Elem, replace_element(T, Elem, NewElem, Result).%, !.


%max_element(L1: list, Res: integer)
% (i, o)
% max_element(l1..ln, res) = res is l1, max_element(l2..ln,res) l1 > res
%                            res is l1, n = 1
%                            max_element(l2..ln, res) otherwise
max_element([H], H).

max_element([H|T], Res):- is_list(H), !, max_element(T, Res).

max_element([H|T], Res):- max_element(T, Res1),
                          Res is max(H, Res1).


%replace_max(L1: list, ReplaceElem, L2: list)
% (i, i, o)
% replacE_max(l1..ln, repEl) = replace_element(l1, repEl,
%                                                   max_element(l1)) U
%                                                                     replace_max(l2..ln,
%                                                                                    replEl)
%                                                                                    ,is_list(l1)
%                              l1 U replace_max(l2..ln, replEl),
%                                                            otherwise
replace_max([], _, []).

replace_max([H|T], ReplaceElem, [Res1|Result]):- is_list(H), !,
                          max_element(H, M1),
                          replace_element(H, ReplaceElem, M1, Res1),
                          replace_max(T, ReplaceElem, Result).

replace_max([H|T], ReplaceElem, [H|Result]):- replace_max(T, ReplaceElem, Result).


%main(L: list, Result: list)
% (i, o)
main([H|T], Result):- max_element([H|T], Maxx), replace_max([H|T], Maxx, Result).
