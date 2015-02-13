CREATE OR REPLACE PROCEDURE empnames
IS
BEGIN 
DECLARE
employee_name emp.ename%TYPE;

CURSOR c_emp IS
  select ename from emp where empno >= 7700;

BEGIN
 OPEN c_emp;
 LOOP
  FETCH c_emp INTO employee_name;
	EXIT WHEN c_emp %NOTFOUND;
  DBMS_OUTPUT.PUT_LINE(employee_name);
 END LOOP;
END;
END;
