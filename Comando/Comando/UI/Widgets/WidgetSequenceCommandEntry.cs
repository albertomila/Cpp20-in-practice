using System;
namespace Comando
{
	[System.ComponentModel.ToolboxItem(true)]
	public partial class WidgetSequenceCommandEntry : Gtk.Bin
	{
		public delegate void OnEntryDeleted(WidgetSequenceCommandEntry sender);
		public event OnEntryDeleted OnEntryDeletedEvent;
		private GameConfigCommandDescriptor _commandDescriptor = null;

		public WidgetSequenceCommandEntry()
		{
            this.Build();

			RefreshCommandPickerVisibility();
		}

		public WidgetSequenceCommandEntry(GameConfigCommandDescriptor commandDescriptor)
		{
            this.Build();
			_commandDescriptor = commandDescriptor;
			_inputCommand.Text = _commandDescriptor._command;
			_inputArguments.Text = _commandDescriptor._arguments;

			RefreshCommandPickerVisibility();
		}

		private void RefreshCommandPickerVisibility()
		{
			CommandsTable commandTable = MainApp.GetInstance().GetCommands();
			_commandPickerButton.Visible = commandTable.GetCommands().Count > 0;
		}

		public string GetCommand()
		{
			return _inputCommand.Text;
		}

		public string GetArguments()
		{
			return _inputArguments.Text;
		}

		public GameConfigCommandDescriptor GetCommandDescriptor()
		{
			return _commandDescriptor;
		}

		protected void OnDeleteEntryButtonClick(object sender, EventArgs e)
		{
            OnEntryDeletedEvent?.Invoke(this);
		}

		public void RefreshData()
		{
			 _commandDescriptor._command = _inputCommand.Text;
			_commandDescriptor._arguments = _inputArguments.Text;
		}

		protected void OnCommandPickerButtonClick(object sender, EventArgs e)
		{
			MainApp.GetInstance().OpenCommandPicker(OnCommandPickedEvent);
		}

		protected void OnCommandPickedEvent(string command)
		{
			_inputCommand.Text = command;
			MainApp.GetInstance().CloseCommandPicker();
		}
	}
}
