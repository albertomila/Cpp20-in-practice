using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

class ApplicationConfigLoader
{
    private ApplicationConfig _applicationConfig;
    private string _descriptorFile = string.Empty;

    public ApplicationConfigLoader()
    {
        _descriptorFile = Config.GetConfigDirectory("application_config.xml");
    }

    public ApplicationConfig GetConfig()
    {
        return _applicationConfig;
    }

    public void Load()
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
                    case "application_config":
						{
							_applicationConfig = new ApplicationConfig();
							_applicationConfig._hostTargets = new List<string>();
							string attribute = reader["port"];
							Config.AssertResource(attribute);
							_applicationConfig._port = int.Parse(attribute);

                            attribute = reader["service"];
                            Config.AssertResource(attribute);
                            _applicationConfig._service = attribute;

                            attribute = reader["sendcommand"];
                            Config.AssertResource(attribute);
							_applicationConfig._sendCommand = attribute;

                            attribute = reader["consolecommand"];
                            Config.AssertResource(attribute);
							_applicationConfig._sendConsoleCommand = attribute;

                            attribute = reader["default_host"];
                            Config.AssertResource(attribute);
							_applicationConfig._defaultHost = attribute;


                        }
                        break;
                    case "host_target":
						{
							string attribute = reader["target"];
							Config.AssertResource(attribute);
							_applicationConfig._hostTargets.Add(attribute);
						}
                        break;
                }
            }
        }
		reader.Close();
    }

    public void Save()
	{
		XmlWriter writer = XmlWriter.Create(_descriptorFile);
		writer.WriteRaw("\n<application_config ");
		writer.WriteRaw("port=\"" + _applicationConfig._port + "\" ");
        writer.WriteRaw("service=\"" + _applicationConfig._service + "\" ");
        writer.WriteRaw("sendcommand=\"" + _applicationConfig._sendCommand + "\" ");
		writer.WriteRaw("consolecommand=\"" + _applicationConfig._sendConsoleCommand + "\" ");
		writer.WriteRaw("default_host=\"" + _applicationConfig._defaultHost + "\">\n");

        writer.WriteRaw("    <host_targets>\n");
		foreach (string hostTarget in _applicationConfig._hostTargets)
		{
			writer.WriteRaw("        <host_target target=\"" + hostTarget + "\" />\n");
		}
		writer.WriteRaw("    </host_targets>\n");

		writer.WriteRaw("</application_config>");
		writer.Close();
    }
}
