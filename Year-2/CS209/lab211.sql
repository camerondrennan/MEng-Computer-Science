rem lab31.sql
SELECT  ig_max, max(a1), min(a1)
	FROM	derivative, year_price
	WHERE 	derivative.deriv_no = year_price.deriv_no
	GROUP BY ig_max;
