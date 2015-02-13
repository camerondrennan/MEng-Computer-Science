rem cameron2.sql
/*Lab qu1 (lab23)*/
SELECT model_no, make_name, model_name, year_start, year_finish, service_interval
	FROM	model;

/*Lab qu2 (lab25)*/
SELECT  IG_MIN, IG_MAX, model_name, deriv_name		    		
	FROM	derivative, model
	WHERE	model.model_no = derivative.model_no
	AND	IG_MAX > '6'
	AND	NOT auto = 'Y'
	AND 	(make_name = 'Audi' OR make_name = 'New Audi');

/*Lab qu3 (lab27)*/
SELECT  trade                              
        FROM    model, derivative, year_price
        WHERE   year_price.deriv_no = derivative.deriv_no
        AND     model.model_no = derivative.model_no
        AND     regi = '53'
	AND	body = 'Saloon'
	AND	deriv_name = 'Quattro';

/*The difference is (i) returns the avg(a1) of an Audi between 10000 and 20000. Whereas (ii) returns the a1 of an Audi between 10000 and 20000 (which is different from avg(a1) because avg caluclates the average of a1*/




