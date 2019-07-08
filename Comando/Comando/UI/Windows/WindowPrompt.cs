using System;
namespace Comando
{
	public partial class WindowPrompt : Gtk.Window
	{
		public delegate void OnAcceptButtonPressDelegate();
		public delegate void OnCancelButtonPressDelegate();

        public event OnAcceptButtonPressDelegate OnAcceptEvent;
		public event OnCancelButtonPressDelegate OnCancelEvent;
		private object _data = null;


        public WindowPrompt(string description)
            : base(Gtk.WindowType.Toplevel)
        {
            this.Build();
            _description.Text = description;
        }

		public void SetCancelVisible(bool visible)
		{
			if (visible)
			{
				_buttonCancel.Show();
			}
			else
			{
				_buttonCancel.Hide();
			}
		}
        
        public void SetExternalData(object data)
        {
            _data = data;
        }

        public object GetExternalData()
		{
			return _data;
		}

		[GLib.ConnectBefore]
		protected void OnAcceptButtonPress(object o, Gtk.ButtonReleaseEventArgs args)
		{
            OnAcceptEvent?.Invoke();
		}

		[GLib.ConnectBefore]
		protected void OnCancelButtonPress(object o, Gtk.ButtonReleaseEventArgs args)
		{
            OnCancelEvent?.Invoke();
		}
	}
}
