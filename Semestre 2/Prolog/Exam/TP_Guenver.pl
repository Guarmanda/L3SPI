% Guenver Yann TP ProgLog 


% Excercice 1 
insere_a(_,[],_,Res,Res).
insere_a(X,[T|Q],N,L,R) :- N\=1, M is N-1, append(L,[T],L2),insere_a(X,Q,M,L2,R),!.
insere_a(X,Q,N,L,Res) :- N=1,M is N-1,append(L,[X],L2), insere_a(X,Q,M,L2,Res).
insere_a(X,L,N,Res) :- insere_a(X,L,N,[],Res).

% Exercice 2
pgcd(A,A,A).
pgcd(A,B,Res) :- A<B, NewB is B-A, pgcd(A,NewB,Res),!.
pgcd(A,B,Res) :- B<A, pgcd(B,A,Res),!.

% Exercice 3
word(abalone,a,b,a,l,o,n,e).
word(abandon,a,b,a,n,d,o,n).
word(enhance,e,n,h,a,n,c,e).
word(anagram,a,n,a,g,r,a,m).
word(connect,c,o,n,n,e,c,t).
word(elegant,e,l,e,g,a,n,t).

motscroises(V1,V2,V3,H1,H2,H3) :- word(V1,_,A,_,B,_,C,_),
word(V2,_,D,_,E,_,F,_), word(V3,_,G,_,H,_,I,_),
word(H1,_,A,_,D,_,G,_),word(H2,_,B,_,E,_,H,_),word(H3,_,C,_,F,_,I,_).

% Exercice 4
substituer(_,_,[],[]).
substituer(X,Y,[X|Q],[Y|Q1]) :- substituer(X,Y,Q,Q1),!.
substituer(X,Y,[Z|Q],[Z|Q1]) :- X\=Z, substituer(X,Y,Q,Q1).




