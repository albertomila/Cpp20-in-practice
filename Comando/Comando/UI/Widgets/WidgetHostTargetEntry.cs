using System;
namespace Comando
{
	[System.ComponentModel.ToolboxItem(true)]
	public partial class WidgetHostTargetEntry : Gtk.Bin
	{
		public delegate void OnEntryButtonEvent(WidgetHostTargetEntry sender);
		public event OnEntryButtonEvent OnEntryDeletedEvent;
		public event OnEntryButtonEvent OnEntryUpdateConnectionEvent;

		private HostStatus _host = null;


		public WidgetHostTargetEntry(HostStatus host)
		{
            this.Build();
			_host = host;
			_inputHostTarget.Text = host._host;
			RefreshVisuals();

			_inputHostTarget.TextInserted += OnTextInsertedEvent;
		}

		private void OnTextInsertedEvent(object o, Gtk.TextInsertedArgs args)
		{
			_host._host = _inputHostTarget.Text.Trim();
			_inputHostTarget.Text = _host._host;
		}
		 
		public HostStatus GetHost()
		{
			return _host;
		}

		public string GetHostTarget()
		{
			return _inputHostTarget.Text;
		}

		[GLib.ConnectBefore]
		protected void OnRemoveHostTargetButtonPress(object sender, EventArgs e)
		{
			OnEntryDeletedEvent?.Invoke(this);
		}

		protected void OnUpdateConnectionButtonPress(object sender, EventArgs e)
		{
            OnEntryUpdateConnectionEvent?.Invoke(this);
		}

		public void RefreshVisuals()
		{
			switch(_host._connectionStatus)
			{
				case HostStatus.EStatus.Disconnected:
					_labelConnectionStatus.ModifyFg(Gtk.StateType.Normal, new Gdk.Color(0xFF,0x00,0x00));
					_labelConnectionStatus.Text = "Disconnected";
					_inputHostTarget.ModifyBase(Gtk.StateType.Normal, new Gdk.Color(0xFF,0x66,0x66));
					break;
				case HostStatus.EStatus.Connecting:
					_labelConnectionStatus.ModifyFg(Gtk.StateType.Normal, new Gdk.Color(0x00,0x00,0xFF));
					_labelConnectionStatus.Text = "Connecting";
					_inputHostTarget.ModifyBase(Gtk.StateType.Normal, new Gdk.Color(0x72,0xC2,0xFF));
					break;
				case HostStatus.EStatus.Connected:
					_labelConnectionStatus.ModifyFg(Gtk.StateType.Normal, new Gdk.Color(0x00,0x90,0x00));
					_labelConnectionStatus.Text = "Connected";
					_inputHostTarget.ModifyBase(Gtk.StateType.Normal, new Gdk.Color(0x76,0xE0,0x76));
					break;
			}
		}
	}
}
