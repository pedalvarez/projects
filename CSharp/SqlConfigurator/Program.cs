using System;
using System.Windows.Forms;
using System.Reflection;
using System.IO;

namespace SQLConfigurator
{
    /// <summary>
    ///  uses  Visual Studio ADO.NET Add Data Connection dialogs
    ///  http://code.msdn.microsoft.com/Connection/Release/ProjectReleases.aspx?ReleaseId=3863
    ///  
    ///  Show how to use the dialogs to access different databases and configure connection strings
    /// 
    /// </summary>

    static class Program
    {
        static string applicationPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location); 
        [STAThread]
        static void Main(string[] args)
        {
            Environment.CurrentDirectory = applicationPath;

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            bool fromMSI = false;
            if (args.Length > 0)
            {
                if (args[0] == "embedded")
                {
                    fromMSI = true;
                }
            }
            Application.Run(new Form1(fromMSI));
        }
    }
}