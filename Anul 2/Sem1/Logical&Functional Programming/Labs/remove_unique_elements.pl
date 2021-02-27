%count_elem(List: list, E;em, element, Result: integer)
%(i, i, output)  -->  input input output
count_elem([], _, 0):- !.

count_elem([H|T], H, Res):- count_elem(T, H, Res1),
                            Res is Res1 + 1, !.

count_elem([_|T], Elem, Res):- count_elem(T, Elem, Res).


%delete_elem(L1: list, L2: list, Rez: list)
%(i, i, o)
delete_elem([], _, []):- !.

delete_elem([H|T], L2, Rez):- count_elem(L2, H, C), C =:= 1, delete_elem(T, L2, Rez).

delete_elem([H|T], L2, [H|Rez]):- count_elem(L2, H, C), C > 1, delete_elem(T, L2, Rez).

