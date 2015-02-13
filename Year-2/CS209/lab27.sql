rem lab27.sql
SELECT  trade                              
        FROM    model, derivative, year_price
        WHERE   year_price.deriv_no = derivative.deriv_no
        AND     model.model_no = derivative.model_no
        AND     regi = '53'
	AND	body = 'Saloon'
	AND	deriv_name = 'Quattro';

