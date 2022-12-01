using System;
using System.Windows.Forms;
using System.Xml;

namespace SQLConfigurator
{
    /// <summary>
    ///  uses  Visual Studio ADO.NET Add Data Connection dialogs
    ///  http://code.msdn.microsoft.com/Connection/Release/ProjectReleases.aspx?ReleaseId=3863
    ///  
    ///  Show how to use the dialogs to access different databases and configure connection strings
    /// 
    /// </summary>
    
    public partial class Form1 : Form
    {
        static private XmlDocument config = new XmlDocument();

        string connectstring;
        string serverType;
        string connectionType;
        string logsPath;                
        bool enableLogToFile;        
        bool fromMSI;
        const string filename = "\\config.xml";

        public Form1(bool frommsi)
        {
            fromMSI = frommsi;
            InitializeComponent();            
            config.Load(Environment.CurrentDirectory + filename );
        }

        private void connectionStringButton_Click(object sender, EventArgs e)
        {
            DataConnectionDialog dcd = new DataConnectionDialog();                      
                      
            DataConnectionConfiguration dcs = new DataConnectionConfiguration(connectstring, serverType, connectionType);
            
            dcs.LoadConfiguration(dcd);                        

            // coudl go wrong if bad connectionstring
            try
            {
                dcd.ConnectionString = connectstring;
            }
            catch (Exception) { }

            if (DataConnectionDialog.Show(dcd) == DialogResult.OK)
            {               
                connectstring = dcd.ConnectionString;

                if (comboDbType.Text == "SQLSERVER" || comboDbType.Text == "ORACLE")
                {
                    ChekDatabaseTypeAgainstConnectionString();
                }

                serverType = comboDbType.Text;

                textBoxConnString.Text = connectstring;

                SetConfigValue("connection_string", connectstring);
                SetConfigValue("database_type", serverType);

                // Save info
                saveConfigFile();                
            }

            //dcs.SaveConfiguration(dcd);
        }

