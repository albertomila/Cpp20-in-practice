using System;
using System.Collections.Generic;
using System.Drawing;
using System.Diagnostics;

namespace Comando
{
	public partial class WindowHostTargets : Gtk.Window
	{
		private List<WidgetHostTargetEntry> _hostTargets = null;
		private int _incrementPosY = 30;

		public WindowHostTargets(List<HostStatus> hostTargets) :
				base(Gtk.WindowType.Toplevel)
		{
			_hostTargets = new List<WidgetHostTargetEntry>();

			this.Build();

			foreach (HostStatus hostTarget in hostTargets)
			{
	            AddHostEntry(hostTarget);
			}
            RefreshVisuals();
		}

		private void AddHostEntry(HostStatus host)
		{
			WidgetHostTargetEntry hostTargetWidget = new WidgetHostTargetEntry(host);
			hostTargetWidget.OnEntryDeletedEvent += OnEntryDeleted;
			hostTargetWidget.OnEntryUpdateConnectionEvent += OnEntryUpdateConnectionEvent;
			hostTargetWidget.Show();
			_hostTargets.Add(hostTargetWidget);
			_hostTargetsCanvas.Add(hostTargetWidget);
			RefreshVisuals();
		}

		private void AddNewHostEntry()
		{
			string defaultHost = MainApp.GetInstance().GetConfig().GetApplicationConfig()._defaultHost;
			HostStatus newHost = MainApp.GetInstance().GetHostsController().AddHost(defaultHost);
			AddHostEntry(newHost);
		}

		[GLib.ConnectBefore]
		protected void OnAddHostButtonPress(object o, Gtk.ButtonReleaseEventArgs args)
		{
            AddNewHostEntry();
		}

		private void OnEntryDeleted(WidgetHostTargetEntry sender)
		{
			_hostTargets.Remove(sender);
			_hostTargetsCanvas.Remove(sender);
			MainApp.GetInstance().GetHostsController().RemoveHost(sender.GetHost());
			RefreshVisuals();
		}

		private void OnEntryUpdateConnectionEvent(WidgetHostTargetEntry sender)
		{
			MainApp.GetInstance().GetHostsController().TryConnectHost(sender.GetHost());
		}

		private WidgetHostTargetEntry GetWidgetHostEntry(HostStatus host)
		{
			foreach (WidgetHostTargetEntry widgetHost in _hostTargets)
			{
				if (widgetHost.GetHost() == host)
				{
					return widgetHost;
				}
			}

			Debug.Assert(false, "Widget host entry not found!");
			return null;
		}

		public void RefreshVisuals()
		{
			Point _nextPosition = new Point(0, 0);
			
			foreach (WidgetHostTargetEntry hostTargetWidget in _hostTargets)
			{
				UIUtils.SetWidgetPosition(_hostTargetsCanvas, hostTargetWidget, _nextPosition);
				_nextPosition.Y += _incrementPosY;
				hostTargetWidget.RefreshVisuals();
			}

			UIUtils.SetWidgetPosition(_hostTargetsCanvas, _buttonAddhostEntry, _nextPosition);
			_hostTargetsCanvas.HeightRequest = _nextPosition.Y + 50;
		}

		[GLib.ConnectBefore]
		protected void OnAddHostTargetsButtonPress(object o, Gtk.ButtonReleaseEventArgs args)
		{
			List<string> hostTargets = new List<string>();

			foreach (WidgetHostTargetEntry hostTargetWidget in _hostTargets)
			{
				hostTargets.Add(hostTargetWidget.GetHostTarget());
			}

			MainApp.GetInstance().OnAddHostTargetsButtonPress(hostTargets);
		}
	}
}
