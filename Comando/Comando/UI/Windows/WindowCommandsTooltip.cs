using System;
namespace Comando
{
	public partial class WindowCommandsTooltip : Gtk.Window
	{
		public WindowCommandsTooltip() :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
		}
		public Gtk.Label GetLabel()
		{
			return this.CommandText;
		}
	}
}
