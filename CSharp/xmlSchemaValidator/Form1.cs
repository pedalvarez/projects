using System;
using System.Drawing;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Schema;

namespace xmlSchemaValidator
{
    public partial class Form1 : Form
    {
        private static Color LOG_INFO_COLOR = Color.White;
        private static Color LOG_SUCCESS_COLOR = Color.LightGreen;
        private static Color LOG_DEBUG_COLOR = Color.LightBlue;
        private static Color LOG_WARNING_COLOR = Color.LightYellow;
        private static Color LOG_ERROR_COLOR = Color.LightCoral;
        private Log _log;

        public Form1()
        {          
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _log = new Log();
            dgwInformation.DataSource = _log.LogDataTable;
            dgwInformation.Columns.GetFirstColumn(DataGridViewElementStates.Visible, DataGridViewElementStates.None).Width = 40;
            dgwInformation.Columns.GetLastColumn(DataGridViewElementStates.Visible, DataGridViewElementStates.None).AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            dgwInformation.RowsAdded += new DataGridViewRowsAddedEventHandler(dgwInformation_RowsAdded);
            dgwInformation.Sorted += new EventHandler(dgwInformation_Sorted);
        }

        private void dgwInformation_Sorted(object sender, EventArgs e)
        { 
            foreach (DataGridViewRow row in dgwInformation.Rows)
            {
                row.DefaultCellStyle.BackColor = GetLogRowColor(row);
            }
        }

        private void dgwInformation_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {
            DataGridViewRow row = dgwInformation.Rows[e.RowIndex];
            row.DefaultCellStyle.BackColor = GetLogRowColor(row);
            dgwInformation.FirstDisplayedCell = row.Cells[0];
        }

        private Color GetLogRowColor(DataGridViewRow row)
        {
            Color color = Color.White;
            foreach (DataGridViewCell cell in row.Cells)
            {
                if (cell.ValueType == typeof(LogMessageType))
                {
                    switch ((LogMessageType)cell.Value)
                    {
                        case LogMessageType.Info:
                            color = LOG_INFO_COLOR;
                            break;
                        case LogMessageType.Warning:
                            color = LOG_WARNING_COLOR;
                            break;
                        case LogMessageType.Debug:
                            color = LOG_DEBUG_COLOR;
                            break;
                        case LogMessageType.Success:
                            color = LOG_SUCCESS_COLOR;
                            break;
                        case LogMessageType.Error:
                            color = LOG_ERROR_COLOR;
                            break;
                    }
                    break;
                }
            }
            return color;
        }

        private void bValidate_Click(object sender, EventArgs e)
        {
            validate();
        }

        private void validate()
        {
            _log.Clean();
            if (textXml.Text.Length == 0) {
                MessageBox.Show("XML file cannot be empty","XML Schema Validator");
                return;
            }
            if (textXsd.Text.Length == 0)
            {
                MessageBox.Show("XSD file cannot be empty","XML Schema Validator");
                return;
            }
            
            _log.I("Validating: " + textXml.Text + " against " + textXsd.Text);
            Cursor.Current = Cursors.WaitCursor;

            try
            {                
                XmlSchemaSet schemaSet = new XmlSchemaSet();                   
                schemaSet.Add(textNameSpace.Text, textXsd.Text);
                schemaSet.Compile();
                
                XmlReaderSettings settings = new XmlReaderSettings();
                settings.CloseInput = true;                
                settings.ValidationType = ValidationType.Schema;
                settings.ValidationFlags |= XmlSchemaValidationFlags.ProcessInlineSchema;
                settings.ValidationFlags |= XmlSchemaValidationFlags.ProcessSchemaLocation;
                settings.ValidationFlags |= XmlSchemaValidationFlags.ReportValidationWarnings;                
                settings.ValidationEventHandler += new ValidationEventHandler(ValidationCallBack);
                settings.Schemas.Add(schemaSet);                                                

                XmlReader r = XmlReader.Create(textXml.Text, settings);
                while ( r.Read()) ;
                r.Close();
            }
            catch (Exception ex)
            {
                _log.E(ex.Message);
            }

            Cursor.Current = Cursors.Default;

            _log.S("Done");
        }
        
        private void ValidationCallBack(object sender, ValidationEventArgs args)
        {
            if (args.Severity == XmlSeverityType.Warning)
                _log.W( args.Message );
            else
                _log.E( args.Message );
        }

        private void bXml_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "XML Files (.xml)|*.xml";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.Multiselect = false;                      
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textXml.Text = openFileDialog1.FileName;
            }
        }

        private void bXsd_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Schema Files (.xsd)|*.xsd";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.Multiselect = false;
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textXsd.Text = openFileDialog1.FileName;
            }
        }

        private void saveSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        private void openXMLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bXml_Click(sender, e);
        }

        private void openXSDToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bXsd_Click(sender, e);
        }

        private void validateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            validate();
        }        
    }
}
