namespace xmlSchemaValidator
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
            this.bValidate = new System.Windows.Forms.Button();
            this.textXml = new System.Windows.Forms.TextBox();
            this.textXsd = new System.Windows.Forms.TextBox();
            this.bXsd = new System.Windows.Forms.Button();
            this.bXml = new System.Windows.Forms.Button();
            this.textNameSpace = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dgwInformation = new System.Windows.Forms.DataGridView();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openXMLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openXSDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.validateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.dgwInformation)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // bValidate
            // 
            this.bValidate.Location = new System.Drawing.Point(7, 225);
            this.bValidate.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bValidate.Name = "bValidate";
            this.bValidate.Size = new System.Drawing.Size(88, 27);
            this.bValidate.TabIndex = 0;
            this.bValidate.Text = "Validate";
            this.bValidate.UseVisualStyleBackColor = true;
            this.bValidate.Click += new System.EventHandler(this.bValidate_Click);
            // 
            // textXml
            // 
            this.textXml.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textXml.Location = new System.Drawing.Point(7, 70);
            this.textXml.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.textXml.Name = "textXml";
            this.textXml.Size = new System.Drawing.Size(473, 23);
            this.textXml.TabIndex = 2;
            // 
            // textXsd
            // 
            this.textXsd.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textXsd.Location = new System.Drawing.Point(7, 134);
            this.textXsd.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.textXsd.Name = "textXsd";
            this.textXsd.Size = new System.Drawing.Size(473, 23);
            this.textXsd.TabIndex = 3;
            // 
            // bXsd
            // 
            this.bXsd.Location = new System.Drawing.Point(7, 100);
            this.bXsd.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bXsd.Name = "bXsd";
            this.bXsd.Size = new System.Drawing.Size(88, 27);
            this.bXsd.TabIndex = 4;
            this.bXsd.Text = "XSD...";
            this.bXsd.UseVisualStyleBackColor = true;
            this.bXsd.Click += new System.EventHandler(this.bXsd_Click);
            // 
            // bXml
            // 
            this.bXml.Location = new System.Drawing.Point(7, 37);
            this.bXml.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.bXml.Name = "bXml";
            this.bXml.Size = new System.Drawing.Size(88, 27);
            this.bXml.TabIndex = 5;
            this.bXml.Text = "XML...";
            this.bXml.UseVisualStyleBackColor = true;
            this.bXml.Click += new System.EventHandler(this.bXml_Click);
            // 
            // textNameSpace
            // 
            this.textNameSpace.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textNameSpace.Location = new System.Drawing.Point(7, 183);
            this.textNameSpace.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.textNameSpace.Name = "textNameSpace";
            this.textNameSpace.Size = new System.Drawing.Size(473, 23);
            this.textNameSpace.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 162);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(102, 15);
            this.label1.TabIndex = 7;
            this.label1.Text = "Target namespace";
            // 
            // dgwInformation
            // 
            this.dgwInformation.AllowUserToAddRows = false;
            this.dgwInformation.AllowUserToDeleteRows = false;
            this.dgwInformation.AllowUserToResizeRows = false;
            this.dgwInformation.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgwInformation.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;
            this.dgwInformation.BackgroundColor = System.Drawing.SystemColors.ControlLightLight;
            this.dgwInformation.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgwInformation.EnableHeadersVisualStyles = false;
            this.dgwInformation.Location = new System.Drawing.Point(7, 273);
            this.dgwInformation.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.dgwInformation.Name = "dgwInformation";
            this.dgwInformation.ReadOnly = true;
            this.dgwInformation.RowHeadersVisible = false;
            this.dgwInformation.RowTemplate.DefaultCellStyle.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgwInformation.RowTemplate.Height = 25;
            this.dgwInformation.RowTemplate.ReadOnly = true;
            this.dgwInformation.RowTemplate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.dgwInformation.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dgwInformation.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgwInformation.Size = new System.Drawing.Size(474, 355);
            this.dgwInformation.TabIndex = 8;
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(0);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(0);
            this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.menuStrip1.Size = new System.Drawing.Size(495, 24);
            this.menuStrip1.TabIndex = 51;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openXMLToolStripMenuItem,
            this.openXSDToolStripMenuItem,
            this.validateToolStripMenuItem,
            this.saveSettingsToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openXMLToolStripMenuItem
            // 
            this.openXMLToolStripMenuItem.Name = "openXMLToolStripMenuItem";
            this.openXMLToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.openXMLToolStripMenuItem.Text = "Open XML...";
            this.openXMLToolStripMenuItem.Click += new System.EventHandler(this.openXMLToolStripMenuItem_Click);
            // 
            // openXSDToolStripMenuItem
            // 
            this.openXSDToolStripMenuItem.Name = "openXSDToolStripMenuItem";
            this.openXSDToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.openXSDToolStripMenuItem.Text = "Open XSD...";
            this.openXSDToolStripMenuItem.Click += new System.EventHandler(this.openXSDToolStripMenuItem_Click);
            // 
            // validateToolStripMenuItem
            // 
            this.validateToolStripMenuItem.Name = "validateToolStripMenuItem";
            this.validateToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.validateToolStripMenuItem.Text = "Validate";
            this.validateToolStripMenuItem.Click += new System.EventHandler(this.validateToolStripMenuItem_Click);
            // 
            // saveSettingsToolStripMenuItem
            // 
            this.saveSettingsToolStripMenuItem.Name = "saveSettingsToolStripMenuItem";
            this.saveSettingsToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.saveSettingsToolStripMenuItem.Text = "Exit";
            this.saveSettingsToolStripMenuItem.Click += new System.EventHandler(this.saveSettingsToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(495, 643);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.dgwInformation);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textNameSpace);
            this.Controls.Add(this.bXml);
            this.Controls.Add(this.bXsd);
            this.Controls.Add(this.textXsd);
            this.Controls.Add(this.textXml);
            this.Controls.Add(this.bValidate);
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "Form1";
            this.Text = "XML Schema Validator";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgwInformation)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bValidate;
        private System.Windows.Forms.TextBox textXml;
        private System.Windows.Forms.TextBox textXsd;
        private System.Windows.Forms.Button bXsd;
        private System.Windows.Forms.Button bXml;
        private System.Windows.Forms.TextBox textNameSpace;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView dgwInformation;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openXMLToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openXSDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem validateToolStripMenuItem;
    }
}

