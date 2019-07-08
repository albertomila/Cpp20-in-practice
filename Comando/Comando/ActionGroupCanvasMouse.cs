using System;
namespace Comando
{
	public partial class ActionGroupCanvasMouse : Gtk.ActionGroup
	{
		public ActionGroupCanvasMouse() :
				base("Comando.ActionGroupCanvasMouse")
		{
			this.Build();
		}
	}
}
