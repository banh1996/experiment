% Student exercise profile
:- set_prolog_flag(occurs_check, error).        % disallow cyclic terms
:- set_prolog_stack(global, limit(8 000 000)).  % limit term space (8Mb)
:- set_prolog_stack(local,  limit(2 000 000)).  % limit environment space

% Your program goes here
%q1
mystery([], []).
mystery([H|Tail], [H,H|DTail]) :- mystery(Tail,DTail).

%q2a
gcd(A,B,X) :- A=B, X=A.
gcd(A,B,X) :- A<B, B1 is B-A, gcd(A,B1,X).
gcd(A,B,X) :- A>B, gcd(B,A,X).

%q2b
copy(L,R) :- accCp(L,R).
accCp([],[]).
accCp([H|T1],[H|T2]) :- accCp(T1,T2).

bubble_sort(List,Sorted):-b_sort(List,[],Sorted).
	b_sort([],Acc,Acc).
	b_sort([H|T],Acc,Sorted):-bubble(H,T,NT,Max),b_sort(NT,[Max|Acc],Sorted).
bubble(X,[],[],X).
bubble(X,[Y|T],[Y|NT],Max):-X>Y,bubble(X,T,NT,Max).
bubble(X,[Y|T],[X|NT],Max):-X=<Y,bubble(Y,T,NT,Max).

duplicate_help(X, A, Z) :- A==1, copy(X,Z).
duplicate_help(X, A, Z) :- A>1, A1 is A-1, duplicate_help(X, A1, X1),
    append(X1, X, Z).

duplicate(X, A, Z) :-
    duplicate_help(X, A, X1), bubble_sort(X1, Z).

%q3
%check_condition([x,y|z], r) :- x == 10, y == 20, z == x+y, true.
%check_condition([x,y|z], r) :- x == 10, y > 20, z == x-y, true.
insertAt(Element,0,L,[Element|L]).
insertAt(Element,Pos,[E|L],[E|ZL]):-
    Pos1 is Pos-1,
    insertAt(Element,Pos1,L,ZL).

%find_int(X) :- 


%q4, A,B,C,D,E is the finished job time.
:- use_module(library(clpfd)).

zmin_deleted(Zs1,Zs0) :-
   same_length(Zs1,[_|Zs0]),
   maplist(#=<(Min),Zs1),
   select(Min,Zs1,Zs0).

minl([Only], Only).
minl([Head|Tail], Minimum) :-
    minl(Tail, TailMin),
    Minimum is min(Head, TailMin).

%q4_solve(X) :- A=0, B is A+1, C is A-1, D is B-1, E is D+1, 
%    min is minl([A,B,C,D,E]), bubble_sort([A,B,C,D,E],X).






