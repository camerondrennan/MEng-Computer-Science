<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html401/loose.dtd">
<html> <head> <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<%@ page 
	import = "java.sql.*"
%>
<title>JSP Example </title></head><body><table>
<%	
	Class.forName("oracle.jdbc.driver.OracleDriver");
	Connection dbconn = DriverManager.getConnection( "jdbc:oracle:thin:@devweb2013.cis.strath.ac.uk:1521:XE","emb11137","strathclyde1");
	Statement sql = dbconn.createStatement();
	ResultSet results = sql.executeQuery("SELECT ename FROM emp where empno >= 7700");
	while(results.next())
		{		
		out.println("<tr><td>"); 
		out.println(results.getString(1));
		out.println("</td></tr>"); 
		}					
%>
</table></body></html>

