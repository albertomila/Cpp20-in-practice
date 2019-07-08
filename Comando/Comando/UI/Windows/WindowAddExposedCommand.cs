using System;
namespace Comando
{
	public partial class WindowAddExposedCommand : Gtk.Window
	{
        private UITabPage _parent = null;
        private int _sectionIndex = 0;
		private GameConfigButtonDescriptor _editCommandDescriptor = null;
		private UICommandElement _editUICommandElement = null;
		public WindowAddExposedCommand(UITabPage parent, int sectionIndex) :
				base(Gtk.WindowType.Toplevel)
		{
            this.Build();
            _parent = parent;
            _sectionIndex = sectionIndex;
			RefreshCommandPickerVisibility();
		}

		public WindowAddExposedCommand(UITabPage parent, UICommandElement uiCommandElement, GameConfigButtonDescriptor commandDescriptor) :
				base(Gtk.WindowType.Toplevel)
		{
			this.Build();
            _parent = parent;
            _editCommandDescriptor = commandDescriptor;
			_editUICommandElement = uiCommandElement;
			_inputTittle.Text = _editCommandDescriptor._tittle;
			_inputCommand.Text = _editCommandDescriptor._command;
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
                _parent.OnEditExposedCommandButtonPress
				        ( _editUICommandElement
				        , _editCommandDescriptor
				        , _inputTittle.Text
				        , _inputCommand.Text
				        , _editCommandDescriptor._arguments);
			}
			else
			{
                _parent.OnAddNewCommandButtonPress(_inputTittle.Text, _inputCommand.Text, _sectionIndex);
			}
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
