using System;
using System.Collections.Generic;
using System.Drawing;

namespace Comando
{
	public partial class WindowAddSequenceCommand : Gtk.Window
    {
        private UITabPage _parent = null;
        private int _sectionIndex = 0;
		private List<WidgetSequenceCommandEntry> _commandList = null;
		private GameConfigButtonDescriptor _editCommandDescriptor = null;
		private UICommandElement _editUICommandElement = null;

		public WindowAddSequenceCommand(UITabPage parent, int sectionIndex) :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
            _parent = parent;
            _sectionIndex = sectionIndex;
			_commandList = new List<WidgetSequenceCommandEntry>();

           	AddNewCommandEntry();
		}

		public WindowAddSequenceCommand(UITabPage parent, UICommandElement uiCommandElement, GameConfigButtonDescriptor commandDescriptor) :
				base(Gtk.WindowType.Toplevel)
		{
            this.Build();
            _parent = parent;
            _commandList = new List<WidgetSequenceCommandEntry>();
			_editCommandDescriptor = commandDescriptor;
			_editUICommandElement = uiCommandElement;

			_inputTitle.Text = _editCommandDescriptor._tittle;
			foreach (GameConfigCommandDescriptor command in commandDescriptor._commandList)
			{
				AddCommandEntry(command);
			}
		}

		private void AddCommandEntry(GameConfigCommandDescriptor command)
		{
			WidgetSequenceCommandEntry commandSequenceWidget = new WidgetSequenceCommandEntry(command);
			DoAddCommandEntry(commandSequenceWidget);
		}

		private void AddNewCommandEntry()
		{
			WidgetSequenceCommandEntry commandSequenceWidget = new WidgetSequenceCommandEntry();
			DoAddCommandEntry(commandSequenceWidget);
		}

		private void DoAddCommandEntry(WidgetSequenceCommandEntry commandSequenceWidget)
		{
			commandSequenceWidget.OnEntryDeletedEvent += OnEntryDeletedEvent;
			commandSequenceWidget.Show();
			_commandList.Add(commandSequenceWidget);
			_inputContainer.Add(commandSequenceWidget);
			UpdateVisualsEntries();
		}

		private void OnEntryDeletedEvent(WidgetSequenceCommandEntry sender)
		{
			_commandList.Remove(sender);
			_inputContainer.Remove(sender);
			UpdateVisualsEntries();
		}

		private void UpdateVisualsEntries()
		{
			Point _nextPosition = new Point(0, 0);
			int _incrementPosY = 30;

			foreach (WidgetSequenceCommandEntry commandSequence in _commandList)
			{
				UIUtils.SetWidgetPosition(_inputContainer, commandSequence, _nextPosition);
				_nextPosition.Y += _incrementPosY;
			}

			UIUtils.SetWidgetPosition(_inputContainer, _buttonAddEntry, _nextPosition);
			_inputContainer.HeightRequest = _nextPosition.Y + 50;
		}

		[GLib.ConnectBefore]
		protected void OnAddEntryButtonPress(object o, EventArgs e)
		{
            AddNewCommandEntry();
		}

		string GetTitle()
		{
			return _inputTitle.Text;
		}

		List<KeyValuePair<string, string>> GetCommandList()
		{
			List<KeyValuePair<string, string>> commandList = new List<KeyValuePair<string, string>>();
			foreach (WidgetSequenceCommandEntry widgetCommand in _commandList)
			{
				commandList.Add(
					new KeyValuePair<string, string>(widgetCommand.GetCommand(), widgetCommand.GetArguments())
				);
			}
			return commandList;
		}

		[GLib.ConnectBefore]
		protected void OnAddNewSequenceCommandButtonClick(object sender, EventArgs e)
		{
			if (_editCommandDescriptor != null)
			{
                _parent.OnEditSequenceCommandButtonPress(_editUICommandElement, _editCommandDescriptor, GetTitle(), GetCommandList());
			}
			else
			{
                _parent.OnAddNewSequenceCommandButtonClick(GetTitle(), GetCommandList(), _sectionIndex);
			}
		}
	}
}
