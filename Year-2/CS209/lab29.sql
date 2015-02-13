
rem lab29.sql
SELECT regi, avg(new), avg(a1), avg(good), avg(fair), avg(trade)
	FROM year_price, derivative, model
	WHERE year_price.deriv_no = derivative.deriv_no
	AND model.model_no = derivative.model_no
	AND make_name = 'Audi'
	AND model_name = 'A4'
	GROUP BY regi
	HAVING avg(a1) > 10000 AND avg(a1) < 20000;  

