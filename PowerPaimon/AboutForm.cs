using System.Diagnostics;
using PowerPaimon.Properties;

namespace PowerPaimon
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void UpdateLanguage()
        {
            LabelDescription.Text = Resources.AboutDesc1;
            LabelDescription2.Text = Resources.AboutDesc2;
        }

        private void LinkLabelSource_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/catteol/PowerPaimon");
        }

        private void LinkLabelIssues_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/catteol/PowerPaimon/issues");
        }

        private void OpenLink(string url)
        {
            var psi = new ProcessStartInfo
            {
                FileName = url,
                UseShellExecute = true
            };

            Process.Start(psi);
        }

        private void AboutForm_Load(object sender, EventArgs e)
        {
            UpdateLanguage();
        }
    }
}
