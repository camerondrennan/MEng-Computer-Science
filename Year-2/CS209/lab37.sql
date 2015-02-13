REM lab37.sql

select game.* 
from game,team
where tno = team_2
and tna like 'Ang%'
and game_date = '16-JUN-06';

