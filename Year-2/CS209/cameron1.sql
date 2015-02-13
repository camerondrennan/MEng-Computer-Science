/* set up the page size */
SET PAGESIZE 80
SET LINESIZE 65

/* set up the column headings and formats */
COLUMN Dname HEADING "DEPARTMENT NAME" format A15
COLUMN Deptno HEADING "DEPARTMENT NUMBER"
COLUMN Loc HEADING Location

/* print the titles */
TTITLE CENTER 'DEPARTMENT LOCATIONS' SKIP 1 -



/* execute the query on the database */
SELECT Dname, Deptno, Loc from dept;

