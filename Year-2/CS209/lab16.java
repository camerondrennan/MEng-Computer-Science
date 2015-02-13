import java.net.URL;
import java.sql.*;


public class lab16
{
	static final int iMaxNumRows = 100;

	Connection con;
	Driver driver = null;
	CallableStatement cstmt;
	ResultSet result;
	PreparedStatement pstmt;
	static String sUserPwd = new String("");
	static String sDatabase = new String("");

	// EMP table columns
	static int aiEMEmpNo[] = new int[iMaxNumRows];
	static String asEMEName[] = new String[iMaxNumRows];
	static int aiEMDeptNo[] = new int[iMaxNumRows];
	static int afEMSal[] = new int[iMaxNumRows];

	// counter for number of rows in each table
	int iNumDept = 0;
	int iNumSalGrade = 0;
	int iNumEmp = 0;

	private void connect(String sTypeJDBC) throws Exception {
        
		String url;
		try {
      		// Create a new JDBC connection.  This is our session.
 			DriverManager.registerDriver (new oracle.jdbc.driver.OracleDriver ());

			url = "jdbc:oracle:thin:" + sUserPwd +"@devweb2013.cis.strath.ac.uk:1521:XE";

			con = DriverManager.getConnection(url);
			con.setAutoCommit(false); 
		} catch(Exception e) {
			System.err.println("System Exception in connect");
			e.printStackTrace();
	      	throw e;
    	}
	}                                    

  	public void closeConnection() throws Exception
  	{
    	try {
			con.close();
    	} catch (Exception e) {
			System.err.println("System Exception in closeConnection");
			e.printStackTrace();
		}
	}        



	public String listEmp () throws Exception{
		String retVal = new String("NUMBER\tNAME\tDEPTNO\tSALARY\n");

		try {
			pstmt = con.prepareStatement(
				"SELECT EMPNO, ENAME,  SAL, DEPTNO FROM EMP WHERE EMPNO < 7700");
			result = pstmt.executeQuery();

			int i = 0;
			while (result.next()) {
				aiEMEmpNo[i] = result.getInt("EMPNO");
				asEMEName[i] = result.getString("ENAME");
				afEMSal[i] = result.getInt("SAL");
				aiEMDeptNo[i] = result.getInt("DEPTNO");
				retVal = retVal + aiEMEmpNo[i] + "\t" +
					asEMEName[i] + "\t" + aiEMDeptNo[i] + "\t" +
					afEMSal[i] + "\n"; 
				i++;
			}
			iNumEmp = i;
	    	pstmt.close();
		} 
		catch (Exception e) {
			System.err.println("System Exception in listEmp");
			e.printStackTrace();
			throw e;
		}
		return(retVal);
	}




	public static String runQuery (String sTypeJDBC, String sTable)
	{
		String retVal = new String();
		lab16 myQuery = new lab16();
		try {
			myQuery.connect(sTypeJDBC);
			retVal = myQuery.listEmp();
			myQuery.closeConnection();
		} 
		catch (Exception e) {
			System.err.println("System Exception in runQuery");
			e.printStackTrace();
			retVal = "System Exception in runQuery";
		}
		return(retVal);
	}


	public static void main (String argv[])
	{
		String sTable = new String();
		if ( argv.length == 1 ) {
			sUserPwd = argv[0];
			//sDatabase = argv[1];
			System.out.println(runQuery("client", sTable));
		}
		else {
			System.out.println("Usage: java lab16 <username>/<password>"); 
		}
	}
}
