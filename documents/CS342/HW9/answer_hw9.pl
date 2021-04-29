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
duplicate([], A, []).
duplicate([H|Tail], A, [H,H|DTail]) :- A>1, 
    duplicate([H|Tail], A-1, [H,H|DTail]).
%duplicate([H|Tail], A, [H,H|DTail]) :- A<1, mystery(Tail,DTail).

copy(L,R) :- accCp(L,R).
accCp([],[]).
accCp([H|T1],[H|T2]) :- accCp(T1,T2).
%q3

/** <examples> Your example queries go here, e.g.
?- member(X, [cat, mouse]).
*/
