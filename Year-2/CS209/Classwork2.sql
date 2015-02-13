DROP TABLE INTRODUCED;
DROP TABLE PAINTS;
DROP TABLE LOCATED;
DROP TABLE OWNER_HISTORY;
DROP TABLE EXHIBITION;
DROP TABLE IN_GALLERY;
DROP TABLE ON_LOAN;
DROP TABLE ROOM;
DROP TABLE INSURANCE_CERT;
DROP TABLE PAINTING;
DROP TABLE OWNER;
DROP TABLE ARTIST;

CREATE TABLE ARTIST
(A_id		CHAR(15) 	CONSTRAINT ART_PK primary key,
NAME		CHAR(15) 	CONSTRAINT NULL_ARTIST NOT NULL,		
DOB		DATE		CONSTRAINT NULL_DOB NOT NULL,		
DOD		DATE,
NATIONALITY 	CHAR(15) 	CONSTRAINT NULL_NAT NOT NULL); 

INSERT INTO ARTIST(A_id, NAME, DOB, DOD, NATIONALITY) VALUES
			  	(13253460, 'CAMERON', '12-MAY-1966', '01-JAN-2013', 'SCOTTISH');
INSERT INTO ARTIST(A_id, NAME, DOB, DOD, NATIONALITY) VALUES
			  	(23765876, 'STUART', '25-DEC-1810', '23-FEB-1855', 'ITALIAN');
INSERT INTO ARTIST(A_id, NAME, DOB, DOD, NATIONALITY) VALUES
			  	(36585433, 'ANGUS', '05-MAR-2000', '07-JUN-2005', 'FRENCH');
INSERT INTO ARTIST(A_id, NAME, DOB, DOD, NATIONALITY) VALUES
			  	(49789651, 'MICHAEL', '16-AUG-1986', '22-SEP-2000', 'COLUMBIAN');

CREATE TABLE PAINTING
(P_id		CHAR(15) 	CONSTRAINT P_PK primary key,
TITLE		CHAR(15) 	CONSTRAINT NULL_TITLE NOT NULL,
VALUE		NUMBER(15,2) 	CONSTRAINT NULL_VALUE NOT NULL 
		    	     	CONSTRAINT PVAL_CHECK CHECK(VALUE>0),
AQUISITION_DATE	DATE,
INSURANCE_VALUE	NUMBER(15,2));

INSERT INTO PAINTING(P_id, TITLE, VALUE, AQUISITION_DATE, INSURANCE_VALUE) VALUES
			  	(43987498, 'MONA', 100000.00, '10-MAR-1888', 150000.00);
INSERT INTO PAINTING(P_id, TITLE, VALUE, AQUISITION_DATE, INSURANCE_VALUE) VALUES
			  	(83745844, 'LISA', 1000.00, '13-FEB-1844', 1500.00);
INSERT INTO PAINTING(P_id, TITLE, VALUE, AQUISITION_DATE, INSURANCE_VALUE) VALUES
			  	(98648974, 'SHREK', 9999.99, '10-AUG-2002', 12000.00);
INSERT INTO PAINTING(P_id, TITLE, VALUE, AQUISITION_DATE, INSURANCE_VALUE) VALUES
			  	(40987598, 'FIONA', 599.99, '05-APR-1992', 650.00);

CREATE TABLE OWNER
(O_id		CHAR(15) 	CONSTRAINT OWNER_PK primary key,
NAME		CHAR(15) 	CONSTRAINT NULL_OWNERNAME NOT NULL);

INSERT INTO OWNER(O_id, NAME) VALUES
			  	(23857905, 'BRUNO');
INSERT INTO OWNER(O_id, NAME) VALUES
			  	(89769966, 'IAIN');
INSERT INTO OWNER(O_id, NAME) VALUES
			  	(68975495, 'ADAM');
INSERT INTO OWNER(O_id, NAME) VALUES
			  	(67548555, 'GREGOR');

