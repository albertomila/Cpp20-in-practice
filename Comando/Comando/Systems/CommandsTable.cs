using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Comando
{
    public class CommandsTable
    {
        Dictionary<string, string> _commandTable = null;

        public CommandsTable()
        {
            _commandTable = new Dictionary<string, string>();
        }

        public void AddCommand(string command, string description)
        {
            if(!_commandTable.ContainsKey(command))
            {
                _commandTable.Add(command, description);
            }
        }

        public Dictionary<string, string> GetCommands()
        {
            return _commandTable;
        }
    }
}
