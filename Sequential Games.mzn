% Sequential Games

% Sample data
% num = 25;
% fun = [-2,0,3,-2,1,2,-5,-3,2,1,-2,0,1,4,0,0,-2,-5,-3,-4,5,-4,5,-2,5];
% cap = 5;
% refill = 2;

% Given
int: num;                  % Number n ∈ N of games;
set of int: games = 1..num; 
int: refill;               % Refill amount R ∈ N;
set of int: x_total = 0.. (cap + refill); 
array [games] of int: fun; % Fun value vi ∈ Z for each game i ∈ [n];
int: cap;                  % Pocket Capacity C ∈ N;
%int: K;                   % Goal K ∈ N;


% Find
array[games] of var int: t;
array[games] of var int: plays;


% The constraints on t and p are:
% 1. ∑i∈[n] pivi ≥ K:
% sum(i, i∈[n], p(i) · v(i)) ≥ K
%constraint sum(i in games) (plays[i] * fun[i]) >= K;



%%%%%%%%%%%%%%%%%%%%%%%%%%% Constraint %%%%%%%%%%%%%%%%%%%%%%%%%%%

% 1. The number of tokens ti available to play game i is C when we start playing the
% first game, and for i > 1 is the minimum of C and ti−1 − pi−1 + R:
constraint (t[1] = cap) /\ ((forall (i in games)
((1 < i /\ i <= num) -> (exists(x in x_total) ( (x = (t[i-1] - plays[i-1] + refill)) /\
  ( (x > cap) -> (t[i] = cap) ) /\ ( (x <= cap) -> (t[i] = x) )  )))));


% 2. We play each game at least once, and at most times
constraint forall (i in games) ((1 <= i /\ i <= num) -> (1 <= plays[i] /\ plays[i] <= t[i]));




%%%%%%%%%%%%%%%%%%%%%% Addtional Constraint %%%%%%%%%%%%%%%%%%%%%%

% If we have negative fun for a game, We just want to play this game for once 
% That is we just need to decide the number of plays for positive fun
% In other words, we ignore negative fun games 
constraint forall (i in games) (fun[i] < 1 -> plays[i] = 1);






%%%%%%%%%%%%%%%%%%%%%%% Solve and Output %%%%%%%%%%%%%%%%%%%%%%%%%

solve maximize sum(i in games)(plays[i] * fun[i]);
%solve satisfy;
output ["fun for each games            " ++ show(fun) ++ "\n" ++ 
        "number of tokens in each game " ++ show(t) ++ "\n" ++ 
        "sequence of play               " ++ show(plays) ++ "\n" ++ 
        "total fun: " ++ show (sum(i in games)(plays[i] * fun[i]))] ;