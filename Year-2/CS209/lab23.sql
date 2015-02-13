
rem lab23.sql
SELECT  IG_MIN, IG_MAX, model_name, deriv_name		    		
	FROM	derivative, model
	WHERE	model.model_no = derivative.model_no
	AND	IG_MAX > '6'
	AND	NOT auto = 'Y'
	AND 	(make_name = 'Audi' OR make_name = 'New Audi');


