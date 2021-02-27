%maximum_element(L: list, Max: integer)
%(i, o)
maximum_element([H], H):- !.

maximum_element([H|T], Max):- maximum_element(T, Max), Max >= H.

maximum_element([H|T], H):- maximum_element(T, Max), H > Max.


replace_sublists([H|T], Elem, NewElem) :-
