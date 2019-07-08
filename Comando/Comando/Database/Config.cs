using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

public class Config
{
    private ApplicationConfigLoader _applicationConfigLoader = null;
    private GamesConfigLoader _gamesLoader = null;

    public static void AssertResource(string attribute)
    {
        Debug.Assert(attribute != null, "Attribute " + attribute + " doesn't exist");
    }

    public static string GetConfigDirectory(string file)
    {
		string configFolder = AppDomain.CurrentDomain.BaseDirectory;
		configFolder += "/Resources/config/";
        configFolder += file;
        return configFolder;
    }

    public Config()
    {
        _applicationConfigLoader = new ApplicationConfigLoader();
        _gamesLoader = new GamesConfigLoader();
    }

    public void Load()
    {
        _applicationConfigLoader.Load();
        _gamesLoader.Load();
    }

    public void Save()
	{
        _applicationConfigLoader.Save();
        _gamesLoader.Save();
    }

    public ApplicationConfig GetApplicationConfig()
    {
        return _applicationConfigLoader.GetConfig();
    }

    public List<GameConfigDB> GetGameConfigs()
    {
        return _gamesLoader.GetConfigs();
    }

    public GamesConfigLoader GetGameConfig()
    {
        return _gamesLoader;
    }
}