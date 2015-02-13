
rem lab25.sql
SELECT  make_name, model_name, deriv_name		    		
	FROM	model, derivative
	WHERE	model.model_no = derivative.model_no;