CREATE TABLE OWNER_HISTORY
(OH_id		CHAR(15) 	CONSTRAINT OWNERHIS_PK primary key,
DATE_BOUGHT	DATE		CONSTRAINT NULL_BOUGHT NOT NULL,
DATE_SOLD	DATE		CONSTRAINT NULL_SOLD NOT NULL,		
P_id		CHAR(15)	CONSTRAINT OWNERHIS_P_id_FK REFERENCES 
				PAINTING(P_id) ON DELETE CASCADE,
O_id		CHAR(15)	CONSTRAINT OWNERHIS_O_id_FK REFERENCES 
				OWNER(O_id) ON DELETE CASCADE);

INSERT INTO OWNER_HISTORY(OH_id, DATE_BOUGHT, DATE_SOLD, P_id, O_id) VALUES
			  	(89769966, '15-DEC-1985', '30-JUN-2000',
				43987498, 23857905);
INSERT INTO OWNER_HISTORY(OH_id, DATE_BOUGHT, DATE_SOLD, P_id, O_id) VALUES
			  	(23857905, '06-FEB-1860', '22-AUG-1967',
				98648974, 89769966);
INSERT INTO OWNER_HISTORY(OH_id, DATE_BOUGHT, DATE_SOLD, P_id, O_id) VALUES
			  	(67548555, '17-MAR-2012', '04-MAY-2013',
				98648974, 68975495);
INSERT INTO OWNER_HISTORY(OH_id, DATE_BOUGHT, DATE_SOLD, P_id, O_id) VALUES
			  	(68975495, '27-MAY-1999', '27-JUL-2005',
				40987598, 67548555);

CREATE TABLE IN_GALLERY
(P_id		CHAR(15) 	CONSTRAINT INGALL_PK primary key
				CONSTRAINT INGALL_FK REFERENCES 
				PAINTING(P_id) ON DELETE CASCADE);

INSERT INTO IN_GALLERY(P_id) VALUES (43987498);
INSERT INTO IN_GALLERY(P_id) VALUES (83745844);

CREATE TABLE ON_LOAN
(P_id		CHAR(15) 	CONSTRAINT ONLOAN_PK primary key
				CONSTRAINT ONLOAN_FK REFERENCES 
				PAINTING(P_id) ON DELETE CASCADE);

INSERT INTO ON_LOAN(P_id) VALUES (98648974);
INSERT INTO ON_LOAN(P_id) VALUES (40987598);

CREATE TABLE ROOM
(R_No		NUMBER(3,0) 	CONSTRAINT ROOM_PK primary key,
TEMPERATURE	NUMBER(3,1)	CONSTRAINT NULL_TEMP NOT NULL,
HUMIDITY	NUMBER(3,1)	CONSTRAINT NULL_HUMID NOT NULL);

INSERT INTO ROOM(R_No, TEMPERATURE, HUMIDITY) VALUES
			  	(298, 32.1, 56.4);
INSERT INTO ROOM(R_No, TEMPERATURE, HUMIDITY) VALUES
			  	(250, 24.7, 40.5);
INSERT INTO ROOM(R_No, TEMPERATURE, HUMIDITY) VALUES
			  	(650, 44.6, 77.8);
INSERT INTO ROOM(R_No, TEMPERATURE, HUMIDITY) VALUES
			  	(976, 30.7, 53.9);

CREATE TABLE INSURANCE_CERT
(CERTid		CHAR(15) 	CONSTRAINT INSUR_PK primary key,
INSURER		CHAR(15)	CONSTRAINT NULL_INSURER NOT NULL);

INSERT INTO INSURANCE_CERT(CERTid, INSURER) VALUES
			  	(13124235, 'AVIVA');
INSERT INTO INSURANCE_CERT(CERTid, INSURER) VALUES
			  	(45687340, 'ONEBANK');
INSERT INTO INSURANCE_CERT(CERTid, INSURER) VALUES
			  	(23589793, 'INSURAPARE');
INSERT INTO INSURANCE_CERT(CERTid, INSURER) VALUES
			  	(21109748, 'PAINTINSURE');

CREATE TABLE EXHIBITION
(VENUE		CHAR(15)	CONSTRAINT NULL_VENUE NOT NULL,
UTITLE		CHAR(15)	CONSTRAINT EXHIB_PK primary key,
STARTDATE	DATE		CONSTRAINT NULL_STARTDATE NOT NULL,
FINSHDATE	DATE		CONSTRAINT NULL_FINISHDATE NOT NULL,
SPONSORS	CHAR(15)	CONSTRAINT NULL_SPONSORS NOT NULL);

