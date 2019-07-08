using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Diagnostics;
using System.IO;
using System.Web;


class GameConfigDescriptorLoader
{
	private GameConfigDB _gameConfigDB = null;
	private GameConfigSectionDescriptor _currentGameConfigSectionDescriptor = null;
	private GameConfigButtonDescriptor _currentGameConfigButtonDescriptor = null;
    private string _descriptorFile = string.Empty;

	public GameConfigDescriptorLoader(string file)
    {
        _descriptorFile = file;
    }

	public GameConfigDB GetConfig()
    {
        return _gameConfigDB;
    }

	public int GetSecondsFrom1970()
	{
		DateTime dt = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Local);//from 1970/1/1 00:00:00 to now
		DateTime dtNow = DateTime.Now;
		TimeSpan result = dtNow.Subtract(dt);
		int seconds = Convert.ToInt32(result.TotalSeconds);
		return seconds;
	}

    public void CreateNew(string name)
    {
        _gameConfigDB = new GameConfigDB();
        _gameConfigDB.SetName(name);
		_gameConfigDB.SetCreationDate(GetSecondsFrom1970());
    }

    public void DeleteConfig()
    {
        File.Delete(_descriptorFile);
        _gameConfigDB = null;
        _descriptorFile = string.Empty;
    }

    public FileOperationResult Load()
    {
        try
        {
            XmlReader reader = XmlReader.Create(_descriptorFile);
            while (reader.Read())
            {
                // Only detect start elements.
                if (reader.IsStartElement())
                {
                    // Get element name and switch on it.
                    switch (reader.Name)
                    {
                        case "commands":
                            {
                                _gameConfigDB = new GameConfigDB();

                                string attribute = reader["name"];
                                Config.AssertResource(attribute);
                                _gameConfigDB.SetName(attribute);

								attribute = reader["creationDate"];
                                Config.AssertResource(attribute);
								_gameConfigDB.SetCreationDate(Int32.Parse(attribute));
                            }

                            break;

                        case "section":
						    {
							    if (_currentGameConfigSectionDescriptor != null)
							    {
								    _gameConfigDB.AddSection(_currentGameConfigSectionDescriptor);
								    _currentGameConfigSectionDescriptor = null;
							    }
	                            _currentGameConfigSectionDescriptor = new GameConfigSectionDescriptor();
							    string attribute = reader["tittle"];
							    Config.AssertResource(attribute);
	                            _currentGameConfigSectionDescriptor._tittle = Utils.DecodeHTML(attribute);
						    }
                            break;

                        case "command":
						    {
	                            _currentGameConfigButtonDescriptor = new GameConfigButtonDescriptor();
							    string attribute = reader["type"];
							    Config.AssertResource(attribute);

							    GameConfigButtonDescriptor.Etype type = Utils.static_cast<GameConfigButtonDescriptor.Etype>(Int32.Parse(attribute));
							    _currentGameConfigButtonDescriptor._type = type;

	                            attribute = reader["tittle"];
	                            Config.AssertResource(attribute);
	                            _currentGameConfigButtonDescriptor._tittle = Utils.DecodeHTML(attribute);

							    if (type == GameConfigButtonDescriptor.Etype.MultiCommand)
							    {
								    _currentGameConfigButtonDescriptor._commandList = new List<GameConfigCommandDescriptor>();
							    }
							    else
							    {
								    attribute = reader["command"];
								    Config.AssertResource(attribute);
								    _currentGameConfigButtonDescriptor._command = Utils.DecodeHTML(attribute);
							    }

							    if (  type == GameConfigButtonDescriptor.Etype.FixedArgument
							       || type == GameConfigButtonDescriptor.Etype.ExposedArgument)
							    {
		                            attribute = reader["arguments"];
		                            Config.AssertResource(attribute);
									_currentGameConfigButtonDescriptor._arguments = Utils.DecodeHTML(attribute);
							    }

							    _currentGameConfigSectionDescriptor._buttons.Add(_currentGameConfigButtonDescriptor);
						    }
                            break;

                        case "command_sequence":
						    {
							    GameConfigCommandDescriptor commandDescriptor= new GameConfigCommandDescriptor();
	                            string attribute = reader["command"];
	                            Config.AssertResource(attribute);
	                            commandDescriptor._command = Utils.DecodeHTML(attribute);

	                            attribute = reader["arguments"];
	                            Config.AssertResource(attribute);
								commandDescriptor._arguments = Utils.DecodeHTML(attribute);

							    _currentGameConfigButtonDescriptor._commandList.Add(commandDescriptor);
						    }
                            break;
                    }
                }
            }

		    if (_currentGameConfigSectionDescriptor != null)
		    {
			    _gameConfigDB.AddSection(_currentGameConfigSectionDescriptor);
			    _currentGameConfigSectionDescriptor = null;
		    }
		    reader.Close();

            return new FileOperationResult(true);
        }
        catch (System.Exception ex)
        {
            return new FileOperationResult(false, ex.Message);
        }
    }

	public FileOperationResult Export(string fileName)
	{
        return Save(fileName);
	}

	public FileOperationResult Save()
	{
        return Save(_descriptorFile);
	}


    private FileOperationResult Save(string fileName)
    {
        try
        {
            XmlWriter writer = XmlWriter.Create(fileName);
			writer.WriteRaw("\n<commands name=\"" + _gameConfigDB.GetName() + "\" creationDate=\"" + _gameConfigDB.GetCreationDate() + "\">\n");

            foreach (GameConfigSectionDescriptor section in _gameConfigDB.GetSections())
            {
                writer.WriteRaw("    <section ");
				writer.WriteRaw("tittle=\"" + Utils.EncodeHTML(section._tittle) + "\">\n");

                foreach (GameConfigButtonDescriptor button in section._buttons)
                {
                    writer.WriteRaw("        <command ");
                    writer.WriteRaw("type=\"" + (int)button._type + "\" ");
					writer.WriteRaw("tittle=\"" + Utils.EncodeHTML(button._tittle) + "\" ");

                    if (button._type != GameConfigButtonDescriptor.Etype.MultiCommand)
                    {
						writer.WriteRaw("command=\"" + Utils.EncodeHTML(button._command) + "\" ");
                    }

                    if (button._type == GameConfigButtonDescriptor.Etype.FixedArgument
					    || button._type == GameConfigButtonDescriptor.Etype.ExposedArgument)
                    {
						writer.WriteRaw("arguments=\"" + Utils.EncodeHTML(button._arguments) + "\" ");
                    }

                    if (button._type == GameConfigButtonDescriptor.Etype.MultiCommand)
                    {
                        writer.WriteRaw(">\n");
                        foreach (GameConfigCommandDescriptor commandDescriptor in button._commandList)
                        {
                            writer.WriteRaw("            <command_sequence ");
							writer.WriteRaw("command=\"" + Utils.EncodeHTML(commandDescriptor._command) + "\" ");
                            writer.WriteRaw("arguments=\"" + Utils.EncodeHTML(commandDescriptor._arguments) + "\" ");
                            writer.WriteRaw("/>\n");
                        }
                        writer.WriteRaw("        </command>\n");
                    }
                    else
                    {
                        writer.WriteRaw("/>\n");
                    }

                }

                writer.WriteRaw("    </section>\n");
            }

            writer.WriteRaw("</commands>\n");
            writer.Close();

            return new FileOperationResult(true);
        }
        catch (System.Exception ex)
        {
            return new FileOperationResult(false, ex.Message);
        }
    }
}