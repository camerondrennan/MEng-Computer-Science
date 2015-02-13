SELECT MODEL_NAME, DERIV_NAME
FROM model Z, derivative Y, year_price X
WHERE Z.model_no = y.model_no
AND y.deriv_no = x.deriv_no
AND new > (SELECT AVG(new)
	FROM year_price
	WHERE x.regi = regi);

