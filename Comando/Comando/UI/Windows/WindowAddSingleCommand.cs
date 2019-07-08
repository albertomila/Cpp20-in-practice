using System;
namespace Comando
{
	public partial class WindowAddSingleCommand : Gtk.Window
    {
        private UITabPage _parent = null;
        private int _sectionIndex = 0;
		private GameConfigButtonDescriptor _editCommandDescriptor = null;
		private UICommandElement _editUICommandElement = null;

		public WindowAddSingleCommand(UITabPage parent, int sectionIndex) :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
            _parent = parent;
            _sectionIndex = sectionIndex;

			RefreshCommandPickerVisibility();
		}

		public WindowAddSingleCommand(UITabPage parent, UICommandElement uiCommandElement, GameConfigButtonDescriptor commandDescriptor) :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
            _parent = parent;
            _editCommandDescriptor = commandDescriptor;
			_editUICommandElement = uiCommandElement;
			_inputTittle.Text = _editCommandDescriptor._tittle;
			_inputCommand.Text = _editCommandDescriptor._command;
			_inputArguments.Text = _editCommandDescriptor._arguments;

			RefreshCommandPickerVisibility();
		}

		private void RefreshCommandPickerVisibility()
		{
			CommandsTable commandTable = MainApp.GetInstance().GetCommands();
			_commandPickerButton.Visible = commandTable.GetCommands().Count > 0;
		}

		protected void OnAddNewCommandButtonClick(object sender, EventArgs e)
		{
			if (_editCommandDescriptor != null)
			{
                _parent.OnEditSingleCommandButtonPress
				        ( _editUICommandElement
				        , _editCommandDescriptor
				        , _inputTittle.Text
				        , _inputCommand.Text
				        , _inputArguments.Text);
			}
			else
			{
                _parent.OnAddNewCommandButtonPress(_inputTittle.Text, _inputCommand.Text, _inputArguments.Text, _sectionIndex);
			}
		}

		protected void OnPickCommandButtonClick(object sender, EventArgs e)
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