        private void ChekDatabaseTypeAgainstConnectionString()
        {
            if (connectstring.ToUpper().IndexOf("PROVIDER", 0) >= 0)
            {
                if (connectstring.ToUpper().IndexOf("MSDAORA", 0) > 0 || connectstring.ToUpper().IndexOf("ORAOLEDB.ORACLE", 0) > 0)
                {
                    if (comboDbType.Text == "SQLSERVER")
                    {
                        MessageBox.Show("Database Type chosen is 'SQLSERVER' but the connection stribng indicates 'ORACLE'", " SQLConfigurator");
                    }
                    comboDbType.Text = "ORACLE";
                }
                else
                {
                    comboDbType.Text = "SQLSERVER";
                }
            }
            else
            {
                comboDbType.Text = "SQLSERVER";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Get version
            toolTipPort.SetToolTip(comboDbType, "Type of database server. Allowed values: SQLSERVER, POSTGRESQL, ORACLE or OTHER");
            toolTipPort.SetToolTip(comboConnectionType, "Type of database connection. Allowed values: OLE DB, ODBC, NPGSQL");
            toolTipPort.SetToolTip(connectionStringButton, "Click to configure and test the connection string to be used");
            toolTipPort.SetToolTip(textBoxLogsPath, "Path to all log files");
            connectstring = GetConfigValue("connection_string");
            serverType = GetConfigValue("database_type");
            connectionType = GetConfigValue("connection_type");
            logsPath = GetConfigValue("logs_path");
            enableLogToFile = Convert.ToBoolean(GetConfigValue("log_file"));                     
            checkBoxEnableLogTofile.Checked = enableLogToFile;
            textBoxLogsPath.Text = logsPath;
            comboDbType.Text = serverType;
            comboConnectionType.Text = connectionType;
            textBoxConnString.Text = connectstring;

            this.BringToFront();
        }
        
        string GetConfigValue(string param)
        {
            try
            {
                XmlNodeList xmlNodes = config.GetElementsByTagName(param);
                if (xmlNodes.Count == 0)
                {

                    MessageBox.Show("Configuration parameter '" + param + "' does not exist. Default value will be used instead.", " SQLConfigurator");
                    
                }
                else
                {
                    return xmlNodes[0].InnerText;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Could not load configuration parameter '" + param + "'. " + ex.Message);
            }
            return null;
        }

        void SetConfigValue(string param, string value)
        {
            try
            {
                XmlNodeList xmlNodes = config.GetElementsByTagName(param);
                if (xmlNodes.Count == 0)
                {
                    MessageBox.Show("Configuration parameter '" + param + "' does not exist!!!", " SQLConfigurator");
                }
                else
                {
                    xmlNodes[0].InnerText = value;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Could not set configuration parameter '" + param + "' to '" + value +  " '" + ex.Message);
            }            
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void acceptButton_Click(object sender, EventArgs e)
        {            
            enableLogToFile = checkBoxEnableLogTofile.Checked;            
                        
            // Save info
            SetConfigValue("connection_string", connectstring);
            SetConfigValue("database_type", serverType);
            SetConfigValue("connection_type", connectionType);            
            SetConfigValue("logs_path", logsPath);
            SetConfigValue("log_file", Convert.ToString(enableLogToFile));            
            saveConfigFile();                       
                       
            Application.Exit();
        }
            
        private void saveConfigFile(){

            try
            {                
                config.Save(Environment.CurrentDirectory + filename);
            }
            catch(System.Exception ex)
            {            
                MessageBox.Show("Failed to save configuration. " + ex.Message.ToString(), " SQLConfigurator");
            }
        }
                                
        private bool IsTextValidated(string strTextEntry)
        {
            System.Text.RegularExpressions.Regex objNotWholePattern = new System.Text.RegularExpressions.Regex("[^0-9]");
            return !objNotWholePattern.IsMatch(strTextEntry)
                 && (strTextEntry != "");
        }

        private void VersionsListButton_Click(object sender, EventArgs e)
        {
            VersionsListDialog vld = new VersionsListDialog();
            vld.ShowDialog();
        }               

        public bool IsUserAdministrator()
        {            
            bool isAdmin;
            try
            {   //get the currently logged in user
                System.Security.Principal.WindowsIdentity user = System.Security.Principal.WindowsIdentity.GetCurrent();
                System.Security.Principal.WindowsPrincipal principal = new System.Security.Principal.WindowsPrincipal(user);
                isAdmin = principal.IsInRole(System.Security.Principal.WindowsBuiltInRole.Administrator);
            }
            catch (UnauthorizedAccessException )
            {
                isAdmin = false;
            }
            catch (Exception )
            {
                isAdmin = false;
            }
            return isAdmin;
        }

        private void comboDbType_SelectedIndexChanged(object sender, EventArgs e)
        {
            serverType = comboDbType.Text;
            ResolveDBButtoms();
        }

        private void comboConnectionType_SelectedIndexChanged(object sender, EventArgs e)
        {
            connectionType = comboConnectionType.Text;
            ResolveDBButtoms();             
        }


        private void ResolveDBButtoms() {

            if (comboConnectionType.Text == "OLE DB")
            {
                if (comboDbType.Text == "POSTGRESQL" )
                {
                    connectionStringButton.Enabled = false;
                    textBoxConnString.ReadOnly = false;

                    if (comboDbType.Text == "POSTGRESQL")
                    {
                        textBoxConnString.Text = "Server=127.0.0.1;Port=5432;User Id=postgres;Password=postgres;Database=DB";
                    }
                }
                else if (comboDbType.Text == "SQLSERVER")
                {           
                    connectionStringButton.Enabled = true;
                    textBoxConnString.ReadOnly = true;
                    textBoxConnString.Text = "Provider=SQLOLEDB;Data Source=(local);Initial Catalog=DB;Integrated Security=SSPI;Connect Timeout=20";
                }
                else if (comboDbType.Text == "ORACLE")
                {
                    connectionStringButton.Enabled = true;
                    textBoxConnString.ReadOnly = true;
                    textBoxConnString.Text = "Provider=OraOLEDB.Oracle;Data Source=orcl;User Id=sys;Password=sa;OLEDB.NET=True;";
                }
                else{
                    MessageBox.Show("OTHER database type only supported with ODBC connections", " SQLConfigurator");
                    comboConnectionType.Text = "ODBC";
                }                
            }
            else if(comboConnectionType.Text == "ODBC")
            {
                connectionStringButton.Enabled = true;
                textBoxConnString.ReadOnly = false;    

                if (comboDbType.Text == "SQLSERVER")
                {
                    textBoxConnString.Text = "Driver={SQL Server};Server=(local);Trusted_Connection=Yes;Database=DB;";
                }
                else if (comboDbType.Text == "ORACLE")
                {
                    textBoxConnString.Text = "Driver={Microsoft ODBC for Oracle};Server=ORCL;Persist Security Info=False;Trusted_Connection=Yes";
                }
                else if (comboDbType.Text == "POSTGRESQL")
                {
                    textBoxConnString.Text = "Server=127.0.0.1;Port=5432;User Id=postgres;Password=postgres;Database=DB";
                }
                else {
                    textBoxConnString.Text = "Dsn=DB;uid=sa;pwd=sa";
                }
            }
            else if (comboConnectionType.Text == "NPGSQL"){
                connectionStringButton.Enabled = false;
                textBoxConnString.ReadOnly = false;

                if (comboDbType.Text != "POSTGRESQL")
                {
                    MessageBox.Show("NPGSQL only supported for PosgreSQL databases", " SQLConfigurator");   
                    comboDbType.Text = "POSTGRESQL";
                }
                textBoxConnString.Text = "Server=127.0.0.1;Port=5432;User Id=postgres;Password=postgres;Database=DB";
            }

            connectstring = textBoxConnString.Text;
        }              

        private void buttonLogsPath_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            DialogResult result = folderBrowserDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                logsPath = folderBrowserDialog1.SelectedPath;
                textBoxLogsPath.Text = logsPath;
            }
        }
    }    
}
