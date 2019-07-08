using System;
namespace Comando
{
	[System.ComponentModel.ToolboxItem(true)]
	public partial class WidgetCommandList : Gtk.Bin
    {
        public WidgetCommandList()
		{
			this.Build();
        }

        public Gtk.Label GetLabel()
        {
            return commandsText;
        }
    }
}
