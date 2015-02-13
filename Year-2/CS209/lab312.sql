REM lab412.sql

/* The first view created counts the number of games which have been
played. The count() function counts the number of records in each
group (ie the number of games each team has played) and returns it
in a column headed 'p' which is given as an alias after the function */

drop view played;
drop view wv;
drop view lv;
drop view dv;
drop view gv;
drop view final_tables;
drop view goals_scored;

create view played as
select tna, count(*) p
from team, game
where (tno = team_1
or tno = team_2)
and round = 'first'
group by tna;

/* The next three views hold the following counts:

	wins (w)
	draws (d)
	looses (l)
	

In addition for wins and draws the number of points gained is calculated
using Oracle arithmetic operators. The results of these calculations
are stored in the following columns:

	wpts - points from wins
	dpts - points from draws
*/

create view wv as
select tna, count(*) w , count(*) * 3 wpts
from team, game
where ((tno = team_1
and team_1_goals > team_2_goals)
or (tno = team_2
and team_2_goals > team_1_goals))
and round = 'first'
group by tna;

create view dv as
select tna, count(*) d , count(*) * 1 dpts
from team, game
where ((tno = team_1
and team_1_goals = team_2_goals)
or (tno = team_2
and team_2_goals = team_1_goals))
and round = 'first'
group by tna;

create view lv as
select tna, count(*) l , count(*) * 0 lpts
from team, game
where ((tno = team_1
and team_1_goals < team_2_goals)
or (tno = team_2
and team_2_goals < team_1_goals))
and round = 'first'
group by tna;



/*
The next  view uses the Oracle sum() function to calculate the 
number of goals each team has scored. Records in the game table are
grouped by team name and the sum() function calculates the sum of goals
scored in each team's games as follows:

	goals for - f
	goals against - a
	
*/


create view goals_scored as
select tna,game_date ,team_1_goals f, team_2_goals a
from team, game 
where tno = team_1 and round = 'first'
union
select tna,game_date ,team_2_goals f, team_1_goals a
from team, game 
where tno = team_2 and round = 'first';


create view gv as
select tna, sum(f) f, sum(a) a from goals_scored group by tna;




/* The last view uses the preceeding nine views to create an overall
summary which represents the league table. The first part (ie the select
part) identifies the attribute names to display. Most of these attributes
have the Oracle function nvl() applied to them. This function converts
any null values to a numeric zero - the result being headed by the name
shown at the end of each of these lines. The last line in the select part 
uses a similar approach and Oracle arithmetic operators to calculate the
total number of points.
The conditions in the where clause arrange that each of the views
is joined to the played view. The (+) at the end of each line ensures that
if a team had not fro example scored any away wins (cf Dunfermline at 10/10/90)
then its record would not be lost when performing the join. This type
of join is called an OUTER JOIN.
*/
 
create view final_tables as
select 
played.tna, 
p, 
nvl(w, 0) w,
nvl(d,0) d,
nvl( l, 0) l,
nvl(f,0) f,
nvl (a,0) a,
( nvl(wpts,0)+nvl(dpts,0)) pts,
grp
from played, wv, dv, lv, gv, team 
where played.tna = wv.tna (+)
and played.tna = dv.tna (+)
and played.tna = lv.tna (+)
and played.tna = gv.tna (+)
and played.tna = team.tna ;







