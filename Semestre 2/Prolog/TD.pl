% Question 1
my_last(X,[X|[]]).
my_last(X,[_|Y]):- my_last(X,Y).

% Question 2
avantDernier(X,[X,_]).
avantDernier(X,[_|Y]):- avantDernier(X,Y).

% Question 3
element_at(X,[X|_],1).
element_at(X,[_|Y],N):- M is N-1,element_at(X,Y,M).

% Question 4
nbElem(X,[],X).
nbElem(X,[_|Y],N):- M is N+1,nbElem(X,Y,M).
nbElem(X,Y):- nbElem(X,Y,0).

% Question 5
inverse(X,[],X).
inverse(X,[Z|Y],N):- inverse(X,Y,[Z|N]).
inverse(X,Y):- inverse(X,Y,[]).

% Question 6
palindrome(X):- inverse(X,X).

% Question 7
my_flatten([],[]).
my_flatten([H|T],X):- is_list(H),append(H,T,Y),my_flatten(Y,X).
my_flatten([H|T],Y):- my_flatten(T,X),append([H],X,Y).

% Question 8
compress([], []).
compress([Tete,Tete|Rest],Result):- !, compress([Tete|Rest], Result).
compress([Tete|Queue], [Tete|Result]):- compress(Queue, Result).

% Question 9
pack([], []).
pack([X], [[X]]).
pack([H, T|TS], [[H]|TR]):- H \= T, pack([T|TS], TR).
pack([H, H|HS], [[H|TFR]|TR]):- pack([H|HS], [TFR|TR]).

% Question 10
pack([], []).
pack([X], [[X]]).
pack([H, T|TS], [[H]|TR]):- H \= T, pack([T|TS], TR).
pack([H, H|HS], [[H|TFR]|TR]):- pack([H|HS], [TFR|TR]).





