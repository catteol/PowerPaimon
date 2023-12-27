namespace PowerPaimon
{
    partial class AboutForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AboutForm));
            LabelTitle = new Label();
            LabelDescription = new Label();
            LinkLabelSource = new LinkLabel();
            LinkLabelIssues = new LinkLabel();
            pictureBox1 = new PictureBox();
            LabelVersion = new Label();
            LabelCredit = new Label();
            LabelDescription2 = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            SuspendLayout();
            // 
            // LabelTitle
            // 
            LabelTitle.Font = new Font("Segoe UI", 15.75F, FontStyle.Bold, GraphicsUnit.Point, 0);
            LabelTitle.Location = new Point(12, 152);
            LabelTitle.Name = "LabelTitle";
            LabelTitle.Size = new Size(320, 36);
            LabelTitle.TabIndex = 0;
            LabelTitle.Text = "PowerPaimon";
            LabelTitle.TextAlign = ContentAlignment.TopCenter;
            // 
            // LabelDescription
            // 
            LabelDescription.Location = new Point(12, 228);
            LabelDescription.Name = "LabelDescription";
            LabelDescription.Size = new Size(320, 18);
            LabelDescription.TabIndex = 1;
            LabelDescription.Text = "This program is free and open source.";
            LabelDescription.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // LinkLabelSource
            // 
            LinkLabelSource.LinkArea = new LinkArea(0, 40);
            LinkLabelSource.Location = new Point(12, 245);
            LinkLabelSource.Name = "LinkLabelSource";
            LinkLabelSource.Size = new Size(320, 20);
            LinkLabelSource.TabIndex = 2;
            LinkLabelSource.TabStop = true;
            LinkLabelSource.Text = "https://github.com/rexent-gx/PowerPaimon";
            LinkLabelSource.TextAlign = ContentAlignment.MiddleCenter;
            LinkLabelSource.LinkClicked += LinkLabelSource_LinkClicked;
            // 
            // LinkLabelIssues
            // 
            LinkLabelIssues.LinkArea = new LinkArea(0, 47);
            LinkLabelIssues.Location = new Point(12, 305);
            LinkLabelIssues.Name = "LinkLabelIssues";
            LinkLabelIssues.Size = new Size(320, 17);
            LinkLabelIssues.TabIndex = 3;
            LinkLabelIssues.TabStop = true;
            LinkLabelIssues.Text = "https://github.com/rexent-gx/PowerPaimon/issues";
            LinkLabelIssues.TextAlign = ContentAlignment.MiddleCenter;
            LinkLabelIssues.LinkClicked += LinkLabelIssues_LinkClicked;
            // 
            // pictureBox1
            // 
            pictureBox1.Image = (Image)resources.GetObject("pictureBox1.Image");
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(320, 137);
            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
            pictureBox1.TabIndex = 4;
            pictureBox1.TabStop = false;
            // 
            // LabelVersion
            // 
            LabelVersion.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 0);
            LabelVersion.Location = new Point(12, 176);
            LabelVersion.Name = "LabelVersion";
            LabelVersion.Size = new Size(320, 24);
            LabelVersion.TabIndex = 5;
            LabelVersion.Text = "v3.0.0";
            LabelVersion.TextAlign = ContentAlignment.TopCenter;
            // 
            // LabelCredit
            // 
            LabelCredit.Font = new Font("Segoe UI", 9F, FontStyle.Regular, GraphicsUnit.Point, 0);
            LabelCredit.Location = new Point(12, 200);
            LabelCredit.Name = "LabelCredit";
            LabelCredit.Size = new Size(320, 16);
            LabelCredit.TabIndex = 6;
            LabelCredit.Text = "© 2023 rexent_gx";
            LabelCredit.TextAlign = ContentAlignment.TopCenter;
            // 
            // LabelDescription2
            // 
            LabelDescription2.Location = new Point(12, 275);
            LabelDescription2.Name = "LabelDescription2";
            LabelDescription2.Size = new Size(320, 31);
            LabelDescription2.TabIndex = 7;
            LabelDescription2.Text = "If you encounter any problems or have a suggestion\r\nGo ahead and submit an issue at";
            LabelDescription2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // AboutForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(344, 338);
            Controls.Add(LabelDescription2);
            Controls.Add(LabelCredit);
            Controls.Add(LabelVersion);
            Controls.Add(pictureBox1);
            Controls.Add(LinkLabelIssues);
            Controls.Add(LinkLabelSource);
            Controls.Add(LabelDescription);
            Controls.Add(LabelTitle);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "AboutForm";
            StartPosition = FormStartPosition.CenterParent;
            Text = "About";
            Load += AboutForm_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Label LabelTitle;
        private Label LabelDescription;
        private LinkLabel LinkLabelSource;
        private LinkLabel LinkLabelIssues;
        private PictureBox pictureBox1;
        private Label LabelVersion;
        private Label LabelCredit;
        private Label LabelDescription2;
    }
}