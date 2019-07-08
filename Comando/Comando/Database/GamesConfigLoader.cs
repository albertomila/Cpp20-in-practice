using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class GamesConfigLoader
{
    private string RELATIVE_PATH = "games/";
    private List<GameConfigDescriptorLoader> _gamesLoader = null;

    public GamesConfigLoader()
    {
        _gamesLoader = new List<GameConfigDescriptorLoader>();
        string relativeFullPath = Config.GetConfigDirectory(RELATIVE_PATH);
        string[] files = Directory.GetFiles(relativeFullPath);
        foreach (string file in files)
        {
			if (IsXmlFile(file))
			{
				_gamesLoader.Add(new GameConfigDescriptorLoader(file));
			}
        }
    }

	public bool IsXmlFile(string xml)
	{
		string ext = Path.GetExtension(xml);
		return ext == ".xml";	
	}

    public void Load()
    {
        foreach (GameConfigDescriptorLoader loader in _gamesLoader)
        {
            loader.Load();
        }

		_gamesLoader.Sort(HandleComparison);
    }

	private int HandleComparison(GameConfigDescriptorLoader value1, GameConfigDescriptorLoader value2)
	{
		int creationDate1 = value1.GetConfig().GetCreationDate();
		int creationDate2 = value2.GetConfig().GetCreationDate();

		if (creationDate1 < creationDate2)
		{
			return -1;
		}
		else if (creationDate1 > creationDate2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	public void Save()
    {
        foreach (GameConfigDescriptorLoader loader in _gamesLoader)
        {
            loader.Save();
        }
    }

	public FileOperationResult Export(string fileName, GameConfigDB gameConfigDB)
	{
        foreach (GameConfigDescriptorLoader loader in _gamesLoader)
        {
			if (loader.GetConfig() == gameConfigDB)
			{
				return loader.Export(fileName);
			}
        }

        return new FileOperationResult(false, "not found");
	}

    public GameConfigDB AddNewGameConfig(string name)
    {
        string relativeFullPath = Config.GetConfigDirectory(RELATIVE_PATH);
        relativeFullPath += "game_" + name + ".xml";
        GameConfigDescriptorLoader gameConfigDescriptorLoader = new GameConfigDescriptorLoader(relativeFullPath);
        _gamesLoader.Add(gameConfigDescriptorLoader);
        gameConfigDescriptorLoader.CreateNew(name);
        gameConfigDescriptorLoader.Save();
        gameConfigDescriptorLoader.Load();
        return gameConfigDescriptorLoader.GetConfig();
    }

    public void DeleteGameConfig(GameConfigDB gameConfigDB)
    {
        foreach (GameConfigDescriptorLoader loader in _gamesLoader)
        {
            if(loader.GetConfig() == gameConfigDB)
            {
                loader.DeleteConfig();
                _gamesLoader.Remove(loader);
                return;
            }
        }
    }

    public List<GameConfigDB> GetConfigs()
    {
        List<GameConfigDB> gameConfigs = new List<GameConfigDB>();
        foreach (GameConfigDescriptorLoader loader in _gamesLoader)
        {
            gameConfigs.Add(loader.GetConfig());
        }

        return gameConfigs;
    }
}
