using System.Diagnostics;
using System.Reflection;
using PowerPaimon.Properties;

namespace PowerPaimon
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void AboutForm_Load(object sender, EventArgs e)
        {
            UpdateLanguage();
            System.Diagnostics.Debug.WriteLine("adada");
        }

        private void UpdateLanguage()
        {
            LabelVersion.Text = $"v{Assembly.GetExecutingAssembly().GetName().Version?.ToString(3)}";
            LabelDescription.Text = Resources.AboutDesc1;
            LabelDescription2.Text = Resources.AboutDesc2;
        }

        private void LinkLabelSource_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/rexent-gx/PowerPaimon");
        }

        private void LinkLabelIssues_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenLink("https://github.com/rexent-gx/PowerPaimon/issues");
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

    }
}
