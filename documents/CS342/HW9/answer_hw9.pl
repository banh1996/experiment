% Student exercise profile
:- set_prolog_flag(occurs_check, error).        % disallow cyclic terms
:- set_prolog_stack(global, limit(8 000 000)).  % limit term space (8Mb)
:- set_prolog_stack(local,  limit(2 000 000)).  % limit environment space

% program goes here
%q1
mystery([], []).
mystery([H|Tail], [H,H|DTail]) :- mystery(Tail,DTail).
%Z =  [1, 1, 4, 4, 6, 6]

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
%check_condition(x, y, z, r) :- x == 10, y == 20, z = x+y.
%check_condition([x,y|z], r) :- x == 10, y > 20, z = x-y.
insertAt(Element,0,L,[Element|L]).
insertAt(Element,Pos,[E|L],[E|ZL]):-
    Pos1 is Pos-1,
    insertAt(Element,Pos1,L,ZL).

%find_int(X) :- 


%q4, A,B,C,D,E is the finished job time.
del([X|XS], CNT, [X|RES]) :- NEXT is CNT - 1,
                             del(XS, NEXT, RES).
del([_|XS], 1, XS).

indexOf([Element|_], Element, 0).
indexOf([_|Tail], Element, Index):-
  indexOf(Tail, Element, Index1),
  Index is Index1+1.
replace([_|T], 0, X, [X|T]).
replace([H|T], I, X, [H|R]):- I > -1, NI is I-1, replace(T, NI, X, R), !.
replace(L, _, _, L).
q4_solve(X) :- A = 0, B is A+1, C is A-1, D is B-1, E is D+1,
     IN=[A,B,C,D,E],
	 bubble_sort(IN, Z),
    nth0(0, Z, Q0), indexOf(IN, Q0, Index0),
    		(Index0==0 -> (write('A-'), replace(IN, 0, 11, IN0));
    		(Index0==1 -> (write('B-'), replace(IN, 1, 11, IN0));
			(Index0==2 -> (write('C-'), replace(IN, 2, 11, IN0));
    		(Index0==3 -> (write('D-'), replace(IN, 3, 11, IN0));
    		(Index0==4 -> (write('E-'), replace(IN, 4, 11, IN0))))))),
    nth0(1, Z, Q1), indexOf(IN0, Q1, Index1),
    		(Index1==0 -> (write('A-'), replace(IN0, 0, 11, IN1));
    		(Index1==1 -> (write('B-'), replace(IN0, 1, 11, IN1));
			(Index1==2 -> (write('C-'), replace(IN0, 2, 11, IN1));
    		(Index1==3 -> (write('D-'), replace(IN0, 3, 11, IN1));
    		(Index1==4 -> (write('E-'), replace(IN0, 4, 11, IN1))))))),
    nth0(2, Z, Q2), indexOf(IN1, Q2, Index2),
    		(Index2==0 -> (write('A-'), replace(IN1, 0, 11, IN2));
    		(Index2==1 -> (write('B-'), replace(IN1, 1, 11, IN2));
			(Index2==2 -> (write('C-'), replace(IN1, 2, 11, IN2));
    		(Index2==3 -> (write('D-'), replace(IN1, 3, 11, IN2));
    		(Index2==4 -> (write('E-'), replace(IN1, 4, 11, IN2))))))),
    nth0(3, Z, Q3), indexOf(IN2, Q3, Index3),
    		(Index3==0 -> (write('A-'), replace(IN2, 0, 11, IN3));
    		(Index3==1 -> (write('B-'), replace(IN2, 1, 11, IN3));
			(Index3==2 -> (write('C-'), replace(IN2, 2, 11, IN3));
    		(Index3==3 -> (write('D-'), replace(IN2, 3, 11, IN3));
    		(Index3==4 -> (write('E-'), replace(IN2, 4, 11, IN3))))))),
    nth0(4, Z, Q4), indexOf(IN3, Q4, Index4),
    		(Index4==0 -> (write('A'));
    		(Index4==1 -> (write('B'));
			(Index4==2 -> (write('C'));
    		(Index4==3 -> (write('D'));
    		(Index4==4 -> (write('E'))))))).

%q5
%a.
sentence --> f.
sentence --> t, n, t.
t --> [x].
t --> [y].
t --> [z].
t --> [1].
t --> [0].
n --> [+].
n --> [-].
n --> [=].
f --> [if], b, [then], [begin], sentence, [end].
f --> [if], b, [then], [begin], sentence, [end], [else], [begin], sentence, [end].
b --> t, e, t.
e --> ['|'].
e --> ['<'].
e --> ['>'].

%b.

%c. yes