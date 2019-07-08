using System;
using System.Collections.Generic;
using System.Drawing;
using Gtk;
namespace Comando
{
	[System.ComponentModel.ToolboxItem(true)]
	public partial class WidgetConsole : Gtk.Bin
	{
		private List<string> _commmandsHistory = null;
        private int _selectedCommandHistory = -1;
        private bool _hasChangedHistoryCommand = false;
        private List<KeyValuePair<string, string>> _commandsSorted = null;
		private WindowCommandsTooltip _windowCommandList = null;

        public WidgetConsole()
		{
            this.Build();
            Pango.FontDescription fontDescription = Pango.FontDescription.FromString(UIUtils.CONSOLE_FONT);
            _textfieldOutput.SizeAllocated += new SizeAllocatedHandler(ScrollToBottomOnRender);
            _textfieldOutput.ModifyFont(fontDescription);
            _textfieldOutput.ModifyBase(StateType.Normal, new Gdk.Color(0x00,0x00,0x00));
			_textfieldOutput.ModifyText(StateType.Normal, new Gdk.Color(0x00, 0xFF, 0x00));

            _inputGenericCommand.ModifyBase(StateType.Normal, new Gdk.Color(0x00, 0x00, 0x00));
            _inputGenericCommand.ModifyText(StateType.Normal, new Gdk.Color(0x00, 0xFF, 0x00));
            _inputGenericCommand.ModifyFont(fontDescription);
            _inputGenericCommand.KeyPressEvent += InputGenericCommand_KeyPressEvent;
            _inputGenericCommand.FocusOutEvent += InputGenericCommand_FocusOutEvent;
            _inputGenericCommand.Changed += _inputGenericCommand_Changed;

            _commmandsHistory = new List<string>();
            _commandsSorted = new List<KeyValuePair<string, string>>();

			_windowCommandList = new WindowCommandsTooltip();
			_windowCommandList.SetFrameDimensions(0, 0, 0, 0);
			_windowCommandList.Show();
            HideCommandTooltip();

            Messenger.AddListener("OnCommandsSync", OnCommandsSync);
        }

        private void _inputGenericCommand_Changed(object sender, EventArgs e)
        {
            _windowCommandList.GetLabel().Text = "";
            List<KeyValuePair<string, string>> commands = GetCommandsByInput(_inputGenericCommand.Text, false);

			if (commands.Count == 0)
			{
				commands = GetCommandsByInput(_inputGenericCommand.Text, true);

				if (commands.Count == 0)
				{
                    HideCommandTooltip();
                    return;
				}
			}

            foreach (KeyValuePair<string, string> commandPair in commands)
            {
                if(commands.Count < 4)
                {
                    _windowCommandList.GetLabel().Text += commandPair.Key + ". " + commandPair.Value + "\n";
                }
                else
                {
                    _windowCommandList.GetLabel().Text += commandPair.Key + "\n";
                }
            }

            Point tooltipPos = MainApp.GetInstance().GetWindowPos();
            tooltipPos.X += 865;
            tooltipPos.Y += 780;

            _windowCommandList.Move(tooltipPos.X, tooltipPos.Y);
            _windowCommandList.KeepAbove = true;
        }

        ~WidgetConsole()
        {
            Messenger.RemoveListener("OnCommandsSync", OnCommandsSync);
        }

        private void OnCommandsSync()
        {
            Dictionary<string, string> commands = MainApp.GetInstance().GetCommands().GetCommands();
            foreach (KeyValuePair<string, string> keyCommand in commands)
            {
                _commandsSorted.Add(keyCommand);
            }
            _commandsSorted.Sort((keyPair1, keyPair2) => string.Compare(keyPair1.Key, keyPair2.Key));
        }

        public List<KeyValuePair<string, string>> GetCommandsByInput(string inputText, bool checkContains)
        {
            List<KeyValuePair<string, string>> inputCommands = new List<KeyValuePair<string, string>>();
            foreach (KeyValuePair<string, string> keyCommand in _commandsSorted)
            {
                if(keyCommand.Key.Length < inputText.Length)
                {
                    continue;
                }

				if (checkContains)
				{
					if (keyCommand.Key.Contains(inputText))
	                {
	                    inputCommands.Add(keyCommand);
	                }
				}
				else
				{
	                string commandSubstring = keyCommand.Key.Substring(0, inputText.Length);
	                if (commandSubstring == inputText)
	                {
	                    inputCommands.Add(keyCommand);
	                }
				}
            }
            return inputCommands;
        }

