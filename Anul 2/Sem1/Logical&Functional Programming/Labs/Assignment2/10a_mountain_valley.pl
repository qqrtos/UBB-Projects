ascending_list([_]):- true, !.

%ascending_list(L1: list)
%(i)
ascending_list([L1|[L2|T]]):- L1<L2, ascending_list([L2|T]).

%valley(L1: list)
%(i)
valley([H1|[H2|T]]):- H1>H2, valley([H2|T]), !.

valley([H1|[H2|[H3|T]]]):- H1>H2, H2<H3, ascending_list([H2|T]), !.


%:- begin_tests(test).

%test(valley):-
%    assertion(valley([10,6,8])==true).

%test(valley):-
%    assertion(valley([1,2,3])==false).

%test(valley):-
%    assertion(valley([10,9,8])==false).

%test(valley):-
%    assertion(valley([10,9,8,7,8,9,10])==true).

%:- end_tests(test).
