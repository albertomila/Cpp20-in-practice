using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class ApplicationConfig
{
	public int _port = 0;
    public string _service = string.Empty;
    public string _sendCommand = string.Empty;
    public string _sendConsoleCommand = string.Empty;
    public string _defaultHost = string.Empty;
    public List<string> _hostTargets = null;
}