INSERT INTO EXHIBITION(VENUE, UTITLE, STARTDATE, FINSHDATE, SPONSORS) VALUES
				('RUGBY PARK', 'RP', '01-JAN-1888', '07-JAN-1888', 'UNITE');
INSERT INTO EXHIBITION(VENUE, UTITLE, STARTDATE, FINSHDATE, SPONSORS) VALUES
				('PARK HEAD', 'PH', '30-MAY-1789', '22-AUG-1789', 'JANSPORT');
INSERT INTO EXHIBITION(VENUE, UTITLE, STARTDATE, FINSHDATE, SPONSORS) VALUES
				('IBROX', 'IB', '11-JUN-1688', '2-FEB-1689', 'RIVER');
INSERT INTO EXHIBITION(VENUE, UTITLE, STARTDATE, FINSHDATE, SPONSORS) VALUES
				('TANNANDICE', 'TA', '07-DEC-1890', '02-AUG-1891', 'PIES');

CREATE TABLE PAINTS
(A_id		CHAR(15)        CONSTRAINT PAINTS_A_id_FK REFERENCES
                                ARTIST(A_id) ON DELETE CASCADE,
P_id		CHAR(15)	CONSTRAINT PAINTS_P_id_FK REFERENCES
				PAINTING(P_id) ON DELETE CASCADE,
				CONSTRAINT PAINTS_PK primary key(A_id,P_id));

INSERT INTO PAINTS(A_id, P_id) VALUES (13253460, 43987498);
INSERT INTO PAINTS(A_id, P_id) VALUES (23765876, 83745844);
INSERT INTO PAINTS(A_id, P_id) VALUES (36585433, 98648974);
INSERT INTO PAINTS(A_id, P_id) VALUES (49789651, 40987598);

CREATE TABLE LOCATED
(R_No		NUMBER(3,0)	CONSTRAINT LOCATED_R_No_FK REFERENCES
				ROOM(R_No) ON DELETE CASCADE,
P_id		CHAR(15)	CONSTRAINT LOCATED_P_id_FK REFERENCES
				PAINTING(P_id) ON DELETE CASCADE,
				CONSTRAINT LOCATED_PK primary key(R_No,P_id));

INSERT INTO LOCATED(R_No, P_id) VALUES (298, 43987498);
INSERT INTO LOCATED(R_No, P_id) VALUES (250, 83745844);
INSERT INTO LOCATED(R_No, P_id) VALUES (650, 98648974);
INSERT INTO LOCATED(R_No, P_id) VALUES (976, 40987598);

CREATE TABLE INTRODUCED
(O_id		CHAR(15) 	CONSTRAINT INTRO_O_id_FK REFERENCES
				OWNER(O_id) ON DELETE CASCADE,
O_id1		CHAR(15) 	CONSTRAINT INTRO_O_id1_FK REFERENCES
				OWNER(O_id) ON DELETE CASCADE,
				CONSTRAINT INTRO_PK primary key(O_id));

INSERT INTO INTRODUCED(O_id, O_id1) VALUES (23857905, 89769966);
INSERT INTO INTRODUCED(O_id, O_id1) VALUES (68975495, 23857905);
INSERT INTO INTRODUCED(O_id, O_id1) VALUES (89769966, 67548555);
INSERT INTO INTRODUCED(O_id, O_id1) VALUES (67548555, 68975495);

SELECT pa.TITLE, pa.VALUE, oh.OH_id 
	FROM PAINTING pa
	JOIN OWNER_HISTORY oh
	ON pa.P_id = oh.P_id
	WHERE VALUE > 1000
	GROUP BY pa.TITLE, pa.VALUE, oh.OH_id;

SELECT TITLE, VALUE 
	FROM PAINTING 
	WHERE VALUE IN (SELECT VALUE 
	FROM PAINTING
	WHERE VALUE > 999); 

SELECT P_id, DATE_SOLD
	FROM OWNER_HISTORY 
	WHERE DATE_SOLD IN (SELECT max(DATE_SOLD) 
	FROM OWNER_HISTORY); 

SELECT i.O_id ||'Introduces '|| i1.O_id1
	FROM INTRODUCED i, INTRODUCED i1
	WHERE i.O_id = i1.O_id;
