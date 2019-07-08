using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class GameConfigCommandDescriptor
{
	public string _command;
	public string _arguments;
}

public class GameConfigButtonDescriptor
{
	public enum Etype
	{
		  FixedArgument
		, ExposedArgument
		, MultiCommand
	}
	public Etype _type;
    public string _tittle;
    public string _command;
    public string _arguments;
	public List<GameConfigCommandDescriptor> _commandList;


	public void AddSequenceCommand(List<KeyValuePair<string, string>> commandList)
	{
		_commandList = new List<GameConfigCommandDescriptor>();
		foreach (KeyValuePair<string, string> command in commandList)
		{
			GameConfigCommandDescriptor commandDescriptor = new GameConfigCommandDescriptor();
			commandDescriptor._command = command.Key;
			commandDescriptor._arguments = command.Value;
			_commandList.Add(commandDescriptor);
		}
	}
}

public class GameConfigSectionDescriptor
{
	public string _tittle;
	public List<GameConfigButtonDescriptor> _buttons;

	public GameConfigSectionDescriptor()
	{
		_buttons = new List<GameConfigButtonDescriptor>();
	}
}

public class GameConfigDB
{
    private string _name = string.Empty;
	private int _creationDate = 0;
	private List<GameConfigSectionDescriptor> _sections;

	public GameConfigDB()
    {
        _sections = new List<GameConfigSectionDescriptor>();
    }

    public string GetName()
    {
        return _name;
    }

    public void SetName(string name)
    {
        _name = name;
    }

	public int GetCreationDate()
	{
		return _creationDate;
	}

	public void SetCreationDate(int creationDate)
	{
		_creationDate = creationDate;
	}


    public GameConfigButtonDescriptor AddNewCommand(GameConfigButtonDescriptor.Etype type, string tittle, string command, string arguments, int sectionIndex)
	{
		GameConfigButtonDescriptor newCommand = new GameConfigButtonDescriptor();
		newCommand._tittle = tittle;
		newCommand._type = type;
		newCommand._command = command;
		newCommand._arguments = arguments;

		_sections[sectionIndex]._buttons.Add(newCommand);

		return newCommand;
	}

	public GameConfigButtonDescriptor AddNewSequenceCommand(GameConfigButtonDescriptor.Etype type, string tittle, List<KeyValuePair<string, string>> commandList, int sectionIndex)
	{
		GameConfigButtonDescriptor newCommand = new GameConfigButtonDescriptor();
		newCommand._tittle = tittle;
		newCommand._type = type;
		newCommand.AddSequenceCommand(commandList);
		_sections[sectionIndex]._buttons.Add(newCommand);

		return newCommand;
	}

	public void RemoveCommand(GameConfigButtonDescriptor commandDescriptor)
	{
		foreach (GameConfigSectionDescriptor section in _sections)
		{
			foreach (GameConfigButtonDescriptor command in section._buttons)
			{
				if (command == commandDescriptor)
				{
					section._buttons.Remove(command);
					break;
				}
			}
		}
    }

    public void AddCommandAtLocation(GameConfigButtonDescriptor commandDescriptor, int sectionIndex, int commandIndex)
    {
        _sections[sectionIndex]._buttons.Insert(commandIndex, commandDescriptor);
    }

    public void AddSection(GameConfigSectionDescriptor sectionDescriptor)
    {
        _sections.Add(sectionDescriptor);
    }

	public GameConfigSectionDescriptor GetSection(int sectionIndex)
	{
		return _sections[sectionIndex];
	}

	public void RemoveSection(int sectionIndex)
	{
		_sections.RemoveAt(sectionIndex);
	}

	public GameConfigSectionDescriptor AddNewSection(string tittle, int previousSectionIndex)
	{
		GameConfigSectionDescriptor newSection = new GameConfigSectionDescriptor();
		newSection._tittle = tittle;
		newSection._buttons = new List<GameConfigButtonDescriptor>();

		if (previousSectionIndex < _sections.Count-1)
		{
			_sections.Insert(previousSectionIndex + 1, newSection);
		}
		else
		{
			_sections.Add(newSection);
		}

		return newSection;
    }

	public List<GameConfigSectionDescriptor> GetSections()
    {
        return _sections;
    }
}