        private void InputGenericCommand_FocusOutEvent(object o, FocusOutEventArgs args)
        {
            if(_hasChangedHistoryCommand)
            {
                SetCursorLastPos();
                _hasChangedHistoryCommand = false;
            }
        }


        [GLib.ConnectBefore]
		void InputGenericCommand_KeyPressEvent(object o, KeyPressEventArgs args)
		{
			Gdk.Key pressedKey = args.Event.Key;
			if (pressedKey == Gdk.Key.Return)
			{
				MainApp.GetInstance().ExecuteConsoleCommand(_inputGenericCommand.Text);
				_commmandsHistory.Add(_inputGenericCommand.Text);
                _selectedCommandHistory = -1;
                UpdateHistoryCommand();
            }
			else if (pressedKey == Gdk.Key.Up)
			{
                if (_commmandsHistory.Count > 0)
				{
					if (_selectedCommandHistory == -1)
					{
						_selectedCommandHistory = (_commmandsHistory.Count - 1);
                        UpdateHistoryCommand();
                    }
                    else if(_selectedCommandHistory >= 0)
					{
                        if(_selectedCommandHistory > 0)
                        {
                            --_selectedCommandHistory;
                        }
                        UpdateHistoryCommand();
                    }
                }
			}
			else if (pressedKey == Gdk.Key.Down)
			{
				if (_commmandsHistory.Count > 0)
                {
                    if (_selectedCommandHistory == -1)
                    {
                        return;
                    }
                    else if (_selectedCommandHistory < _commmandsHistory.Count - 1)
					{
						++_selectedCommandHistory;
						UpdateHistoryCommand();
                    }
                    else if(_selectedCommandHistory >= _commmandsHistory.Count - 1)
                    {
                        _selectedCommandHistory = -1;
                        UpdateHistoryCommand();
                    }
				}
            }
            else if (pressedKey == Gdk.Key.Tab)
            {

				List<KeyValuePair<string, string>> commands = GetCommandsByInput(_inputGenericCommand.Text, false);
                if (commands.Count == 0)
                {
					commands = GetCommandsByInput(_inputGenericCommand.Text, true);
                }
                if (commands.Count > 0)
                {
                    _inputGenericCommand.Text = commands[0].Key;
                }

                SetCursorLastPos();
                _hasChangedHistoryCommand = true;
            }
        }

		private void UpdateHistoryCommand()
        {
            if(_selectedCommandHistory == -1 )
            {
                _inputGenericCommand.Text = string.Empty;
            }
            else
            {
                _inputGenericCommand.Text = _commmandsHistory[_selectedCommandHistory];
            }
            SetCursorLastPos();
            _hasChangedHistoryCommand = true;
        }

        private void SetCursorLastPos()
        {
            _inputGenericCommand.GrabFocus();
            if (_inputGenericCommand.Text.Length > 0)
            {
                _inputGenericCommand.Position = _inputGenericCommand.Text.Length;
            }
            else
            {
                _inputGenericCommand.Position = 0;
            }
        }

        protected void OnSendGenericCommandButtonPress(object sender, EventArgs e)
		{
			MainApp.GetInstance().ExecuteConsoleCommand(_inputGenericCommand.Text);
			_commmandsHistory.Add(_inputGenericCommand.Text);
            _selectedCommandHistory = -1;
        }

		public void WriteOutput(string message)
		{
			TextBuffer output = _textfieldOutput.Buffer;
			output.Text += message + "\n";

			if (output.Text.Length > 2000)
			{
				output.Text = output.Text.Substring(output.Text.Length - 2000);
			}

			_textfieldOutput.ScrollToIter(_textfieldOutput.Buffer.EndIter, 0, true, 0, 0);
		}

		public void ScrollToBottomOnRender(object sender, Gtk.SizeAllocatedArgs e)
		{
			_textfieldOutput.ScrollToIter(_textfieldOutput.Buffer.EndIter, 0, true, 0, 0);
		}

        private void HideCommandTooltip()
        {
            _windowCommandList.Move(10000, 10000);
        }
	}
}
