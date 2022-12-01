using System;
using System.Data;

namespace xmlSchemaValidator
{
    public enum LogMessageType { Info, Success, Warning, Error, Debug }

    public class Log
    {
        private DataTable _logDataTable;
        private string _tag;
        private bool _debug;
        private System.Windows.Forms.Label _logDataLabel;

        public Log()
        {
            _logDataTable = new DataTable();
            _logDataTable.Columns.Add("No", typeof(string));
            _logDataTable.Columns.Add("Type", typeof(LogMessageType));
            _logDataTable.Columns.Add("Message", typeof(string));
            _debug = false;
            _tag = "";
            _logDataLabel = null;
        }

        public void Clean()
        {
            _logDataTable.Clear();
        }

        public DataTable LogDataTable
        {
            get { return _logDataTable; }
            set { _logDataTable = value; }
        }

        public System.Windows.Forms.Label LogDataLabel
        {
            get { return _logDataLabel; }
            set { _logDataLabel = value; }
        }

        public bool Debug
        {
            set { _debug = value; }
        }

        public string Tag
        {
            set { _tag = value; }
        }

        public void LogMessage(string message, LogMessageType type)
        {
            string no = Convert.ToString(_logDataTable.Rows.Count + 1);
            if (_logDataTable.Rows.Count + 1 < 1000) no = "0" + Convert.ToString(_logDataTable.Rows.Count + 1);
            if (_logDataTable.Rows.Count + 1 < 100) no = "00" + Convert.ToString(_logDataTable.Rows.Count + 1);
            if (_logDataTable.Rows.Count + 1 < 10) no = "000" + Convert.ToString(_logDataTable.Rows.Count + 1);
            _logDataTable.Rows.Add(no, type, message);

            if (_logDataLabel != null)
                _logDataLabel.Text = message;

        }

        public void I(string message)
        {
            LogMessage(message, LogMessageType.Info);
        }

        public void D(string message)
        {
            
            if (_debug) LogMessage(_tag + ": " + message, LogMessageType.Debug);
        }

        public void W(string message)
        {
            LogMessage(_tag + ": " + message, LogMessageType.Warning);
        }

        public void S(string message)
        {
            LogMessage(message, LogMessageType.Success);
        }

        public void E(string message)
        {
            LogMessage(message, LogMessageType.Error); ;
        }
    }
}
