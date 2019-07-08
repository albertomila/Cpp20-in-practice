using System;
using System.Drawing;
using Gtk;

namespace Comando
{
	public class UICommandExposedArgument : UICommandElement
	{
		protected Point _buttonSize = new Point(100, 40);
		protected Point _inputSize = new Point(60, 40);
		private Gtk.Button _button = null;
		private Gtk.Entry _inputArguments = null;

        public UICommandExposedArgument(Gtk.Fixed parent, GameConfigButtonDescriptor commandDescriptor)
		    : base(parent, commandDescriptor)
		{
        }

        public override void Init()
        {
            Gtk.Label label = new Gtk.Label();
            Pango.FontDescription fontDescription = Pango.FontDescription.FromString(UIUtils.BUTTON_FONT);
            label.ModifyFont(fontDescription);
            label.ShowAll();

            _button = new Gtk.Button(label);
			_button.CanFocus = true;
			_button.UseUnderline = true;
			_button.TooltipText = GetCommandDescriptor()._command;
			_button.WidthRequest = _buttonSize.X;
			_button.HeightRequest = _buttonSize.Y;
			_button.Show();
            _button.ButtonPressEvent += OnButtonPressEvent;
            _button.ButtonReleaseEvent += OnButtonReleaseEvent;

            GetParent().Add(_button);

            _inputArguments = new Gtk.Entry();
			_inputArguments.CanFocus = true;
			_inputArguments.Text = GetCommandDescriptor()._arguments;
			_inputArguments.Name = "_inputArguments";
			_inputArguments.IsEditable = true;
			_inputArguments.InvisibleChar = '●';
			_inputArguments.Show();
			_inputArguments.WidthRequest = _inputSize.X;
			_inputArguments.HeightRequest = _inputSize.Y;
			_inputArguments.TextInserted += OnArgumentsTextInserted;
            GetParent().Add(_inputArguments);

			Refresh();
		}

		void OnArgumentsTextInserted (object o, TextInsertedArgs args)
		{
            GetCommandDescriptor()._arguments = _inputArguments.Text;
		}

		public override void Uninit()
		{
            GetParent().Remove(_button);
            GetParent().Remove(_inputArguments);
        }

		protected override void DoSetLocation()
		{
			UIUtils.SetWidgetPosition(GetParent(), _button, GetLocation());

			Point inputPos = GetLocation();
			inputPos.X += _buttonSize.X;
			UIUtils.SetWidgetPosition(GetParent(), _inputArguments, inputPos);
		}

		public override void PreOnButtonPressEvent()
		{
            GetCommandDescriptor()._arguments = _inputArguments.Text;
		}

		public override void Refresh()
		{
			Gtk.Label label = (Gtk.Label)_button.Child;
			SetLabelText(label);
		}
	}
}
