using System;
using System.Windows.Forms;

namespace SQLConfigurator
{
    public partial class VersionsListDialog : Form
    {
        public VersionsListDialog()
        {
            InitializeComponent();
        }                

        private void acceptButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void VersionsListDialog_Load(object sender, EventArgs e)
        {
            string applicationPath = System.IO.Directory.GetCurrentDirectory();

            String[] exeFileNames = System.IO.Directory.GetFiles(applicationPath, "*.exe");

            AddFilesToList(exeFileNames);

            String[] dllFileNames = System.IO.Directory.GetFiles(applicationPath, "*.dll");

            AddFilesToList(dllFileNames);

            try
            {
                String[] extlogicFileNames = System.IO.Directory.GetFiles( "\\ExternalLogic", "*.dll");

                AddFilesToList(extlogicFileNames);
            }
            catch (System.Exception)
            { }

        }

        private void AddFilesToList(String[] files)
        {
            for( int i = 0; i < files.Length; i++)
            {
                System.Reflection.Assembly asm = null;
                try
                {
                    asm = System.Reflection.Assembly.LoadFrom(files[i]);
                }
                catch (Exception)
                {                    
                }
                if (asm != null)
                {
                    ListViewItem lvi = listView1.Items.Add( System.IO.Path.GetFileName(files[i]),files[i]);
                    lvi.Tag = files[i];
                    lvi.SubItems.Add(asm.GetName().Name);
                    lvi.SubItems.Add(asm.GetName().Version.ToString());
                }
                else 
                {
                    ListViewItem lvi = listView1.Items.Add(System.IO.Path.GetFileName(files[i]), files[i]);
                    lvi.Tag = files[i];
                }
            }                                      
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {            
            ListViewItem lvi = listView1.GetItemAt(e.X, e.Y);
         
            if (lvi != null)
            {
                ShowReferencedAssemblies(lvi.Tag.ToString());                
            }
        }

        private bool ShowReferencedAssemblies(String file)
        {
            try
            {
                System.Reflection.Assembly asm = System.Reflection.Assembly.LoadFrom(file);

                System.Reflection.AssemblyName[] list = asm.GetReferencedAssemblies();

                String msg="";
                if (list.Length > 0)
                {                    
                    for (int i = 0; i < list.Length; i++)
                    {                        
                        msg += list[i].Name + ", " + list[i].Version.ToString();
                        msg += "\n";                      
                    }

                    MessageBox.Show(msg, "References for " + asm.GetName().Name);
                }
            }
            catch (Exception)
            {                
                return false;
            }
            return true;
        }

        private void listView1_KeyPress(object sender, KeyPressEventArgs e)
        {            
            ListViewItem lvi = listView1.SelectedItems[0];         
            if (lvi != null)
            {
                ShowReferencedAssemblies(lvi.Tag.ToString());
            }
        }        
    }
}