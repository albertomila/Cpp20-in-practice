using System;
namespace Comando
{
	public partial class WindowAddTab : Gtk.Window
	{
		public delegate void OnAcceptButtonPressDelegate(string tabName);
		public event OnAcceptButtonPressDelegate OnAcceptButtonPressEvent = null;
		public WindowAddTab() :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
		}

		protected void OnAcceptButtonClick(object sender, EventArgs e)
		{
			OnAcceptButtonPressEvent?.Invoke(_inputName.Text);
		}
	}
}
