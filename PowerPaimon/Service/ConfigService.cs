﻿using Newtonsoft.Json;
using PowerPaimon.Model;

namespace PowerPaimon.Service
{
    public class ConfigService
    {
        private const string ConfigName = "fps_config.json";

        public Config Config { get; private set; } = new();

        public ConfigService()
        {
            Load();
            Sanitize();
        }

        private void Load()
        {
            if (!File.Exists(ConfigName))
                return;

            try
            {
                var json = File.ReadAllText(ConfigName);
                Config = JsonConvert.DeserializeObject<Config>(json) ?? throw new Exception("Failed to load config.");
            }
            catch (Exception)
            {
                MessageBox.Show(
                    @$"Failed to load config file{Environment.NewLine}Your config file doesn't appear to be in the correct format. It will be reset to default.",
                    @"Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                Config = new();
            }
        }

        private void Sanitize()
        {
            Config.FPSTarget = Math.Clamp(Config.FPSTarget, 1, 420);
            Config.Priority = Math.Clamp(Config.Priority, 0, 5);
            Config.CustomResX = Math.Clamp(Config.CustomResX, 200, 7680);
            Config.CustomResY = Math.Clamp(Config.CustomResY, 200, 4320);
            Config.MonitorNum = Math.Clamp(Config.MonitorNum, 1, 100);
        }

        public void Save()
        {
            var json = JsonConvert.SerializeObject(Config, Formatting.Indented);
            File.WriteAllText(ConfigName, json);
        }

    }
}
