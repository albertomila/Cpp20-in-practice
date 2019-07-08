using System;
namespace Comando
{
	public partial class WindowConfiguration : Gtk.Window
	{
		public WindowConfiguration() :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
		}

		public void SetPort(string port)
		{
			_inputPort.Text = port;
		}

		public string GetPort()
		{
			return _inputPort.Text;
		}

		public void SetService(string service)
		{
			_inputService.Text = service;
		}

		public string GetService()
		{
			return _inputService.Text;
		}

		public void SetTarget(string target)
		{
			_inputTarget.Text = target;
		}

		public string GetTarget()
		{
			return _inputTarget.Text;	
		}

		public void SetTargetCommand(string target)
		{
			_inputTargetCommand.Text = target;
		}

		public string GetTargetCommand()
		{
			return _inputTargetCommand.Text;	
		}

		public void SetDefaultIP(string target)
		{
			_defaultIP.Text = target;
		}

		public string GetDefaultIP()
		{
			return _defaultIP.Text;	
		}

		protected void OnWindowAcceptButtonPressed(object sender, EventArgs e)
		{
			MainApp.GetInstance().OnWindowAcceptButtonPressed(sender, e);
		}
	}
}
