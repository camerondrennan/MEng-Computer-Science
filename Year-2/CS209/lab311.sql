REM lab411.sql

create view t1_groupA
	as
select tna, game_date, team_1_goals, team_2, team_2_goals
from team, game
where tno = team_1
and grp = 'A'
and round = 'first';

