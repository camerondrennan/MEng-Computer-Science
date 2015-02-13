/* set up the page size */
SET PAGESIZE 80

/* set up the column headings and formats */
COLUMN EMPNO HEADING EMPLOYEE_NO
COLUMN DEPTNO HEADING DEPARTMENT
COLUMN ENAME HEADING EMPLOYEE
COLUMN TODAY NOPRINT NEW_VALUE DATEVAR
COLUMN SAL FORMAT $99,999 HEADING SALARY


/* prompt the user for a value */
PROMPT Enter the lowest value for employee number
ACCEPT ENUMBER NUMBER PROMPT 'Emp. no.: '

/* print the titles */
TTITLE CENTER 'PERSONNEL REPORT' SKIP 1 -
CENTER DATEVAR SKIP 2


/* execute the query on the database */
SELECT TO_CHAR ( SYSDATE, 'DD/MM/YY/' ) TODAY ,
EMPNO, DEPTNO, ENAME, SAL
FROM EMP
WHERE EMPNO < &ENUMBER;
