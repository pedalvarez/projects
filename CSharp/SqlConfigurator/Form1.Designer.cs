namespace SQLConfigurator
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.toolTipPort = new System.Windows.Forms.ToolTip(this.components);
            this.acceptButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.label6 = new System.Windows.Forms.Label();            
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.VersionsListButton = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.textBoxLogsPath = new System.Windows.Forms.TextBox();
            this.checkBoxEnableLogTofile = new System.Windows.Forms.CheckBox();
            this.label8 = new System.Windows.Forms.Label();
            this.buttonLogsPath = new System.Windows.Forms.Button();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboConnectionType = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.comboDbType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxConnString = new System.Windows.Forms.TextBox();
            this.connectionStringButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // acceptButton
            // 
            this.acceptButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.acceptButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.acceptButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.acceptButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.acceptButton.Location = new System.Drawing.Point(31, 265);
            this.acceptButton.Margin = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.acceptButton.MinimumSize = new System.Drawing.Size(75, 23);
            this.acceptButton.Name = "acceptButton";
            this.acceptButton.Size = new System.Drawing.Size(89, 23);
            this.acceptButton.TabIndex = 5;
            this.acceptButton.Text = "&OK";
            this.acceptButton.Click += new System.EventHandler(this.acceptButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.AutoSize = true;
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cancelButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.cancelButton.Location = new System.Drawing.Point(187, 265);
            this.cancelButton.Margin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.cancelButton.MinimumSize = new System.Drawing.Size(75, 23);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(93, 23);
            this.cancelButton.TabIndex = 6;
            this.cancelButton.Text = "&Cancel";
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.label6);            
            this.tabPage4.Controls.Add(this.groupBox3);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(295, 235);
            this.tabPage4.TabIndex = 4;
            this.tabPage4.Text = "About";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(80, 63);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "Copyright © 2020";
            
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.VersionsListButton);
            this.groupBox3.Location = new System.Drawing.Point(3, 99);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(287, 49);
            this.groupBox3.TabIndex = 14;
            this.groupBox3.TabStop = false;
            // 
            // VersionsListButton
            // 
            this.VersionsListButton.Location = new System.Drawing.Point(25, 19);
            this.VersionsListButton.Name = "VersionsListButton";
            this.VersionsListButton.Size = new System.Drawing.Size(89, 23);
            this.VersionsListButton.TabIndex = 0;
            this.VersionsListButton.Text = "&Versions list...";
            this.VersionsListButton.UseVisualStyleBackColor = true;
            this.VersionsListButton.Click += new System.EventHandler(this.VersionsListButton_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.textBoxLogsPath);
            this.tabPage2.Controls.Add(this.checkBoxEnableLogTofile);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Controls.Add(this.buttonLogsPath);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(295, 235);
            this.tabPage2.TabIndex = 2;
            this.tabPage2.Text = "Parameters";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // textBoxLogsPath
            // 
            this.textBoxLogsPath.Location = new System.Drawing.Point(9, 55);
            this.textBoxLogsPath.Name = "textBoxLogsPath";
            this.textBoxLogsPath.ReadOnly = true;
            this.textBoxLogsPath.Size = new System.Drawing.Size(206, 20);
            this.textBoxLogsPath.TabIndex = 12;
            // 
            // checkBoxEnableLogTofile
            // 
            this.checkBoxEnableLogTofile.AutoSize = true;
            this.checkBoxEnableLogTofile.Location = new System.Drawing.Point(9, 19);
            this.checkBoxEnableLogTofile.Name = "checkBoxEnableLogTofile";
            this.checkBoxEnableLogTofile.Size = new System.Drawing.Size(124, 17);
            this.checkBoxEnableLogTofile.TabIndex = 15;
            this.checkBoxEnableLogTofile.Text = "Enable logging to file";
            this.checkBoxEnableLogTofile.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 39);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(58, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Logs Path:";
            // 
            // buttonLogsPath
            // 
            this.buttonLogsPath.Location = new System.Drawing.Point(221, 52);
            this.buttonLogsPath.Name = "buttonLogsPath";
            this.buttonLogsPath.Size = new System.Drawing.Size(47, 23);
            this.buttonLogsPath.TabIndex = 13;
            this.buttonLogsPath.Text = "...";
            this.buttonLogsPath.UseVisualStyleBackColor = true;
            this.buttonLogsPath.Click += new System.EventHandler(this.buttonLogsPath_Click);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(295, 235);
            this.tabPage1.TabIndex = 1;
            this.tabPage1.Text = "Database";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboConnectionType);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.comboDbType);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textBoxConnString);
            this.groupBox1.Controls.Add(this.connectionStringButton);
            this.groupBox1.Location = new System.Drawing.Point(3, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(289, 226);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            // 
            // comboConnectionType
            // 
            this.comboConnectionType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboConnectionType.Items.AddRange(new object[] {
            "OLE DB",
            "ODBC",
            "NPGSQL"});
            this.comboConnectionType.Location = new System.Drawing.Point(23, 25);
            this.comboConnectionType.Name = "comboConnectionType";
            this.comboConnectionType.Size = new System.Drawing.Size(105, 21);
            this.comboConnectionType.TabIndex = 16;
            this.comboConnectionType.SelectedIndexChanged += new System.EventHandler(this.comboConnectionType_SelectedIndexChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(23, 10);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(87, 13);
            this.label7.TabIndex = 17;
            this.label7.Text = "Connection type:";
            // 
            // comboDbType
            // 
            this.comboDbType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboDbType.Items.AddRange(new object[] {
            "SQLSERVER",
            "ORACLE",
            "POSTGRESQL",
            "OTHER"});
            this.comboDbType.Location = new System.Drawing.Point(178, 25);
            this.comboDbType.Name = "comboDbType";
            this.comboDbType.Size = new System.Drawing.Size(105, 21);
            this.comboDbType.TabIndex = 9;
            this.comboDbType.SelectedIndexChanged += new System.EventHandler(this.comboDbType_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(178, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Database type:";
            // 
            // textBoxConnString
            // 
            this.textBoxConnString.Location = new System.Drawing.Point(23, 52);
            this.textBoxConnString.Multiline = true;
            this.textBoxConnString.Name = "textBoxConnString";
            this.textBoxConnString.Size = new System.Drawing.Size(260, 58);
            this.textBoxConnString.TabIndex = 7;
            // 
            // connectionStringButton
            // 
            this.connectionStringButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.connectionStringButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.connectionStringButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.connectionStringButton.Location = new System.Drawing.Point(23, 116);
            this.connectionStringButton.Margin = new System.Windows.Forms.Padding(3, 3, 6, 3);
            this.connectionStringButton.MinimumSize = new System.Drawing.Size(101, 23);
            this.connectionStringButton.Name = "connectionStringButton";
            this.connectionStringButton.Size = new System.Drawing.Size(101, 23);
            this.connectionStringButton.TabIndex = 8;
            this.connectionStringButton.Text = "Connection &String...";
            this.connectionStringButton.Click += new System.EventHandler(this.connectionStringButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(-1, 1);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(303, 261);
            this.tabControl1.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(302, 297);
            this.Controls.Add(this.acceptButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = " SQLConfigurator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolTip toolTipPort;
        private System.Windows.Forms.Button acceptButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Label label6;        
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button VersionsListButton;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox textBoxLogsPath;
        private System.Windows.Forms.CheckBox checkBoxEnableLogTofile;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button buttonLogsPath;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboConnectionType;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboDbType;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxConnString;
        private System.Windows.Forms.Button connectionStringButton;
        private System.Windows.Forms.TabControl tabControl1;
    }
}

